
#include "cocos2d.h"

USING_NS_CC;

enum bulletType
{
	kBullet1	= 0,
	kBullet2,

	kMax,
};

typedef struct _tagBulletAttr
{
	std::string	sImage;
	int			nDamage;
	float		fSpeed;

}BulletAttr;

static const BulletAttr s_bulletAttr[bulletType::kMax] = 
{
	{"bullet1.png",	10,	1.0f},
	{"bullet2.png",	10,	1.0f}
};

class Bullet : public Node
{
CC_CONSTRUCTOR_ACCESS:
	Bullet();

public:
	~Bullet();

	static Bullet* create(bulletType);

	bool init(bulletType);

	virtual Rect getBoundingBox() const;

CC_SYNTHESIZE_READONLY(Sprite*, m_pBullet, Bullet)
CC_SYNTHESIZE(int, m_nDamage, Damage)
CC_SYNTHESIZE(float, m_fSpeed, Speed)
};