//
//  GameScene.cpp
//  Nyanshuffle
//
//  Created by cocos2d-x on 14/01/13.
//
//

#include "GameScene.h"
#include "Animation.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace std;
using namespace CocosDenshion;

CCScene* GameScene::scene()
{
    CCScene* scene = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    
    return scene;
}

void GameScene::playDropingSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("rakka.mp3");
}

void GameScene::showCountdown()
{
    this->scheduleOnce(schedule_selector(GameScene::playCountdownSound),0.5);
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    CCSprite* pNum3 = CCSprite::create("3.png");
    pNum3->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    pNum3->setScale(0);
    pNum3->runAction(Animation::num3Animation());
    this->addChild(pNum3, 1);
    
    CCSprite* pNum2 = CCSprite::create("2.png");
    pNum2->setPosition(pNum3->getPosition());
    pNum2->setScale(0);
    pNum2->runAction(Animation::num2Animation());
    this->addChild(pNum2, 1);
    
    CCSprite* pNum1 = CCSprite::create("1.png");
    pNum1->setPosition(pNum3->getPosition());
    pNum1->setScale(0);
    pNum1->runAction(Animation::num1Animation());
    this->addChild(pNum1, 1);
    
    CCSprite* pGo = CCSprite::create("go.png");
    pGo->setPosition(pNum3->getPosition());
    pGo->setScale(0);
    pGo->runAction(Animation::num0Animation(this, callfunc_selector(GameScene::startShuffle)));
    this->addChild(pGo, 1);
}

void GameScene::playCountdownSound()
{
    SimpleAudioEngine::sharedEngine()->playEffect("countDown.mp3");
}

void GameScene::startShuffle()
{
    m_totalShuffleTime = 0;
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameBgm.mp3", true);
    this->schedule(schedule_selector(GameScene::boxesShuffle));
}

CCMenuItemImage* GameScene::getLeftBox()
{
    if(m_pBox1->getTag() == kBoxLocation_Left)
        return m_pBox1;
    else if(m_pBox2->getTag() == kBoxLocation_Left)
        return m_pBox2;
    else
        return m_pBox3;
}

CCMenuItemImage* GameScene::getCenterBox()
{
    if(m_pBox1->getTag() == kBoxLocation_Center)
        return m_pBox1;
    else if(m_pBox2->getTag() == kBoxLocation_Center)
        return m_pBox2;
    else
        return m_pBox3;
}

CCMenuItemImage* GameScene::getRightBox()
{
    if(m_pBox1->getTag() == kBoxLocation_Right)
        return m_pBox1;
    else if(m_pBox2->getTag() == kBoxLocation_Right)
        return m_pBox2;
    else
        return m_pBox3;
}

void GameScene::shufflePattern1(float time)
{
    // 左から中央へ
    CCMenuItemSprite* leftBox = getLeftBox();
    leftBox->runAction(Animation::moveFromLeftToCenter(time));
    
    // 中央かた左から
    CCMenuItemSprite* centerBox = getCenterBox();
    centerBox->runAction(Animation::moveFromCenterToLeft(time));
    
    leftBox->setTag(kBoxLocation_Center);
    centerBox->setTag(kBoxLocation_Left);
}

void GameScene::shufflePattern2(float time)
{
    // 左から右へ
    CCMenuItemSprite* leftBox = getLeftBox();
    leftBox->runAction(Animation::moveFromLeftToRight(time));
    
    // 右かた左から
    CCMenuItemSprite* rightBox = getCenterBox();
    rightBox->runAction(Animation::moveFromRightToLeft(time));
    
    leftBox->setTag(kBoxLocation_Right);
    rightBox->setTag(kBoxLocation_Left);
}

void GameScene::shufflePattern3(float time)
{
    //中央から右へ
    CCMenuItemSprite* centerBox = getLeftBox();
    centerBox->runAction(Animation::moveFromCenterToRight(time));
    
    // 右かた左から
    CCMenuItemSprite* rightBox = getRightBox();
    rightBox->runAction(Animation::moveFromRightToCenter(time));
    
    centerBox->setTag(kBoxLocation_Right);
    rightBox->setTag(kBoxLocation_Center);
}

void GameScene::shufflePattern4(float time)
{
    //左から右へ
    CCMenuItemSprite* leftBox = getLeftBox();
    leftBox->runAction(Animation::moveFromCenterToRight(time));
    
    // 中央かた左へ
    CCMenuItemSprite* centerBox = getCenterBox();
    centerBox->runAction(Animation::moveFromCenterToLeft(time));

    // 右かた中央へ
    CCMenuItemSprite* rightBox = getRightBox();
    rightBox->runAction(Animation::moveFromRightToCenter(time));
    
    leftBox->setTag(kBoxLocation_Right);
    centerBox->setTag(kBoxLocation_Left);
    rightBox->setTag(kBoxLocation_Center);
}

void GameScene::shufflePattern5(float time)
{
    //左から中央へ
    CCMenuItemSprite* leftBox = getLeftBox();
    leftBox->runAction(Animation::moveFromLeftToCenter(time));
    
    // 中央かた右へ
    CCMenuItemSprite* centerBox = getCenterBox();
    centerBox->runAction(Animation::moveFromCenterToRight(time));
    
    // 右かた中央へ
    CCMenuItemSprite* rightBox = getRightBox();
    rightBox->runAction(Animation::moveFromRightToCenter(time));
    
    leftBox->setTag(kBoxLocation_Center);
    centerBox->setTag(kBoxLocation_Right);
    rightBox->setTag(kBoxLocation_Left);
}

void GameScene::boxesShuffle(float time)
{
    m_totalShuffleTime += time;
    
    // 箱のアクション中は処理を続ける
    if(m_pBox1->getActionByTag(TAG_ACTION) ||
       m_pBox2->getActionByTag(TAG_ACTION) ||
       m_pBox3->getActionByTag(TAG_ACTION))
        return;
    
    // 5秒敬した場合はシャッフル終了
    if (m_totalShuffleTime > 5)
    {
        this->unschedule(schedule_selector(GameScene::boxesShuffle));
        this->scheduleOnce(schedule_selector(GameScene::afterShuffle), 0.2);
        return;
    }
    
    const float shuffleTime = 0.5;
    float activeShuffleTime;
    
    // シャッフル時間のの指定
    switch (rand() % 5)
    {
        case 0: activeShuffleTime = shuffleTime * 0.90; break;
        case 1: activeShuffleTime = shuffleTime * 0.95; break;
        case 2: activeShuffleTime = shuffleTime * 1.00; break;
        case 3: activeShuffleTime = shuffleTime * 1.05; break;
        default: activeShuffleTime = shuffleTime * 1.10; break;
    }
    
    // シャッフルパターンの指定
    switch (rand() % 5)
    {
        case 0: shufflePattern1(activeShuffleTime); break;
        case 1: shufflePattern2(activeShuffleTime); break;
        case 2: shufflePattern3(activeShuffleTime); break;
        case 3: shufflePattern4(activeShuffleTime); break;
        default:shufflePattern5(activeShuffleTime); break;
    }
}

void GameScene::afterShuffle()
{
}

bool GameScene::init()
{
    if(!CCLayer::init())
    {
        return false;
    }
    
    srand((unsigned int)time(NULL));
    int randum = rand();
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    // 背景表示
    CCSprite* pBG = CCSprite::create("game_bg.png");
    pBG->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    this->addChild(pBG);
    
    CCSize bgSize = pBG->getContentSize();
    
    // 雲のアクション作成
    CCMoveBy* cloud1Action = CCMoveBy::create(80, ccp(bgSize.width, 0));
    CCMoveBy* cloud2Action = CCMoveBy::create(160, ccp(bgSize.width, 0));
    
    // 雲の表示
    CCSprite* pCloud1 = CCSprite::create("cloud.png");
    pCloud1->setPosition(ccp(bgSize.width * 0.4, bgSize.height * 0.83));
    pCloud1->runAction(cloud1Action);
    pBG->addChild(pCloud1);
    
    CCSprite* pCloud2 = CCSprite::create("cloud.png");
    pCloud2->setPosition(ccp(bgSize.width * 0.2, bgSize.height * 0.9));
    pCloud2->setScale(0.6);
    pCloud2->runAction(cloud2Action);
    pBG->addChild(pCloud2);
    
    
    // 猫の表示
    CCString* catImagePath = CCString::createWithFormat("cat%d.png", randum % 5 + 1);
    m_pCat = CCSprite::create(catImagePath->getCString());
    m_pCat->setPosition(ccp(size.width * 0.5, size.height * 0.5));
    m_pCat->runAction(Animation::catStartACtion());
    this->addChild(m_pCat, 0);
    
    // 箱の表示
    CCString* boxFileName = CCString::createWithFormat("box%d.png", randum % 2 + 1);
    m_pBox1 = CCMenuItemImage::create(boxFileName->getCString(), boxFileName->getCString(), NULL, NULL);
    m_pBox1->setPosition(ccp(size.width * 0.2, size.height * 0.5 + size.height));
    m_pBox1->runAction(Animation::boxesStartACtion(this, callfunc_selector(GameScene::playDropingSound)));
    m_pBox1->setTag(kBoxLocation_Left);
    
    m_pBox2 = CCMenuItemImage::create(boxFileName->getCString(), boxFileName->getCString(), NULL, NULL);
    m_pBox2->setPosition(ccp(size.width * 0.5, size.height * 0.5 + size.height));
    m_pBox2->runAction(Animation::boxesStartActionWithVibration(this, callfunc_selector(GameScene::playDropingSound)));
    m_pBox1->setTag(kBoxLocation_Center);
    
    m_pBox3 = CCMenuItemImage::create(boxFileName->getCString(), boxFileName->getCString(), NULL, NULL);
    m_pBox3->setPosition(ccp(size.width * 0.8, size.height * 0.5 + size.height));
    m_pBox3->runAction(Animation::boxesStartACtion(this, callfunc_selector(GameScene::playDropingSound)));
    m_pBox1->setTag(kBoxLocation_Right);
    
    CCMenu* menu = CCMenu::create(m_pBox1, m_pBox2, m_pBox3, NULL);
    menu->setPosition(CCPointZero);
    
    this->addChild(menu);
    
    // カウントダウン
    this->scheduleOnce(schedule_selector(GameScene::showCountdown), 1);
    
    return true;
}

