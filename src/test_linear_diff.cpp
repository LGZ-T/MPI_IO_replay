#include "suffix_tree.h"
#include <iostream>

using namespace std;

// NOTE: This version is now obsolete, test_linear_diff_2 is the new, more efficient version
int main()
{
	string test_left = "BOOKKE";
	cout << "Begining" << endl;
	SuffixTree st(test_left);

	cout << "Constructing Suffix tree of " << test_left << endl;
	st.construct();

	string test_right = "BOKKECBAOOK";
	
	int begin = 0, end = 0, limit = test_right.size();
	int pos;
	int sub_begin;

	cout << "__________________________________________________________________________" << endl;
	cout << "Left:" << test_left << '\t' << "Right:" << test_right << endl;
	for (; begin < limit && end < limit; begin++) {
		string sub = test_right.substr(begin, end-begin+1);
		if ((pos = st.search(sub)) > -1) {
			end++;
			begin--;	// keep the value of begin unchanged
			sub_begin = pos;

			if (end >= limit) {
				// TODO: I know it's ugly, will do sth about it later...
				goto match;
			}
			continue;
		}
		else {
			if (end == begin)	// there are no such char in test_left match test_right[begin]
			{
				cout << test_right[begin] << endl;
				begin--;
				begin++;
				end++;
			}
			else {
			match:
				cout << test_left.substr(sub_begin, end-begin+1-1) << '\t';
				cout << "beginning at " << sub_begin << " and ending at " << sub_begin+sub.size()-1 << endl;
				begin = end;
				begin--;
			}
		}
	}

	return 0;
}
