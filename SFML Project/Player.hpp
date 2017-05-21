#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Include.h"

class Player : public Drawable
{
private:
	Texture swingTexture;
	Texture texturePlayer;
	Sprite spritePlayer;
	int lookDirection;
	int spriteAnimation;

	RectangleShape hitbox;

	Texture heartTexture;
	Sprite heart;

	int hp = 3;
	int kills = 0;
	bool playerKilled = false;

	int animationSwing;
	bool isAttacking;
	bool wasAttacking;
	bool isSwinging;
	Clock time;
public:
	Player();
	~Player();
	void update(lua_State* L, float dt);	//(float dt, lua_State* L);
	void draw(RenderTarget &target, RenderStates states)const;

	void setSpritePosition(lua_State* L);
	void setLookDirection(lua_State* L);

	Sprite getSprite()const;
	void updateSpriteAnimation();
	void damageHp();
	int getHp()const;
	void setPlayerPosInLua(lua_State* L, Vector2f pos);
	void checkAttacking(lua_State* L, float dt);
	bool getIsSwinging()const;
	RectangleShape getHitbox()const;
	void setPlayerPos(lua_State* L, Vector2f pos);

	void movePlayer(Vector2f move, lua_State* L, float dt);
	void setHeartPos(Vector2f pos);
	void updateHeartSprite(lua_State* L);
	bool isPlayerKilled()const;
	void setPlayerDead(bool set);
	void restart();
};

#endif // !
