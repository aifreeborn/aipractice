/*
 * =============================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2022年01月24日 21时54分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include <iostream>
#include "Picture.h"

char *init[] = {"Paris", "in the", "Spring"};

int main()
{
    Picture p(init, 3);
    std::cout << p << std::endl;

    Picture q = frame(p);
    std::cout << q << std::endl;

    Picture r = p | q;
    std::cout << r << std::endl;

    Picture s = q & r;
    std::cout << s << std::endl << frame(s) << std::endl;
}
