//
//  FightMapLayer.h
//  UniversalSniper
//
//  Created by 排骨 on 14-12-17.
//
//

#ifndef __UniversalSniper__FightMapLayer__
#define __UniversalSniper__FightMapLayer__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class FightMapLayer:public CCLayer
{
public:
    static FightMapLayer* create();
    
private:
    FightMapLayer();
    ~FightMapLayer();
    void onExit();
    bool init();
    void setMapContent();
    
private:
};

#endif /* defined(__UniversalSniper__FightMapLayer__) */
