//
//  Animation.h
//  Nyanshuffle
//
//  Created by cocos2d-x on 14/01/13.
//
//

#ifndef __Nyanshuffle__Animation__
#define __Nyanshuffle__Animation__

#include "cocos2d.h"

USING_NS_CC;

#define TAG_ACTION 1001

class Animation
{
public:
    static CCFiniteTimeAction* catStartACtion();
    
    static CCFiniteTimeAction* vibrationAnimation();
    static CCFiniteTimeAction* boxesStartACtion(CCObject* target, SEL_CallFunc selector);
    static CCFiniteTimeAction* boxesStartActionWithVibration(CCObject* target, SEL_CallFunc selector);
    
    static CCFiniteTimeAction* num3Animation();
    static CCFiniteTimeAction* num2Animation();
    static CCFiniteTimeAction* num1Animation();
    static CCFiniteTimeAction* num0Animation(CCObject* target, SEL_CallFunc selector);
    
    static CCFiniteTimeAction* moveFromLeftToCenter(float time);
    static CCFiniteTimeAction* moveFromLeftToRight(float time);
    static CCFiniteTimeAction* moveFromCenterToLeft(float time);
    static CCFiniteTimeAction* moveFromCenterToRight(float time);
    static CCFiniteTimeAction* moveFromRightToCenter(float time);
    static CCFiniteTimeAction* moveFromRightToLeft(float time);
    
};

#endif /* defined(__Nyanshuffle__Animation__) */
