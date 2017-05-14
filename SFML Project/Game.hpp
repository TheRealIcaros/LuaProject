#ifndef GAME_HPP
#define GAME_HPP

#include "Include.h"
#include "Editor.hpp"
#include "EntityContainer.hpp"
#include "Map.hpp"

class Game : public Drawable
{
private:
	RectangleShape start;
	RectangleShape editor;
	RectangleShape exit;

	lua_State* L;
	EntityContainer et;
	Clock dt;
	Editor edit;
	Map map;

	//int lookDirection;
	bool wasPressed;
	int selectedBlock;

	bool startStateOn;
	bool editorStateOn;

	Vector2i playerSpawn;

public:
	Game();
	~Game();
	void update(RenderWindow &window);
	void draw(RenderTarget &target, RenderStates states)const;

	void updateStartState();

	void updateEditorState(RenderWindow &window);

	static int CheckMovement(lua_State* L);
};
#endif // !
