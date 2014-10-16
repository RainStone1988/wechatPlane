
#include "cocos2d.h"
#include "Bullet.h"

USING_NS_CC;

class BulletLayer : public Layer
{
CC_CONSTRUCTOR_ACCESS:
	BulletLayer();

	virtual bool init() override;

public:
	~BulletLayer();

	CREATE_FUNC(BulletLayer);

	void startShoot(float interval);

	void removeBullet(Node* pNode);

public:
	Vector<Bullet*>		m_vecBullets;

private:

	int					m_nBulletDamage;
};