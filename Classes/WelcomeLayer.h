
#include "cocos2d.h"

USING_NS_CC;

class WelcomeLayer : public Layer
{
CC_CONSTRUCTOR_ACCESS:
	WelcomeLayer();

	virtual bool init() override;

public:
	~WelcomeLayer();

	static Scene* createScene();

	CREATE_FUNC(WelcomeLayer);

	void loadingDone(Node* pNode);
};