#include "Enemy.hpp"

Enemy::Enemy()
{

}

Enemy::Enemy(lua_State* L, float x, float y)
{
	this->textureEnemy.loadFromFile("../Images/ghost.png");
	this->spriteEnemy.setTexture(this->textureEnemy);
	this->lookDirection = 0;
	this->spriteEnemy.setTextureRect(sf::IntRect(0, 0, 16, 16));
	this->spriteEnemy.setPosition(Vector2f(x, y));
}

Enemy::~Enemy()
{

}

void Enemy::update(lua_State* L, float dt, int i)
{
	this->setSpritePosition(L, i);
}

void Enemy::draw(RenderTarget &target, RenderStates states)const
{
	target.draw(this->spriteEnemy, states);
}

void Enemy::setSpritePosition(lua_State* L, int i)
{
	lua_getglobal(L, "getEnemyPos");
	lua_pushinteger(L, i);
	lua_pcall(L, 1, 2, 0);
	if (lua_isnumber(L, -2) && lua_isnumber(L, -1))
	{
		double x = lua_tonumber(L, -2);
		double y = lua_tonumber(L, -1);
		this->spriteEnemy.setPosition(x, y);
	}
	lua_pop(L, 2);
}

Sprite Enemy::getSprite()const
{
	return this->spriteEnemy;
}