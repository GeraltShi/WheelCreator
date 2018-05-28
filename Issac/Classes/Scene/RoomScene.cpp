#include "RoomScene.h"
#include <iostream>

USING_NS_CC;
using namespace std;

Scene *RoomScene::createScene()
{
    return create();
}

bool RoomScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    const Size size = Director::getInstance()->getWinSize();
    std::cout << size.width <<" "<< size.height << endl;
    //TODO 应该有更好的方法生成背景贴图，而不是暴力生成4个或多个碎片
    //TODO 动态加载贴图？如Issac的buff皮肤（在别的贴图上）如何更新
    Texture2D *texture_room = Director::getInstance()->getTextureCache()->addImage("res/gfx/backdrop/01_basement.png");
    //TODO 更小的地图切片和随机性支持
    Sprite * room_piece1 = Sprite::createWithTexture(texture_room,Rect(0,0,221,143));
    room_piece1->setAnchorPoint(Point(0,0));
    room_piece1->setPosition(0, 143);
    addChild(room_piece1,0);
    
    Sprite * room_piece2 = Sprite::createWithTexture(texture_room,Rect(0,0,221,143));
    room_piece2->setFlippedX(true);
    room_piece2->setAnchorPoint(Point(0,0));
    room_piece2->setPosition(221, 143);
    addChild(room_piece2,0);
    
    Sprite * room_piece3 = Sprite::createWithTexture(texture_room,Rect(0,0,221,143));
    room_piece3->setFlippedY(true);
    room_piece3->setAnchorPoint(Point(0,0));
    room_piece3->setPosition(0, 0);
    addChild(room_piece3,0);
    
    Sprite * room_piece4 = Sprite::createWithTexture(texture_room,Rect(0,0,221,143));
    room_piece4->setFlippedX(true);
    room_piece4->setFlippedY(true);
    room_piece4->setAnchorPoint(Point(0,0));
    room_piece4->setPosition(221, 0);
    addChild(room_piece4,0);
    
    Texture2D *texture_shading = Director::getInstance()->getTextureCache()->addImage("res/gfx/backdrop/shading_utero.png");
    Sprite * shading = Sprite::createWithTexture(texture_shading,Rect(0,0,442,286));
    shading->setPosition(221,143);
    addChild(shading,0);
    BlendFunc blend = {GL_SRC_ALPHA,GL_ONE};
    shading->setBlendFunc(blend);
    
    Texture2D *texture_door = Director::getInstance()->getTextureCache()->addImage("res/gfx/grid/door_01_normaldoor.png");
    Sprite * door = Sprite::createWithTexture(texture_door,Rect(0,96,64,48));
    Sprite * door_center = Sprite::createWithTexture(texture_door,Rect(64,0,64,48));
    door->setPosition(221, 250);
    door_center->setPosition(221, 250);
    addChild(door,1);addChild(door_center,1);
    //TODO Issac比peppa灵活，他动的时候全身都在跳舞，不动的时候也会眨眼睛，SpriteFrame
    //TODO 弹幕Tear的生成、生命周期、碰撞过程、管理（多Tear对象共存），Tear生成时头会抖
    
    //TODO 这不是遮罩，遮罩应该在整个Scene最顶部，是一种颜色混合模式
    Texture2D *texture_overlay = Director::getInstance()->getTextureCache()->addImage("res/gfx/overlays/basement/1x1_overlay_1.png");
    Sprite * overlay = Sprite::createWithTexture(texture_overlay,Rect(0,0,442,286));
    overlay->setPosition(221,143);
    addChild(overlay,2);
    
    Texture2D *texture_rainbowpoop = Director::getInstance()->getTextureCache()->addImage("res/gfx/grid/grid_poop_rainbow.png");
    Sprite * rainbowpoop = Sprite::createWithTexture(texture_rainbowpoop,Rect(0,0,32,32));// TODO 地面物品都有着损坏状态，不应该在这里生成
    rainbowpoop->setPosition(300,150);// TODO 地面物品网格化，对齐
    addChild(rainbowpoop,3);
    
    build_frame_cache();
    player = Issac::createIssac();

    addChild(player, 3);
    
    monster = Monster::createMonster();
    addChild(monster, 3, "fatty1");
    
    monster2 = Monster::createMonster();
    addChild(monster2, 3, "fatty2");
    //TODO 状态栏层应该独立于RoomScene，生命值和图案用状态reg统一管理
    Texture2D * texture_heart = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/ui_hearts.png");
    Sprite * heart = Sprite::createWithTexture(texture_heart, Rect(0,0,16,16));
    heart->setPosition(70,250);
    addChild(heart, 8);
    
    //TODO 物品栏层应该独立于RoomScene，物品用状态reg统一管理
    Texture2D * texture_hud = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/hudpickups.png");
    Sprite * coin = Sprite::createWithTexture(texture_hud, Rect(0,0,16,16));
    coin->setPosition(30,224);
    Sprite * bomb = Sprite::createWithTexture(texture_hud, Rect(0,16,16,16));
    bomb->setPosition(30,208);
    Sprite * goldkey = Sprite::createWithTexture(texture_hud, Rect(16,16,16,16));
    goldkey->setPosition(30,192);
    Sprite * silverkey = Sprite::createWithTexture(texture_hud, Rect(16,0,16,16));
    silverkey->setPosition(30,176);
    addChild(coin, 8);
    addChild(bomb, 8);
    addChild(goldkey, 8);
    addChild(silverkey, 8);
    
    //TODO 小地图应加载到缓存，并设置透明度，独立于RoomScene，元素都在texture_minimap中
    Texture2D * texture_minimap = Director::getInstance()->getTextureCache()->addImage("res/gfx/ui/minimap1.png");
    Sprite * minimap = Sprite::createWithTexture(texture_minimap, Rect(0,0,56,48));
    minimap->setPosition(370,240);
    addChild(minimap, 8);
    
    //TODO 数字缓存加载，需专门处理物品计数和字符显示，字符大小：18x31
    Texture2D * texture_font = Director::getInstance()->getTextureCache()->addImage("res/font/pftempestasevencondensed_0.png");
    Sprite * num0 = Sprite::createWithTexture(texture_font, Rect(18*14,21*3,18,21));
    num0->setPosition(46,224);
    addChild(num0, 8);
    
    //srand(static_cast<unsigned>(time(nullptr)));//初始化时种下种子，不能在update或fire方法里种，不然随机性消失
    //TODO 加载所有界面元素
    //TODO 1.石头生成，门生成和进入响应，需触发地图更新，怪没打完逃不出去！ gfx\grid
    //TODO 2.光影遮罩       gfx\overlays res\backdrop（光）
    //TODO 3.物品生成       gfx\items
    
    //TODO 4.小地图和生命值，物品栏在z最大处（最顶层），（且随窗口大小自适应，如来不及就做成固定大小）
    //TODO 4.1 计分板，原版好像没有这个东西，可以做成计时闯关，时间短分高（如果做不出难度更新）
    
    //TODO 5.生成怪物               gfx\monsters gfx\bosses
    //TODO 6.地面破坏效果，由物品生命周期控制，（随机纹理，来不及就不做，与贴图随机选择有关）gfx\effects
    //TODO 7.Issac 吃buff后状态的变化，如换了个皮肤，与类内皮肤成员有关
    //TODO 99. 联机模式，素材中有babyIssac
    //TODO 100. (Issac有宠物，它会自己攻击)   gfx\familiar
   
    scheduleUpdate();
    return true;
}

void RoomScene::set_event_listener(IRoomSceneListener * listener)
{
    this->listener_ = listener;

    //TODO 事件监听
    auto _touchListener = EventListenerTouchOneByOne::create();

    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = [this](Touch* touch, Event* event) {
        this->listener_->on_touch_began(touch, event);
        return false;
    };

    auto _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = [this](Event * event)
    {
        this->listener_->on_mouse_down(event);
        return false;
    };
    
    auto _keyboard_listener = EventListenerKeyboard::create();
    _keyboard_listener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
        this->listener_->on_key_pressed(keyCode, event);
    };
    
    _keyboard_listener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event)
    {
        this->listener_->on_key_released(keyCode, event);
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboard_listener, this);
}

void RoomScene::update(float delta)
{
    //TODO 每隔一定时间更新monster位置，monster不会自己撞墙
    monster->move(1,0);
    monster2->move(2,0);
    // Move对头部的频度更高，但优先级比方向键低。相当于方向键是“插队”
    player->move(model.walk_direction, model.tear_direction);
    if(model.tear_direction == 5){
        this->schedule(schedule_selector(RoomScene::fire), 0.5);
    }
    //TODO Issac所有的状态更新：如碰撞掉血，被炸弹炸掉血，吃小邢邢回血，自身物品状态都由场景触发
    //TODO 碰撞方向判定，闪动效果（提醒玩家螳臂当车了）
    //TODO 碰撞效果，Issac固定掉半格血，怪物可能自爆，也可能还活着
    //std::cout << "Walking d: "<<model.walk_direction<<" Tear d: " << model.tear_direction << " PrevHead d: "<< player->getPrevHeadOrientation()<<endl;
}

void RoomScene::fire(float dt){
    auto fcache = SpriteFrameCache::getInstance();
    const auto frame0 = fcache->getSpriteFrameByName("t_frame0");
    const auto frame1 = fcache->getSpriteFrameByName("t_frame1");
    const auto frame2 = fcache->getSpriteFrameByName("t_frame2");
    const auto frame3 = fcache->getSpriteFrameByName("t_frame3");
    const auto frame4 = fcache->getSpriteFrameByName("t_frame4");
    const auto frame5 = fcache->getSpriteFrameByName("t_frame5");
    const auto frame6 = fcache->getSpriteFrameByName("t_frame6");
    const auto frame7 = fcache->getSpriteFrameByName("t_frame7");
    const auto frame8 = fcache->getSpriteFrameByName("t_frame8");
    const auto frame9 = fcache->getSpriteFrameByName("t_frame9");
    const auto frame10 = fcache->getSpriteFrameByName("t_frame10");
    const auto frame11 = fcache->getSpriteFrameByName("t_frame11");
    const auto frame12 = fcache->getSpriteFrameByName("t_frame12");
    const auto frame13 = fcache->getSpriteFrameByName("t_frame13");
    const auto frame14 = fcache->getSpriteFrameByName("t_frame14");
    const auto frame15 = fcache->getSpriteFrameByName("t_frame15");
    
    
    Vector<SpriteFrame *> array;
    array.pushBack(frame0);
    array.pushBack(frame1);
    array.pushBack(frame2);
    array.pushBack(frame3);
    array.pushBack(frame4);
    array.pushBack(frame5);
    array.pushBack(frame6);
    array.pushBack(frame7);
    array.pushBack(frame8);
    array.pushBack(frame9);
    array.pushBack(frame10);
    array.pushBack(frame11);
    array.pushBack(frame12);
    array.pushBack(frame13);
    array.pushBack(frame14);
    array.pushBack(frame15);
    
    const auto animation = Animation::createWithSpriteFrames(array, 0.05f);
    Action * poof_anim = Animate::create(animation);
    
    Texture2D * tearTexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/tears.png");
    SpriteFrame *tearFrame = SpriteFrame::createWithTexture(tearTexture, Rect(0,32,32,32));
    tearSprite = Sprite::createWithSpriteFrame(tearFrame);
    const int advance = 15;
    int x_advance;
    int y_advance;
    switch (model.tear_direction) {
        case 2:
            x_advance = 0;
            y_advance = advance+random(-10,10);
            break;
        case 4:
            x_advance = -advance+random(-10,10);
            y_advance = 0;
            break;
        case 6:
            x_advance = advance+random(-10,10);
            y_advance = 0;
            break;
        case 8:
            x_advance = 0;
            y_advance = -advance+random(-10,10);
            break;
        default:
            x_advance = 0;
            y_advance = 0;
    }
    
    tearSprite->setPosition(Vec2(player->getPosition().x+x_advance, player->getPosition().y+y_advance+5));
    const float speed = 0.38;
    //子弹运行的距离和时间
    MoveBy * tear_move = nullptr;
    switch (model.tear_direction) {
        case 2:
            tear_move = MoveBy::create(speed, Vec2(0,100));
            break;
        case 4:
            tear_move = MoveBy::create(speed, Vec2(-100,0));
            break;
        case 6:
            tear_move = MoveBy::create(speed, Vec2(100,0));
            break;
        case 8:
            tear_move = MoveBy::create(speed, Vec2(0,-100));
            break;
        default:
            break;
    }
    //子弹执行完动作后进行函数回调，调用移除子弹函数
    if(model.tear_direction != 5){
        //子弹开始跑动
        this->addChild(tearSprite, 3);
        Sequence* sequence = Sequence::create(tear_move, poof_anim, RemoveSelf::create(true),NULL);
        tearSprite->runAction(sequence);
    }
}

void RoomScene::monster_move(float dt)
{

}

void RoomScene::build_frame_cache() const
{
    Texture2D * poofTexture = Director::getInstance()->getTextureCache()->addImage("res/gfx/effects/effect_015_tearpoofa.png");
    const auto frame0 = SpriteFrame::createWithTexture(poofTexture, Rect(0, 0, 64, 64));
    const auto frame1 = SpriteFrame::createWithTexture(poofTexture, Rect(64, 0, 64, 64));
    const auto frame2 = SpriteFrame::createWithTexture(poofTexture, Rect(128, 0, 64, 64));
    const auto frame3 = SpriteFrame::createWithTexture(poofTexture, Rect(192, 0, 64, 64));
    const auto frame4 = SpriteFrame::createWithTexture(poofTexture, Rect(0, 64, 64, 64));
    const auto frame5 = SpriteFrame::createWithTexture(poofTexture, Rect(64, 64, 64, 64));
    const auto frame6 = SpriteFrame::createWithTexture(poofTexture, Rect(128, 64, 64, 64));
    const auto frame7 = SpriteFrame::createWithTexture(poofTexture, Rect(192, 64, 64, 64));
    const auto frame8 = SpriteFrame::createWithTexture(poofTexture, Rect(0, 128, 64, 64));
    const auto frame9 = SpriteFrame::createWithTexture(poofTexture, Rect(64, 128, 64, 64));
    const auto frame10 = SpriteFrame::createWithTexture(poofTexture, Rect(128, 128, 64, 64));
    const auto frame11 = SpriteFrame::createWithTexture(poofTexture, Rect(192, 128, 64, 64));
    const auto frame12 = SpriteFrame::createWithTexture(poofTexture, Rect(0, 192, 64, 64));
    const auto frame13 = SpriteFrame::createWithTexture(poofTexture, Rect(64, 192, 64, 64));
    const auto frame14 = SpriteFrame::createWithTexture(poofTexture, Rect(128, 192, 64, 64));
    const auto frame15 = SpriteFrame::createWithTexture(poofTexture, Rect(192, 192, 64, 64));

    auto fcache = SpriteFrameCache::getInstance();
    fcache->addSpriteFrame(frame0, "t_frame0");
    fcache->addSpriteFrame(frame1, "t_frame1");
    fcache->addSpriteFrame(frame2, "t_frame2");
    fcache->addSpriteFrame(frame3, "t_frame3");
    fcache->addSpriteFrame(frame4, "t_frame4");
    fcache->addSpriteFrame(frame5, "t_frame5");
    fcache->addSpriteFrame(frame6, "t_frame6");
    fcache->addSpriteFrame(frame7, "t_frame7");
    fcache->addSpriteFrame(frame8, "t_frame8");
    fcache->addSpriteFrame(frame9, "t_frame9");
    fcache->addSpriteFrame(frame10, "t_frame10");
    fcache->addSpriteFrame(frame11, "t_frame11");
    fcache->addSpriteFrame(frame12, "t_frame12");
    fcache->addSpriteFrame(frame13, "t_frame13");
    fcache->addSpriteFrame(frame14, "t_frame14");
    fcache->addSpriteFrame(frame15, "t_frame15");
}
