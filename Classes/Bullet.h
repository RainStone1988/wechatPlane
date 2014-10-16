
#include "cocos2d.h"

USING_NS_CC;

enum bulletType
{
	bullet1	= 0,
	bullet2,
};
typedef struct _tagBulletAttribute
{
	bulletType	etype;
	std::string	sImage;
	int			nDamage;
	float		fSpeed;
}BulletAttr;

static const BulletAttr s_bulletAttr[] = 
{
	{bulletType::bullet1, "bullet1.png", 10, 1.0f},
	{bulletType::bullet2, "bullet2.png", 20, 1.0f}
};

class Bullet : public Node
{
CC_CONSTRUCTOR_ACCESS:
	Bullet();

public:
	~Bullet();

	bool init(bulletType type);

	static Bullet* create(bulletType type);

	Rect getBoundingBoxInGL();
	
CC_SYNTHESIZE_READONLY(Sprite*, m_pBullet, Bullet)
CC_SYNTHESIZE_READONLY(int, m_nDamage, Damage)
CC_SYNTHESIZE_READONLY(float, m_fSpeed, Speed)
};