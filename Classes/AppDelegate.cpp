#include "AppDelegate.h"
#include "WelcomeLayer.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLView::create("wechatPlane");
        director->setOpenGLView(glview);
    }

	//director->setContentScaleFactor();
	glview->setDesignResolutionSize(480, 640, ResolutionPolicy::FIXED_WIDTH);
	

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	std::vector<std::string> paths;
	paths.push_back("font");
	paths.push_back("sound");
	paths.push_back("ui");
	FileUtils::getInstance()->setSearchResolutionsOrder(paths);

    // create a scene. it's an autorelease object
	auto scene = WelcomeLayer::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
