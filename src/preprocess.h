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

	// the inner maps is used to match arguments like fh and request
	map<string, map<string, unsigned int>> argument_maps;

	// the data structure stores each function's name, paras etc
	T all_data;

	int extract_data_from_single_line(string & line);

	unsigned int build_match(string& key, string& value);

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
	argument_maps.clear();
	argument_maps.insert(make_pair("fh", map<string, unsigned int>()));
	argument_maps.insert(make_pair("request", map<string, unsigned int>()));
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

template<typename T, typename K>
unsigned int Preprocess<T, K>::build_match(string& key, string& value)
{
	typename map<string,map<string, unsigned int>>::iterator outer_it;
	if ((outer_it = argument_maps.find(key)) == argument_maps.end())
		return 0;

	typename map<string, unsigned int>::iterator inner_it;
	if ((inner_it = (outer_it->second).find(value)) == (outer_it->second).end()) {
		unsigned int num = outer_it->second.size() + 1;
		outer_it->second.insert(make_pair(value, num));
	}

	return (outer_it->second)[value];
}

// analyze each line, note this funtion is data-specific
template<typename T, typename K>
int Preprocess<T, K>::extract_data_from_single_line(std::string & line)
{
	std::string key, value, temp;
	K cur_func;

	if (line == "Start tracing..." || line == "Outputing all data...")
		return 0;

	// extract function's name, parameters, etc
	for(int cur_para_begin = 0,
			cur_para_end = line.find(' ', cur_para_begin); 

		cur_para_end >= 0; 
		
		cur_para_begin = cur_para_end+1,cur_para_end = line.find(' ', cur_para_begin)){
		
		// TODO: boost string have built-in trim whitespace, while c++ std don't
		// trim whitspace
		while (line[cur_para_begin] == ' ')
			cur_para_begin++;
		temp.assign(line, cur_para_begin, cur_para_end-cur_para_begin);
		size_t split_pos = temp.find('=');
		// TODO: spilt_pos is unsigned int, always positive
		if (split_pos >= 0) {
			value.assign(temp, split_pos+1, std::string::npos);
			key.assign(temp, 0, split_pos);
		}
		else
			value.clear();

		// ignore timestamps and nullify info, status, request
		if (key == "tm1" || key == "tm2" || key == "tm1_first")
			continue;
		if (key == "info" || key == "status" || key == "tag")
			value = key;

		// TODO: remove it later
		if (key == "fh" || key == "request") {
			unsigned int assigned_value = build_match(key, value);
			value = to_string(assigned_value);
			}

		cur_func.insert(pair<std::string, std::string>(key, value));
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
			out << kitor->first << "=" << kitor->second << ' ';
		}
		out << std::endl;
	}

	return 0;
}

#endif // _PREPROCESS_H
