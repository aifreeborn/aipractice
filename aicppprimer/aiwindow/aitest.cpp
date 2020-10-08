/*
 * =============================================================================
 *
 *       Filename:  aitest.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020年09月30日 17时07分35秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#include <cstdlib>
#include "AIScreen.h"

int main(int argc, char *argv[])
{
#if 0
    AIScreen myscreen(10, 10, '#');

    char ch = myscreen.get();
    std::cout << "ch = " << ch << std::endl;
    ch = myscreen.get(0, 1);
    std::cout << "ch = " << ch << std::endl;

    myscreen.move(4, 0).set('@');

    AIScreen tmp = myscreen.move(5, 1);
    tmp.set('a');
#endif
    AIScreen myscreen(5, 3);
    const AIScreen blank(5, 3);

    std::cout << 'S';
    myscreen.set('#').display(std::cout);
    std::cout << 'S';
    blank.display(std::cout);
    std::cout << 'S' << std::endl;

    //myscreen.show();
    return EXIT_SUCCESS;
}
