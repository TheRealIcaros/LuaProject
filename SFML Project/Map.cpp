#include "Map.hpp"

Map::Map()
{
	if (!this->grassTexture.loadFromFile("../Images/grass.png"))
	{
		cout << "Wall image not found!" << endl;
	}
	if (!this->wallTexture.loadFromFile("../Images/wall.png"))
	{
		cout << "Grass image not found!" << endl;
	}
	if (!this->waterTexture.loadFromFile("../Images/water.png"))
	{
		cout << "Water image not found!" << endl;
	}
	if (!this->spawnEnemyTexture.loadFromFile("../Images/spawnpoint.png"))
	{
		cout << "Spawnpoint enemy image not found!" << endl;
	}
	if (!this->spawnPlayerTexture.loadFromFile("../Images/playerspawn.png"))
	{
		cout << "Spawnpoint player image not found!" << endl;
	}

	this->reloadVectors();
}

Map::~Map()
{
	this->clearVector();
}

void Map::update(RenderWindow &window)
{
}

void Map::draw(RenderTarget &target, RenderStates states)const
{
	for (int y = 0; y < this->map.size(); y++)
	{
		for (int x = 0; x < this->map[y].size(); x++)
		{
			target.draw(*this->map[y][x], states);
		}
	}
}

Vector2i Map::loadFromFile(lua_State* L, RenderWindow &window)
{
	while (!mapFound)
	{
		cout << "Write a name of the map: ";
		string input;
		cin >> input;
		cout << endl;

		lua_getglobal(L, "loadFromFile");
		lua_pushstring(L, input.c_str());
		int error = lua_pcall(L, 1, 1, 0);
		if (error)
		{
			cout << "load Lrror msg: " << lua_tostring(L, -1) << endl;
			lua_pop(L, 1);
		}

		mapFound = lua_toboolean(L, -1);
		lua_pop(L, 1);

		if (mapFound)
		{
			reloadSprites(L);
			mapFound = checkPlayerSpawnArea();
		}
	}

	if (mapFound)
	{
		return this->playerSpawn;
	}

	return Vector2i(-1, -1);
}

void Map::reloadSprites(lua_State* L)
{
	lua_getglobal(L, "getMapSize");
	lua_pcall(L, 0, 1, 0);

	this->sizeXY = lua_tointeger(L, -1);
	lua_pop(L, 1);

	clearVector();
	reloadVectors();

	for (int y = 0; y < this->map.size(); y++)
	{
		for (int x = 0; x < this->map[y].size(); x++)
		{
			lua_getglobal(L, "getMaterial");
			lua_pushinteger(L, x);
			lua_pushinteger(L, y);
			int error = lua_pcall(L, 2, 1, 0);
			if (error)
			{
				cout << "reload Error msg: " << lua_tostring(L, -1) << endl;
				lua_pop(L, 1);
			}

			int temp = lua_tointeger(L, -1);
			lua_pop(L, 1);

			switch (temp)
			{
			case 0:
				this->map[y][x]->setTexture(this->grassTexture);
				break;
			case 1:
				this->map[y][x]->setTexture(this->wallTexture);
				break;
			case 2:
				this->map[y][x]->setTexture(this->waterTexture);
				break;
			case 3:
				this->map[y][x]->setTexture(this->spawnEnemyTexture);
				break;
			case 4:
				this->map[y][x]->setTexture(this->spawnPlayerTexture);
				break;
			}
		}
	}
}

void Map::reloadVectors()
{
	Vector2i startPos = Vector2i(32, 32);
	vector <Sprite*> mapRow;
	for (int y = 0; y < sizeXY; y++)
	{
		this->map.push_back(mapRow);
		for (int x = 0; x < sizeXY; x++)
		{
			this->map[y].push_back(new Sprite());
			this->map[y][x]->setTexture(this->grassTexture);
			this->map[y][x]->setPosition(startPos.x + (x * 16), startPos.y + (y * 16));
		}
	}
}

void Map::clearVector()
{
	for (int y = 0; y < this->map.size(); y++)
	{
		for (int x = 0; x < this->map[y].size(); x++)
		{
			delete this->map[y][x];
		}

		this->map[y].clear();
	}
	this->map.clear();
}

bool Map::checkPlayerSpawnArea()
{
	int found = 0;
	for (int y = 0; y < this->map.size(); y++ && found <= 1)
	{
		for (int x = 0; x < this->map[y].size(); x++ && found <= 1)
		{
			if (this->map[x][y]->getTexture() == &this->spawnPlayerTexture)
			{
				found++;
				playerSpawn.x = y;
				playerSpawn.y = x;
			}
		}
	}

	if (found > 1)
	{
		cout << "To many player spawns [Blue Spawn Point]. Only 1 works." << endl;
		return false;
	}
	else if (found == 0)
	{
		cout << "No player spawns found [Blue Spawn Point]. Only 1 works." << endl;
		return false;
	}
	return true;
}

vector<Vector2i*> Map::findEnemySpawnPoints()
{
	vector<Vector2i*> enemySpawnPoints;
	for (int y = 0; y < this->map.size(); y++)
	{
		for (int x = 0; x < this->map[y].size(); x++)
		{
			if (this->map[x][y]->getTexture() == &this->spawnEnemyTexture)
			{
				enemySpawnPoints.push_back(new Vector2i(y, x));
			}
		}
	}

	cout << enemySpawnPoints.size() << endl;
	return enemySpawnPoints;
}

int Map::getMapSize()const
{
	return this->sizeXY;
}

bool Map::CompareTexture(Vector2i pos)
{
	bool result = false;

	if (this->map[pos.x][pos.y]->getTexture() == &this->wallTexture)
	{
		result = true;
	}

	return result;
}