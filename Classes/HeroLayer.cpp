
#include "HeroLayer.h"
#include "GameOverLayer.h"

HeroLayer::HeroLayer()
	: m_pHero(NULL)
	, m_bLive(true)
	, m_nScore(0)
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
	if (m_bLive)
	{
		auto winSize = Director::getInstance()->getWinSize();
		auto heroSize = m_pHero->getBoundingBox().size;

		auto local = touch->getLocation();
		auto preLocal = touch->getPreviousLocation();
		auto realPos = m_pHero->getPosition() + (local - preLocal);

		if (realPos.x < heroSize.width/2)
		{
			realPos.x = heroSize.width/2;
		}
		else if (realPos.x > (winSize.width - heroSize.width/2))
		{
			realPos.x = (winSize.width - heroSize.width/2);
		}

		if (realPos.y < 0)
		{
			realPos.y = 0;
		}
		else if (realPos.y > (winSize.height-heroSize.height))
		{
			realPos.y = (winSize.height - heroSize.height);
		}

		m_pHero->setPosition(realPos);
	}
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
	auto back = GameOverLayer::createScene(m_nScore);
	Director::getInstance()->replaceScene(back);
}

void HeroLayer::blowup(int score)
{
	m_bLive = false;
	m_nScore = score;

	auto animation = AnimationCache::getInstance()->getAnimation("hero_blowup");
	auto animate = Animate::create(animation);
	auto over = CallFuncN::create(CC_CALLBACK_0(HeroLayer::removeHero, this));
	auto seq = Sequence::create(animate, over, NULL);
	m_pHero->runAction(seq);
}