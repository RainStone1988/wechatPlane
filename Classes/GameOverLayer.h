
#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public Layer
{
CC_CONSTRUCTOR_ACCESS:
	GameOverLayer();

	virtual bool init() override;

public:
	~GameOverLayer();

	static Scene* createScene(int nScore);

	static GameOverLayer* create(int nScore);

	void back2Game(Ref* pSender);

	void setScore(int nScore);

	void showAD();

private:
	int	m_nScore;
};
