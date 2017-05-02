#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Include.h"

class Enemy : public Drawable
{
private:
	Texture textureEnemy;
	Sprite spriteEnemy;
	int lookDirection;
public:
	Enemy();
	Enemy(lua_State* L, float x = 0, float y = 0);
	~Enemy();
	void update(lua_State* L, float dt, int i);
	void draw(RenderTarget &target, RenderStates states)const;

	void setSpritePosition(lua_State* L, int i);

	Sprite getSprite()const;
};

#endif // !
