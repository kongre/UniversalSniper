//
//  FightMapController.cpp
//  UniversalSniper
//
//  Created by 排骨 on 14-12-17.
//
//

#include "FightMapController.h"
#include "../GameObject/UConstant.h"

enum ChildZOrderNum {
    Default_Zorder = 0,
    MaskTexture_Zorder = 1,
};

FightMapController::FightMapController()
{
    m_node = NULL;
    m_zoomOutScale = 2;
    m_baseScale = 1;
    m_mapScrollByFinger = false;
    m_zoomOutState = false;
    m_maskTexture = NULL;
}

FightMapController::~FightMapController()
{
    
}

FightMapController* FightMapController::controllerWithNode(cocos2d::CCNode *node, float baseScale)
{
    FightMapController *pController = new FightMapController();
    if (pController && pController->initWithNode(node,baseScale)) {
        pController->autorelease();
        return pController;
    }
    CC_SAFE_DELETE(pController);
    return NULL;
}

bool FightMapController::initWithNode(cocos2d::CCNode *node, float baseScale)
{
    bool bRet = false;
    do {
        m_node = node;
        m_baseScale = baseScale;
        m_originalPoint = m_node->getPosition();
        
        bRet = true;
    } while (0);
    return bRet;
}

void FightMapController::setTouchEnableWithPriority(int priority)
{
    this -> setTouchEnabled(true);
    this -> setTouchPriority(priority);
}

void FightMapController::setTouchEnableMoveRect(cocos2d::CCRect rect)
{
    m_touchMoveEnableRect = rect;
}

void FightMapController::setBoundingRect(float widthOffset, float heightOffset)
{
    float nodeZoomOutWidth = m_node->getContentSize().width*m_baseScale*m_zoomOutScale;
    float nodeZoomOutHeight = m_node->getContentSize().height*m_baseScale*m_zoomOutScale;
    m_minWidthOffset = m_node->getPositionX()-nodeZoomOutWidth/2+widthOffset;
    m_maxWidthOffset = m_node->getPositionX()+nodeZoomOutWidth/2-widthOffset;
    m_minHeightOffset = m_node->getPositionY()-nodeZoomOutHeight/2+heightOffset;
    m_maxHeightOffset = m_node->getPositionY()+nodeZoomOutHeight/2-heightOffset;
}

//以某点为中心放大
void FightMapController::zoomOutOnPoint(CCPoint zoomOutOnPoint)
{
    m_zoomOutState = true;
    this -> addMaskTexture();
    CCPoint offsetPos = ccpSub(zoomOutOnPoint,m_originalPoint);
    offsetPos = ccpMult(offsetPos, m_zoomOutScale);
    CCPoint newPos = ccpSub(m_originalPoint, offsetPos);
    newPos = getNewPosWhenScroll(newPos);
    m_node->runAction(CCSpawn::createWithTwoActions(CCScaleTo::create(0.2, m_baseScale*m_zoomOutScale), CCMoveTo::create(0.2, newPos)));
}

//恢复到原始图片大小
void FightMapController::zoomToOriganlState()
{
    CCLOG("zoomToOriganlState");
    m_zoomOutState = false;
    this->hideMaskTexture();
    m_node -> setScale(m_baseScale);
    m_node -> setPosition(m_originalPoint);
}

void FightMapController::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    if (it != pTouches->end())
    {
        CCTouch *pTouch = (CCTouch*)*it;
        CCPoint pTouchPoint = pTouch->getLocationInView();
        pTouchPoint = CCDirector::sharedDirector()->convertToGL(pTouchPoint);
        
        if (m_zoomOutState) {
            if (m_touchMoveEnableRect.containsPoint(pTouchPoint)) {
                m_mapScrollByFinger = true;
            }else{
                zoomToOriganlState();
            }
        }else{
            zoomOutOnPoint(pTouchPoint);
        }
    }
}

void FightMapController::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if (m_mapScrollByFinger) {
        CCTouch *touch = (CCTouch*)pTouches->anyObject();
        CCPoint diff = touch->getDelta();
        CCPoint currentPos = m_node->getPosition();
        CCPoint newPos = ccpAdd(currentPos, diff);
        newPos = getNewPosWhenScroll(newPos);
        m_node->setPosition(newPos);
    }
}

void FightMapController::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    m_mapScrollByFinger = false;
}

CCPoint FightMapController::getNewPosWhenScroll(cocos2d::CCPoint newPos)
{
    newPos.x =MIN(newPos.x, m_maxWidthOffset);
    newPos.x = MAX(newPos.x, m_minWidthOffset);
    
    newPos.y = MIN(newPos.y, m_maxHeightOffset);
    newPos.y = MAX(newPos.y, m_minHeightOffset);
    return newPos;
}

void FightMapController::addMaskTexture()
{
    if (!m_maskTexture) {
        CCSize pWinSize = CCDirector::sharedDirector()->getWinSize();
        m_maskTexture = CCRenderTexture::create(pWinSize.width, pWinSize.height, kCCTexture2DPixelFormat_RGBA8888);
        m_maskTexture -> setPosition(ccp(pWinSize.width/2, pWinSize.height/2));
        this -> addChild(m_maskTexture,MaskTexture_Zorder);
        
        CCSprite *m_mask = CCSprite::create("image/sniperscope_0.png");
        m_mask ->setScale(m_baseScale);
        m_mask->setPosition(ccp(pWinSize.width*0.5, pWinSize.height*0.5));
        
        ccBlendFunc blend;
        blend.src = GL_ONE;
        blend.dst = GL_ZERO;
        m_mask->setBlendFunc(blend);
        
        m_maskTexture->clear(0,0,0,1.0f);
        m_maskTexture->begin();
        m_mask->visit();
        m_maskTexture->end();
        
    }else{
        m_maskTexture -> setVisible(true);
    }
}

void FightMapController::hideMaskTexture()
{
    m_maskTexture -> setVisible(false);
}
