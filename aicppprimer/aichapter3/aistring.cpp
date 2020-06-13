/*
 * =============================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/09/2020 12:40:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

/************************************ main ************************************/
int main()
{
#if 0
	// 读取一整行不空则显示
    string line;

    cout << "Please input: ";
    while (getline(cin, line))
        if (!line.empty()) {
            cout << "-> " << line << endl;
            cout << "-> string size is " << line.size() << endl;
            cout << "Please input: ";
        }
    cout << endl;
#endif
#if 1
	// 计算标点符号的个数
	string str("hello world!!!");
	decltype(str.size()) punct_cnt = 0;

	for (auto c : str)
		if (ispunct(c))
			punct_cnt++;
	cout << punct_cnt
		<< " punctuation characters in " << str << endl;
#endif

    return 0;
}

