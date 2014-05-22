#! /usr/bin/python

import re
# TODO: fh's value is not consistant

OUTPUTFILE = 'sample_file'

def generate_head(code_file, out_file):
	data = '/* \n *This file is generated automaticaly by a wrapper generator!\n'
	data += ' * define neccessary variables below\n'
	data += ' */\n\n'

	data += '#include "simple_compress.h"\n'
	# sc should be initialized in input header
	data += 'SimpleCompress *sc;\n\n'

	data += 'struct timespec tm1, tm2, tm3, tm4, compute_time, mpi_time, this_func_time;\n'
	data += 'struct timespec compute_time_all, mpi_time_all, recorder_time_all;\n'
	data += 'int ret, result_len;\n'
	data += 'char comm_name[100], etype_name[100], filetype_name[100], datatype_name[100], oldtype_name[100], newtype_name[100];\n'

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


def generate_one_function(para_list, out_file, func_file):
	if len(para_list) < 3:
		return 1

	func_info = ''	# info for replay
# generate function head
	head = ''
	head += para_list[1] + ' '	# return type
	func_name = para_list[0].lstrip('P') + '('
	func = para_list[0].lstrip('P')
	func_info += func + ' '
	head += func_name	# function name

	for index, para in enumerate(para_list):
		if index > 1:
			head += para + ','
	
	head = head[:-1]
	head += ')\n'

# generate function body
	paras = para_list[2:]
	
	def datatype_code(datatype):
		datatype_code = '''PMPI_Type_get_name(%(data)s, %(data)s_name, &result_len);\n
		if (result_len == 0) {
			sprintf(%(data)s_name, "%%lu", %(data)s);
		}
		'''
		result = datatype_code % {'data' : datatype}
		return result

	get_name = {'comm': 'PMPI_Comm_get_name(comm, comm_name, &result_len);\n', 
				'datatype': datatype_code('datatype'),
				'etype': datatype_code('etype'),
				'filetype': datatype_code('filetype'),
				'oldtype' : datatype_code('oldtype'),
				'newtype': 'sprintf(newtype_name, "%lu", *newtype);\n'}

	para_format = {
			'MPI_File' : '%lu',
			'MPI_Offset' : '%lld',
			'MPI_Datatype' : '%s',
			'MPI_Comm' : '%s',
			'MPI_Status' : '%lu',
			'MPI_Info' : '%lu',
			'MPI_Op' : '%lu',
			'MPI_Request' : '%lu',
			'MPI_Aint' : '%ld',	# I assume MPI_Aint is the equivalent of ptrdiff_t, which is long int
			'int' : '%d',
			'char' : '%s',
			}
				
	call_para = '('
	extra_data = ''
	after_call = ''
	# TODO: the tm1 tm2 written to th file is really compute_time and mpi_time
	print_format_1 = '"tm1=%ld.%.9ld tm2=%ld.%.9ld func=' + para_list[0].lstrip('P') + ' '
	print_format_2 = 'compute_time.tv_sec, compute_time.tv_nsec, mpi_time.tv_sec, mpi_time.tv_nsec'
	call_delim = ', '
	delim = ' '
	para_delim = ', '

	body = '{\n'
	print func
	if func == 'MPI_File_close':
		body += '\tMPI_File real_fh = *fh;\n'
		

	for para in paras:
		type_of_para =  str(para.split()[0])
		true_para = str(para.split()[1])
		pointer = true_para.startswith('*')
		call_para += true_para.lstrip('*').rstrip('[]')
		call_para += call_delim
		true_para = true_para.rstrip('[]')

		func_info += true_para.lstrip('*') + ' '

		
		extra = get_name.get(true_para.lstrip('*'), None)
		if extra is not None:
			# for MPI_Datatype*
			if pointer == True and type_of_para == 'MPI_Datatype':
				true_true_para = true_para.lstrip('*')
				after_call += 'sprintf(%s_name, "%%lu", *' % true_true_para + true_para.lstrip('*') + ');\n'
			else:
				extra_data += extra
			
			extra = None
			
			print_format_1 += true_para.lstrip('*') + '=' + para_format.get(type_of_para, 'Error') + delim
			print_format_2 += para_delim + true_para.lstrip('*') + '_name'
		elif pointer == True:
			# char*
			if type_of_para == 'char':
				print_format_1 += true_para.lstrip('*') + '=' + para_format.get(type_of_para, 'Error') + delim
				print_format_2 += para_delim + true_para.lstrip('*')
			# for void *buf, int *comm, int *size, etc.
			elif type_of_para == 'void' or type_of_para == 'int':
				print_format_1 += true_para.lstrip('*') + '=' + true_para.lstrip("*") + delim
			else:
				#print_format_1 += true_para.lstrip('*') + '=' + para_format.get(type_of_para, 'Error') + delim
				# get address
				print_format_1 += true_para.lstrip('*') + '=' + "%lu" + delim
				if type_of_para == 'MPI_File': # only use address
					#print_format_2 += ', ' + true_para
					if func == 'MPI_File_close':
						print_format_2 += para_delim + 'real_fh'
					else:
						print_format_2 += para_delim + '*' + true_para.lstrip("*")
				else:
					print_format_2 += para_delim + true_para.lstrip('*')

		else:
			print_format_1 += true_para.lstrip('*') + '=' + para_format.get(type_of_para, 'Error') + delim
			if type_of_para == 'MPI_File':
				print_format_2 += para_delim + true_para
			#	print_format_2 += para_delim + true_para
			else:
				print_format_2 += para_delim + true_para
	
	#print_format_1 = print_format_1[:-1]
	print_format_1 += '\\n"' + para_delim

			
	call_para = call_para[:-2]
	call_para += ')'

	body += '\t/* tm1 is the length of time elapsed between the IO or MPI communication calls. It\'s spend in computing */\n'
	body += '\ttm1 = recorder_wtime();\n'
	body += '\tcompute_time = tm1 - tm4;\n'
	body += '\tcompute_time_all += compute_time;\n'
	body += extra_data
	body += '\ttm2 = recorder_wtime();\n'
	body += '\tret = RECORDER_MPI_CALL(' + para_list[0] + ')' + call_para + ';\n'
	body += '\ttm3 = recorder_wtime();\n'
	body += '\tmpi_time = tm3 - tm2;\n'
	body += '\tmpi_time_all += mpi_time;\n'
	body += after_call

#	body += '\tif (__recorderfh != NULL)\n'
	body += '\tbytes = sprintf(rec_buffer + written_bytes, ' + print_format_1 + delim + print_format_2 + ');\n'
	body += '\tread_func(sc, rec_buffer);\n'
	body += '\twrite_or_compress(sc);\n'

	''' 
	does not need buffer here
	body += "\twritten_bytes += bytes;\n"
	body += "\tif (written_bytes > threshold) {\n"
	body += "\t\tfputs(rec_buffer, __recorderfh);\n"
	body += "\t\twritten_bytes = 0;\n}\n\n"
	'''

	body += '\tthis_func_time = recorder_wtime() - tm1;\n'
	body += '\trecorder_time_all += this_func_time - mpi_time;\n;'
	body += '\t/* tm4 stands for the true exit moment of this function */\n'
	body += '\ttm4 = recorder_wtime();\n'

	body += '\treturn ret;\n'
	body += '}\n\n'

	result = head + body
	out_file.write(result)
	func_file.write(func_info + '\n')
	return 0
		

def process(line, goodbye, out_file, func_file):
	recorder_prefix = 'RECORDER_FORWARD_DECL'
	print line	
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

	generate_one_function(para_list, out_file, func_file)

	return 0

if __name__ == '__main__':
	input_file = open("../recorder-mpi-init-finalize-compress.c")
	output_file = open('sample_output.c', 'w')
	input_header = open('input_header_compress')

	func_file = open('func_info', 'w')

	generate_head(input_header, output_file)
	for line in input_file:
		if process(line, '(PMPI_Finalize', output_file, func_file) == 2:
			break

	input_file.close()
	output_file.close()
	func_file.close()
