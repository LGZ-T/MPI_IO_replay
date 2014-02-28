#include "merge_two_logs.h"
#include "datatype.h"
#include <vector>

using namespace std;

// support 2-power logs only, but I guess it's enough
template<typename T>
T * excursive_merge(vector<string> logs, T data)
{
	T *data1,  *data2;
	vector<string> vector1, vector2;
	vector<string>::iterator itb, ite;

	if (logs.size() > 2) {
		for (itb=logs.begin(), ite=(logs.end() - 1); itb < ite; itb++, ite-- ) {
			vector1.push_back(*itb);
			vector2.insert(vector2.begin(), *ite);
		}

		data1 = excursive_merge(vector1, data);
		data2 = excursive_merge(vector2, data);
		cout << "Initialize data merge..." << endl;
		MergeTwoLogs<str_hmap_list, str_hmap> m1(data1, data2);
		cout << "Data merge begin..." << endl;
		m1.merge();
		data1 = m1.get_result();
		cout << vector1[0] << " and " << vector2[0] << " merged" << endl;
	}
	else {
		MergeTwoLogs<str_hmap_list, str_hmap> m2(logs[0], logs[1]);
		m2.merge();
		data1 = m2.get_result();
		cout << logs[0] << " and " << logs[1] << " merged" << endl;
	}

	return data1;
}

int main(void)
{
	string prefix = "../input_data/zhangyou_IOR/log.";
	vector<string> files { prefix + "0", prefix + "1", prefix + "2", prefix + "3", prefix + "4", prefix + "5", prefix + "6", prefix + "7" };
	str_hmap_list data;
	cout << "Merge begin..." << endl;
	excursive_merge(files, data);

	return 0;
}

