import SocketServer
#import BaseHTTPServer, SimpleHTTPServer
#import ssl
import MySQLdb

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
	
	def validate_token(self, token_string):
		query = """SELECT id FROM User where token=%s"""
		cur.execute(query, (token_string))		
		row = cur.fetchone()
			
		if row == None:
			return None
		return row[0]

	def insert_sign_in(self, user_id, reason_id):
		sql = """INSERT INTO Sign_In (user_id, reason_id, sign_in_time) VALUES (%s, %s, %s)"""
		cur.execute(sql, (user_id, reason_id, datetime.now(),))
		db.commit()

	def sign_in(self, token, reason_id):
		try:
			user_id = self.validate_token(token)
		
			if user_id == None:
				return "No user with token found"

			self.insert_sign_in(user_id, 1)
			return str(user_id)
		
		except Exception, err:
			print "Unexpected Error: "+str(err)
			return "Unknown Database Error"
	
	def generate_token(self):
		#temperory generator until we figure out a better way		
		max_id = 100000		
		try:
			cur.execute("""SELECT MAX(id) FROM User""")		
			max_id = cur.fetchone()
			if max_id != None:
				max_id = max_id[0]
		except:
			max_id = None
		
		if max_id != None:
			return "user"+str(max_id+1)
		else:
			return "user1"
			
	def insert_user(self, user_id, token):
		sql = """INSERT INTO User(id, token) VALUES (%s, %s)"""
		try:		
			cur.execute(sql, (user_id,token))
			return True
		except Exception, err:
			print "Unexpected Error: "+str(err)
			return False
	
	def insert_user_info(self, last_name, first_name, middle_name, sex, sin,\
			street_address, city, province, postal_code, \
			phone, alternate_phone, email):
		sql = """INSERT INTO User_Info(last_name, first_name, middle_name, gender, sin,
			street_address, city, province, postal_code, phone, 
			alternate_phone, email) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)"""
		
		query = """SELECT id FROM User_Info WHERE sin=%s"""
		try:
			cur.execute(sql, (last_name, first_name, middle_name, sex, \
					sin, street_address, city, province, \
					postal_code, phone, alternate_phone, email))
			print "GOT HERE!"
			db.commit()
			cur.execute(query, (sin))

			user_id = cur.fetchone()
			if user_id != None:
				user_id = user_id[0]
			if user_id == None:
				return None
								
			return user_id
		except Exception, err:
			print "Unexpected Error: "+str(err)
			return None

	def register(self,last_name, first_name, middle_name, sex, sin, date_of_birth, \
				street_address, city, province, postal_code, phone, alternate_phone, email):		

		check_duplicate = self.sin_already_exists(sin)
		if check_duplicate:
			return "User with this SIN already exists. Here is the related info: "+str(check_duplicate)

		user_id = self.insert_user_info(last_name, first_name, \
				middle_name, sex, sin, \
				street_address, city, province, postal_code, \
				phone, alternate_phone, email)

		if user_id == None:
			return "Failed to input user into the database"

		token = self.generate_token()
		success = self.insert_user(user_id, token)
		#success = True
		if success:
			db.commit()					
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

	def sin_already_exists(self, sin):
		query = """SELECT * FROM User_Info WHERE sin = %s"""
		info_query = """SELECT * FROM User u, User_Info i where i.sin=%s AND u.id=i.id"""
		cur.execute(query, (sin))
		row = cur.fetchone()
		if row != None:
			cur.execute(info_query, (sin))
			return cur.fetchone()
		else:
			return False
	
	def validate_sin(self, sin):		
		# SOMEONE CHECK SIN IS A 9 DIGIT NUMBER WITH REGEX - DAVID
		return True;

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
				if self.validate_token(token) == None:
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
	db = MySQLdb.connect(host="localhost",
				user = "root",
				passwd = "root",
				db="PCRS_V3");
	cur = db.cursor()
	server = SocketServer.TCPServer((HOST, PORT), MyTCPHandler)
	try:
		server.serve_forever()
	finally:
		cur.close()
		db.close()
