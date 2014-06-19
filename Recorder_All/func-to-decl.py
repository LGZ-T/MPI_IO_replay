#! /usr/bin/python
# useage ./func-to-decl.py func_list decl_list

import sys

if __name__ == '__main__':
	infile = open(sys.argv[1])
	outfile = open(sys.argv[2], 'w')

	for line in infile:
		func_begin = line.find(' ') + 1
		func_end = line.find('(')
		decl = 'RECORDER_FORWARD_DECL(P' + line[func_begin:func_end] + ', int, ' + line[func_end:-2] + ');'
		outfile.write(decl + '\n')
