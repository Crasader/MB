#include "AppDelegate.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
	MapManager::getInstance()->freeInstance();
	HeroData::getInstance()->freeInstance();
	SoundManager::getInstance()->freeInstance();
	UnlockManager::getInstace()->freeInstance();
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
	// _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        //glview = GLViewImpl::create("Monster Breaker");
		//		glview = GLViewImpl::createWithRect("Monster Breaker", Rect(0, 0, 1080, 1920));
		
		// pc test frame
		glview = GLViewImpl::createWithRect("Monster Breaker", Rect(0, 0, 506.25, 900));
		//glview = GLViewImpl::createWithRect("Monster Breaker", Rect(0, 0, 540, 960));
		//glview = GLViewImpl::createWithRect("Monster Breaker", Rect(0, 0, 360, 640));

		director->setOpenGLView(glview);
    }

	glview->setDesignResolutionSize(1080, 1920, ResolutionPolicy::NO_BORDER);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
	auto scene = SplashScene::createScene();
	// debug
	//auto scene = TestScene::createScene();

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
