import SocketServer
import BaseHTTPServer, SimpleHTTPServer
#import ssl
from query import Query
from form import Form
from xmlgen import options_xml

from datetime import datetime
from BaseHTTPServer import BaseHTTPRequestHandler
from StringIO import StringIO

class CustomHandler(BaseHTTPServer.BaseHTTPRequestHandler):
	def sign_in(self, token, reason_id):
		try:
			user_id = query.validate_token(token)

			if user_id == None:
				return "1 - No user with token found"

			query.insert_sign_in(user_id, 1)
			return str(user_id)

		except Exception, err:
			print "Unexpected Error: "+str(err)
			return "2 - Unknown Database Error"

	def register(self, id, args, sin):
		section = form.sectionMap[id]
		user_id = query.insert_user_info(form.buildQuery(section), args, sin)

		if user_id == None:
			return "3 - Failed to input user into the database"

		token = query.generate_token()
		success = query.insert_user(user_id, token)
		#success = True
		if success:				
			return token 
		return "4 - Failed to input user token"
	
	def options(self):
		options = query.select_registration_options()		
		return options_xml(options)

	def process_param(self, response_data, name, value):
		print "processing "+name+" "+str(value)
		if value and value.strip() != "":
			value = value.strip()
		else:
			response_data = response_data + name+ " is empty.\n"
			value = False
		return (value, response_data)

	def validate_sin(self, sin):		
		sin = "".join(sin.split()) # remove whitespace
		if (len(sin) != 9): return False
		return sin.isdigit()
	
	def do_POST(s):
		return_code = 200;
		response_data = ""
		if s.path == "/validate/":
			if 'token' in s.headers:
				token = s.headers["token"]
				if query.validate_token(token) == None:
					response_data = "No token found when user tries to sign in"
					return_code = 404
				else:	
					response_data = "User exists in the system"
					return_code = 200
		elif s.path == "/signin/":
			if 'token' in s.headers and 'reason_id' \
			in s.headers:			
				token = s.headers["token"]
				reason_id = s.headers["reason_id"]
				response_data = self.sign_in(token, int(reason_id))
			else:
				response_data = "7 - request must have both token and reason_id in header"
				return_code = 404
		
		elif s.path == "/register/":
			response_data = ""
			should_register = True
			sectionID = s.headers.get("sectionID", False)
			argumentMap = form.buildArgumentMap()
			arguments = argumentMap[sectionID]
			args = list()
			sin = None
			for argument in arguments:
				if argument != "sin":
					print "Not sin"
					(value, response_data) = self.process_param(response_data, argument, s.headers.get(argument, False))
					if not value:
						should_register = False
					args.append(value)
				else:
					sin = s.headers.get("sin", "0")
					print "SIN!" + sin
					if not self.validate_sin(sin):
						response_data = response_data + "sin is invalid\n"
						should_register = False;
					else:					
						print "is valid"						
						check_duplicate = query.sin_already_exists(sin)
						if check_duplicate:
							response_data = response_data + "User with this SIN already exists. Here is the related info: "+str(check_duplicate)
							should_register = False;
						else:
							args.append(sin)
			if should_register and sin != None:
				response_data = self.register(sectionID, args, sin)
			else:
				response_data = "8 - "+ response_data + "\n Will not register the user"
		elif s.path == "/options/":
			response_data = s.options()
		else:
			response_data = "9 - unknown request"
			return_code = 404

		s.send_response(return_code, response_data)
		s.send_header("Content-type", "text/html")
		s.end_headers()

if __name__ == "__main__":
	HOST, PORT = "localhost", 9999
	query = Query()
	form = Form("client_information_form")
	server = BaseHTTPServer.HTTPServer((HOST, PORT), CustomHandler)
	try:
		server.serve_forever()
	finally:
		query.close()
	server.server_close()
