
#include "EnemyLayer.h"
#include "Enemy.h"

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
	this->schedule(schedule_selector(EnemyLayer::addEnemy2), 3.0f);
	

	return true;
}

void EnemyLayer::addEnemy1(float interval)
{
	auto enemy = Enemy::create(enemyType::enemy1);
	this->addChild(enemy);
	m_vecEnemys.pushBack(enemy);

	setEnemyPos(enemy);

	runEnemyAct(enemy, 4.0f);
}

void EnemyLayer::addEnemy2(float interval)
{
	auto enemy = Enemy::create(enemyType::enemy2);
	this->addChild(enemy);
	m_vecEnemys.pushBack(enemy);

	setEnemyPos(enemy);

	runEnemyAct(enemy, 5.5f);
}

void EnemyLayer::setEnemyPos(Enemy* enemy)
{
	auto winSize = Director::getInstance()->getWinSize();
	auto enemySize = enemy->getEnemy()->getBoundingBox().size;

	auto min = 0;
	auto max = winSize.width - enemySize.width;
	int range = max - min;
	float actual = rand()%range + min;

	enemy->getEnemy()->setAnchorPoint(Vec2::ZERO);
	enemy->getEnemy()->setPosition(actual, winSize.height);
}

void EnemyLayer::runEnemyAct(Enemy* enemy, int nSpeed)
{
//	auto winsSize = Director::getInstance()->getWinSize();
	auto enemySize = enemy->getEnemy()->getBoundingBox().size;
	auto enemyPos = enemy->getEnemy()->getPosition();
	
	auto actMove = MoveTo::create(nSpeed, Vec2(enemyPos.x, -enemySize.height));
	auto actDone = CallFuncN::create(CC_CALLBACK_1(EnemyLayer::removeEnemys, this));
	auto seq = Sequence::create(actMove, actDone, NULL);
	enemy->getEnemy()->runAction(seq);
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