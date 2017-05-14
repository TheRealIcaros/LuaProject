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


	bool mapFound = false;

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
};
#endif
