#ifndef __ROOM_SCENE_H__
#define __ROOM_SCENE_H__

#include "cocos2d.h"
#include "Controller/Event/IRoomSceneListener.h"
#include "Model/RoomSceneModel.hpp"
#include "Character/Issac.hpp"
#include "Character/Monster.hpp"
#include "Character/SimpleItem.h"
#include<vector>

USING_NS_CC;

class RoomScene : public Scene
{
  public:
    static Scene *createScene();
    bool init() override;
    CREATE_FUNC(RoomScene)
    
//    CC_SYNTHESIZE(RoomSceneModel, model, Model)
    RoomSceneModel model;
    void set_model(RoomSceneModel model);
    CC_SYNTHESIZE_RETAIN(Issac*, player, Player)
    CC_SYNTHESIZE_RETAIN(Sprite*, tearSprite, TearSprite)
    CC_SYNTHESIZE_RETAIN(Sprite*, pausescreen, Pausescreen)
    CC_SYNTHESIZE_RETAIN(SimpleItem*, bomb, Bomb)

    void set_event_listener(IRoomSceneListener *listener);
    void update(float delta) override;
    void fire(float dt);
    void monster_move(float dt);
    int scheduled = 0;
private:
    IRoomSceneListener * listener_ = nullptr;
    void build_frame_cache() const;
    //使用cocos2d内置Vector管理Sprite等Ref类型的内存
    //和CC_SYNTHESIZE_RETAIN作用类似
	Vector<Monster*> monsters_;
};

#endif // __ROOM_SCENE_H__
