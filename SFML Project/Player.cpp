#include "Player.hpp"

Player::Player()
{
	this->texturePlayer.loadFromFile("../Images/player.png");
	this->spritePlayer.setTexture(this->texturePlayer);

	this->lookDirection = 0;
	this->spritePlayer.setTextureRect(sf::IntRect(0, 0, 16, 16));
	this->spritePlayer.setPosition(Vector2f(0.0, 0.0));
	this->hp = 3;

	this->spriteAnimation = 0;
}

Player::~Player()
{
}

void Player::update(lua_State* L, float dt)	//(float dt, lua_State* L)
{
	this->setSpritePosition(L);
	this->setLookDirection(L);	
	this->updateSpriteAnimation();

	this->spritePlayer.setTextureRect(sf::IntRect(this->spriteAnimation * 16, this->lookDirection * 16, 16, 16));
}

void Player::draw(RenderTarget &target, RenderStates states)const
{
	target.draw(this->spritePlayer, states);
}

void Player::setSpritePosition(lua_State* L)
{
	lua_getglobal(L, "getPlayerPos");
	lua_pcall(L, 0, 2, 0);
	if (lua_isnumber(L, -2) && lua_isnumber(L, -1))
	{
		float x = lua_tonumber(L, -2);
		float y = lua_tonumber(L, -1);
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
		this->lookDirection = lua_tointeger(L, -1);
	}
	lua_pop(L, 1);
}

Sprite Player::getSprite()const
{
	return this->spritePlayer;
}

void Player::updateSpriteAnimation()
{
	if (this->time.getElapsedTime().asSeconds() >= 0.33f)
	{
		this->time.restart();
		if (this->spriteAnimation == 0)
			this->spriteAnimation = 1;
		else
			this->spriteAnimation = 0;
	}
}

void Player::damageHp()
{
	if (this->hp > 0)
	{
		this->hp = hp--;
	}
	if (this->hp == 0)
		cout << "You are dead! LOSER!" << endl;
}

int Player::getHp()
{
	return this->hp;
}

void Player::setPlayerPosInLua(lua_State* L, Vector2i pos)
{
	lua_getglobal(L, "setPlayerPos");
	lua_pushinteger(L, pos.x);
	lua_pushinteger(L, pos.y);
	lua_pcall(L, 2, 0, 0);
}