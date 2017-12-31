#include "source2.h"
#include <iostream>
using namespace std;

int main()
{
	Triehard2 * test = new Triehard2();
	cout << "success! Created test" << endl;
	int x[3] = {0,1,0};
	int y[5] = {1,0,1,1,0};
	int z[1] = {0};
	int a[7] = {1,0,1,1,0,0,0};
	int b[7] = {0,1,1,0,0,1,1};
	test->insert(x, 3);
	cout << "success! inserted x" << endl;
	test->insert(a, 7);
	cout << "success! inserted a" << endl;
	test->insert(y, 5);
	cout << "success! inserted y" << endl;
	test->insert(y, 5);
	cout << "success! inserted y" << endl;
	test->insert(y, 5);
	cout << "success! inserted y" << endl;
	test->insert(z, 1);
	cout << "success! inserted z" << endl;
	test->insert(b, 7);
	cout << "success! inserted b" << endl;
	test->myPrintIsBetterThanYoursLogan();
	cout << "Print Done!" << endl;
	test->cut(y, 5);
	cout << "success! cut y" << endl;
	test->myPrintIsBetterThanYoursLogan();
	delete test;
	cout << "success! Completed test" << endl;
	//while(1);
}
