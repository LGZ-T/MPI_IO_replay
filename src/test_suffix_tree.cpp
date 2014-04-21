#include "suffix_tree.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Begining" << endl;
	SuffixTree st("abcabxabcd");

	cout << "Constructing..." << endl;
	st.construct();

	cout << "Printing..." << endl;
	st.print_tree();

	return 0;
}
