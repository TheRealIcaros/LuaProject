#ifndef GAME_HPP
#define GAME_HPP

#include "Include.h"
#include "Editor.hpp"
#include "EntityContainer.hpp"
#include "Map.hpp"

class Game : public Drawable
{
private:
	Texture startTexture;
	Texture editorTexture;
	Texture exitTexture;
	Sprite start;
	Sprite editor;
	Sprite exit;

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
	vector<Vector2i*> enemySpawnPoints;

public:
	Game();
	~Game();
	void update(RenderWindow &window);
	void draw(RenderTarget &target, RenderStates states)const;

	void updateStartState();

	void updateEditorState(RenderWindow &window);

	static int playerIsAttacking(lua_State* L);
	static int CheckMovement(lua_State* L);

	Vector2i* randomEnemySpawnPoint();

	void playerTileCollision(lua_State* L);
	Vector2i getPlayArea();
	bool place_free(float dt, RectangleShape rect1, Sprite* rect2, lua_State* L, Vector2f dir);
};
#endif // !
