
#include "cocos2d.h"

USING_NS_CC;

class HeroLayer : public Layer
{
CC_CONSTRUCTOR_ACCESS:
	HeroLayer();

	virtual bool init() override;

public:
	~HeroLayer();

	static HeroLayer* getInstance();

	static HeroLayer* create();

	virtual bool onTouchBegan(Touch *touch, Event *unused_event) override;
	virtual void onTouchMoved(Touch *touch, Event *unused_event) override;

	Vec2 getHeroPosition();
	Size getHeroContentSize();

	Sprite* getHero();

	void removeHero();

private:
	static HeroLayer*	s_pHeroLayer;
	Sprite*		m_pHero;
};