from random import randint

class TokenGenerator:
	def __init__(self, path):
		f = open(path,'r')
		self.list = []
		self.size = 0
		for line in f:
			self.list.append(line.replace("\n",""))
			self.size = self.size+1

	def close(self):
		f.close()

	def get(self):
		word = ""
		for i in range(0,3):
			word = word+self.list[randint(0, self.size-1)]
		return word
