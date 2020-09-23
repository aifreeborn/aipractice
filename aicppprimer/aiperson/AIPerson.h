/*
 * =============================================================================
 *
 *       Filename:  AIPerson.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020年09月23日 22时17分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#ifndef AIPERSON_H_
#define AIPERSON_H_

#include <string>
#include <iostream>

class AIPerson {
    friend std::istream &read(std::istream &is, AIPerson &per);
    friend std::ostream &print(std::ostream &os, AIPerson &per);
    public:
        std::string get_name() const { return name; };
        std::string get_address() const { return address; };

    private:
        std::string name;
        std::string address;
};

std::istream &read(std::istream &is, AIPerson &per);
std::ostream &print(std::ostream &os, AIPerson &per);

#endif /* AIPERSON_H_ */
