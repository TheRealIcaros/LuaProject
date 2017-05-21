#ifndef MAP_HPP
#define MAP_HPP

#include "Include.h"

class Map : public Drawable
{
private:
	Texture grassTexture;
	Texture wallTexture;
	Texture waterTexture;
	Texture spawnEnemyTexture;
	Texture spawnPlayerTexture;

	Font font;
	Text playerKills;

	bool mapFound = false;

	vector<Sprite*> barrier;

	Vector2i playerSpawn;
	vector<vector <Sprite*>> map;
	int sizeXY;

public:
	Map();
	~Map();
	void update(RenderWindow &window);
	void draw(RenderTarget &target, RenderStates states)const;

	Vector2i loadFromFile(lua_State* L, RenderWindow &window);
	void reloadSprites(lua_State* L);

	void reloadVectors();
	void clearVector();
	bool checkPlayerSpawnArea();
	vector<Vector2i> findEnemySpawnPoints();

	int getMapSize()const;
	bool CompareTexture(Vector2i pos, int texture);
	Sprite* getSprite(Vector2i pos)const;

	float tileLeft(int x, int y);
	float tileRight(int x, int y);
	float tileTop(int x, int y);
	float tileBottom(int x, int y);

	void resetTables(lua_State* L);
	void resetMapFound();
	bool checkEnemySpawnArea();
	void addBarrier();
	void clearBarrier();
	Sprite* getBarrier(int i);
};
#endif
