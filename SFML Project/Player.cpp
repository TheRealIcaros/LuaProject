#include "Player.hpp"

Player::Player()
{
	this->texturePlayer.loadFromFile("../Images/player.png");
	this->spritePlayer.setTexture(this->texturePlayer);

	this->swingTexture.loadFromFile("../Images/swing.png");

	this->lookDirection = 0;
	this->spritePlayer.setTextureRect(sf::IntRect(0, 0, 16, 16));
	this->spritePlayer.setPosition(Vector2f(0.0, 0.0));
	this->hp = 3;

	this->spriteAnimation = 0;

	this->animationSwing = 0;
	this->isAttacking = false;

	this->hitbox.setSize(Vector2f(10.0, 14.0));
	this->hitbox.setFillColor(sf::Color(0, 100, 100, 230));
	this->hitbox.setOrigin(-3.0, -2.0);

	this->heartTexture.loadFromFile("../Images/HeartSpriteSheet.png");
	this->heart.setTexture(this->heartTexture);
	this->heart.setTextureRect(sf::IntRect(0, 0, 96, 32));
	this->heart.setPosition(Vector2f((16 - 6) * 16, 0));

}

Player::~Player()
{
}

void Player::update(lua_State* L, float dt)
{

	this->checkAttacking(L, dt);
	if (!this->isSwinging)
	{
		this->setSpritePosition(L);
	}
	this->setLookDirection(L);	
	this->updateSpriteAnimation();

	if(!this->isSwinging)
		this->spritePlayer.setTextureRect(sf::IntRect(this->spriteAnimation * 16, this->lookDirection * 16, 16, 16));

	this->hitbox.setPosition(this->spritePlayer.getPosition().x, this->spritePlayer.getPosition().y);
	this->wasAttacking = this->isAttacking;
}

void Player::draw(RenderTarget &target, RenderStates states)const
{
	target.draw(this->spritePlayer, states);
	target.draw(this->hitbox, states);
	target.draw(this->heart, states);
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
	if (!this->isSwinging)
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
	else
	{
		this->spritePlayer.setTexture(this->swingTexture);
		this->spritePlayer.setTextureRect(sf::IntRect(this->animationSwing * 30.0, this->lookDirection * 31.0, 30.0, 31.0));
		switch (this->lookDirection)
		{
		case 0:
			this->spritePlayer.setOrigin(15.0, 0.0);
			break;
		case 1:
			this->spritePlayer.setOrigin(0.0, 15.0);
			break;
		case 2:
			this->spritePlayer.setOrigin(0.0, 15.0);
			break;
		case 3:
			this->spritePlayer.setOrigin(15.0, 15.0);
			break;
		}
		if (this->time.getElapsedTime().asSeconds() >= 0.05f)
		{
			this->animationSwing++;
			this->time.restart();
		}

		if (this->animationSwing >= 4)
		{
			this->animationSwing = 0;
			this->spritePlayer.setTexture(this->texturePlayer);
			this->spritePlayer.setOrigin(0.0, 0.0);
			this->spritePlayer.setTextureRect(sf::IntRect(this->spriteAnimation * 16, this->lookDirection * 16, 16, 16));
			this->isSwinging = false;
		}
	}
}

void Player::damageHp()
{
	if (this->hp > 0)
	{
		this->hp = hp--;
	}
}

int Player::getHp()const
{
	return this->hp;
}

void Player::setPlayerPosInLua(lua_State* L, Vector2f pos)
{
	lua_getglobal(L, "setPlayerPos");
	lua_pushnumber(L, pos.x);
	lua_pushnumber(L, pos.y);
	lua_pcall(L, 2, 0, 0);
}

void Player::checkAttacking(lua_State* L, float dt)
{
	lua_getglobal(L, "getPlayerIsAttacking");
	lua_pcall(L, 0, 1, 0);
	if (lua_isboolean(L, -1))
	{
		this->isAttacking = lua_toboolean(L, -1);
	}
	lua_pop(L, 1);

	if (this->isAttacking && this->wasAttacking && !this->isSwinging)
	{
		this->isSwinging = true;
	}
}

bool Player::getIsSwinging()const
{
	return this->isSwinging;
}

RectangleShape Player::getHitbox()const
{
	return this->hitbox;
}

void Player::setPlayerPos(lua_State* L, Vector2f pos)
{
	this->setPlayerPosInLua(L, pos);
}

void Player::movePlayer(Vector2f move, lua_State* L, float dt)
{
	lua_getglobal(L, "movePlayerFromC");
	lua_pushnumber(L, move.x);
	lua_pushnumber(L, move.y);
	lua_pushnumber(L, dt);
	lua_pcall(L, 3, 0, 0);
}

void Player::setHeartPos(Vector2f pos)
{
	this->heart.setPosition(pos);
}

void Player::updateHeartSprite(lua_State* L)
{
	lua_getglobal(L, "getHp");
	lua_pcall(L, 0, 1, 0);
	if (lua_isinteger(L, -1))
	{
		this->hp = lua_tointeger(L, -1);
		lua_pop(L, 1);

		this->heart.setTextureRect(IntRect(0, 0, 32 * this->hp, 32));
	}

	if (this->hp <= 0)
	{
		this->playerKilled = true;
	}
}

bool Player::isPlayerKilled()const
{
	return this->playerKilled;
}

void Player::setPlayerDead(bool set)
{
	this->playerKilled = set;
}

void Player::restart()
{
	this->hp = 3;
	this->kills = 0;

	this->heart.setTextureRect(IntRect(0, 0, 32 * this->hp, 32));
}