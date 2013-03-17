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
        sections = self.root.findall("./*")
        for section in sections:
            self.buildQuery(section)

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
                string2 += "%s, "
            else:
                string2 += "%s, "
        string += columns[len(columns)-1].attrib['column'] + ") "
        if columns[len(columns)-1].attrib['type'] != "integer":
            string2 += "%s) "
        else:
            string2 += "%s)"
        string += string2
        print string
        return str(string)

    def buildClientForm(self):
        sections = self.root.findall("./*")
        string = MutableString()
        for i in range(len(sections)-1):
            fields = sections[i].findall("./*")
            for i in range(len(fields)-1):
                string += fields[i].attrib["id"] + "," + fields[i].attrib["type"] + ";"
                string += fields[i].attrib["id"] + "," + fields[i].attrib["type"]
        print string
        return string

    def buildArgumentMap(self):
        sections = self.root.findall("./*")
        mapping = dict()
        for section in sections:
            arguments = list()
            mapping[section.attrib['id']] = arguments
            fields = section.findall("./*")
            for field in fields:
                arguments.append(field.attrib["column"])
        print mapping
        return mapping

if __name__ == "__main__":
    xml = Form("form.xml")
    xml.printSections()
    xml.buildClientForm()
    xml.buildArgumentMap()
