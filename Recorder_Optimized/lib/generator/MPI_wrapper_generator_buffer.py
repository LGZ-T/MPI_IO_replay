#! /usr/bin/python

import re
# TODO: fh's value not consistant

OUTPUTFILE = 'sample_file'

def generate_head(code_file, out_file):
	data = '/* \n *This file is generated automaticaly by wrapper generator.\n'
	data += ' * define neccessary variables below\n'
	data += ' */\n\n'

#	data += '#include "simple_compress.h"\n'

	data += 'double tm1, tm2;\n'
	data += 'int ret, result_len;\n'
	data += 'char comm_name[100], etype_name[100], filetype_name[100], datatype_name[100];\n'

	# add buffer
	data += '#define BUFFER_SIZE 4096\n'
	data += 'const int threshold = BUFFER_SIZE * 0.9;\n'
	data += 'int bytes, written_bytes;\n'
	data += 'char rec_buffer[4096];\n\n'


# copy initialzation from recorder
	try:
		all_the_text = code_file.read()
	finally:
		code_file.close()

	data += all_the_text
	out_file.write(data)

	return


def generate_one_function(para_list, out_file):
	if len(para_list) < 3:
		return 1

# generate function head
	head = ''
	head += para_list[1] + ' '	# return type
	head += para_list[0].lstrip('P') + '('	# function name

	for index, para in enumerate(para_list):
		if index > 1:
			head += para + ','
	
	head = head[:-1]
	head += ')\n'

# generate function body
	paras = para_list[2:]
	
	get_name = {'comm': 'PMPI_Comm_get_name(comm, comm_name, &result_len);\n', 
				'datatype': 'PMPI_Type_get_name(datatype, datatype_name, &result_len);\n',
				'etype': 'PMPI_Type_get_name(etype, etype_name, &result_len);\n',
				'filetype': 'PMPI_Type_get_name(filetype, filetype_name, &result_len);\n'}

	para_format = {
			'MPI_File' : '%d',
			'MPI_Offset' : '%d',
			'MPI_Datatype' : '%s',
			'MPI_Comm' : '%s',
			'MPI_Status' : '%d',
			'MPI_Info' : '%d',
			'MPI_Op' : '%d',
			'__D_MPI_REQUEST' : '%d',
			'int' : '%d',
			'char' : '%s',
			}
				
	call_para = '('
	extra_data = ''
	print_format_1 = '"tm1=%.5f tm2=%.5f func=' + para_list[0].lstrip('P') + ' '
	print_format_2 = 'tm1, tm2'
	call_delim = ', '
	delim = ' '
	para_delim = ', '
	for para in paras:
		type_of_para =  str(para.split()[0])
		true_para = str(para.split()[1])
		pointer = true_para.startswith('*')
		call_para += true_para.lstrip('*')
		call_para += call_delim

		
		extra = get_name.get(true_para, None)
		if extra is not None:
			extra_data += extra
			extra = None
			print_format_1 += true_para + '=' + para_format.get(type_of_para, 'Error') + delim
			print_format_2 += para_delim + true_para + '_name'
		elif pointer == True:
			# for void *buf, int *comm, int *size, etc.
			if type_of_para == 'void' or type_of_para == 'int':
				print_format_1 += true_para.lstrip('*') + '=' + true_para + delim
			else:
				print_format_1 += true_para.lstrip('*') + '=' + para_format.get(type_of_para, 'Error') + delim
				if type_of_para == 'MPI_File': # only use address
					#print_format_2 += ', ' + true_para
					print_format_2 += para_delim + true_para.lstrip('*')
				else:
					print_format_2 += para_delim + true_para.lstrip('*')

		else:
			print_format_1 += true_para.lstrip('*') + '=' + para_format.get(type_of_para, 'Error') + delim
			if type_of_para == 'MPI_File':
			#	print_format_2 += ', ' + '&' + true_para
				print_format_2 += para_delim + true_para
			else:
				print_format_2 += para_delim + true_para
	
	#print_format_1 = print_format_1[:-1]
	print_format_1 += '\\n"' + para_delim

			
	call_para = call_para[:-2]
	call_para += ')'

	body = '{\n'
	body += '\ttm1 = recorder_wtime();\n'
	body += '\tret = RECORDER_MPI_CALL(' + para_list[0] + ')' + call_para + ';\n'
	body += '\ttm2 = recorder_wtime();\n'
	body += extra_data

#	body += '\tif (__recorderfh != NULL)\n'
	body += '\tbytes = sprintf(rec_buffer + written_bytes, ' + print_format_1 + delim + print_format_2 + ');\n'
	body += '\twritten_bytes += bytes;\n'
	body += '\tif (written_bytes > threshold) {\n'
	body += '\t\twrite(__recorderfd, rec_buffer, written_bytes);\n'
	body += '\t\twritten_bytes = 0;\n}\n\n'

	body += '\treturn ret;\n'
	body += '}\n\n'

	result = head + body
	out_file.write(result)
	return 0
		

def process(line, goodbye, out_file):
	recorder_prefix = 'RECORDER_FORWARD_DECL'
	if line.startswith(recorder_prefix) == False:
		return 1
	
	#strip prefix and parathens
	striped = line[len(recorder_prefix):-2]
	
	if striped.startswith(goodbye):
		print "!!!!!!!!!!! Bye !!!!!!!!!!"
		return 2

	print striped
	para_list = []
	temp = striped.split(',')
	print temp
	for para in temp:
		bone = para.strip(' ()')
		if len(bone) > 0:
			para_list += [bone]
	print para_list

	generate_one_function(para_list, out_file)

	return 0

if __name__ == '__main__':
	input_file = open("../recorder-mpi-init-finalize.c")
	output_file = open('sample_output.c', 'w')
	input_header = open('input_header_buffer')

	generate_head(input_header, output_file)
	for line in input_file:
		if process(line, '(PMPI_Finalize', output_file) == 2:
			break

	input_file.close()
	output_file.close()
