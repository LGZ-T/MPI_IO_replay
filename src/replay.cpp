#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "datatype.h"
#include "preprocess.h"
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>

using namespace std;

int construct_trace(string infile_prefix, string outfile_prefix, str_hmap_list& la, str_hmap_list& a_aux, int i)
{
	string c_filename = outfile_prefix + to_string(i);
	cout << "output to " << c_filename << endl;
	ofstream fout(c_filename.c_str());

	string m_filename = infile_prefix + to_string(i);
	ifstream fin(m_filename);

	int pos = 1;
	int copy;
	string line;
	while (getline(fin, line)) {
		vector<string> substrs;
		// Hell, boost is soooo convenient! Timesaver!
		boost::split(substrs, line, boost::is_any_of(" \t"));
		
		switch(substrs[0][0])
		{
		case 'k':
			cout << "k -- " << line << endl;
			copy = stoi(substrs[1]);

			for (int i=0; i<copy; i++) {
				fout <<	la[pos] << a_aux[pos] << endl;
				pos++;
			}
			break;
		case 'd':
			cout << "d -- " << line << endl;
			pos += stoi(substrs[1]);
			break;
		case 'i':
			cout << "i -- " << line << endl;
			//boost::trim_left(line, boost::is_any_of("insert "))
			line = line.substr(7);
			fout << line << endl;
			break;
		default:
			cout << "can't recognize this!" << endl;
		}
	}
	fin.close();
	fout.close();
	
	return 0;
}

int gen_code_head(string code_file)
{
	string code = code_file;
	ofstream fout(code.c_str());

	fout << "#define _GNU_SOURCE // for clock_gettime, must be placed at the head of file!" << endl;
	fout << "#include <stdio.h>" << endl;
	fout << "#include <time.h>" << endl;
	fout << "#include <sys/time.h>" << endl;
	fout << "#include <mpi.h>" << endl << endl;
	fout << "#define BUFS 1024*1024*100" << endl << "#define HANDLES 100000" << endl << endl;
	fout << "struct timespec begin, end, dur;" << endl;
	fout << "MPI_Datatype datatype[HANDLES];" << endl;
	fout << "MPI_File fh[HANDLES];" << endl;
	fout << "MPI_Request request[HANDLES];" << endl;
	fout << "MPI_Status status, array_of_statuses[HANDLES];" << endl;

	fout << "#define AS 300000" << endl;
	fout << "int array_of_gsizes_arraystore[AS], array_of_distribs_arraystore[AS], array_of_dargs_arraystore[AS], array_of_psizes_arraystore[AS], array_of_sizes_arraystore[AS], array_of_subsizes_arraystore[AS], array_of_starts_arraystore[AS], array_of_blocklengths_arraystore[AS], array_of_displacements_arraystore[AS], array_of_types_arraystore[AS];" << endl;
	fout << "int f_count, procs, myrank;" << endl;
	fout << "int size, rank;" << endl;
	fout << "unsigned long f_offset;" << endl;
	fout << "char sendbuf[BUFS], recvbuf[BUFS], buf[BUFS], buffer[BUFS];" << endl << endl;

	fout << "int main(int argc,char *argv[])" << endl;
	fout << "{" << endl;
	fout << "\tMPI_Init(&argc,&argv);" << endl;
	fout << "\tclock_gettime(CLOCK_MONOTONIC, &begin);" << endl;
	fout << "\tMPI_Comm_size(MPI_COMM_WORLD,&procs);" << endl;
	fout << "\tMPI_Comm_rank(MPI_COMM_WORLD,&myrank);" << endl << endl;
	fout << "\tprintf(\"Process %d running...\\n\", myrank);" << endl << endl;

	fout.close();

	return 0;
}

int gen_code_tail(string code_file)
{
	ofstream fout(code_file.c_str(), ios::out | ios::app);

	fout << "\tprintf(\"Process %d finished\\n\", myrank);" << endl << endl;
	fout << "\tclock_gettime(CLOCK_MONOTONIC, &end);\n" << endl;
	fout << "\tdur.tv_sec = end.tv_sec - begin.tv_sec;\n" << endl;
	fout << "\tdur.tv_nsec = end.tv_nsec - begin.tv_nsec + dur.tv_sec * 1000000000;\n";
	fout << "\tprintf(\"Process %d cost %ld.%09ld time\\n\", myrank, dur.tv_sec, dur.tv_nsec);\n" << endl << endl;
	fout << "\tMPI_Finalize();" << endl;
	fout << "\treturn 0;" << endl;
	fout << "}" << endl;

	fout.close();
}

long get_compute_time(string tm, double ratio)
{
	vector<string> substrs;
	boost::split(substrs, tm, boost::is_any_of("."));

	if (substrs.size() != 2) {
		cout << "time info error!" << endl;
		cout << "tm1:" << tm;
		cout << endl;
		return 1;
	}
	long sec = stol(substrs[0]);
	long nsec = stol(substrs[1]);

	nsec += sec * 1000000000;

	nsec = ratio * (double)nsec;

	return nsec;
}

int gen_code_body(string code_file, string file_prefix, map<string, vector<string>>& func_info, int procs, int i, double ratio)
{	
	string code = code_file;
	ofstream fout(code.c_str(), ios::out | ios::app);

	string filename = file_prefix + to_string(i);
	cout << "gen - " << filename << endl;

	ifstream fin(filename.c_str());
	Preprocess<str_hmap_list, str_hmap> pp(filename, procs, i);
	pp.run();
	str_hmap_list &l = pp.get_data();
    	str_hmap_list &aux = pp.get_auxiliary();

	fout << "\tif (myrank == " << i << ") {" << endl;

	for (unsigned int i=0; i<l.size(); i++) {
		if (l[i].find("func") == l[i].end())
			continue;
		
		string compute_time = aux[i]["tm1"];
		long nsec = get_compute_time(compute_time, ratio);

		// long int i
		fout << "\t\tfor(long int i=0; i<" << nsec << "; i++); /* Simulate compute time */" << endl << endl;

		int repetition;
		repetition = 0;
		typename str_hmap_list::iterator iter;
		if (l[i].find("repetition") != l[i].end()) {
			repetition = stoi(l[i]["repetition"]);
			if (l[i].find("offset") != l[i].end()) 
				; 	// TODO: get interval
		}


		if (repetition){
			string compute_time = aux[i]["tm1_first"];
			nsec = get_compute_time(compute_time, ratio);
			fout << "\t\tfor(long int i=0; i<" << nsec << "; i++); /* Simulate compute time */" << endl << endl;
			
			if (l[i].find("offset") != l[i].end()) {
				fout << "\t\tf_offset = " << l[i]["original_offset"] << ";" << endl;
			}
			fout << "\t\tfor (int r=0; r<" << repetition << "; r++){" << endl;
			
			compute_time = aux[i]["tm1"];
			nsec = get_compute_time(compute_time, ratio);
			fout << "\t\t\tif(r)" << endl;
			fout << "\t\t\t\tfor(long int in_loop=0; in_loop<" << nsec << "; in_loop++); /* Simulate compute time in loops */" << endl << endl;

			if (l[i].find("offset") != l[i].end()) {
				fout << "\t\t\tf_count=" << l[i]["count"] << ";" << endl;
				fout << "\t\t\tf_offset += f_count * 1;" << endl;
				// TODO: multiply datatype size here
			}
		}
		string func = l[i]["func"];
		fout << "\t\t" << func << '(';

	//	copy(func_info[func].begin()+1, func_info[func].end(), ostream_iterator<string>(fout, ", " ));
	//	fout << *(func_info[func].end()-1) << ");" << endl;
		typename vector<string>::iterator v_it;
		// TODO: figure out why should I minus 1 here 
		for (v_it = func_info[func].begin()+1; v_it<func_info[func].end()-1; v_it++) {
			string parameter = *v_it;
			string argument = l[i][*v_it];

			if (boost::starts_with(parameter, "array") && parameter != "array_of_requests" && parameter != "array_of_statuses") {
				vector<string> substrs;
				boost::split(substrs, argument, boost::is_any_of("-"));

				int size = stoi(substrs[0]);
				stringstream ss;
				ss << "(";
				for (int i=0; i<size; i++)
					ss << parameter << "_arraystore[" << i <<"] = " << substrs[i+1] << ",";
				ss << parameter << "_arraystore)";
				argument = ss.str();
			}
			if (parameter == "comm" && argument == "")
				argument = "MPI_COMM_WORLD";
			else if (parameter == "op")
				argument = "MPI_SUM";
			else if (parameter == "fh") {
				argument = "fh" + string("[") + argument + "]";
				if (func == "MPI_File_open" || func == "MPI_File_close")
					argument = "&(" + argument + ")";
			}
			else if (parameter == "request")
				argument = "request" + string("[") + argument + "]";
			else if ((parameter == "datatype" || parameter == "etype" || parameter == "filetype" || parameter == "oldtype" || parameter == "newtype")) {
				if (boost::starts_with(argument, "MPI") == 0) {
					argument = "datatype[" + string(argument) + "]";	// TODO
					if (parameter == "newtype" || func == "MPI_Type_commit")
						argument = "&" + argument;
				}
				else if(argument == "MPI_UNSIGNED_INT")
					argument = "MPI_INT";
			}


			else  if (parameter == "offset" && repetition != 0) {
				argument = "f_offset";
			}
			else if (parameter == "tag" || parameter == "sendtag" || parameter == "recvtag" )
				argument = "1";
			else if (parameter == "size" || parameter == "rank") {
				if (func == "MPI_Comm_rank" || func == "MPI_Comm_size")
					argument = "&" + argument;
			}
			else if (parameter == "status")
				argument = "&" + argument;
			else if (parameter == "filename" || parameter == "datarep")
				argument = "\"" + argument + "\"";
			else if (parameter == "info")
				argument = "MPI_INFO_NULL";

			if (argument.size() == 0) {
				cout << "Para " << parameter << " have no value!" << endl;
			}
			fout << argument;

			if (v_it != func_info[func].end()-2)
				fout << ", ";
		}
		fout << ");" << endl << endl;
		if (repetition)
			fout << "\t\t}" << endl << endl;
		
	}
	
	fout << "\t}\n" << endl;	// for if rank == xx
	fout.close();

	return 0;
}

int get_func_info(const char* filename, map<string, vector<string>>& func_info)
{
	ifstream fin(filename);

	if (!fin) {
		cout << "Can't open function info file!" << endl;
		return 1;
	}

	string line;
	while (getline(fin, line)) {
		vector<string> substrs;
		boost::split(substrs, line, boost::is_any_of(" \t\n"));

		func_info.insert(make_pair(substrs[0], substrs));
	}

	return 0;
}

double get_ratio(void)
{
	//TODO
	return (double)1/3;
}

int main(int argc, char* argv[])
{
	if (argc != 2) {
		cout << "Usage: ./replay NUM(number of files)";
		return 1;
	}
    	int logs = stoi(argv[1]);

	const char * zero = "lcs/merged_lcs.0";
	string base(zero);
	Preprocess<str_hmap_list, str_hmap> ppa(base, logs, 0);
	ppa.run();	
    //ppa.data_print();
    	str_hmap_list& la = ppa.get_data();
	str_hmap_list& a_aux = ppa.get_auxiliary();

	// func name and parameters
	map<string, vector<string>> func_info;
	if (get_func_info("Recorder_All/lib/generator/func_info", func_info)) {
		cout << "Func info missing?" << endl;
		return 1;
	}

	for (typename map<string, vector<string>>::iterator it=func_info.begin(); it!=func_info.end(); ++it) {
		cout << it->first << endl;
		copy(it->second.begin(), it->second.end(), ostream_iterator<string>(cout, "---"));
		cout << endl;
	}

	cout << "func_info?" << endl;

	string code_file("code/temp.c");
	string infile_prefix("lcs/merged_lcs.");
	string outfile_prefix("construct/log.");

	double ratio = get_ratio();
	gen_code_head(code_file);
	// infile!
	gen_code_body(code_file, infile_prefix, func_info, logs, 0, ratio);

	for (int i=1; i<8; i++) {
		construct_trace(infile_prefix, outfile_prefix, la, a_aux, i);
		gen_code_body(code_file, outfile_prefix, func_info, logs, i, ratio);
	}
	gen_code_tail(code_file);
	
	return 0;
}
