
#include "UFOLayer.h"
#include "common.h"

UFOLayer::UFOLayer()
	: m_pDoubleBullets(NULL)
{

}
UFOLayer::~UFOLayer()
{

}

bool UFOLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->schedule(schedule_selector(UFOLayer::addDoubleBullets), 20.0f);

	return true;
}

void UFOLayer::addDoubleBullets(float interval)
{
	m_pDoubleBullets = Sprite::createWithSpriteFrameName("ufo1.png");
	this->addChild(m_pDoubleBullets);

	auto winSize = Director::getInstance()->getWinSize();
	auto bltSize = m_pDoubleBullets->getBoundingBox().size;

	m_pDoubleBullets->setAnchorPoint(Vec2::ZERO);
	int min = 0;
	int max = winSize.width - bltSize.width;
	int actualX = getRandom(min, max);
	m_pDoubleBullets->setPosition(actualX, winSize.height);

	auto actMove = MoveTo::create(3.0f, Vec2(actualX, -bltSize.height));
	auto actDone = CallFuncN::create(CC_CALLBACK_1(UFOLayer::removeDoubleBullets, this));
	auto seq = Sequence::create(actMove, actDone, NULL);
	m_pDoubleBullets->runAction(seq);
}

void UFOLayer::removeDoubleBullets(Node* pNode)
{
	if (NULL != pNode)
	{
		auto doubleBullets = static_cast<Sprite*>(pNode);
		this->removeChild(doubleBullets);

		m_pDoubleBullets = NULL;
	}
}