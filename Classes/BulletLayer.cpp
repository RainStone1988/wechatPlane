
#include "BulletLayer.h"
#include "HeroLayer.h"

BulletLayer::BulletLayer()
{

}
BulletLayer::~BulletLayer()
{

}

bool BulletLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	startSingleShoot(0.0f);

	return true;
}

void BulletLayer::startSingleShoot(float delay)
{
	this->schedule(schedule_selector(BulletLayer::addSingleBullet), 0.2f, kRepeatForever, delay);
}
void BulletLayer::stopSingleShoot()
{
	this->unschedule(schedule_selector(BulletLayer::addSingleBullet));
}
void BulletLayer::addSingleBullet(float interval)
{
	this->addBulletByType(bulletType::kBullet1);
}

void BulletLayer::startDoubleShoot()
{
	this->schedule(schedule_selector(BulletLayer::addDoubleBullet), 0.2f, 30, 0.0f);
}
void BulletLayer::addDoubleBullet(float interval)
{
	this->addBulletByType(bulletType::kBullet2);
}

void BulletLayer::removeBullet(Node* pNode)
{
	if (NULL != pNode)
	{
		auto bullet = static_cast<Bullet*>(pNode);
		this->removeChild(bullet);
		m_vecBullets.eraseObject(bullet);
	}
}
void BulletLayer::addBulletByType(bulletType type)
{
	auto winSize = Director::getInstance()->getWinSize();
	auto heroSize = HeroLayer::getInstance()->getHeroContentSize();
	auto heroPos = HeroLayer::getInstance()->getHeroPosition();

	if (bulletType::kBullet1 == type)
	{
		auto blt1 = Bullet::create(type);
		this->addChild(blt1);
		this->m_vecBullets.pushBack(blt1);

		blt1->setPosition(heroPos.x, heroPos.y+heroSize.height);

		auto actMv = MoveTo::create(1.0f, Vec2(heroPos.x, winSize.height));
		auto actDone = CallFuncN::create(CC_CALLBACK_1(BulletLayer::removeBullet, this));
		auto seq = Sequence::create(actMv, actDone, NULL);
		blt1->runAction(seq);
	}
	else if (bulletType::kBullet2 == type)
	{
		auto bltL = Bullet::create(type);
		auto bltR = Bullet::create(type);
		this->addChild(bltL);
		this->addChild(bltR);
		this->m_vecBullets.pushBack(bltL);
		this->m_vecBullets.pushBack(bltR);

		auto bltSize = bltR->getBullet()->getBoundingBox().size;
		const auto distance = bltSize.width*3;
		auto posL = Vec2(heroPos.x-distance/3-bltSize.width/2, heroPos.y+heroSize.height);
		auto posR = Vec2(heroPos.x+distance/3+bltSize.width/2, heroPos.y+heroSize.height);
		bltL->setPosition(posL);
		bltR->setPosition(posR);


		auto actMv = MoveTo::create(1.0f, Vec2(posL.x, winSize.height));
		auto actDone = CallFuncN::create(CC_CALLBACK_1(BulletLayer::removeBullet, this));
		auto seq = Sequence::create(actMv, actDone, NULL);
		bltL->runAction(seq);

		actMv = MoveTo::create(1.0f, Vec2(posR.x, winSize.height));
		actDone = CallFuncN::create(CC_CALLBACK_1(BulletLayer::removeBullet, this));
		seq = Sequence::create(actMv, actDone, NULL);
		bltR->runAction(seq);
	}
}