#include "Game.hpp"

Game::Game(lua_State* L)
{
	this->L = L;
	bool wasPressed = false;

	int lookDirection = 0;
}

Game::~Game()
{
	//lua_close(L);
}

void Game::update(lua_State* L)
{
	
}

void Game::draw(RenderTarget &target, RenderStates states)const
{

}

//int Game::CheckMovement(lua_State* L)
//{
//	Vector2f dir;
//
//	if (Keyboard::isKeyPressed(Keyboard::D))
//	{
//		dir.x = 1;
//		lookDirection = 2;
//	}
//	if (Keyboard::isKeyPressed(Keyboard::A))
//	{
//		dir.x = -1;
//		this->lookDirection = 3;
//	}
//
//	if (Keyboard::isKeyPressed(Keyboard::W))
//	{
//		dir.y = -1;
//		this->lookDirection = 1;
//	}
//	if (Keyboard::isKeyPressed(Keyboard::S))
//	{
//		dir.y = 1;
//		this->lookDirection = 0;
//	}
//
//	lua_pushnumber(L, dir.x);
//	lua_pushnumber(L, dir.y);
//	lua_pushinteger(L, this->lookDirection);
//
//	return 3;
//}