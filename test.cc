#include "source1.h"
#include <iostream>
using namespace std;

int main()
{
	Triehard * test = new Triehard();
	cout << "success!" << endl;
	int x[4] = {0,1,0};
	cout << "success!" << endl;
	int y[5] = {1,0,1,1,0};
	cout << "success!" << endl;
	test->insert(x, 3);
	cout << "success!" << endl;
	test->print();
	/*test->insert(y, 5);
	cout << "success!" << endl;
	test->cut(x, 4);
	cout << "success!" << endl;
	delete test;
	cout << "success!" << endl;
	while(1);*/
}
