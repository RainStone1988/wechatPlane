
#include "GameLayer.h"
#include "HeroLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "ControlLayer.h"
#include "UFOLayer.h"

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
	
	// background
	m_pBackground1 = Sprite::createWithSpriteFrameName("background.png");
	this->addChild(m_pBackground1);

	auto bg1Size = m_pBackground1->getContentSize();
	m_pBackground1->setAnchorPoint(Vec2::ZERO);
	m_pBackground1->setPosition(Vec2::ZERO);

	m_pBackground2 = Sprite::createWithSpriteFrameName("background.png");
	this->addChild(m_pBackground2);

	m_pBackground2->setAnchorPoint(Vec2::ZERO);
	m_pBackground2->setPosition(0, bg1Size.height - 2);

	// backgroundMove
	this->schedule(schedule_selector(GameLayer::backgroundMove), 0.01f);

	// hero
	m_pHeroLayer = HeroLayer::create();
	this->addChild(m_pHeroLayer);
	
	// bullet
	m_pBulletLayer = BulletLayer::create();
	this->addChild(m_pBulletLayer);

	// 加载enemy
	m_pEnemyLayer = EnemyLayer::create();
	this->addChild(m_pEnemyLayer);

	// Control
	m_pControlLayer = ControlLayer::create();
	this->addChild(m_pControlLayer);

	// UFO
	m_pUFOLayer = UFOLayer::create();
	this->addChild(m_pUFOLayer);


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
		m_pBulletLayer->unscheduleAllSelectors();
		m_pEnemyLayer->unscheduleAllSelectors();
		m_pUFOLayer->unscheduleAllSelectors();
		this->unscheduleAllSelectors();

		m_pHeroLayer->blowup(m_nScore);
	}

	auto ufoDbBlt = m_pUFOLayer->getDoubleBullets();
	if (NULL == ufoDbBlt)
	{
		return;
	}

	auto doulbeBulletsBox = ufoDbBlt->getBoundingBox();
	auto heroBox = m_pHeroLayer->getHero()->getBoundingBox();
	if (heroBox.intersectsRect(doulbeBulletsBox))
	{
		m_pUFOLayer->removeDoubleBullets(m_pUFOLayer->getDoubleBullets());
		m_pBulletLayer->stopSingleShoot();
		m_pBulletLayer->startDoubleShoot();
		m_pBulletLayer->startSingleShoot(6.2f);
	}
}

bool GameLayer::bulletCollisionEnemy(Bullet* bullet)
{
	for (auto tagEnemy : m_pEnemyLayer->m_vecEnemys)
	{
		auto enemy = static_cast<Enemy*>(tagEnemy);
		auto emyBox = enemy->getBoundingBox();
		auto bltBox = bullet->getBoundingBox();

		if (bltBox.intersectsRect(emyBox))
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
	if (m_pHeroLayer->getLiveStatus())
	{
		auto heroBox = m_pHeroLayer->getHero()->getBoundingBox();
		heroBox.origin.x += 20;
		heroBox.origin.y += 20;
		heroBox.size.width -= 40;
		heroBox.size.height -= 40;

		for (auto& tag : m_pEnemyLayer->m_vecEnemys)
		{
			auto enemy = static_cast<Enemy*>(tag);
			if (heroBox.intersectsRect(enemy->getBoundingBox()))
			{
				return true;
			}
		}
	}

	return false;
}