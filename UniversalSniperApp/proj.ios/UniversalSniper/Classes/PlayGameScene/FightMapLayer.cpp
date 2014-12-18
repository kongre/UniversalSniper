//
//  FightMapLayer.cpp
//  UniversalSniper
//
//  Created by 排骨 on 14-12-17.
//
//

#include "FightMapLayer.h"
#include "../GameObject/UConstant.h"
#include "FightMapController.h"

FightMapLayer::FightMapLayer()
{
    
}

FightMapLayer::~FightMapLayer()
{
    
}

void FightMapLayer::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
}

FightMapLayer* FightMapLayer::create()
{
    FightMapLayer *pLayer = new FightMapLayer();
    if (pLayer && pLayer->init()) {
        pLayer->autorelease();
        return pLayer;
    }
    CC_SAFE_DELETE(pLayer);
    return NULL;
}

bool FightMapLayer::init()
{
    bool bRet = false;
    do {
        this -> setMapContent();
        bRet = true;
    } while (0);
    return bRet;
}

void FightMapLayer::setMapContent()
{
    CCSize pWinSize = CCDirector::sharedDirector()->getWinSize();
    float pScale = pWinSize.height/BASE_HEIGHT;
    CCSprite *mapSprite = CCSprite::create("image/play_game_scene.jpg");
    mapSprite -> setPosition(ccp(pWinSize.width/2, pWinSize.height/2));
    this -> addChild(mapSprite);
    
    FightMapController *pMapController = FightMapController::controllerWithNode(mapSprite, pScale);
    pMapController -> setTouchEnableMoveRect(CCRectMake(0, 0, pWinSize.width/2, pWinSize.height*0.3));
    pMapController->setBoundingRect(pWinSize.width*0.2, pWinSize.height*0.2);
    pMapController -> setTouchEnableWithPriority(0);
    this -> addChild(pMapController);
    
    CCLayerColor *pLayerColor = CCLayerColor::create(ccc4(200, 0, 0, 255), 10, 10);
    pLayerColor->setPosition(ccp(pWinSize.width/2, pWinSize.height/2));
    pLayerColor -> setAnchorPoint(ccp(0.5, 0.5));
    this -> addChild(pLayerColor);
}
