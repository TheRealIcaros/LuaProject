#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Include.h"

class Player : public Drawable
{
private:
	Texture texturePlayer;
	Sprite spritePlayer;
	int lookDirection;
	int spriteAnimation;

	int hp;

	Clock time;
public:
	Player(lua_State* L);
	~Player();
	void update(lua_State* L, float dt);	//(float dt, lua_State* L);
	void draw(RenderTarget &target, RenderStates states)const;

	void setSpritePosition(lua_State* L);
	void setLookDirection(lua_State* L);

	Sprite getSprite()const;
	void updateSpriteAnimation();
	void damageHp();
	int getHp();
};

#endif // !
