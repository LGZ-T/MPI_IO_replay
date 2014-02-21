#include <string>
#include "mergetwologs.h"

// unit test
int main()
{
	string file1("../input_data/root1_IOR/log.0");
	string file2("../input_data/root1_IOR/log.1");

	MergeTwoLogs<str_hmap_list, str_hmap> m(file1, file2, 5, 0.05);
	m.merge();
}
