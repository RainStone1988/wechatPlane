
#include "cocos2d.h"

USING_NS_CC;

class NoTouchLayer : public Layer
{
CC_CONSTRUCTOR_ACCESS:
	NoTouchLayer();

	virtual bool init() override;

public:
	~NoTouchLayer();

	CREATE_FUNC(NoTouchLayer);

	bool onTouchBegan(Touch *touch, Event *event);
	void onTouchMoved(Touch *touch, Event *event);
};