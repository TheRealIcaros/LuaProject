#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Include.h"

class Player : public Drawable
{
private:
	Texture texturePlayer;
	Sprite spritePlayer;
public:
	Player(float x, float y, lua_State* L);
	~Player();
	void update(float dt, lua_State* L);
	void draw(RenderTarget &target, RenderStates states)const;

	void setSpritePosition(lua_State* L);
};

#endif // !
