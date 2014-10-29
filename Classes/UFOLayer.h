
#include "cocos2d.h"

USING_NS_CC;

class UFOLayer : public Layer
{
CC_CONSTRUCTOR_ACCESS:
	UFOLayer();

public:
	~UFOLayer();

	CREATE_FUNC(UFOLayer);

	virtual bool init() override;

	void addDoubleBullets(float interval);

	void removeDoubleBullets(Node* pNode);

CC_SYNTHESIZE_READONLY(Sprite*, m_pDoubleBullets, DoubleBullets)
};