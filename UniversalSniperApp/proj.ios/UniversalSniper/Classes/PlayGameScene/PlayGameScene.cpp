//
//  PlayGameScene.cpp
//  UniversalSniper
//
//  Created by 排骨 on 14-12-17.
//
//

#include "PlayGameScene.h"
#include "FightMapLayer.h"

PlayGameScene::PlayGameScene()
{
    
}

PlayGameScene::~PlayGameScene()
{
    
}

CCScene* PlayGameScene::scene()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
    CCScene *pScene = CCScene::create();
    FightMapLayer *pLayer = FightMapLayer::create();
    pScene->addChild(pLayer);
    return pScene;
}