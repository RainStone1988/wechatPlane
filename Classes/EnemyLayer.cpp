
#include "EnemyLayer.h"
#include "Enemy.h"
#include "common.h"

EnemyLayer::EnemyLayer()
{

}
EnemyLayer::~EnemyLayer()
{

}

bool EnemyLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->schedule(schedule_selector(EnemyLayer::addEnemy1), 1.0f);
	this->schedule(schedule_selector(EnemyLayer::addEnemy2), 5.0f);
	this->schedule(schedule_selector(EnemyLayer::addEnemy3), 15.0f);
	

	return true;
}

void EnemyLayer::addEnemy1(float interval)
{
	auto enemy = Enemy::create(enemyType::enemy1);
	this->addChild(enemy);
	m_vecEnemys.pushBack(enemy);

	setEnemyPos(enemy);
	runEnemyAct(enemy);
}

void EnemyLayer::addEnemy2(float interval)
{
	auto enemy = Enemy::create(enemyType::enemy2);
	this->addChild(enemy);
	m_vecEnemys.pushBack(enemy);

	setEnemyPos(enemy);
	runEnemyAct(enemy);
}

void EnemyLayer::addEnemy3(float interval)
{
	auto enemy = Enemy::create(enemyType::enemy3);
	this->addChild(enemy);
	m_vecEnemys.pushBack(enemy);

	setEnemyPos(enemy);
	runEnemyAct(enemy);
}

void EnemyLayer::setEnemyPos(Enemy* enemy)
{
	auto winSize = Director::getInstance()->getWinSize();
	auto enemySize = enemy->getEnemy()->getBoundingBox().size;

	auto min = 0;
	auto max = winSize.width - enemySize.width;
	auto actual = getRandom(min, max);

	enemy->getEnemy()->setAnchorPoint(Vec2::ZERO);
	enemy->setPosition(actual, winSize.height);
}

void EnemyLayer::runEnemyAct(Enemy* enemy)
{
	auto enemySize = enemy->getEnemy()->getBoundingBox().size;
	auto enemyPos = enemy->getPosition();
	
	auto actMove = MoveTo::create(enemy->getSpeed(), Vec2(enemyPos.x, -enemySize.height));
	auto actDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::removeEnemys, this));
	auto seq = Sequence::create(actMove, actDone, NULL);
	enemy->runAction(seq);
}

void EnemyLayer::removeEnemys(Node* pNode)
{
	if (NULL != pNode)
	{
		auto enemy = static_cast<Enemy*>(pNode);
		this->removeChild(enemy);
		m_vecEnemys.eraseObject(enemy);
	}
}