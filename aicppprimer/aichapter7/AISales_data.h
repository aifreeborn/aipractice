/*
 * =============================================================================
 *
 *       Filename:  Sales_data.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020年06月14日 12时21分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#ifndef AISALES_DATA_H_
#define AISALES_DATA_H_

#include <iostream>
#include <string>

struct AISales_data {
    std::string isbn() const { return book_no; }
    AISales_data &combine(const AISales_data&);
    double avg_price() const;

    std::string book_no;
    unsigned units_sold = 0; // 销量
    double revenue = 0.0;    // 总销售收入
};

AISales_data ai_sales_add(const AISales_data&, const AISales_data&);
std::ostream &ai_sales_print(std::ostream&, const AISales_data&);
std::istream &ai_sales_read(std::istream&, AISales_data&);

#endif /* end AISALES_DATA_H_ */
