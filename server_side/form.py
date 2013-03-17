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
        elements = section.findall("./input")
        table = section.attrib["id"]
        string = MutableString()
        string += "insert into "
        string2 = MutableString()
        string2 += "values("
        string += table + "("
        for i in range(len(elements)-1):
            string += elements[i].attrib['id'] + ", "
            string2 += "%s, "
        string += elements[len(elements)-1].attrib['id'] + ") "
        string2 += "'%s') "
        string += string2
        print string
        return str(string)

    def buildArgumentMap(self):
        sections = self.root.findall("./div")
        mapping = dict()
        for section in sections:
            arguments = list()
            mapping[section.attrib["id"]] = arguments
            fields = section.findall("./input")
            for field in fields:
                arguments.append(field.attrib["id"])
        print mapping
        return mapping
