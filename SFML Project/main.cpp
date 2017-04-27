#include "Include.h"
#include "Player.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	int error = luaL_loadfile(L, "../Lua Scripts/Player.lua") || lua_pcall(L, 0, 1, 0);
	if (error)
	{
		cout << "Error msg: " << lua_tostring(L, -1) << endl;
		lua_pop(L, 1);
	}

	Player p(5, 5, L);

	Clock dt;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		p.update(dt.restart().asMilliseconds(), L);

		window.clear();
		window.draw(p);
		window.display();
	}

	return 0;
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