#include <iostream>
#include "datatype.h"
#include "preprocess.h"
#include "suffix_tree_trace.h"

using namespace std;
// unit test
int main(void)
{
	std::string file("../input_data/zhangyou_IOR/log.0");
	Preprocess<str_hmap_list, str_hmap> pp(file);
	pp.run();	
	pp.data_print();

	cout << "_____________________________________________________" << endl;

	SuffixTree st(pp.get_data());

	st.construct();

	cout << "_____________________________________________________" << endl;

	st.print_tree();
}
