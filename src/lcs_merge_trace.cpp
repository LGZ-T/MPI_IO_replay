#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "preprocess.h"


using namespace std;

// well, I know it's ugly. Don't laugh. -_-!
int display_shortest_edit_script(ostream& fout, int k, int d, int x, vector<vector<int>*>& storage, str_hmap_list& a, str_hmap_list& b);

// TODO: test version, find edit script of strings, final ver should read MPI traces properly
int find_shortest_edit(ostream& fout, str_hmap_list& a, str_hmap_list& b)
{
	const int N = a.size() - 1;
	const int M = b.size() - 1;
	const int MAX = N + M;

	// v[k] stores the furthest reaching D-path's row index(x) in diagonal k(means k=x-y)
	vector<int> v(2*MAX+1);

	// all indexes of vector should have the form of v[???+zero]
	const int zero = MAX;

	vector<vector<int>*> storage(MAX);

	v[zero+1] = 0;

	int x, y;
	for (int d=0; d<=MAX; d++) {
		for (int k=-d; k<=d; k+=2){
			if (k==-d || (v[k-1+zero] < v[k+1+zero] && k!=d))
				x = v[k+1+zero];
			else
				x = v[k-1+zero] + 1;

			y = x - k;

			while (x<N && y<M && a[x+1] == b[y+1]) {
				x++;
				y++;
			}
			v[k+zero] = x;

			cout << "diagonal k=" << k << " with depth d=" << d << " stop at (" << x << "," << y << ")" << endl;

			if (x>=N && y>=M) {
				display_shortest_edit_script(fout, k, d, x, storage, a, b);
				return d;
			}
		}

		// store the current vector
		storage[d] = new vector<int>(2*d+1);

		vector<int>::iterator iter_begin, iter_end;
		iter_begin = v.begin() + zero - d;
		iter_end = v.begin() + zero + d + 1;
		copy(iter_begin, iter_end, (*storage[d]).begin());

		for (int i=0; i<2*d+1; i++)
			cout << (*storage[d])[i] << " ";
		cout << endl; 

		copy((*storage[d]).begin(), (*storage[d]).end(), ostream_iterator<int>(cout, " "));
		cout << endl;
	}
	return -1;
}

int display_shortest_edit_script(ostream& fout, int k, int d, int value, vector<vector<int>*>& storage, str_hmap_list& a, str_hmap_list& b)
{
	cout << endl;
	cout << "Display here." << endl;
	cout << "k:" << k << " d:" << d << " value:" << value << endl;

	if (d == 0) {
        if (value > 0)
            fout << "keep " << value << endl;
		return 0;
    }

	int x = value;
	int y = x - k;

    // the length of snake
    int keep = 0;

	// strip the snake
	do {
		value = x;
		cout << "k:" << k << " d:" << d << " value:" << value << endl;

		int middle = d-1;
	
		if ((*storage[d-1])[k+1+middle] == value) {
			display_shortest_edit_script(fout, k+1, d-1, value, storage, a, b);

			cout << "vectical edge from (" << value << "," << (value - (k+1)) << ") to " << "(" << value << "," << value-k << ")" << endl; 
            // insert unique element in string B
            fout << "insert " << b[value-k] << endl;

            // output snake
            if (keep > 0)
                fout << "keep " << keep << endl;

			break;
		}
		else if ((*storage[d-1])[k-1+middle] == value-1) {
			display_shortest_edit_script(fout, k-1, d-1, value-1, storage, a, b);
			cout << "horizontal edge from (" << value-1 << "," << value-1-(k-1) << ") to " << "(" << value << "," << value-k << ")" << endl;
			//fout << "delete " << value-1 << endl;
            fout << "delete 1" << endl;

            if (keep > 0)
                fout << "keep " << keep << endl;

            break;
		}
		else {
			cout << "strip snake" << endl;
            keep++;
		}
		
	} while(a[x--] == b[y--]);

	return 0;
}

// merge adjacent del
void post_process(const char* temp_filename, const char* filename)
{
    ifstream fin(temp_filename);
    ofstream fout(filename);

    string line;
    string last = "";

    // number of delete
    int nd = 0;
    
    while (getline(fin, line)) {
        if (line.find("d") != 0) {
            if (last != "")
                fout << last << endl;

            last = line;
            continue;   // not del
        }

        if (last.find("d") != 0) {
            if (last != "")
                fout << last << endl;

            nd = 1;
            last = line;
        }
        else {
            nd++;
            last = "delete " + to_string(nd);
        }
        cout << line << endl;
    }
    fout << last << endl;
}

int main(void)
{
    // Note: the first element in la and lb must be NULL(or sth like it), because the algorithm will ignore the first element
	string a("../input_data/zhangyou_IOR/log.0");
	string b("../input_data/zhangyou_IOR/log.1");
	Preprocess<str_hmap_list, str_hmap> ppa(a);
	ppa.run();	
    ppa.data_print();
    str_hmap_list la = ppa.get_data();

	Preprocess<str_hmap_list, str_hmap> ppb(b);
	ppb.run();	
    ppb.data_print();
    str_hmap_list lb = ppb.get_data();

    const char* temp_filename = "lcs_diff_output_temp";
    ofstream fout(temp_filename);
    const char* filename = "lcs_diff_output";

	int r = find_shortest_edit(fout, la, lb);
    
	cout << "The edit distance between strings is " << r << endl;
    
    post_process(temp_filename, filename);

	return 0;
}
