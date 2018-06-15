#include "Collectable.h"

Collectable *Collectable::createCollectable(int collectableType)
{
	Collectable *pRet = new (std::nothrow) Collectable();
	if (pRet && pRet->init(collectableType))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool Collectable::init(int collectableType)
{
	if (!Sprite::init())
	{
		return false;
	}

	moveSpeed = 0;
	radiusSize = 0;
	tearSpeed = 0;
	tearExistTime = 0;
	health = 0;
	attack = 0;
	enFly = false;
	enBounce = true;
	enhalfTearDis = true;

	Sprite *temp_collectableImg;
	switch (collectableType)
	{
	case (0):	//半颗红心
		temp_collectableImg=Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("res/gfx/items/pick ups/pickup_001_heart.png"), Rect(32, 0, 32, 32));
		health = 1;
		break;
	case (1):	//一颗红心
		temp_collectableImg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("res/gfx/items/pick ups/pickup_001_heart.png"), Rect(0, 0, 32, 32));
		health = 1;
		break;
	case (2):	//加攻击0.3,加血半颗心，加移动速度，加射速，加射程
		temp_collectableImg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("res/gfx/items/collectibles/collectibles_012_magicmushroom.png"), Rect(0, 0, 32, 32));
		attack = 0.5;
		health = 1;
		moveSpeed = 20;
		tearExistTime = 10;
		break;
	//下面的贴图都是不对的,全用蓝心代替
	case(3):	//加攻击3,扣1颗心的血，减慢移动速度
		temp_collectableImg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("res/gfx/items/pick ups/pickup_001_heart.png"), Rect(0, 32, 32, 32));
		attack = 3;
		health = -2;
		moveSpeed = -20;
		break;
	case(4):	//加攻击1
		temp_collectableImg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("res/gfx/items/pick ups/pickup_001_heart.png"), Rect(0, 32, 32, 32));
		attack = 1;
		break;
	case(5):	//减攻击0.7，射程几乎无限
		temp_collectableImg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("res/gfx/items/pick ups/pickup_001_heart.png"), Rect(0, 32, 32, 32));
		attack = -0.3;
		tearExistTime = 999;
		break;
	case(6):	//加攻击4，射程减半
		temp_collectableImg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("res/gfx/items/pick ups/pickup_001_heart.png"), Rect(0, 32, 32, 32));
		attack = 4;
		enhalfTearDis = true;
		break;
	case(7):	//子弹现在反弹了
		temp_collectableImg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("res/gfx/items/pick ups/pickup_001_heart.png"), Rect(0, 32, 32, 32));
		enBounce = true;
		break;
	case(8):	//人能够飞了
		temp_collectableImg = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("res/gfx/items/pick ups/pickup_001_heart.png"), Rect(0, 32, 32, 32));
		enFly = true;
		break;
	}
	this->addChild(temp_collectableImg);
	this->createPhyBody();
	this->setTag(9);
	return true;

	//暂时没有使用的贴图
	//一颗蓝心Sprite * pickup_heart_maxplusfull = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("res/gfx/items/pick ups/pickup_001_heart.png"), Rect(0, 32, 32, 32));
	//半颗蓝心Sprite * pickup_heart_maxplushalf = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->addImage("res/gfx/items/pick ups/pickup_001_heart.png"), Rect(32, 32, 32, 32));
}

void Collectable::createPhyBody() 
{
	auto phyBody = PhysicsBody::createCircle(10, PHYSICSBODY_MATERIAL_DEFAULT);
	//静态
	phyBody->setDynamic(false);
	//设置物体的恢复力
	phyBody->getShape(0)->setRestitution(0.0f);
	//设置物体的摩擦力
	phyBody->getShape(0)->setFriction(0.0f);
	//碰撞、监听筛选
	phyBody->setCategoryBitmask(0x80);	// 1000_0000(80)
	phyBody->setCollisionBitmask(0xFF);   // 1111_1111(FF)
	phyBody->setContactTestBitmask(0x09); //0000_1001(09)
										  //添加物理躯体
	this->addComponent(phyBody);
}