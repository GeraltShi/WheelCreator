#include "RoomSceneController.h"
#include "Scene/RoomScene.h"
#include <iostream>

USING_NS_CC;
using namespace std;

Scene * RoomSceneController::createScene(int roomID)
{
    return create(roomID);
}

bool RoomSceneController::init(int roomID)
{
    if (!Scene::initWithPhysics())
    {
        return false;
    }

	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    scene_ = RoomScene::create(roomID);
    scene_->set_event_listener(this);
    addChild(scene_);

    //TODO 地图服务
    level_service_ = LevelService();

    return true;
}

void RoomSceneController::on_touch_began(Touch * touch, Event * event)
{
    cocos2d::log("room_scene_on_touch");
}

void RoomSceneController::on_mouse_down(Event * event)
{
    cocos2d::log("room_scene_on_touch");
    count++;
}

int RoomSceneController::check_key_inRoom(EventKeyboard::KeyCode keyCode)
{
    if(!scene_->model.paused){
        switch (keyCode)
        {
            case EventKeyboard::KeyCode::KEY_ESCAPE:
                //std::cout << "ESC pressed" << endl;
                scene_->stopAllActions();
                scene_->model.paused = true;
                break;
            default: break;
        }
        int dirx = -1; int diry = -1;
        if(key_map_[EventKeyboard::KeyCode::KEY_A]) dirx = 0;
        if(key_map_[EventKeyboard::KeyCode::KEY_D]) dirx = 1;
        if((!key_map_[EventKeyboard::KeyCode::KEY_A])&& (!key_map_[EventKeyboard::KeyCode::KEY_D])) dirx = -1;
        if(key_map_[EventKeyboard::KeyCode::KEY_W]) diry = 0;
        if(key_map_[EventKeyboard::KeyCode::KEY_S]) diry = 1;
        if((!key_map_[EventKeyboard::KeyCode::KEY_W])&& (!key_map_[EventKeyboard::KeyCode::KEY_S])) diry = -1;
        if(dirx == 0 && diry == 0){return 1;}
        if(dirx == -1 && diry == 0){return 2;}
        if(dirx == 1 && diry == 0){return 3;}
        if(dirx == 0 && diry == -1){return 4;}
        if(dirx == -1 && diry == -1){return 5;}
        if(dirx == 1 && diry == -1){return 6;}
        if(dirx == 0 && diry == 1){return 7;}
        if(dirx == -1 && diry == 1){return 8;}
        if(dirx == 1 && diry == 1){return 9;}
    } else {
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                scene_->model.paused_menu_cursor = (scene_->model.paused_menu_cursor +1)%2;
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                scene_->model.paused_menu_cursor = (scene_->model.paused_menu_cursor +3)%2;
                break;
            case EventKeyboard::KeyCode::KEY_ENTER:
                if(scene_->model.paused_menu_cursor == 0){
                    scene_->model.paused = false;
                } else{
                    Director::getInstance()->popScene();
                }
                break;
            default:
                break;
        }
    }
   
    return 4;
}

int RoomSceneController::check_head(){
    if(key_map_[EventKeyboard::KeyCode::KEY_UP_ARROW]) return 2;
    if(key_map_[EventKeyboard::KeyCode::KEY_DOWN_ARROW]) return 8;
    if(key_map_[EventKeyboard::KeyCode::KEY_LEFT_ARROW]) return 4;
    if(key_map_[EventKeyboard::KeyCode::KEY_RIGHT_ARROW]) return 6;
    return 5;
}

int RoomSceneController::check_pause(EventKeyboard::KeyCode keyCode){
    int shift = 0;
    if(scene_->model.paused){
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
                shift = -1;
                break;
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
                shift = 1;
                break;
            case EventKeyboard::KeyCode::KEY_ENTER:
                if(scene_->model.paused_menu_cursor == 0){
                    scene_->model.paused = false;
                } else{
                    //Director::getInstance()->popScene();
                }
                break;
            default:
                break;
        }
    }
    return shift;
}
void RoomSceneController::on_key_pressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    key_map_[keyCode] = 1;
    //scene_->set_model(RoomSceneModel{ check_key_inRoom(keyCode), check_head() });
    scene_->model.walk_direction = check_key_inRoom(keyCode);
    scene_->model.tear_direction = check_head();
    scene_->model.shift_pausemenu(check_pause(keyCode));
}

void RoomSceneController::on_key_released(EventKeyboard::KeyCode keyCode, Event * event)
{
    key_map_.erase(keyCode);
    scene_->model.walk_direction = check_key_inRoom(keyCode);
    scene_->model.tear_direction = check_head();
}
