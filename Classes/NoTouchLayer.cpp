
#include "NoTouchLayer.h"

NoTouchLayer::NoTouchLayer()
{

}
NoTouchLayer::~NoTouchLayer()
{

}

bool NoTouchLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(NoTouchLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(NoTouchLayer::onTouchMoved, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	listener->setSwallowTouches(true);


	return true;
}

bool NoTouchLayer::onTouchBegan(Touch *touch, Event *event)
{
	return true;
}

void NoTouchLayer::onTouchMoved(Touch *touch, Event *event)
{
	return;
}