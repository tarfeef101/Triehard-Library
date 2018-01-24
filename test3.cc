#include "source3.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	Triehard * test = new Triehard();
	cout << "success! Created test" << endl;
	vector<int> x = {1,2,3};
	vector<int> y = {5,7,7,7,5};
	vector<int> z = {5};
	vector<int> a = {5,7,7,8,9};
	vector<int> b = {1,2};
	cout << "Search result for searching 123: " << test->search(&x) << endl;
	test->insert(&x);
	cout << "success! inserted x" << endl;
	test->insert(&a);
	cout << "success! inserted a" << endl;
	test->insert(&y);
	cout << "success! inserted y" << endl;
	test->insert(&z);
	cout << "success! inserted z" << endl;
	test->insert(&b);
	cout << "success! inserted b" << endl;
	test->myPrintIsBetterThanYoursLogan();
	cout << "Print Done!" << endl;
	cout << "Search result for 57775: " << test->search(&y) << endl;
	cout << "Compression rate compared to a standard trie: " << test->compressionovertrie() << endl;
	cout << "Compression rate compared to a list of lists: " << test->compressionoverdict() << endl;
	test->cut(&y);
	cout << "success! cut y" << endl;
	test->myPrintIsBetterThanYoursLogan();
	cout << "Search result for 57775: " << test->search(&y) << endl;
	delete test;
	cout << "success! Completed test" << endl;
	//while(1);
}
