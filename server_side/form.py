import xml.etree.ElementTree as ET
from UserString import MutableString

class Form:

    def __init__(self, file):
        self.root = self.readXML(file)
        self.sectionMap = dict()
        for section in self.root.findall("./*"):
            self.sectionMap[section.attrib["id"]] = section

    def readXML(self, file):
        f = open(file, "r")
        string = f.read()
        return ET.fromstring(string)

    def printSections(self):
        sections = self.root.findall("./div")
        for section in sections:
            self.buildQuery(section)

    def buildQuery(self, section):
        elements = section.findall("./*")
        table = section.attrib["id"]
        string = MutableString()
        string += "insert into "
        string2 = MutableString()
        string2 += "values("
        string += table + "("
        for i in range(len(elements)-1):
            if (elements[i].tag != "br"):
                string += elements[i].attrib['id'] + ", "
                string2 += "%s, "
        if (elements[len(elements)-1].tag != "br"):
            string += elements[len(elements)-1].attrib['id'] + ") "
            string2 += "'%s') "
        string += string2
        return str(string)

    def buildArgumentMap(self):
        sections = self.root.findall("./div")
        mapping = dict()
        for section in sections:
            arguments = list()
            mapping[section.attrib["id"]] = arguments
            fields = section.findall("./*")
            for field in fields:
                if (field.tag != "br"):
                    arguments.append(field.attrib["id"])
        return mapping
