#! /usr/bin/python

if __name__ == '__main__':
	infile = open('func_list')
	outfile = open('decl_list', 'w')

	for line in infile:
		func_begin = line.find(' ') + 1
		func_end = line.find('(')
		decl = 'RECORDER_FORWARD_DECL(P' + line[func_begin:func_end] + ', int, ' + line[func_end:-2] + ');'
		outfile.write(decl + '\n')
