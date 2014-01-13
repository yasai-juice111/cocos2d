//
//  AppMacros.h
//  Nyanshuffle
//
//  Created by cocos2d-x on 14/01/13.
//
//

#ifndef _AppMacros_h
#define _AppMacros_h

#include "cocos2d.h"

typedef struct tagResource
{
    cocos2d::CCSize size;
    char directory[100];

}Resource;

static Resource smallResource = { cocos2d::CCSizeMake(512, 384), "S"};
static Resource mediumResource = { cocos2d::CCSizeMake(1024, 768), "M"};
static Resource largeResource = { cocos2d::CCSizeMake(2048, 1536), "L"};


static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(1024, 768);

#define LEVEL_FONT_SIZE (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / mediumResource.size.width * 48);

#endif //__AppMacros_h__
