#ifndef _PREPROCESS_H_
#define _PREPROCESS_H_

#include <iostream>
#include <fstream>
#include <string>
#include <tr1/unordered_map>
#include <map>
#include <list>
#include <vector>
#include "datatype.h"

using namespace std;

/*
 * Read raw trace file and convert.
 */
template <typename T, typename K>
class Preprocess {
private:
	string filename;

	// the data structure stores each function's name, paras etc
	T all_data;
	int extract_data_from_single_line(string & line);

	// return 0 if repetition found, 
	// -1 if function name unmatch,
	// 1 if offset unmatch,
	// 2 if other paras unmatch
//	int consecutive_op(K & cur_func);	No longer needed

	// compress the obvious consecutive op on large file
//	int push_with_simple_compress(K & cur_func);	No longer needed

public:
	Preprocess(string filename_para);
//	~Preprocess();

	// return 0 if success
	void changefile(string file_name_para);
	int run();
	// TODO: why the adding of const will cause error?
	int data_print(ostream & out);
	T & get_data(void);
};

// Important! The implementation and definition of TEMPLATE CLASS MUST put in the same FILE!!!
template <typename T, typename K>
Preprocess<T, K>::Preprocess(string filename_para)
{
	filename = filename_para;
	std::cout << "File " << filename << std::endl;
}

template <typename T, typename K>
void Preprocess<T, K>::changefile(string filename_para)
{
	filename = filename_para;
}

// TODO: should have an output parameter here
template <typename T, typename K>
int Preprocess<T, K>::run()
{
	fstream fin(filename.c_str());
	if (!fin) {
		std::cout << "Unable to open input file:" << filename << std::endl;
		return 1;
	}
	std::string ReadLine;
	int lineno = 0;

	std::cout << "Running" << std::endl;
	while (getline(fin,ReadLine))
	{
		lineno++;
		std::cout << lineno << '\t' << ReadLine << std::endl;
		Preprocess::extract_data_from_single_line(ReadLine);
//		if (lineno > 100)
//			break;
	}

	return 0;
}

// analyze each line, note this funtion is data-specific
template<typename T, typename K>
int Preprocess<T, K>::extract_data_from_single_line(std::string & line)
{
	std::string temp, temp_value;
	K cur_func;

	if (line.empty() || line == "Start tracing...")
		return 0;

	// extract function's name, parameters, etc
	for(int cur_para_begin = 0,
			cur_para_end = line.find(' ', cur_para_begin); 

		cur_para_end >= 0; 
		
		cur_para_begin = cur_para_end+1,cur_para_end = line.find(' ', cur_para_begin)){
		
		// TODO: boost string have built-in trim whitespace, while c++ don't
		// trim whitspace
		while (line[cur_para_begin] == ' ')
			cur_para_begin++;
		temp.assign(line, cur_para_begin, cur_para_end-cur_para_begin);
		size_t split_pos = temp.find('=');
		// TODO: spilt_pos is unsigned int, always positive
		if (split_pos >= 0) {
			temp_value.assign(temp, split_pos+1, std::string::npos);
			temp.assign(temp, 0, split_pos);
		}
		else
			temp_value.clear();

		// ignore timestamps and nullify info, status, request
		if (temp == "tm1" || temp == "tm2")
			continue;
		if (temp == "info" || temp == "status" || temp == "request")
			temp_value = temp;

		// TODO: remove it later
		if (temp == "fh")
			temp_value = temp;

		cur_func.insert(pair<std::string, std::string>(temp, temp_value));
	}
	all_data.push_back(cur_func);

	return 0;
}


template<typename T, typename K>
T & Preprocess<T, K>::get_data(void)
{
	return all_data;
}

// for test
template<typename T, typename K>
int Preprocess<T, K>::data_print(ostream & out = cout)
{
	out << "Outputing all data..." << std::endl;
	if (all_data.empty()) {
		out << "No data so far" << std::endl;
		return 1;
	}

	typename T::iterator titor;
	for(titor=all_data.begin(); titor!=all_data.end(); titor++) {
		typename K::iterator kitor;
		for (kitor=titor->begin(); kitor!=titor->end(); kitor++){
			out << kitor->first << " = " << kitor->second << '\t';
		}
		out << std::endl << std::endl;
	}

	return 0;
}

#endif // _PREPROCESS_H_
