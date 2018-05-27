#ifndef Issac_hpp
#define Issac_hpp

#include <stdio.h>
#include <vector>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class Issac : public Sprite {
public:
    static Issac *createIssac();
    static Sprite *createSprite();
    virtual bool init();

    CREATE_FUNC(Issac)

    CC_SYNTHESIZE_RETAIN(Animate*, idleAnimate, IdleAnimate)
    CC_SYNTHESIZE_RETAIN(Animate*, moveAnimate, MoveAnimate)

    CC_SYNTHESIZE(bool, moving, Moving)
    CC_SYNTHESIZE(int, prev_walk_orientation, PrevWalkOrientation)
    CC_SYNTHESIZE(int, prev_head_orientation, PrevHeadOrientation)

    void move(int walk_direction, int head_direction);

private:
    void build_sprite_frame_cache(Texture2D *texture_);
    void build_animation_cache();
};
#endif
