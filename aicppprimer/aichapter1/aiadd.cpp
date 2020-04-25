/*
 * =============================================================================
 *
 *       Filename:  aiadd.cpp
 *
 *    Description:  计算两个数的和并显示
 *
 *        Version:  1.0
 *        Created:  04/23/2020 06:39:39 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include <iostream>


/************************************ main ************************************/
int main(int argc, char *argv[])
{
    int v1 = 0, v2 = 0;

    std::cout << "Enter two numbers:" << std::endl;
    std::cin >> v1 >> v2;
    std::cout << "The sum of " << v1 << " and " << v2
        << " is " << v1 + v2 << std::endl;

    return 0;
}

