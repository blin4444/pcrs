import SocketServer
#import BaseHTTPServer, SimpleHTTPServer
#import ssl
from query import Query
from form import Form

from datetime import datetime
from BaseHTTPServer import BaseHTTPRequestHandler
from StringIO import StringIO

#The HTTPRequest class is taken from Brandon Rhodes
#http://stackoverflow.com/questions/2115410/does-python-have-a-module-for-parsing-http-requests-and-responses
class HTTPRequest(BaseHTTPRequestHandler):
	def __init__(self, request_text):
		self.rfile = StringIO(request_text)
		self.raw_requestline = self.rfile.readline()
		self.error_code = self.error_message = None
		self.parse_request()
	def send_error(self, code, message):
		self.error_code = code
		self.error_message = message

class MyTCPHandler(SocketServer.BaseRequestHandler):
	
	
	def sign_in(self, token, reason_id):
		try:
			user_id = query.validate_token(token)
		
			if user_id == None:
				return "No user with token found"

			query.insert_sign_in(user_id, 1)
			return str(user_id)
		
		except Exception, err:
			print "Unexpected Error: "+str(err)
			return "Unknown Database Error"
	
	def register(self, id, args, sin):
		
		
		section = form.sectionMap[id]
		user_id = query.insert_user_info(form.buildQuery(section), args, sin)
		
		if user_id == None:
			return "Failed to input user into the database"

		token = query.generate_token()
		success = query.insert_user(user_id, token)
		#success = True
		if success:				
			return token 
		return "Failed to input user info"
	
	def list_all(self):
		return "Unimplemented";

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
		return sin.isdigit(); 

	def handle(self):
		self.data = self.request.recv(2048).strip()
		print self.data

		request = HTTPRequest(self.data)	
		reponse_data = ""
		if request.error_code != None:
			response_data = "Request Data Corrupted: "+request.error_message
		elif request.path == "/validate/":
			if 'token' in request.headers:
				token = request.headers["token"]
				if query.validate_token(token) == None:
					response_data = "No user with token found"
				else:	
					response_data = "User exists in the system"
		elif request.path == "/signin/":
			if 'token' in request.headers and 'reason_id' \
			in request.headers:			
				token = request.headers["token"]
				reason_id = request.headers["reason_id"]
				response_data = self.sign_in(token, int(reason_id))
			else:
				response_data = "request must have both token and reason_id in header"
		
		elif request.path == "/register/":
			response_data = ""
			should_register = True
			sectionID = request.headers.get("sectionID", False)
			argumentMap = form.buildArgumentMap()
			arguments = argumentMap[sectionID]
			args = list()
			sin = None
			for argument in arguments:
				if argument != "sin":
					print "Not sin"
					(value, response_data) = self.process_param(response_data, argument, request.headers.get(argument, False))
					if not value:
						should_register = False
					args.append(value)
				else:
					sin = request.headers.get("sin", "0")
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
				response_data = response_data + "\n Will not register the user"
		elif request.path == "/list/":
			response_data = self.list_all()
		else:
			response_data = "unknown request"
		
		self.request.sendall(response_data)

	def insert_registration_option(self, user_id, es_id, ud_id, ga_id, rs_id):
		sql = """INSERT INTO Registration_Option(user_id, es_id, ud_id, ga_id, rs_id, registration_time)
		VALUES(%s, %s, %s, %s, %s, %s)"""
		try:
			self.cur.execute(sql, (user_id, es_id, ud_id, ga_id, rs_id, datetime.now()))
			self.db.commit()
			return True
		except Exception, err:
			print "Unexpected Error when inserting registration option: "+str(err)
			return False 

if __name__ == "__main__":
	HOST, PORT = "localhost", 9999
	query = Query()
	form = Form("client_information_form")
	server = SocketServer.TCPServer((HOST, PORT), MyTCPHandler)
	try:
		server.serve_forever()
	finally:
		query.close()
