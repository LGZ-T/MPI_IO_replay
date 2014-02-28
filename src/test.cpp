#include <iostream>

class TestC{
public:
	TestC()
	{
		std::cout << "C" << std::endl;
	}
	void call(void)
	{
		TestA * aa = new TestA();
		aa->call();
	}
};


int main(void)
{
	//Preprocess<str_hmap_list, str_hmap> pp("xxx");
	//pp.run();
	
	TestC* c = new TestC();
	c->call();

	return 0;
}
