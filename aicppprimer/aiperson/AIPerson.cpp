/*
 * =============================================================================
 *
 *       Filename:  AIPerson.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020年09月23日 22时18分25秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include <iostream>
#include "AIPerson.h"


std::istream &read(std::istream &is, AIPerson &per)
{
    is >> per.name >> per.address;
    return is;
}

std::ostream &print(std::ostream &os, AIPerson &per)
{
    os << per.get_name() << per.get_address();
    return os;
}
