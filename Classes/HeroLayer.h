
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
	void blowup(int score);


CC_SYNTHESIZE_READONLY(Sprite*, m_pHero, Hero)
CC_SYNTHESIZE(bool, m_bLive, LiveStatus)

private:
	static HeroLayer*	s_pHeroLayer;
	int	m_nScore;
};