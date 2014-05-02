#include "suffix_tree.h"
#include <iostream>

using namespace std;

int main()
{
	cout << "Begining" << endl;
	SuffixTree st("BOOKKE");

	cout << "Constructing..." << endl;
	st.construct();

	cout << "Printing..." << endl;
	st.print_tree();

	cout << "Search OK:" << st.search("OK") << endl;
	cout << "Search KKE:" << st.search("KKE") << endl;
	cout << "Search BOO:" << st.search("BOO") << endl;
	cout << "Search B:" << st.search("B") << endl;

	cout << endl;

	cout << "Search BB:" << st.search("BB") << endl;
	cout << "Search KKK:" << st.search("KKK") << endl;
	cout << "Search b:" << st.search("b") << endl;

	return 0;
}
