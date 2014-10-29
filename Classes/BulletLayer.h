
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

	void startSingleShoot(float delay);
	void stopSingleShoot();
	void addSingleBullet(float interval);

	void startDoubleShoot();
	void addDoubleBullet(float interval);

	void removeBullet(Node* pNode);

	void addBulletByType(bulletType);

public:
	Vector<Bullet*>		m_vecBullets;



private:

	int					m_nBulletDamage;
};