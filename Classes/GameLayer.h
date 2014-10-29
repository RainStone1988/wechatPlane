
#include "cocos2d.h"

USING_NS_CC;

class HeroLayer;
class BulletLayer;
class EnemyLayer;
class Bullet;
class ControlLayer;
class UFOLayer;

const int g_MAX_SCORE = 100000000;

class GameLayer : public Layer
{
CC_CONSTRUCTOR_ACCESS:
	GameLayer();

	virtual bool init() override;

	void backgroundMove(float duration);

	void gameUpdate(float interval);

	bool bulletCollisionEnemy(Bullet* bullet);

	bool enemyCollisionHero();

public:
	~GameLayer();

	CREATE_FUNC(GameLayer);

	static Scene* createScene();

private:
	Sprite*			m_pBackground1;
	Sprite*			m_pBackground2;

	HeroLayer*		m_pHeroLayer;
	BulletLayer*	m_pBulletLayer;
	EnemyLayer*		m_pEnemyLayer;
	ControlLayer*	m_pControlLayer;
	UFOLayer*		m_pUFOLayer;

	int				m_nScore;
};