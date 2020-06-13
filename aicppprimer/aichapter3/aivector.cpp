#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	int i;
	vector<int> nums;

	while (cin >> i) {
		nums.push_back(i);
	};
	
	for (auto j : nums)
		cout << j << ' ';
	cout << endl;
	return 0;
}
