#include "Game.hpp"

Game::Game() : edit()
{
	this->startTexture.loadFromFile("../Images/StartMenu.png");
	this->start.setTexture(this->startTexture);
	this->start.setPosition(Vector2f(300.0f, 75.0f));

	this->editorTexture.loadFromFile("../Images/EditorMenu.png");
	this->editor.setTexture(this->editorTexture);
	this->editor.setPosition(Vector2f(300.0f, 175.0f));

	this->exitTexture.loadFromFile("../Images/QuitMenu.png");
	this->exit.setTexture(this->exitTexture);
	this->exit.setPosition(Vector2f(300.0f, 275.0f));

	this->L = luaL_newstate();
	luaL_openlibs(this->L);

	lua_pushcfunction(this->L, Game::CheckMovement);
	lua_setglobal(this->L, "CheckMovement");

	lua_pushcfunction(this->L, Game::playerIsAttacking);
	lua_setglobal(this->L, "playerIsAttacking");

	int error = luaL_loadfile(this->L, "../Lua Scripts/Game.lua") || lua_pcall(this->L, 0, 1, 0);
	if (error)
	{
		cout << "Error msg: " << lua_tostring(this->L, -1) << endl;
		lua_pop(this->L, 1);
	}

	lua_getglobal(L, "Start");
	lua_pcall(this->L, 0, 0, 0);

	this->et = EntityContainer(this->L);
	this->map = Map();

	this->wasPressed = false;
	this->selectedBlock = 0;

	this->startStateOn = false;
	this->editorStateOn = false;
}

Game::~Game()
{
	for (int x = 0; x < this->enemySpawnPoints.size(); x++)
	{
		delete this->enemySpawnPoints[x];
	}

	this->enemySpawnPoints.clear();

	lua_close(this->L);
}

void Game::update(RenderWindow &window)
{
	if (Keyboard::isKeyPressed(Keyboard::F1) && (this->startStateOn || this->editorStateOn))
	{
		cout << "Returning to Main Menu" << endl;
		this->startStateOn = false;
		this->editorStateOn = false;
	}


	if (Keyboard::isKeyPressed(Keyboard::R))
		this->et.restart(this->L);

	if (!this->startStateOn && !this->editorStateOn)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (this->start.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
			{
				cout << "Entering Game State" << endl;
				this->startStateOn = true;
				this->dt.restart();

				this->playerSpawn = map.loadFromFile(L, window);
				this->et.setPlayerSpawnPos(this->L, this->playerSpawn);
				this->enemySpawnPoints = this->map.findEnemySpawnPoints();
			}
			if (this->editor.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
			{
				cout << "Entering Editor State" << endl;
				this->editorStateOn = true;
			}
			if (this->exit.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
			{
				window.close();
			}
		}
	}
	
	if (this->startStateOn)
	{
		this->updateStartState();
	}

	if (this->editorStateOn)
	{
		this->updateEditorState(window);
	}
}

void Game::draw(RenderTarget &target, RenderStates states)const
{
	if (!this->startStateOn && !this->editorStateOn)
	{
		target.draw(this->start, states);
		target.draw(this->editor, states);
		target.draw(this->exit, states);
	}

	if (this->startStateOn)
	{
		target.draw(this->map, states);
		target.draw(this->et, states);
	}

	if (this->editorStateOn)
	{
		target.draw(this->edit, states);
	}
}

void Game::updateStartState()
{
	this->playerTileCollision(L);
	lua_getglobal(this->L, "Update");
	lua_pushnumber(this->L, this->dt.getElapsedTime().asSeconds());
	int error = lua_pcall(this->L, 1, 0, 0);
	if (error)
	{
		cout << "Update Error msg: " << lua_tostring(this->L, -1) << endl;
		lua_pop(this->L, 1);
	}
	bool isPressed = Keyboard::isKeyPressed(Keyboard::O);
	if (isPressed && !this->wasPressed)
	{
		Vector2i* enemySpawn = randomEnemySpawnPoint();
		this->wasPressed = true;
		et.addEnemy(this->L, enemySpawn->x, enemySpawn->y);
	}
	this->et.update(this->L, this->dt.getElapsedTime().asSeconds());

	this->dt.restart();

	this->wasPressed = isPressed;
}

void Game::updateEditorState(RenderWindow &window)
{
	this->edit.update(window);
}

int Game::playerIsAttacking(lua_State* L)
{
	bool isAttacking = Keyboard::isKeyPressed(Keyboard::Space);

	lua_pushboolean(L, isAttacking);

	return 1;
}

int Game::CheckMovement(lua_State* L)
{
	Vector2f dir(0.0, 0.0);
	if (lua_isinteger(L, -1))
	{
		int lookDirection = lua_tointeger(L, -1);
		lua_pop(L, 1);

		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			dir.x = 1;
			lookDirection = 2;
		}
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			dir.x = -1;
			lookDirection = 3;
		}

		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			dir.y = -1;
			lookDirection = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			dir.y = 1;
			lookDirection = 0;
		}

		lua_pushnumber(L, dir.x);
		lua_pushnumber(L, dir.y);
		lua_pushinteger(L, lookDirection);

		return 3;
	}
	else
	{
		lua_pop(L, 1);
		return 0;
	}
}

Vector2i* Game::randomEnemySpawnPoint()
{
	/*default_random_engine generator;
	uniform_int_distribution<int> distribution(0, this->enemySpawnPoints.size());

	int number = distribution(generator);*/

	/*srand(time(NULL));
	//int number = rand() % this->enemySpawnPoints.size();
	//
	//cout << number << endl;
	//
	//return this->enemySpawnPoints.at(number);*/

	random_device rd;
	uniform_int_distribution<int> uniDistribution(0, this->enemySpawnPoints.size() -1);
	int number = uniDistribution(rd);
	return this->enemySpawnPoints.at(number);
}

void Game::playerTileCollision(lua_State* L)
{
	Vector2f dir;
	lua_getglobal(L, "getPlayerDir");
	lua_pcall(L, 0, 2, 0);
	if (lua_isinteger(L, -1) && lua_isinteger(L, -2))
	{
		dir.x = lua_tointeger(L, -1);
		dir.y = lua_tointeger(L, -2);
		lua_pop(L, 2);
	}

	Vector2i tile;
	for (int y = -1; y < 2; y++)
	{
		tile.y = getPlayArea().y + y;

		if (tile.y > this->map.getMapSize() - 1)
		{
			tile.y = 0;
		}
		else if (tile.y < 0)
		{
			tile.y = this->map.getMapSize() - 1;
		}
		for (int x = -1; x < 2; x++)
		{
			tile.x = getPlayArea().x + x;
			if (tile.x > this->map.getMapSize() - 1)
			{
				tile.x = 0;
			}
			else if (tile.x < 0)
			{
				tile.x = this->map.getMapSize() - 1;
			}

			//Player Move + Collision
			if (this->map.CompareTexture(tile))
			{
				//cout << "Tile" << endl;
				if (!this->place_free(this->dt.getElapsedTime().asSeconds(), this->et.getPlayer().getHitbox(), this->map.getSprite(tile), L, dir))
				{
					//cout << "Wall hit" << endl;
					if (dir.x > 0.0)
					{

					}
					else if (dir.x < 0.0)
					{

					}
					if (dir.y > 0.0)
					{

					}
					else if (dir.y < 0.0)
					{

					}
					dir.x = 0.0;
					dir.y = 0.0;

					/*lua_getglobal(L, "setPlayerDir");
					lua_pushnumber(L, dir.x);
					lua_pushnumber(L, dir.y);
					lua_pcall(L, 2, 0, 0);*/
				}
			}
		}
	}
}

Vector2i Game::getPlayArea()
{
	int x = (int)this->et.getPlayer().getHitbox().getPosition().x + 8;
	int y = (int)this->et.getPlayer().getHitbox().getPosition().y + 9;
	Vector2i result;
	Vector2i startPos = Vector2i(32, 32);
	result.y = ((x - startPos.x) / 16) % this->map.getMapSize();
	result.x = ((y - startPos.y) / 16) % this->map.getMapSize();
	//cout << result.x << ", " << result.y << endl;
	return result;
}

bool Game::place_free(float dt, RectangleShape rect1, Sprite* rect2, lua_State* L, Vector2f dir)
{
	bool result = true;
	
	rect1.setPosition(rect1.getPosition() + (dt * 75 * dir));

	if (rect1.getGlobalBounds().intersects(rect2->getGlobalBounds()))
	{
		result = false;
	}

	return result;
}