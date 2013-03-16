import xml.etree.ElementTree as ET
from UserString import MutableString

class XMLParser:
    def readXML(self, file):
        f = open(file, "r")
        string = f.read()
        root = ET.fromstring(string)
        list = root.findall("./*")
        for section in list:
            self.loadSection(section)

    def loadSection(self, section):
        list = section.findall(".")
        table = section.attrib["table"]
        for element in list:
            print element.tag
            self.buildQuery(element)

    def buildQuery(self, element):
      columns = element.findall("./*")
    	table = element.attrib["table"]
    	string = MutableString()
    	string += "insert into "
    	string2 = MutableString()
    	string2 += "values("
    	string += table + "("
    	for i in range(len(columns)-1):
    		string += columns[i].attrib['column'] + ", "
    		if columns[i].attrib['type'] != "integer":
    			string2 += "'%s', "
    		else:
    			string2 += "%s, "
    	string += columns[len(columns)-1].attrib['column'] + ") "
    	if columns[len(columns)-1].attrib['type'] != "integer":
    		string2 += "'%s') "
    	else:
    		string2 += "%s)"
    	string += string2
    	print string

if __name__ == "__main__":
    xml = XMLParser()
    xml.readXML("form.xml")
