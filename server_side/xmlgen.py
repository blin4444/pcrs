import StringIO

def options_xml(options_list):
	output = StringIO.StringIO()
	output.write('<?xml version="1.0"?>\n')
	output.write('<Options>\n')
	if len(options_list) != 0:
		prev_title = ""
		for item in options_list:
			if prev_title != item[0]:
				if prev_title != "":
					output.write('\t</Div>\n')
				output.write('\t<Div name="'+item[0]+'">\n')
				prev_title = item[0]
			output.write('\t\t<Input id="'+str(item[1])+'" text="'+item[2]+'" type="radio"/>\n')
		output.write('\t</Div>\n');
	output.write('</Options>\n')
	text = output.getvalue()
	output.close()
	return text
