
#ifndef __H_ENEMY_H_
#define __H_ENEMY_H_

#include "cocos2d.h"

USING_NS_CC;

enum enemyType
{
	enemy1 = 0,
	enemy2,
	enemy3,
};

typedef struct _tagEnemyAttribute
{
	enemyType		eType;
	std::string		sImage;
	int				nLife;
	float			fSpeed;
	int				nScore;
}EnemyAttr;

static const EnemyAttr s_EnemyAttr[] = 
{
	{enemyType::enemy1,	"enemy1.png",		10,		4.0f,	10},
	{enemyType::enemy2,	"enemy2.png",		80,		5.5f,	100},
	{enemyType::enemy3,	"enemy3_n1.png",	160,	7.0f,	200}
};


class Enemy : public Node
{
CC_CONSTRUCTOR_ACCESS:
	Enemy();

	bool init(enemyType type);

public:
	~Enemy();

	static Enemy* create(enemyType type);

	virtual Rect getBoundingBox() const;

CC_SYNTHESIZE_READONLY(	Sprite*,	m_pEnemy,	Enemy)
CC_SYNTHESIZE(			int,		m_nLife,	Life)
CC_SYNTHESIZE_READONLY(	float,		m_fSpeed,	Speed)
CC_SYNTHESIZE_READONLY(	int,		m_nScore,	Score)
};

#endif // __H_ENEMY_H_