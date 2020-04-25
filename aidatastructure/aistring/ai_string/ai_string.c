/*
 * =============================================================================
 *
 *       Filename:  string.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/16/2020 11:19:31 PM
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


#define MAXSIZE 20
enum ai_ret{
    AI_OK = 0,
    AI_ERROR
};

enum ai_bool{
    AI_FALSE = 0,
    AI_TRUE
};


typedef enum ai_ret status_t;
typedef enum ai_bool bool_t;
typedef char string_t[MAXSIZE + 1];  // string[0]存放字符串的长度

// 用常量字符串chars初始化str字符串
status_t string_assign(string_t str, char *chars)
{
    int i;
    size_t str_len;

    str_len = strlen(chars);
    if (str_len > MAXSIZE) {
        return AI_ERROR;
    } else {
        str[0] = str_len;
        for (i = 1; i <= str[0]; i++)
            str[i] = *(chars + i - 1);
        return AI_OK;
    }
}

status_t string_copy(string_t des, string_t src)
{
    int i;

    for (i = 0; i <= src[0]; i++)
        des[i] = src[i];

    return AI_OK;
}

bool_t string_is_empty(string_t str)
{
    if (0 == str[0])
        return AI_TRUE;
    return AI_FALSE;
}

status_t string_get_lenth(string_t str)
{
    return str[0];
}

int string_compare(string_t str1, string_t str2)
{
    int i;

    for (i = 1; i <= str1[0] && i <= str2[0]; i++)
        if (str1[i] != str2[i])
            return str1[i] - str2[i];
    return str1[0] - str2[0];
}

status_t string_concat(string_t con, string_t s1, string_t s2)
{
    int i;

    if (s1[0] + s2[0] <= MAXSIZE) {
        for (i = 1; i <= s1[0]; i++)
            con[i] = s1[i];
        for (i = 1; i <= s2[0]; i++)
            con[s1[0] + i] = s2[i];
        con[0] = s1[0] + s2[0];
        return AI_TRUE;
    } else {
        for (i = 1; i <= s1[0]; i++)
            con[i] = s1[i];
        for (i = 1; i <= MAXSIZE - s2[0]; i++)
            con[s1[0] + i] = s2[i];
        con[0] = MAXSIZE;
        return AI_FALSE;
    }
}

status_t string_get_substr(string_t substr, string_t str, int pos, int len)
{
    int i;

    if (pos < 1 || pos > str[0] || len < 0 || len > str[0] - pos + 1)
        return AI_ERROR;
    for (i = 1; i <= len; i++)
        substr[i] = str[pos + i - 1];
    substr[0] = len;
    return AI_OK;
}


void string_print(char *preface, string_t str)
{
    int i;

    printf("%s: ", preface);
    for (i = 1; i <= str[0]; i++)
        printf("%c", str[i]);
    printf("\n");
}

/************************************ main ************************************/
int main(int argc, char *argv[])
{
    string_t str1, str2;

    string_assign(str1, "hello, ");
    string_print("str1", str1);
    string_assign(str2, "java.");
    string_print("str2", str2);

    printf("str1 length: %d\n", string_get_lenth(str1));
    printf("str2 length: %d\n", string_get_lenth(str2));

    printf("str1 %s str2\n", string_compare(str1, str2) > 0 ? ">" 
                    : string_compare(str1, str2) == 0 ? "=" : "<");

    // string_copy(str1, str2);
    // string_print("str1", str1);
    // string_print("str2", str2);
    // printf("str1 %s str2\n", string_compare(str1, str2) > 0 ? ">" 
    //                 : string_compare(str1, str2) == 0 ? "=" : "<");

    string_t con;
    string_concat(con, str1, str2);
    string_print("con", con);

    string_get_substr(str1, con, 2, 5);
    string_print("str1: ", str1);


    return 0;
}
