#ifndef Monster_hpp
#define Monster_hpp

#include "cocos2d.h"
#include "Moveable.h"
#include "Tear.h"
#include "ViewModel/RoomViewModel.h"

USING_NS_CC;
using namespace std;

#define MonTearOffset 15
const GridPoint moveStep[8] = {GridPoint(1, 0), GridPoint(-1, 0), GridPoint(0, 1), GridPoint(0, -1), GridPoint(1, 1), GridPoint(-1, -1), GridPoint(-1, 1), GridPoint(1, -1)};

class Monster : public Moveable
{
  public:
    virtual bool init();
    virtual void createPhyBody();

    void move(int walk_direction);
    Tear *Fire(Vec2 targetPos);
    int ToPointDir(Vec2);
    GridPoint CalGridPos(Vec2 truePos)
    {
        return GridPoint((int)(truePos.x - 48) / RoomUnitSize.width, (int)(truePos.y - 48) / RoomUnitSize.height);
    }
    double CalDistance(Vec2 x1, Vec2 x2)
    {
        return sqrt((x1.x - x2.x) * (x1.x - x2.x) + (x1.y - x2.y) * (x1.y - x2.y));
    }

    //怪物的移动策略，这是接口。子类每个怪物重写。
    virtual void moveStrategy(int walk_direction) = 0;           //低级寻路
    virtual void moveStrategy(const RoomViewModel &roomMap) = 0; //高级寻路
    //怪物的开火策略，这是接口。子类每个怪物重写。
    virtual void fireStrategy(Vector<Tear *> &tears_) = 0;

    CC_SYNTHESIZE(int, fireCoolTime, FireCoolTime)
  protected:
    void build_sprite_frame_cache(Texture2D *texture_, Texture2D *dead_texture_) const; //必要时需要重载
    static void build_animation_cache();
};

class Fatty : public Monster
{
public:
    static Fatty *createFatty();
    virtual bool init();
    CREATE_FUNC(Fatty)
    void move(int walk_direction);
    virtual void moveStrategy(int walk_direction);
    virtual void moveStrategy(const RoomViewModel &roomMap);
    virtual void fireStrategy(Vector<Tear *> &tears_);
    void build_sprite_frame_cache(Texture2D *texture_, Texture2D *dead_texture_) const;
    static void build_animation_cache();
};

class Fly : public Monster
{
  public:
    static Fly *createFly();
    virtual bool init();
    CREATE_FUNC(Fly)
    void move(int walk_direction);
    virtual void moveStrategy(int walk_direction);
    virtual void moveStrategy(const RoomViewModel &roomMap);
    virtual void fireStrategy(Vector<Tear *> &tears_);
    void build_sprite_frame_cache(Texture2D *texture_) const;
    static void build_animation_cache();
};

class Gaper : public Monster
{
  public:
    static Gaper *createGaper();
    virtual bool init();
    CREATE_FUNC(Gaper)
    void move(int walk_direction);
    virtual void moveStrategy(int walk_direction);
    virtual void moveStrategy(const RoomViewModel &roomMap);
    virtual void fireStrategy(Vector<Tear *> &tears_);
    void build_sprite_frame_cache(Texture2D *headtexture_, Texture2D *bodytexture_, Texture2D *dead_texture_) const;
    static void build_animation_cache();
};

class Spider : public Monster
{
  public:
    static Spider *createSpider();
    virtual bool init();
    CREATE_FUNC(Spider)
    void move(int walk_direction);
    virtual void moveStrategy(int walk_direction);
    virtual void moveStrategy(const RoomViewModel &roomMap);
    virtual void fireStrategy(Vector<Tear *> &tears_);
    void build_sprite_frame_cache(Texture2D *texture_) const;
    static void build_animation_cache();
};
#endif /* Monster_hpp */
