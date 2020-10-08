/*
 * =============================================================================
 *
 *       Filename:  AIWindow_mgr.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2020年09月30日 16时29分04秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  takeno (takeno2020), takeno2020@163.com
 *   Organization:  
 *
 * =============================================================================
 */
#ifndef AIWINDOW_MGR_H_
#define AIWINDOW_MGR_H_

#include <iostream>
#include <string>
#include "AIScreen.h"

class AIWindow_mgr {
    private:
        std::vector<AIScreen> screens{AIScreen(24, 80, ' ')};
        
};

#endif /* AIWINDOW_MGR_H_ */
