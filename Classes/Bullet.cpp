
#include "Bullet.h"


Bullet::Bullet()
{

}
Bullet::~Bullet()
{

}

Bullet* Bullet::create(bulletType type)
{
	Bullet* pRet = new Bullet;
	if (pRet && pRet->init(type))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

bool Bullet::init(bulletType type)
{
	m_pBullet = Sprite::createWithSpriteFrameName(s_bulletAttr[type].sImage);
	this->addChild(m_pBullet);

	m_nDamage = s_bulletAttr[type].nDamage;
	m_fSpeed = s_bulletAttr[type].fSpeed;

	return true;
}

Rect Bullet::getBoundingBox() const
{
	auto rc = m_pBullet->getBoundingBox();
	auto org = this->convertToWorldSpace(rc.origin);
	return Rect(org.x, org.y, rc.size.width, rc.size.height);
}