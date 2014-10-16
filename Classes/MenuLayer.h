
#include "cocos2d.h"

USING_NS_CC;

class MenuLayer : public Layer
{
CC_CONSTRUCTOR_ACCESS:
	MenuLayer();

	virtual bool init() override;

public:
	~MenuLayer();

	static Scene* createScene();

	CREATE_FUNC(MenuLayer);

	void startGame();
};