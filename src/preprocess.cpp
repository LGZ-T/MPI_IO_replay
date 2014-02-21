#include <iostream>
#include <fstream>
#include <string>
#include "preprocess.h"

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
	fstream fin(filename);
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

	// extract funcntion name
	int func_name_begin = line.find(' ');
	func_name_begin++;
	int func_name_end = line.find('(',func_name_begin);
	temp.assign(line, func_name_begin, func_name_end-func_name_begin);
	std::cout << "Func name:" << temp << std::endl;
	cur_func["func"] = temp;

	int paras_end = line.rfind(')');
	line.replace(paras_end, 1, 1, ',');	// for the loop below, this should make para extraction more neat
	// extract function's parameters
	for(int cur_para_begin = func_name_end+1,
			cur_para_end = line.find(',', cur_para_begin); 

		cur_para_end >= 0; 
		
		cur_para_begin = cur_para_end+1,cur_para_end = line.find(',', cur_para_begin)){
		
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

		cur_func.insert(pair<std::string, std::string>(temp, temp_value));
	}
//	all_data.push_back();
	push_with_simple_compress(cur_func);

	return 0;
}


template<typename T, typename K>
int Preprocess<T, K>::push_with_simple_compress(K & cur_func)	{
	int ret;
	if ((ret = consecutive_op(cur_func)) != 0) {
		all_data.push_back(cur_func);
		cout << "Ret:" << ret << endl;
	}
	// edit last function instead of add new function in case of consecutive operation
	else {
		K & last_func = all_data.back();


		typename K::iterator rep_itor = last_func.find("repetition");
		if (rep_itor == last_func.end()) {
			last_func.insert(pair<std::string, std::string>("repetition", "2"));

			typename K::iterator offset_itor = last_func.find("offset");
			if (offset_itor != last_func.end()) {
				last_func.insert(pair<std::string, std::string>("original_offset", last_func["offset"]));
				last_func["offset"] = cur_func["offset"];
			}
		}
		else {
			string inc = std::to_string(std::stol(rep_itor->second) + 1);
			last_func["repetition"] = inc;

			typename K::iterator offset_itor = last_func.find("offset");
			if (offset_itor != last_func.end()) 
				last_func["offset"] = cur_func["offset"];
		}
		
	}

	return 0;
}


// probe consecutive operation on single file
template<typename T, typename K>
int Preprocess<T, K>::consecutive_op(K & cur_func)
{
	if (all_data.empty())
		return 3;

	K last_func = all_data.back();

	if (last_func["func"] != cur_func["func"])
		return -1;
	
	typename K::iterator cur_itor;
	for (cur_itor=cur_func.begin(); cur_itor!=cur_func.end(); cur_itor++) {
		if (cur_itor->first == "offset") {
			if (std::stol(last_func["offset"]) + std::stol(last_func["count"]) != std::stol(cur_func["offset"]))
				return 1;
		}
		else if (cur_func[cur_itor->first] != last_func[cur_itor->first])
			return 2;
	}
	cout << "Repetiton found!" << endl;
	return 0;
}

template<typename T, typename K>
T & Preprocess<T, K>::get_data(void)
{
	return all_data;
}

// for test
template<typename T, typename K>
int Preprocess<T, K>::data_print(void)
{
	std::cout << "Outputing all data..." << std::endl;
	if (all_data.empty()) {
		std::cout << "No data so far" << std::endl;
		return 1;
	}

	typename T::iterator titor;
	for(titor=all_data.begin(); titor!=all_data.end(); titor++) {
		typename K::iterator kitor;
		for (kitor=titor->begin(); kitor!=titor->end(); kitor++){
			std::cout << kitor->first << " = " << kitor->second << '\t';
		}
		std::cout << std::endl << std::endl;
	}

	return 0;
}

#if 0
// unit test
int main()
{
	std::string file("../input_data/root1_IOR/log.0");
	Preprocess<str_hmap_list, str_hmap> pp(file);
	pp.run();	
	pp.data_print();
}
#endif
