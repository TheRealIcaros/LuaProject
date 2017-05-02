#include "Player.hpp"

Player::Player(lua_State* L)
{
	this->texturePlayer.loadFromFile("../Images/player.png");
	this->spritePlayer.setTexture(this->texturePlayer);
	this->lookDirection = 0;
	this->spritePlayer.setTextureRect(sf::IntRect(0, 0, 16, 16));
	this->spritePlayer.setPosition(Vector2f(0.0, 0.0));

	/*lua_getglobal(L, "setPlayerPos");
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	int error = lua_pcall(L, 2, 0, 0);
	if (error)
	{
		cout << "Player.cpp Error msg: " << lua_tostring(L, -1) << endl;
		lua_pop(L, 1);
	}*/
}

Player::~Player()
{
}

void Player::update(lua_State* L, float dt)	//(float dt, lua_State* L)
{
	this->setSpritePosition(L);
	this->setLookDirection(L);
}

void Player::draw(RenderTarget &target, RenderStates states)const
{
	target.draw(spritePlayer, states);
}

void Player::setSpritePosition(lua_State* L)
{
	lua_getglobal(L, "getPlayerPos");
	lua_pcall(L, 0, 2, 0);
	if (lua_isnumber(L, -2) && lua_isnumber(L, -1))
	{
		double x = lua_tonumber(L, -2);
		double y = lua_tonumber(L, -1);
		this->spritePlayer.setPosition(x, y);
	}
	lua_pop(L, 2);
}

void Player::setLookDirection(lua_State* L)
{
	lua_getglobal(L, "getPlayerLookDirection");
	lua_pcall(L, 0, 1, 0);
	if (lua_isinteger(L, -1))
	{
		double y = lua_tointeger(L, -1);
		this->spritePlayer.setTextureRect(sf::IntRect(0, y * 16, 16, 16));
	}
	lua_pop(L, 1);
}

Sprite Player::getSprite()
{
	return this->spritePlayer;
}