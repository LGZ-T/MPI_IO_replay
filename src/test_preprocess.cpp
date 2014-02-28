#include <iostream>
#include "datatype.h"
#include "preprocess.h"

// unit test
int main(void)
{
	std::string file("../input_data/zhangyou_IOR/log.0");
	Preprocess<str_hmap_list, str_hmap> pp(file);
	pp.run();	
	pp.data_print();
}
