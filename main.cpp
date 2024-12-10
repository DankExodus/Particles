#include "Vector.h"

using namespace Vector;

int main()
{
	vector<int> v;
	v.push_back(5);
	v.push_back(6);
	cout << v << endl;

	vector<int> v2 = v;
	vector<int> v3;
	v3 = v2;
	cout << v3 << endl;
}