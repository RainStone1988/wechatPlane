
#include "GameOverLayer.h"
#include "GameLayer.h"

GameOverLayer::GameOverLayer()
{

}
GameOverLayer::~GameOverLayer()
{

}

Scene* GameOverLayer::createScene(int nScore)
{
	auto scene = Scene::create();
	auto layer = GameOverLayer::create(nScore);
	scene->addChild(layer);

	return scene;
}

GameOverLayer* GameOverLayer::create(int nScore)
{
	auto pRet = new GameOverLayer;
	if (pRet)
	{
		pRet->setScore(nScore);
		if (pRet->init())
		{
			pRet->autorelease();
		}
		else
		{
			CC_SAFE_DELETE(pRet);
		}
	}

	return pRet;
}

bool GameOverLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto over = Sprite::createWithSpriteFrameName("gameover.png");
	this->addChild(over);

	auto back = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto back2 = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto backMenuItem = MenuItemSprite::create(back, back2, CC_CALLBACK_1(GameOverLayer::back2Game, this));
	auto menu = Menu::create(backMenuItem, NULL);
	this->addChild(menu);


	auto winSize = Director::getInstance()->getWinSize();
	auto backSize = back->getContentSize();

	over->setAnchorPoint(Vec2::ZERO);
	over->setPosition(Vec2::ZERO);

	menu->setPosition(Vec2::ZERO);
	backMenuItem->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	backMenuItem->setPosition(winSize.width, 0);

	Value finalScore(m_nScore);
	auto scoreItem = Label::createWithBMFont("font.fnt", finalScore.asString());
	scoreItem->setColor(Color3B(143, 146, 147));
	scoreItem->setPosition(winSize.width/2, winSize.height/2);
	this->addChild(scoreItem);

	auto delay = DelayTime::create(0.5f);
	auto scalebig = ScaleTo::create(1.0f, 3.0f);
	auto scalelittle = ScaleTo::create(0.3f, 2.0f);
	auto showAD = CallFunc::create(CC_CALLBACK_0(GameOverLayer::showAD, this));
	auto seq = Sequence::create(delay, scalebig, scalelittle, showAD, NULL);
	scoreItem->runAction(seq);

	return true;
}

void GameOverLayer::back2Game(Ref* pSender)
{
	auto gameScene = GameLayer::createScene();
	auto actScene = TransitionSlideInL::create(1.0f, gameScene);
	Director::getInstance()->replaceScene(actScene);
}

void GameOverLayer::setScore(int nScore)
{
	m_nScore = nScore;
}

void GameOverLayer::showAD()
{

}