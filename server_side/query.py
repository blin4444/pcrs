import MySQLdb
from datetime import datetime
from words import TokenGenerator
class Query:

	def __init__(self):
		self.db = MySQLdb.connect(host="localhost",
				user = "root",
				passwd = "root",
				db="PCRS_V4");
		self.cur = self.db.cursor()
		self.word = TokenGenerator("wordlist.txt")

	def close(self):
		self.cur.close()
		self.db.close()

	def validate_token(self, token_string):
		query = """SELECT id FROM User where token=%s"""
		self.cur.execute(query, (token_string))	
		row = self.cur.fetchone()
			
		if row != None:
			row = row[0]
		return row
	
	def generate_token(self):
		token = self.word.get()
		try:
			self.cur.execute("""SELECT Count(id) FROM User WHERE token LIKE %s%""", (token))		
			count = self.cur.fetchone()
			if count != None:
				count = count[0]
		except:
			count = 0
		
		if count != 0:
			return token+str(count+1)
		
		return token

	def sin_already_exists(self, sin):
		query = """SELECT * FROM User_Info WHERE sin = %s"""
		info_query = """SELECT * FROM User u, User_Info i where i.sin=%s AND u.id=i.id"""
		self.cur.execute(query, (sin))
		row = self.cur.fetchone()
		print "does sin already exist?"+str(row)
		if row != None:
			self.cur.execute(info_query, (sin))
			result = self.cur.fetchone()
			if result == None:
				token = self.generate_token()			
				self.insert_user(row[0], token)
				self.cur.execute(info_query, (sin))
				result = self.cur.fetchone()		
			print str(result)
			return result
		else:
			return None

	def insert_sign_in(self, user_id, reason_id):
		sql = """INSERT INTO Sign_In (user_id, reason_id, sign_in_time) VALUES (%s, %s, %s)"""
		self.cur.execute(sql, (user_id, reason_id, datetime.now(),))
		self.db.commit()

	def insert_user(self, user_id, token):
		sql = """INSERT INTO User(id, token) VALUES (%s, %s)"""
		try:		
			self.cur.execute(sql, (user_id,token))
			self.db.commit()	
			return True
		except Exception, err:
			print "Unexpected Error when inserting user: "+str(err)
			return False
	
	def insert_user_info(self, queryTemplate, args, sin):
	        sql = queryTemplate
	        query = """SELECT id FROM User_Info WHERE sin=%s"""
	        try:
		    print str(tuple(args))
	            self.cur.execute(sql, tuple(args))
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

	def insert_registration_option(self, user_id, es_id, ud_id, ga_id, rs_id, ou_id):
		sql = """INSERT INTO Registration_Option(user_id, es_id, ud_id, ga_id, rs_id, ou_id, registration_time)
			 VALUES(%s, %s, %s, %s, %s, %s, %s)"""
		try:
			self.cur.execute(sql, (user_id, es_id, ud_id, ga_id, rs_id, ou_id, datetime.now()))
			self.db.commit()
			return True
		except Exception, err:
			print "Unexpected Error when inserting registration option: "+str(err)
			return False
	
	def select_registration_options(self):
		sql_es = """SELECT * FROM Employment_Situation"""
		sql_ud = """SELECT * FROM Unemployment_Duration"""
		sql_ga = """SELECT * FROM Government_Assistance"""
		sql_rs = """SELECT * FROM Residency_Status"""
		sql_ou = """SELECT * FROM Office_Use"""

		tables = [("es_id", sql_es),
		("ud_id", sql_ud),
		("ga_id", sql_ga),
		("rs_id", sql_rs),
                ("ou_id", sql_ou)]

		query_list = []

		try:
			for t in tables:
				self.cur.execute(t[1])
				result_set = self.cur.fetchall()
				for r in result_set:
					query_list.append((t[0], r[0], r[1]))
		except Exception, err:
			print "Unexpected Error when extracting registration options:" + str(err)

		return query_list
