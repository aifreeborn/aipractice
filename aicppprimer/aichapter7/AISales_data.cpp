/*
 * =============================================================================
 *
 *       Filename:  AISales_data.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020年06月14日 14时28分23秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include "AISales_data.h"

AISales_data::AISales_data(std::istream &is)
{
    ai_sales_read(is, *this);
}

double AISales_data::avg_price() const
{
    if (units_sold)
        return revenue / units_sold;
    else 
        return 0;
}

AISales_data &AISales_data::combine(const AISales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

std::istream &ai_sales_read(std::istream &is, AISales_data &item)
{
    double price = 0.0;
    is >> item.book_no >> item.units_sold >> price;
    item.revenue = price * item.units_sold;
    return is;
}

std::ostream &ai_sales_print(std::ostream &os, const AISales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " "
        << item.revenue << " " << item.avg_price();
    return os;
}

AISales_data ai_sales_add(const AISales_data &lhs, const AISales_data &rhs)
{
    AISales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}
