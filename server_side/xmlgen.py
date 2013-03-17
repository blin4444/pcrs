import StringIO

def options_xml(options_list):
	output = StringIO.StringIO()
	output.write('<?xml version="1.0"?>\n')
	output.write('<options>\n')
	if len(options_list) != 0:
		prev_title = ""
		for item in options_list:
			if prev_title != item[0]:
				if prev_title != "":
					output.write('\t</div>\n')
				output.write('\t<div name="'+item[0]+'">\n')
				prev_title = item[0]
			output.write('\t\t<input id="'+str(item[1])+'" value="'+item[2]+'" type="radio"/>\n')
		output.write('\t</div>\n');
	output.write('</options>\n')
	text = output.getvalue()
	output.close()
	return text
