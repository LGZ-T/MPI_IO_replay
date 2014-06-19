#! /usr/bin/python
# useage: Type_and_Extern_Generator.py decl_list init-compress.c recorder-dynamic.h
import sys

func_names = []
externs = []

def write_resolve(out_file):
	out_file.write("\n\nint resolve_mpi_symbols()\n{")

	global func_names
	for func in func_names:
		out_file.write("\tMAP_OR_FAIL(P" + func + ");\n")

	out_file.write("}")

def process(line, goodbye, out_file):
	recorder_prefix = 'RECORDER_FORWARD_DECL'
	if line.startswith(recorder_prefix) == False:
		return 1
	
	out_file.write(line)

	#strip prefix and parathens
	striped = line[len(recorder_prefix):-2]
	type_decl = 'RECORDER_TYPE' + striped
	out_file.write(type_decl + ';\n')

	extern = 'RECORDER_EXTERN_DECL' + striped
	externs.append(extern)

	sep = striped.find(',')
	striped = striped[2:sep]
	func_names.append(striped)
	
	if striped.startswith(goodbye):
		#print "!!!!!!!!!!! Bye !!!!!!!!!!"
		out_file.write("/* below are MPI calls not intercepted */")
		# don't exit
		return 1

	#print striped

	return 0

def write_externs(out_file):
	global externs
	for line in externs:
		out_file.write(line + ';\n')

	after = '''
#else

#define RECORDER_MPI_CALL(func) func

#endif

#endif
'''
	out_file.writelines(after)

	return

if __name__ == '__main__':
	input_init_compress = open(sys.argv[1])
	output_init_compress = open(sys.argv[2], "w")
	
	before_init = open("_INC/Before_type.c")
	after_init = open("_INC/After_type.c")

	
	for line in before_init:
		output_init_compress.write(line)

	for line in input_init_compress:
		if process(line, 'MPI_Scan', output_init_compress) == 2:
			break
	
	write_resolve(output_init_compress)

	for line in after_init:
		output_init_compress.write(line)

	input_init_compress.close()
	output_init_compress.close()
	before_init.close()
	after_init.close()

	# new recorder-dynamic.h
	before_extern = open("_INC/Before_extern.h")
	output_extern = open(sys.argv[3], "w")

	for line in before_extern:
		output_extern.write(line)

	write_externs(output_extern)

	before_extern.close()
	output_extern.close()

