/*
 * =============================================================================
 *
 *       Filename:  AIScreen.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020年09月30日 15时55分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#ifndef AISCREEN_H_
#define AISCREEN_H_

#include <iostream>
#include <string>

class AIScreen {
    public:
        // 类中定义的类型名也存在访问权限,也可使用：
        // using pos_t = std::string::size_type;
        // 类型必须先定义后使用，故一般放在类的最开始
        typedef std::string::size_type pos_t;

        AIScreen() = default;
        AIScreen(pos_t ht, pos_t wd, char ch)
            : height(ht), width(wd), contents(ht * wd, ch) { /* empty */ };
        AIScreen(pos_t ht = 0, pos_t wd = 0)
            : cursor(0), height(ht), width(wd), contents(ht * wd, ' ') { /* empty */ }

        // 读取光标处的字符, 隐式内联
        char get() const { return contents[cursor]; }
        // 显式内联
        inline char get(pos_t row, pos_t col) const;

        AIScreen &set(char ch);
        AIScreen &set(pos_t row, pos_t col, char ch);
        // 在之后设为内联
        AIScreen &move(pos_t row, pos_t col);
        void some_member() const;
        void show() const;
        AIScreen &display(std::ostream &os)
            { do_display(os); return *this; }
        const AIScreen &display(std::ostream &os) const
            { do_display(os); return *this; }

    private:
        pos_t cursor = 0;
        pos_t height = 0, width = 0;
        std::string contents;
        // 可变数据成员：即使在一个const对象内也能被修改
        mutable size_t access_ctr = 0;

    private:
        void do_display(std::ostream &os) const { os << contents; }
};

// 指定行r，列c，返回字符
char AIScreen::get(pos_t row, pos_t col) const
{
    pos_t r_pos = row * width;

    return contents[r_pos + col];
}

inline AIScreen &AIScreen::set(char ch)
{
    contents[cursor] = ch;
    return *this;
}

inline AIScreen &AIScreen::set(pos_t row, pos_t col, char ch)
{
    contents[row * width + col] = ch;
    return *this;
}

// 最好只在类的外部定义的地方说明inline（如下），inline成员函数也应该与相应
// 的类定义在同一个头文件中.
inline AIScreen &AIScreen::move(pos_t row, pos_t col)
{
    pos_t r_pos = row * width;
    cursor = r_pos + col;
    return *this;
}

inline void AIScreen::some_member() const
{
    ++access_ctr;
    std::cout << "access_ctr: " << access_ctr << std::endl;
}

inline void AIScreen::show() const
{
    pos_t i, j;

    for (i = 0; i < width; i++) {
        for (j = 0; j < height; j++) {
            std::cout << contents[i * width + j];
        }
        std::cout << std::endl;
    }
}

#endif /* AISCREEN_H_ */
