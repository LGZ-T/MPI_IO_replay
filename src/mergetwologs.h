#ifndef MERGETWOLOGS_H
#define MERGETWOLOGS_H

#include <iostream>
#include <string>
#include "datatype.h"
#include "preprocess.h"

using namespace std;

template<typename T, typename K>
class MergeTwoLogs{
private:
	string _file1;
	string _file2;

	T _data1;
	T _data2;

	Preprocess<T, K> * _pp1;
	Preprocess<T, K> * _pp2;

	// the max len of unmatch log entries
	int _window;
	
	// used by compare, deviation below this is classfied as same
	double _size_deviation;

	int compare(typename T::iterator, typename T::iterator);

	int excute_preprocess(void);

public:
	MergeTwoLogs(string file1, string file2, int window = 5, double size_deviation = 0.05)
		: _file1(file1), _file2(file2), _window(window), _size_deviation(size_deviation)
	{
		_data1.clear();
		_data2.clear();
		_pp1 = new Preprocess<T, K>(file1);
		_pp2 = new Preprocess<T, K>(file2);
	}

	// read T-type data directly, don't need to preprocess
	MergeTwoLogs(T data1, T data2, int window, double size_deviation)
		: _data1(data1), _data2(data2), _window(window), _size_deviation(size_deviation)
	{}

	// merge two _data, _data1 is used to store the result
	int merge(void);

};

template<typename T, typename K>
int MergeTwoLogs<T, K>::merge(void)
{
	if (excute_preprocess() == 2) 
		return 2;
	
	cout << _data1.empty() << endl;
	cout << _data2.empty() << endl;

	typename T::iterator it1, it2;
	for (it1=_data1.begin(), it2=_data2.begin();
			it1!=_data1.end() && it2!=_data2.end();
			it1++, it2++) {
		int match = compare(it1, it2);

		// TODO:search two list downward, until the limit(_window) is reached
		// TODO:then we should rearrange list, so that we could merge as much as possible
		if (!match) {
			cout << "unmatch found." << endl;
			return 1;
		}
	}
	
	cout << "Merge complete." << endl;
	_pp1->data_print();

	ofstream merged_log;
	merged_log.open("../output_data/merged_log");
	cout << "Writing to file..." << endl;
	_pp1->data_print(merged_log);
	cout << "Complete." << endl;
	merged_log.close();

	return 0;
}

template<typename T, typename K>
int MergeTwoLogs<T, K>::excute_preprocess(void)
{
	// already processed
	if ((!_data1.empty()) && (!_data2.empty()))
		return 1;
	
	// TODO: only one of data1 or data2 is not empty, should raise exception
	if (!(_data1.empty() && _data2.empty()))
		return 2;

	_pp1->run();
	_data1 = _pp1->get_data();

	_pp2->run();
	_data2 = _pp2->get_data();

	return 0;
}

// 1 as matched, 0 as unmatched
template<typename T, typename K>
int MergeTwoLogs<T, K>::compare(typename T::iterator it1, typename T::iterator it2)
{
	typename K::iterator kit1, kit2;
	long diff;

	cout << "Begin to match " << (*it1)["func"] << endl;

	for (kit1=it1->begin(), kit2=it2->begin(); kit1!=it1->end(), kit2!=it2->end(); kit1++, kit2++) {
		cout << "Matching " << kit1->first << endl;
		if (kit1->first == kit2->first) {
			if (kit1->second == kit2->second)
				continue;
			else {
				if (kit1->first == "count") { 
					diff = abs(stol(kit1->second) - stol(kit2->second));
					if ((diff / static_cast<double>(stol(kit1->second))) < _window)
						continue;
				}
				else if(kit1->first == "repetition") {
					diff = abs(stol(kit1->second) - stol(kit2->second));
                    if ((diff / static_cast<double>(stol(kit1->second))) < _window)
						continue;
				}
				// TODO: ignore filename for now 
				else if (kit1->first == "filename" || kit1->first == "fh" || kit1->first == "info" || kit2->first == "status")
					continue;
				else {
					cout << "1:" << kit1->first << "->" << kit1->second << endl;
					cout << "2:" << kit2->first << "->" << kit2->second << endl;
					return 0;	// unmatch
				}
			}
		}
		else {
			cout << "1:" << kit1->first << "->" << kit1->second << endl;
			cout << "2:" << kit2->first << "->" << kit2->second << endl;
			return 0;
		}
	}
	
	cout << "Match found.  " << (*it1)["func"] << endl;
	return 1;
}

#endif // MERGETWOLOGS_H
