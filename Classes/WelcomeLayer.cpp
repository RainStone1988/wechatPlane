
#include "WelcomeLayer.h"
#include "GameLayer.h"

WelcomeLayer::WelcomeLayer()
{

}
WelcomeLayer::~WelcomeLayer()
{

}

Scene* WelcomeLayer::createScene()
{
	auto sce = Scene::create();
	auto lay = WelcomeLayer::create();
	sce->addChild(lay);

	return sce;
}

bool WelcomeLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// 加载游戏资源
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");

	auto winSize = Director::getInstance()->getWinSize();

	// 加载背景
	auto background = Sprite::createWithSpriteFrameName("shoot_copyright.png");
	this->addChild(background);
	background->setPosition(winSize.width/2, winSize.height/2);

	// loading
	auto loading = Sprite::createWithSpriteFrameName("game_loading1.png");
	loading->setPosition(winSize.width/2, winSize.height/2 - 40);
	this->addChild(loading);

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.4f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading2.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading3.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading4.png"));

	auto animate = Animate::create(animation);
	auto repeat = Repeat::create(animate, 1);
	auto loadingDone = CallFuncN::create(CC_CALLBACK_1(WelcomeLayer::loadingDone, this));
	auto seq = Sequence::create(animate, repeat, loadingDone, NULL);
	loading->runAction(seq);
	
	animation = Animation::create();
	animation->setDelayPerUnit(0.4f);
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n1.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n2.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n3.png"));
	animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n4.png"));
	AnimationCache::getInstance()->addAnimation(animation, "hero_blowup");

	return true;
}


void WelcomeLayer::loadingDone(Node* pNode)
{
	if (NULL != pNode)
	{
		auto sce = GameLayer::createScene();
		auto realSce = TransitionMoveInB::create(0.5f, sce);
		Director::getInstance()->replaceScene(realSce);
	}
}