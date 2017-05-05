#include "Include.h"
#include "EntityContainer.hpp"
#include "Game.hpp"
//
//static int CheckMovement(lua_State* L);
//static int MousePosition(lua_State* L);
//static int CheckEditorInput(lua_State* L);
//int lookDirection = 0;
//bool wasPressed;
//int selectedBlock = 0;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	sf::RenderWindow window(sf::VideoMode(400, 400), "The legend of Lucas!");
	window.setFramerateLimit(60);

	/*lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	int error;

	lua_pushcfunction(L, CheckMovement);
	lua_setglobal(L, "CheckMovement");

	error = luaL_loadfile(L, "../Lua Scripts/EntityHandler.lua") || lua_pcall(L, 0, 1, 0);
	if (error)
	{
		cout << "Error msg: " << lua_tostring(L, -1) << endl;
		lua_pop(L, 1);
	}

	lua_getglobal(L, "Start");
	lua_pcall(L, 0, 0, 0);

	EntityContainer et(L);
	Clock dt;*/
	Game g;
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}

		g.update(window);

		window.clear();
		window.draw(g);
		window.display();

		//lua_getglobal(L, "Update");
		//lua_pushnumber(L, dt.restart().asSeconds());
		//int error = lua_pcall(L, 1, 0, 0);
		//if (error)
		//{
		//	cout << "Update Error msg: " << lua_tostring(L, -1) << endl;
		//	lua_pop(L, 1);
		//}

		//bool isPressed = Keyboard::isKeyPressed(Keyboard::O);
		//if (isPressed && !wasPressed)
		//{
		//	wasPressed = true;
		//	et.addEnemy(L);
		//}

		//et.update(L, dt.getElapsedTime().asSeconds());

		///*Vector2i pos = Mouse::getPosition(window);
		//cout << pos.x << ", " << pos.y << endl;*/

		//window.clear();
		//window.draw(g);
		//window.draw(et);
		//window.display();

		//wasPressed = isPressed;
	}

	return 0;
}

//static int CheckMovement(lua_State* L)
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
//		lookDirection = 3;
//	}
//
//	if (Keyboard::isKeyPressed(Keyboard::W))
//	{
//		dir.y = -1;
//		lookDirection = 1;
//	}
//	if (Keyboard::isKeyPressed(Keyboard::S))
//	{
//		dir.y = 1;
//		lookDirection = 0;
//	}
//
//	lua_pushnumber(L, dir.x);
//	lua_pushnumber(L, dir.y);
//	lua_pushinteger(L, lookDirection);
//
//	return 3;
//}
//
//static int CheckEditorInput(lua_State* L)
//{
//	if (Keyboard::isKeyPressed(Keyboard::Num1))
//	{
//		selectedBlock = 1;
//	}
//	else if (Keyboard::isKeyPressed(Keyboard::Num2))
//	{
//		selectedBlock = 2;
//	}
//	else if (Keyboard::isKeyPressed(Keyboard::Num3))
//	{
//		selectedBlock = 3;
//	}
//
//	lua_pushinteger(L, selectedBlock);
//
//	return 1;
//}
//
//static int MousePosition(lua_State* L)
//{
//	if (Mouse::isButtonPressed(Mouse::Left))
//	{
//		Vector2i pos = Mouse::getPosition();
//
//		lua_pushinteger(L, pos.x);
//		lua_pushinteger(L, pos.y);
//
//		return 2;
//	}
//	else
//		return 0;
//}