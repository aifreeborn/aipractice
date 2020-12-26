/*
 * =============================================================================
 *
 *       Filename:  aiatoi.c
 *
 *    Description:  atoi函数的简单实现
 *
 *        Version:  1.0
 *        Created:  2020年12月26日 14时05分00秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include <stdio.h>

int aiatoi(const char *str)
{
    int sign = 1;
    long long num = 0;
    const char *digit = NULL;

    if (str != NULL && *str != '\0') {
        if (*str == '+') {
            str++;
            sign = 1;
        } else if (*str == '-') {
            str++;
            sign = -1;
        }

        digit = str;
        while (*digit != '\0') {
            if (*digit >= '0' && *digit <= '9') {
                num = num * 10 + sign * (*digit - '0');
                if (sign == 1 && num > (signed int)0x7fffffff) {
                    num = (signed int)0x7fffffff;
                    break;
                } else if (sign == -1 && num < (signed int)0x80000000) {
                    num = (signed int)0x80000000;
                    break;
                }
                digit++;
            } else {
                break;
            }
        }
    }

    printf("value --> %d\n", (int)num);
    return (int)num;
}

/************************************ main ************************************/
int main(int argc, char* argv[])
{
    char *nll = NULL;
    aiatoi(nll);

    aiatoi("");

    aiatoi("123");

    aiatoi("+123");

    aiatoi("-123");

    aiatoi("1a33");

    aiatoi("+0");

    aiatoi("-0");

    //有效的最大正整数, 0x7FFFFFFF
    aiatoi("+2147483647");    

    aiatoi("-2147483647");

    aiatoi("+2147483648");

    //有效的最小负整数,
    aiatoi("-2147483648");    

    aiatoi("+2147483649");

    aiatoi("-2147483649");

    aiatoi("+");

    aiatoi("-");

    return 0;
}
