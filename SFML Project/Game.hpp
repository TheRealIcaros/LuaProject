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

	Font font;
	Text playerKills;
	Text wave;

	Clock enemySpawnTime;
	float timeDelay = 0.2f;

	bool waveStarted = false;

	bool wasPressed;
	int selectedBlock;

	bool startStateOn;
	bool editorStateOn;

	Vector2i playerSpawn;
	vector<Vector2i> enemySpawnPoints;

	bool temp = true;

	bool canMoveUp = true;
	bool canMoveDown = true;
	bool canMoveLeft = true;
	bool canMoveRight = true;

public:
	Game();
	~Game();
	void update(RenderWindow &window);
	void draw(RenderTarget &target, RenderStates states)const;

	void updateStartState(float dt);

	void updateEditorState(RenderWindow &window);

	static int playerIsAttacking(lua_State* L);
	static int CheckMovement(lua_State* L);

	Vector2i randomEnemySpawnPoint();

	void playerTileCollision(float dt, lua_State* L);
	Vector2i getPlayArea();
	void resizeWindow(RenderWindow &window, int size);
	void drawText(RenderWindow &window);
	void updateKills(lua_State* L);
	void updateWave();
	void displayDeadScreen(RenderWindow& window);
	void collisionTile(Vector2f dir, Vector2i tile);
	void collisionBarrier(Vector2f dir, int i);
};
#endif // !
