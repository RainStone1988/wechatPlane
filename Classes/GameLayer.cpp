
#include "GameLayer.h"
#include "HeroLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "GameOverLayer.h"
#include "ControlLayer.h"

GameLayer::GameLayer()
	: m_pBackground1(NULL)
	, m_pBackground2(NULL)
	, m_pHeroLayer(NULL)
	, m_pBulletLayer(NULL)
	, m_pEnemyLayer(NULL)
	, m_pControlLayer(NULL)
	, m_nScore(0)
{

}
GameLayer::~GameLayer()
{

}

Scene* GameLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = GameLayer::create();
	scene->addChild(layer);

	return scene;
}

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();

	// 加载游戏资源
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");


	// 加载游戏背景
	m_pBackground1 = Sprite::createWithSpriteFrameName("background.png");
	this->addChild(m_pBackground1);

	auto bg1Size = m_pBackground1->getContentSize();
	m_pBackground1->setAnchorPoint(Vec2::ZERO);
	m_pBackground1->setPosition(Vec2::ZERO);

	m_pBackground2 = Sprite::createWithSpriteFrameName("background.png");
	this->addChild(m_pBackground2);

	m_pBackground2->setAnchorPoint(Vec2::ZERO);
	m_pBackground2->setPosition(0, bg1Size.height - 2);

	// 背景滚动
	this->schedule(schedule_selector(GameLayer::backgroundMove), 0.01f);

	// 加载hero
	m_pHeroLayer = HeroLayer::create();
	this->addChild(m_pHeroLayer);
	
	// 加载bullet
	m_pBulletLayer = BulletLayer::create();
	this->addChild(m_pBulletLayer);

	// 加载enemy
	m_pEnemyLayer = EnemyLayer::create();
	this->addChild(m_pEnemyLayer);

	//
	m_pControlLayer = ControlLayer::create();
	this->addChild(m_pControlLayer);


	// 每帧更新
	this->schedule(schedule_selector(GameLayer::gameUpdate));

	return true;
}

void GameLayer::backgroundMove(float duration)
{
	m_pBackground1->setPositionY(m_pBackground1->getPositionY() - 2);
	m_pBackground2->setPositionY(m_pBackground1->getPositionY() + m_pBackground1->getContentSize().height - 2);

	if (m_pBackground2->getPositionY() == 0)
	{
		m_pBackground1->setPositionY(0);
	}
}

void GameLayer::gameUpdate(float interval)
{
	for (auto tag : m_pBulletLayer->m_vecBullets)
	{
		auto bullet = static_cast<Bullet*>(tag);
		if (bulletCollisionEnemy(bullet))
		{
			break;
		}
	}

	if (enemyCollisionHero())
	{
		auto back = GameOverLayer::createScene(m_nScore);
		Director::getInstance()->replaceScene(back);
	}
}

bool GameLayer::bulletCollisionEnemy(Bullet* bullet)
{
	for (auto tagEnemy : m_pEnemyLayer->m_vecEnemys)
	{
		auto enemy = static_cast<Enemy*>(tagEnemy);
		if (bullet->getBoundingBoxInGL().intersectsRect(enemy->getBoundingBoxInGL()))
		{
			auto life = enemy->getLife() - bullet->getDamage();

			if (life <= 0)
			{
				m_nScore += enemy->getScore();
				if (m_nScore > g_MAX_SCORE)
				{
					m_nScore = g_MAX_SCORE;
				}
				m_pControlLayer->updateScore(m_nScore);

				m_pBulletLayer->removeBullet(bullet);
				m_pEnemyLayer->removeEnemys(enemy);
			}
			else
			{
				m_pBulletLayer->removeBullet(bullet);
				enemy->setLife(life);
			}

			return true;
		}
	}

	return false;
}

bool GameLayer::enemyCollisionHero()
{
	for (auto& tag : m_pEnemyLayer->m_vecEnemys)
	{
		auto enemy = static_cast<Enemy*>(tag);
		if (m_pHeroLayer->getHero()->getBoundingBox().intersectsRect(enemy->getBoundingBoxInGL()))
		{
// 			m_pEnemyLayer->removeEnemys(enemy);
// 			m_pHeroLayer->removeHero();

			m_pBulletLayer->unscheduleAllSelectors();
			m_pEnemyLayer->unscheduleAllSelectors();
			this->unscheduleAllSelectors();

			return true;
		}
	}

	return false;
}