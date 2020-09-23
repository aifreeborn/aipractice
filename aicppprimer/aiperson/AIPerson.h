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

class AIPerson {
    public:
        string get_name() const { return name; };
        string get_address() const { return address };

    private:
        string name;
        string address;
};


#endif /* AIPERSON_H_ */
