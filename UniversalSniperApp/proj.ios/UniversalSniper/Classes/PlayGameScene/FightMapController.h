//
//  FightMapController.h
//  UniversalSniper
//
//  Created by 排骨 on 14-12-17.
//
//战斗场景地图缩放控制类

#ifndef __UniversalSniper__FightMapController__
#define __UniversalSniper__FightMapController__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class FightMapController:public CCLayer
{
public:
    static FightMapController* controllerWithNode(CCNode* node, float baseScale);
    void setTouchEnableWithPriority(int priority);
    void setBoundingRect(float widthOffset, float heightOffset);
    void setTouchEnableMoveRect(CCRect rect);//触摸并可以滑动的有效范围
    
private:
    FightMapController();
    ~FightMapController();
    bool initWithNode(CCNode *node, float baseScale);
    
    void zoomOutOnPoint(CCPoint zoomOutOnPoint);
    void zoomToOriganlState();
    CCPoint getNewPosWhenScroll(CCPoint newPos);
    
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
private:
    CCNode *m_node;
    CCPoint m_originalPoint;//node 原始位置
    float m_baseScale;//node 原始scale
    float m_zoomOutScale;//放大的倍数，以m_baseScale为基准
    
    bool m_zoomOutState;//是否处于放大状态
    CCRect m_touchMoveEnableRect;//触摸并可以滑动的有效范围
    bool m_mapScrollByFinger;//地图背景是否跟随手指滑动
    
    float m_maxWidthOffset;//移动最大偏移width
    float m_minWidthOffset;//移动最小偏移width
    float m_maxHeightOffset;//移动最大偏移height
    float m_minHeightOffset;//移动最小偏移height
};

#endif /* defined(__UniversalSniper__FightMapController__) */
