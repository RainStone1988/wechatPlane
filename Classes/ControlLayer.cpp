
#include "ControlLayer.h"
#include "NoTouchLayer.h"

ControlLayer::ControlLayer()
{

}
ControlLayer::~ControlLayer()
{

}

bool ControlLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto normalPause = Sprite::createWithSpriteFrameName("game_pause_nor.png");
	auto selectedPause = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
	m_pPauseMenuItem = MenuItemSprite::create(normalPause, selectedPause, CC_CALLBACK_0(ControlLayer::menuPauseCallback, this));
	auto menu = Menu::create(m_pPauseMenuItem, NULL);
	this->addChild(menu, 101);

	auto winSize = Director::getInstance()->getWinSize();
	auto pauseItemSize = m_pPauseMenuItem->getBoundingBox().size;
	menu->setPosition(Vec2::ZERO);
	m_pPauseMenuItem->setAnchorPoint(Vec2::ZERO);
	m_pPauseMenuItem->setPosition(0, winSize.height - pauseItemSize.height);

	m_pScoreItem = Label::createWithBMFont("font.fnt", "0");
	this->addChild(m_pScoreItem);

	auto pauseItemPos = m_pPauseMenuItem->getPosition();
	m_pScoreItem->setColor(Color3B(143, 146, 147));
	m_pScoreItem->setAnchorPoint(Vec2::ZERO);
	m_pScoreItem->setPosition(pauseItemPos.x + pauseItemSize.width + 5, pauseItemPos.y);

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = CC_CALLBACK_2(ControlLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	
	return true;
}

void ControlLayer::menuPauseCallback()
{
	if (!Director::getInstance()->isPaused())
	{
		m_pPauseMenuItem->setNormalImage(Sprite::createWithSpriteFrameName("game_resume_nor.png"));
		m_pPauseMenuItem->setSelectedImage(Sprite::createWithSpriteFrameName("game_resume_pressed.png"));

		Director::getInstance()->pause();

		m_pNoTouchLayer = NoTouchLayer::create();
		this->addChild(m_pNoTouchLayer);
	}
	else
	{
		m_pPauseMenuItem->setNormalImage(Sprite::createWithSpriteFrameName("game_pause_nor.png"));
		m_pPauseMenuItem->setSelectedImage(Sprite::createWithSpriteFrameName("game_pause_pressed.png"));

		Director::getInstance()->resume();

		this->removeChild(m_pNoTouchLayer);
	}
}

void ControlLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (EventKeyboard::KeyCode::KEY_ESCAPE == keyCode)
	{
		if (Director::getInstance()->isPaused())
		{
			Director::getInstance()->end();
		}
		else
		{
			this->menuPauseCallback();
		}
	}
}

void ControlLayer::updateScore(int score)
{
	Value strScore(score);
	m_pScoreItem->setString(strScore.asString());
}
