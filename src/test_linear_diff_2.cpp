#include "suffix_tree.h"
#include <iostream>

using namespace std;

int main()
{
	string test_left = "BOOKKE";
	cout << "Begining" << endl;
	SuffixTree st(test_left);

	cout << "Constructing Suffix tree of " << test_left << endl;
	st.construct();
	
	st.print_tree();

	string test_right = "BOKKECBAOOK";
	
	int begin = 0, end = 0, limit = test_right.size();
	int pos;
	int sub_begin;

	cout << "__________________________________________________________________________" << endl;
	string::iterator r_iter = test_right.begin();
	
	while (r_iter != test_right.end()) {
		string::iterator pre_iter = r_iter;
		r_iter = st.inc_search(r_iter);

		if (r_iter == pre_iter) {
			cout << *r_iter << endl;
			r_iter++;
		}
		else {
			for (; pre_iter<r_iter; pre_iter++)
				cout << *pre_iter;
			cout << endl;
		}
	}

	return 0;
}
