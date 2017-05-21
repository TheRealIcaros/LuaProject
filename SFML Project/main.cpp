#include "Include.h"
#include "EntityContainer.hpp"
#include "Game.hpp"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

int main()
{
#ifdef _DEBUG
	// Same as using _CrtDumpMemoryLeaks(); at every exit
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// Break at allocation 18. The number of the leaking allocation is shown in message of previous run.
	//_CrtSetBreakAlloc(18);
#endif

	//_CrtSetBreakAlloc(8540);
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	sf::RenderWindow window(sf::VideoMode(320, 320), "The legend of Lucas!");
	window.setFramerateLimit(60);

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
		g.drawText(window);
		window.display();
	}

	return 0;
}