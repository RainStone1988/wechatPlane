
#include "MenuLayer.h"
#include "GameLayer.h"

MenuLayer::MenuLayer()
{

}
MenuLayer::~MenuLayer()
{

}

Scene* MenuLayer::createScene()
{
	auto menuScene = Scene::create();
	auto menuLayer = MenuLayer::create();

	menuScene->addChild(menuLayer);

	return menuScene;
}

bool MenuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto winSize = Director::getInstance()->getWinSize();

	// 加载背景
	auto background = Sprite::create("shoot_copyright.png");
	this->addChild(background);
	background->setPosition(winSize.width/2, winSize.height/2);

	// 创建菜单
	auto startMenu = MenuItemFont::create("stARt", CC_CALLBACK_0(MenuLayer::startGame, this));
	auto menu = Menu::create(startMenu, NULL);
	this->addChild(menu);



	return true;
}

void MenuLayer::startGame()
{
	auto gameScene = GameLayer::createScene();
	Director::getInstance()->replaceScene(gameScene);
}