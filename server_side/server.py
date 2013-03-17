import SocketServer
#import BaseHTTPServer, SimpleHTTPServer
#import ssl
from query import Query

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

			query.insert_sign_in(user_id, reason_id)
			return str(user_id)
		
		except Exception, err:
			print "Unexpected Error: "+str(err)
			return "Unknown Database Error"
	
	def register(self,last_name, first_name, middle_name, sex, sin, date_of_birth, \
				street_address, city, province, postal_code, phone, alternate_phone, email):		

		check_duplicate = query.sin_already_exists(sin)
		print "check dup"+str(check_duplicate)
		if check_duplicate != None:
			return "User with this SIN already exists. Here is the related info: "+str(check_duplicate)

		user_id = query.insert_user_info(last_name, first_name, \
				middle_name, sex, sin, date_of_birth, \
				street_address, city, province, postal_code, \
				phone, alternate_phone, email)

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
		"""Verifies that the SIN is a nine digit number."""
		sin = "".join(sin.split()) # remove whitespace
		if (len(sin) != 9): return False
		return sin.isdigit();

	def handle(self):
		self.data = self.request.recv(2048).strip()
		print self.data

		request = HTTPRequest(self.data)	
		response_data = "Test Response"
		if request.error_code != None:
			response_data = "Request Data Corrupted: "+request.error_message
		elif request.path == "/validate/":
			if 'token' in request.headers:
				token = request.headers["token"]
				if query.validate_token(token) == None:
					response_data = "No user with token found"
				else:	
					response_data = "User exists in the system"
			else:
				response_data = "request must have token parameter in header"
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
			(last_name, response_data) = self.process_param(response_data, "last name", request.headers.get("last_name", False))
			(first_name, response_data) = self.process_param(response_data, "first name", request.headers.get("first_name", False))
			
			middle_name = request.headers.get("middle_name", "")

			(sex, response_data) = self.process_param(response_data, "sex", request.headers.get("sex", False))
			
			sin = request.headers.get("sin", "0")
			if not self.validate_sin(sin):
				sin = False
				response_data = response_data + "sin is invalid\n"			
			#date_of_birth = datetime.strptime(request.headers.get("date_of_birth", "0000-0-0"), "%Y %m %d")
			date_of_birth = datetime.now()			
			
			(street_address, response_data) = self.process_param(response_data, "street address", request.headers.get("street_address", False))
			(city, response_data) = self.process_param(response_data, "city", request.headers.get("city", False))
			(province, response_data) = self.process_param(response_data, "province", request.headers.get("province", False))
			(postal_code, response_data) = self.process_param(response_data, "postal code", request.headers.get("postal_code", False))
			(phone, response_data) = self.process_param(response_data, "phone", request.headers.get("phone", False))
				
			alternate_phone = request.headers.get("alternate_phone", "-")
			email = request.headers.get("email", "-")

			if last_name and first_name and sex and sin and date_of_birth\
				 and street_address and city and province and postal_code and phone:
				response_data = self.register(last_name, first_name, middle_name, sex, sin, date_of_birth, \
							street_address, city, province, postal_code, phone,\
							alternate_phone, email) 
		elif request.path == "/list/":
			response_data = self.list_all()
		else:
			response_data = "unknown request"
		
		self.request.sendall(response_data)
		
if __name__ == "__main__":
	HOST, PORT = "localhost", 9999
	query = Query()

	server = SocketServer.TCPServer((HOST, PORT), MyTCPHandler)
	try:
		server.serve_forever()
	finally:
		query.close()
