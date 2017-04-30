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
	Enemy(float x, float y, lua_State* L);
	~Enemy();
	void update(lua_State* L);	//(float dt, lua_State* L);
	void draw(RenderTarget &target, RenderStates states)const;

	void setSpritePosition(lua_State* L);
};

#endif // !
