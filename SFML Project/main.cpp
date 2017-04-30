#include "Include.h"
#include "Player.hpp"
#include "Enemy.hpp"

static int CheckMovement(lua_State* L);

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "The legend of Lucas!");
	window.setFramerateLimit(60);

	lua_State* L = luaL_newstate();
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

	Player p(0, 0, L);
	Enemy e(50, 50, L);
	Clock dt;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
				window.close();
		}

		lua_getglobal(L, "Update");
		lua_pushnumber(L, dt.restart().asSeconds());
		error = lua_pcall(L, 1, 0, 0);
		if (error)
		{
			cout << "Update Error msg: " << lua_tostring(L, -1) << endl;
			lua_pop(L, 1);
		}

		p.update(L);

		window.clear();
		window.draw(p);
		window.draw(e);
		window.display();
	}

	lua_close(L);

	return 0;
}

static int CheckMovement(lua_State* L)
{
	Vector2f dir;

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		dir.y = -1;
		cout << "W" << endl;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		cout << "S" << endl;
		dir.y = 1;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		dir.x = 1;
		cout << "D" << endl;
	}
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		cout << "A" << endl;
		dir.x = -1;
	}

	/*
	if ((dir.x > 0 || dir.x < 0) && (dir.y > 0 || dir.y < 0))
	{
		dir.x = dir.x * 0.707;
		dir.y = dir.y * 0.707;
	}
	*/

	lua_pushnumber(L, dir.x);
	lua_pushnumber(L, dir.y);

	return 2;
}

/*if (Keyboard::isKeyPressed(sf::Keyboard::Left) && !pressed)
{
//pressed = true;
lua_getglobal(L, "playerColor");
if (!lua_istable(L, -1))
{
cout << "Error msg: " << lua_tostring(L, -1) << endl;
lua_pop(L, 1);
}
else
{
lua_pushstring(L, "r");
lua_gettable(L, -2);
int colorR;

if (lua_type(L, -1) == LUA_TNUMBER)
colorR = lua_tonumber(L, -1);
lua_pop(L, 1);

shape.setFillColor(Color(colorR, 0, 0));


}
lua_pop(L, -1);
}*/