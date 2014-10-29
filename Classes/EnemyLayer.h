
#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;


class EnemyLayer : public Layer
{
CC_CONSTRUCTOR_ACCESS:
	EnemyLayer();

	virtual bool init() override;

	void setEnemyPos(Enemy* enemy);

	void runEnemyAct(Enemy* enemy);


public:
	~EnemyLayer();

	CREATE_FUNC(EnemyLayer);

	void addEnemy1(float interval);
	void addEnemy2(float interval);
	void addEnemy3(float interval);

	void removeEnemys(Node* pNode);

public:
	Vector<Enemy*> m_vecEnemys;
};