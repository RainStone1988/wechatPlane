
#include "Enemy.h"

Enemy::Enemy()
{

}
Enemy::~Enemy()
{

}

Enemy* Enemy::create(enemyType type)
{
	auto pRet = new Enemy;
	if (NULL != pRet && pRet->init(type))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;

}

bool Enemy::init(enemyType type)
{
	m_pEnemy	= Sprite::createWithSpriteFrameName(s_EnemyAttr[type].sImage);
	m_nLife		= s_EnemyAttr[type].nLife;
	m_fSpeed	= s_EnemyAttr[type].fSpeed;
	m_nScore	= s_EnemyAttr[type].nScore;

	this->addChild(m_pEnemy);

	return true;
}

Rect Enemy::getBoundingBoxInGL()
{
	auto rc = m_pEnemy->getBoundingBox();
	auto pos = this->convertToWorldSpace(rc.origin);
	return Rect(pos.x, pos.y, rc.size.width, rc.size.height);
}