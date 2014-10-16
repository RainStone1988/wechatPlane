
#ifndef __H_CONTROLLAYER_H_
#define __H_CONTROLLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class NoTouchLayer;

class ControlLayer : public Layer
{
CC_CONSTRUCTOR_ACCESS:
	ControlLayer();

	virtual bool init() override;

public:
	~ControlLayer();

	CREATE_FUNC(ControlLayer);

	void menuPauseCallback();

	void updateScore(int score);

CC_SYNTHESIZE_READONLY(unsigned int, m_nScore, Score)

private:
	Label*	m_pScoreItem;

	MenuItemSprite*	m_pPauseMenuItem;

	NoTouchLayer*	m_pNoTouchLayer;
};

#endif // __H_CONTROLLAYER_H_