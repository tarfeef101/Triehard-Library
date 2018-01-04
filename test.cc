#include "source1.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	Triehard * test = new Triehard();
	cout << "success! Created test" << endl;
	vector<int> x = {0,1,0};
	vector<int> y = {1,0,1,1,0};
	vector<int> z = {0};
	vector<int> a = {1,0,1,1,0,0,0};
	vector<int> b = {0,1,1,0,0,1,1};
	cout << "Search result for searching 010: " << test->search(&x) << endl;
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
	cout << "Search result for 10110: " << test->search(&y) << endl;
	cout << "Compression rate compared to a standard trie: " << test->compressionovertrie() << endl;
	cout << "Compression rate compared to a list of lists: " << test->compressionoverdict() << endl;
	test->cut(&y);
	cout << "success! cut y" << endl;
	test->myPrintIsBetterThanYoursLogan();
	cout << "Search result for 10110: " << test->search(&y) << endl;
	delete test;
	cout << "success! Completed test" << endl;
	//while(1);
}
