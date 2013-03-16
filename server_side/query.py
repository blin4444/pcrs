import MySQLdb
from datetime import datetime
class Query:

	def __init__(self):
		self.db = MySQLdb.connect(host="localhost",
				user = "root",
				passwd = "root",
				db="PCRS_V3");
		self.cur = self.db.cursor()

	def close(self):
		self.cur.close()
		self.db.close()

	def validate_token(self, token_string):
		query = """SELECT id FROM User where token=%s"""
		self.cur.execute(query, (token_string))		
		row = self.cur.fetchone()
			
		if row == None:
			return None
		return row[0]


	def insert_sign_in(self, user_id, reason_id):
		sql = """INSERT INTO Sign_In (user_id, reason_id, sign_in_time) VALUES (%s, %s, %s)"""
		self.cur.execute(sql, (user_id, reason_id, datetime.now(),))
		self.db.commit()

	def generate_token(self):
		#temperory generator until we figure out a better way		
		max_id = 100000		
		try:
			self.cur.execute("""SELECT MAX(id) FROM User""")		
			max_id = self.cur.fetchone()
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
			self.cur.execute(sql, (user_id,token))
			db.commit()	
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
			self.cur.execute(sql, (last_name, first_name, middle_name, sex, \
					sin, street_address, city, province, \
					postal_code, phone, alternate_phone, email))
			print "GOT HERE!"
			self.db.commit()
			self.cur.execute(query, (sin))

			user_id = self.cur.fetchone()
			if user_id != None:
				user_id = user_id[0]
			if user_id == None:
				return None
								
			return user_id
		except Exception, err:
			print "Unexpected Error: "+str(err)
			return None

	def sin_already_exists(self, sin):
		query = """SELECT * FROM User_Info WHERE sin = %s"""
		info_query = """SELECT * FROM User u, User_Info i where i.sin=%s AND u.id=i.id"""
		self.cur.execute(query, (sin))
		row = self.cur.fetchone()
		if row != None:
			self.cur.execute(info_query, (sin))
			return self.cur.fetchone()
		else:
			return False

