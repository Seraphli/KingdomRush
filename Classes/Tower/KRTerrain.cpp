#include "KRTerrain.h"
#include "BaseMap.h"
#include "TowerPanleLayer.h"

KRTerrain* KRTerrain::createTerrain(int type)
{
	auto terrain = new KRTerrain();
	if(terrain && terrain->init(type)){
		terrain->autorelease();
		return terrain;
	}
	CC_SAFE_DELETE(terrain);
	return NULL;
}

bool KRTerrain::init(int type)
{
	if (!Sprite::init())
	{
		return false;
	}
	isUpdateMenuShown = false;
	switch (type)
	{
	case(1):{
		terrain = Sprite::createWithSpriteFrameName("build_terrain_0004.png");}
		break;
	case(2):{
		terrain = Sprite::createWithSpriteFrameName("build_terrain_0005.png");}
		break;
	case(3):{
		terrain = Sprite::createWithSpriteFrameName("build_terrain_0006.png");}
		break;
	default:{
		terrain = Sprite::createWithSpriteFrameName("build_terrain_0004.png");}
		break;
	}
	addChild(terrain);
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(KRTerrain::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(KRTerrain::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,terrain);
	return true;
}

void KRTerrain::showUpdateMenu()
{
	auto towerPanleLayer = TowerPanleLayer::create();
	towerPanleLayer->setPosition(this->getPosition());
	towerPanleLayer->setTag(getTag());
	towerPanleLayer->setMyTerrain(this);
	static_cast<BaseMap*>(this->getParent())->mTouchLayer->addChild(towerPanleLayer);
	towerPanleLayer->inAnimation();
	isUpdateMenuShown = true;
}
   
void KRTerrain::hideUpdateMenu()
{
	static_cast<BaseMap*>(this->getParent())->mTouchLayer->removeChildByTag(getTag());
	isUpdateMenuShown = false;
}

bool KRTerrain::onTouchBegan(Touch *touch, Event *event)
{
	return true;
}

void KRTerrain::onTouchEnded(Touch* touch, Event* event)
{
	auto target = static_cast<Sprite*>(event->getCurrentTarget());

	Point locationInNode = target->convertTouchToNodeSpace(touch);

	Size size = target->getContentSize();
	Rect rect = Rect(0, 0, size.width, size.height);
	if (rect.containsPoint(locationInNode)&&target->isVisible())
	{  	
		if(isUpdateMenuShown)
		{
			hideUpdateMenu();
		}else{
			showUpdateMenu();
		}
	}else{
		hideUpdateMenu();
	}
}

void KRTerrain::smokeEffect()
{
	auto smoke = Sprite::createWithSpriteFrameName("effect_sellSmoke_0001.png");
	addChild(smoke,99);
	smoke->runAction(Sequence::create(
			Animate::create(AnimationCache::getInstance()->getAnimation("sell_smoke")),
			CallFuncN::create(CC_CALLBACK_0(Sprite::removeFromParent, smoke)),
			NULL));
}