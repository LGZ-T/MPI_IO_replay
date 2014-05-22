#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "datatype.h"
#include "preprocess.h"
#include <boost/algorithm/string.hpp>

using namespace std;

int construct_trace(str_hmap_list la, int i)
{
	string c_filename = "construct/log." + to_string(i);
	cout << "output to " << c_filename << endl;
	ofstream fout(c_filename.c_str());

	string m_filename = "lcs/merged_lcs." + to_string(i);
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
				fout <<	la[pos];
				pos++;
			}
			break;
		case 'd':
			cout << "d -- " << line << endl;
			pos += stoi(substrs[1]);
			break;
		case 'i':
			cout << "i -- " << line << endl;
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

int gen_code(string filename, map<string, vector<string>>& func_info)
{
	string code = "code/temp.c";
	ofstream fout(code.c_str());

	ifstream fin(filename.c_str());
	Preprocess<str_hmap_list, str_hmap> pp(filename);
	pp.run();
	str_hmap_list &l = pp.get_data();

	for (unsigned int i=0; i<l.size(); i++) {
		if (l[i].find("func") == l[i].end())
			continue;
		
		string func = l[i]["func"];
		fout << func << '(';

	//	copy(func_info[func].begin()+1, func_info[func].end(), ostream_iterator<string>(fout, ", " ));
	//	fout << *(func_info[func].end()-1) << ");" << endl;
		typename vector<string>::iterator v_it;
		// TODO: figure out why should minus 2 here 
		for (v_it = func_info[func].begin()+1; v_it<func_info[func].end()-2; v_it++)
			fout << *v_it << ", ";
		fout << *v_it << ");" << endl;
	}
/*
	string line;
	while (getline(fin, line)) {
		if (line == "Start tracing...")
			continue;


	}
*/
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

int main(int argc, char* argv[])
{
    	int logs = 8;

	const char * zero = "lcs/merged_lcs.0";
	string base(zero);
	Preprocess<str_hmap_list, str_hmap> ppa(base);
	ppa.run();	
    ppa.data_print();
    str_hmap_list la = ppa.get_data();

	// func name and parameters
	map<string, vector<string>> func_info;
	get_func_info("Recorder_All/lib/generator/func_info", func_info);

	for (typename map<string, vector<string>>::iterator it=func_info.begin(); it!=func_info.end(); ++it) {
		cout << it->first << endl;
		copy(it->second.begin(), it->second.end(), ostream_iterator<string>(cout, "---"));
		cout << endl;
	}

	for (int i=1; i<2; i++) {
		construct_trace(la, i);
	}
	gen_code(base, func_info);
	
	return 0;
}
