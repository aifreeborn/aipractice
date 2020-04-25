/*
 * =============================================================================
 *
 *       Filename:  ai_kmp.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/21/2020 10:11:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAXSIZE 100


typedef char string_t[MAXSIZE + 1];  // string_t[0]存放字符串的长度


int str_assign(string_t str, char *chars)
{
    int i, len;

    len = strlen(chars);
    if (len > MAXSIZE)
        return -1;

    str[0] = len;
    for (i = 1; i <= len; i++) {
        str[i] = chars[i - 1];
    }
    return 0;
}

void str_print(char *preface, string_t str)
{
    int i;

    printf("%s: ", preface);
    for(i = 1; i <= str[0]; i++)
        printf("%c", str[i]);
    printf("\n");
}

// 朴素的模式匹配算法
int str_index(string_t str, string_t pattern, int pos)
{
    int i = pos;  // 用于主串的下标索引
    int j = 1;    // 用于模式串的索引

    while (i <= str[0] && j <= pattern[0]) {
        if (str[i] == pattern[j]) {
            i++;
            j++;
        } else {
            i = i - j + 2;
            j = 1;
        }
    }

    if (j > pattern[0])
        return i - pattern[0];
    else
        return -1;
}

int str_get_len(string_t str)
{
    return str[0];
}

// kmp模式匹配算法
void str_get_next(string_t str, int *next)
{
    int j, k; // j指向后缀字符，k指向前缀字符

    j = 1;
    k = 0;
    next[1] = 0;

    while (j < str[0]) {
        if (k == 0 || str[k] == str[j]) {
            k++;
            j++;
            next[j] = k;
        } else {
            k = next[k];
        }
    }
}

int str_index_kmp(string_t str, string_t pattern, int pos)
{
    int i = pos;
    int j = 1;
    int next[100];

    str_get_next(pattern, next);
    while (i <= str[0] && j <= pattern[0]) {
        if (j == 0 || str[i] == pattern[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }

    if (j > pattern[0])
        return i - pattern[0];
    else
        return -1;
}

void str_get_nextval(string_t str, int *next)
{
    int k, j;

    k = 0;
    j = 1;
    next[1] = 0;

    while (j < str[0]) {
        if (k == 0 || str[k] == str[j]) {
            k++;
            j++;
            if (str[k] != str[j])
                next[j] = k;
            else
                next[j] = next[k];
        } else {
            k = next[k];
        }
    }
}

int str_index_kmp1(string_t str, string_t pattern, int pos)
{
    int i = pos;
    int j = 1;

    int next[100];
    str_get_nextval(pattern, next);

    while (i <= str[0] && j <= pattern[0]) {
        if (j == 0 || str[i] == pattern[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }

    if (j > pattern[0])
        return i - pattern[0];
    else
        return -1;
}

/************************************ main ************************************/
int main(int argc, char *argv[])
{
    string_t str;

    str_assign(str, "hello world!");
    str_print("str", str);

    string_t s1, s2;
    str_assign(s1, "abcabcadfresfl");
    str_assign(s2, "cadf");
    str_print("s1", s1);
    str_print("s2", s2);
    printf("主串和子串在第%d个字符处首次匹配（朴素模式匹配算法）\n", str_index(s1, s2, 1));
    printf("主串和子串在第%d个字符处首次匹配（KMP算法）\n", str_index_kmp(s1, s2, 1));
    printf("主串和子串在第%d个字符处首次匹配（KMP改进的算法）\n", str_index_kmp1(s1, s2, 1));

    int *next, i;
    string_t s3;

    str_assign(s3, "abcabx");
    next = (int *)malloc((str_get_len(s3) + 1) * sizeof(int));
    str_get_next(s3, next);
    printf("next: ");
    for (i = 1; i < str_get_len(s3) + 1; i++) {
        printf("%d", next[i]);
    }
    printf("\n");

    str_get_nextval(s3, next);
    printf("next: ");
    for (i = 1; i < str_get_len(s3) + 1; i++) {
        printf("%d", next[i]);
    }
    printf("\n");


    return 0;
}
