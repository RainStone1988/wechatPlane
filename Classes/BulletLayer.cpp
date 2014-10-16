
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

	this->schedule(schedule_selector(BulletLayer::startShoot), 0.2f);


	return true;
}

void BulletLayer::startShoot(float interval)
{
	auto winSize = Director::getInstance()->getWinSize();
	auto heroPos = HeroLayer::getInstance()->getHeroPosition();
	auto heroSize = HeroLayer::getInstance()->getHeroContentSize();

	// 创建并保存bullet
	auto bullet = Bullet::create(bulletType::bullet1);
	this->addChild(bullet);
	m_vecBullets.pushBack(bullet);

	// 设置bullet初始位置
	bullet->getBullet()->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	bullet->setPosition(heroPos.x, heroPos.y + heroSize.height);

	auto b3 = bullet->getBoundingBoxInGL();

	// bullet飞行动作
	auto desPos = Vec2(bullet->getPositionX(), winSize.height+bullet->getBullet()->getBoundingBox().size.height);
	auto actMove = MoveTo::create(bullet->getSpeed(), desPos);
	auto actDone = CallFuncN::create(CC_CALLBACK_1(BulletLayer::removeBullet, this));
	auto seq = Sequence::create(actMove, actDone, NULL);
	bullet->runAction(seq);
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
