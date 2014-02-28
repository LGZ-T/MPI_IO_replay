#include <string>
#include "merge_two_logs.h"

// unit test
int main()
{
	string file1("../input_data/zhangyou_IOR/log.0");
	string file2("../input_data/zhangyou_IOR/log.1");

	MergeTwoLogs<str_hmap_list, str_hmap> m(file1, file2, 5, 0.05);
	m.merge();
}
