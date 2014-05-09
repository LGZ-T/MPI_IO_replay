#include <iostream>
#include <vector>
#include <string>

using namespace std;

// TODO: test version, find edit script of strings, final ver should read MPI traces properly
int find_shortest_edit(string& a, string& b)
{
	const int N = a.size() - 1;
	const int M = b.size() - 1;
	const int MAX = N + M;

	// v[k] stores the furthest reaching D-path's row index(x) in diagonal k(means k=x-y)
	vector<int> v(2*MAX+1);

	// all indexes of vector should have the form of v[???+zero]
	const int zero = MAX + 1;

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

			if (x>=N && y>=M)
				return d;

			cout << "diagonal k=" << k << " with depth d=" << d << " stop at (" << x << "," << y << ")" << endl;
		}
	}
	return -1;
}

int main(void)
{
	string a = " abcabba";
	string b = " cbabac";

	int r = find_shortest_edit(a, b);

	cout << "The edit distance between strings is " << r << endl;

	return 0;
}
