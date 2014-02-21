#include <iostream>
#include <string>
#include "datatype.h"
#include "preprocess.h"
#include "mergetwologs.h"

using std::cout;
using std::endl;
using std::string;
//using namespace std;

template<typename T, typename K>
MergeTwoLogs<T, K>::MergeTwoLogs(string file1, string file2, int window_len, double size_deviation)
{
	_file1 = file1;
	_file2 = file2;
	_data1.clear();
	_data2.clear();
	_pp1 = new Preprocess<T, K>(file1);
	_pp2 = new Preprocess<T, K>(file2);
	_window_len = window_len;
	_size_deviation = size_deviation;
}

template<typename T, typename K>
MergeTwoLogs<T, K>::MergeTwoLogs(T data1, T data2, int window_len, double size_deviation)
{
	_data1 = data1;
	_data2 = data2;
	_window_len = window_len;
	_size_deviation = size_deviation;
}

template<typename T, typename K>
int MergeTwoLogs<T, K>::merge(void)
{
	if (excute_preprocess() == 2) 
		return 2;
	
	cout << _data1.empty() << endl;
	cout << _data2.empty() << endl;

	return 0;
}

template<typename T, typename K>
int MergeTwoLogs<T, K>::excute_preprocess(void)
{
	// already processed
	if ((!_data1.empty()) && (!_data2.empty()))
		return 1;
	
	// TODO:one of data1 or data2 is not empty, should raise exception
	if (!(_data1.empty() && _data2.empty()))
		return 2;

//	Preprocess<str_hmap_list, str_hmap> pp1("xxx");
	_pp1->run();
//	_data1 = pp1.get_data();

//	Preprocess<T, K> pp2(_file2);
//	pp2.run();
//	_data2 = pp2.get_data();

	return 0;
}

// unit test
int main()
{
	string file1("../input_data/root1_IOR/log.0");
	string file2("../input_data/root1_IOR/log.1");

	//MergeTwoLogs<str_hmap_list, str_hmap> m(file1, file2, 5, 0.05);
	//m.merge();
	Preprocess<str_hmap_list, str_hmap> pp1(file1);
	pp1.run();
}
