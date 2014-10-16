
#include "HeroLayer.h"

HeroLayer::HeroLayer()
{

}
HeroLayer::~HeroLayer()
{

}

HeroLayer* HeroLayer::s_pHeroLayer = NULL;

HeroLayer* HeroLayer::getInstance()
{
	return s_pHeroLayer;
}

HeroLayer* HeroLayer::create()
{
	s_pHeroLayer = new HeroLayer;
	if (NULL != s_pHeroLayer && s_pHeroLayer->init())
	{
		s_pHeroLayer->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(s_pHeroLayer);
	}

	return s_pHeroLayer;
}

bool HeroLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();

	// ¼ÓÔØhero
	m_pHero = Sprite::createWithSpriteFrameName("hero1.png");
	this->addChild(m_pHero);

	m_pHero->setScale(0.7f);
	m_pHero->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	m_pHero->setPosition(winSize.width/2, 0);

	// ´¥Ãþ¼àÌý
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(HeroLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HeroLayer::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool HeroLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void HeroLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
	Vec2 local = touch->getLocation();
	Vec2 preLocal = touch->getPreviousLocation();
	m_pHero->setPosition(m_pHero->getPosition() + local - preLocal);
}

Vec2 HeroLayer::getHeroPosition()
{
	return m_pHero->getPosition();
}

Size HeroLayer::getHeroContentSize()
{
	return m_pHero->getContentSize();
}

Sprite* HeroLayer::getHero()
{
	return m_pHero;
}

void HeroLayer::removeHero()
{
	this->removeChild(m_pHero);
}