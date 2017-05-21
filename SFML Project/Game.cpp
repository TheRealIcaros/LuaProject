#include "Game.hpp"

Game::Game() : edit()
{
	this->startTexture.loadFromFile("../Images/StartMenu.png");
	this->start.setTexture(this->startTexture);
	this->start.setPosition(Vector2f(60.0f, 42.0f));

	this->editorTexture.loadFromFile("../Images/EditorMenu.png");
	this->editor.setTexture(this->editorTexture);
	this->editor.setPosition(Vector2f(60.0f, 134.0f));

	this->exitTexture.loadFromFile("../Images/QuitMenu.png");
	this->exit.setTexture(this->exitTexture);
	this->exit.setPosition(Vector2f(60.0f, 228.0f));


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

	//text
	if (!this->font.loadFromFile("../Font/BebasNeue.otf"))
		cout << "Can't find font" << endl;

	//Set the font to text
	this->playerKills.setFont(font);

	this->playerKills.setString("Kills: 0");
	this->playerKills.setCharacterSize(15);
	this->playerKills.setFillColor(sf::Color::Red);
	this->playerKills.setPosition(0.0, 0.0);
	this->playerKills.setStyle(sf::Text::Bold);

	//Set the font to text wave
	this->wave.setFont(font);

	this->wave.setString("wave: 0");
	this->wave.setCharacterSize(15);
	this->wave.setFillColor(sf::Color::Red);
	this->wave.setPosition(0.0, 0.0);
	this->wave.setStyle(sf::Text::Bold);

	srand(time(0));
}

Game::~Game()
{
	this->enemySpawnPoints.clear();

	lua_close(this->L);
}

void Game::update(RenderWindow &window)
{
	float nowDt = this->dt.getElapsedTime().asSeconds();

	if ((Keyboard::isKeyPressed(Keyboard::F1) && (this->startStateOn || this->editorStateOn)) || this->et.isPlayerDead())
	{
		if (this->et.isPlayerDead())
		{
			displayDeadScreen(window);
		}

		cout << "Returning to Main Menu" << endl;

		this->resizeWindow(window, 16);

		this->startStateOn = false;
		this->editorStateOn = false;

		this->map.clearVector();
		this->map.resetTables(this->L);
		this->map.resetMapFound();
		this->map.clearBarrier();

		this->et.restart(this->L);
	}

	if (!this->startStateOn && !this->editorStateOn)
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (this->start.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
			{
				cout << "Entering Game State" << endl;
				this->startStateOn = true;

				this->playerSpawn = map.loadFromFile(L, window);

				this->resizeWindow(window, map.getMapSize());

				this->et.setPlayerSpawnPos(this->L, this->playerSpawn);
				this->enemySpawnPoints = this->map.findEnemySpawnPoints();
				//set heart pos on screan
				this->playerKills.setPosition(0.0, 0.0);
				this->wave.setPosition(((this->map.getMapSize() * 16) / 2) - 32, 0.0);
				this->et.setHeartPos(Vector2f((this->map.getMapSize() - 2) * 16, 0));
				this->map.addBarrier();
			}
			if (this->editor.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
			{
				cout << "Entering Editor State" << endl;

				this->resizeWindow(window, 46);

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
		this->updateStartState(nowDt);
	}

	if (this->editorStateOn)
	{
		this->updateEditorState(window);
	}
	this->dt.restart();
}

void Game::draw(RenderTarget &target, RenderStates states)const
{
	if (!this->et.isPlayerDead())
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
	else
	{

	}
}

void Game::updateStartState(float dt)
{
	updateKills(this->L);
	//Check Player Collision
	this->playerTileCollision(dt, L);

	//Update Lua
	lua_getglobal(this->L, "Update");
	lua_pushnumber(this->L, dt);
	int error = lua_pcall(this->L, 1, 0, 0);
	if (error)
	{
		cout << "Update Error msg: " << lua_tostring(this->L, -1) << endl;
		lua_pop(this->L, 1);
	}

	//Spawn Enemy
	bool isPressed = Keyboard::isKeyPressed(Keyboard::O);
	if (isPressed && !this->wasPressed)
	{
		Vector2i enemySpawn = randomEnemySpawnPoint();
		et.addEnemy(this->L, enemySpawn.x, enemySpawn.y);
		this->wasPressed = true;
	}

	if (this->et.getEnemys().empty())
	{
		waveStarted = false;
	}

	if (!waveStarted)
	{
		if (this->et.getEnemys().size() < this->et.getWave() + 2)
		{
			if (enemySpawnTime.getElapsedTime().asSeconds() > timeDelay)
			{
				Vector2i enemySpawn = randomEnemySpawnPoint();
				et.addEnemy(this->L, enemySpawn.x, enemySpawn.y);
				this->enemySpawnTime.restart();
			}
		}

		if (this->et.getEnemys().size() == this->et.getWave() + 2)
		{
			this->waveStarted = true;
			this->et.increaseWave();
			this->updateWave();
		}
	}

	//Update Sprites
	this->et.update(this->L, dt);

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
		else if (Keyboard::isKeyPressed(Keyboard::A))
		{
			dir.x = -1;
			lookDirection = 3;
		}
		else if (Keyboard::isKeyPressed(Keyboard::W))
		{
			dir.y = -1;
			lookDirection = 1;
		}
		else if (Keyboard::isKeyPressed(Keyboard::S))
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

Vector2i Game::randomEnemySpawnPoint()
{
	int number = (rand() * this->enemySpawnTime.getElapsedTime().asMicroseconds()) % this->enemySpawnPoints.size();

	return this->enemySpawnPoints[number];
}

void Game::playerTileCollision(float dt, lua_State* L)
{
	Vector2f dir;
	lua_getglobal(L, "getPlayerDir");
	lua_pcall(L, 0, 2, 0);
	if (lua_isnumber(L, -1) && lua_isnumber(L, -2))
	{
		dir.y = lua_tonumber(L, -1);
		dir.x = lua_tonumber(L, -2);
		lua_pop(L, 2);
	}

	Vector2i tile;
	for (int x = -1; x < 2; x++)
	{
		tile.x = this->getPlayArea().x + x;

		if (tile.x > this->map.getMapSize() - 1)
		{
			tile.x = 0;
		}
		else if (tile.x < 0)
		{
			tile.x = this->map.getMapSize() - 1;
		}

		for (int y = -1; y < 2; y++)
		{
			tile.y = this->getPlayArea().y + y;
			if (tile.y > this->map.getMapSize() - 1)
			{
				tile.y = 0;
			}
			else if (tile.y < 0)
			{
				tile.y = this->map.getMapSize() - 1;
			}

			if (this->map.CompareTexture(tile, 1))
			{
				if (this->et.getPlayer().getHitbox().getGlobalBounds().intersects(this->map.getSprite(tile)->getGlobalBounds()))		
				{
					this->collisionTile(dir, tile);
				}
			}
		}
	}
	Vector2i temp = this->getPlayArea();
	if (temp.x > this->map.getMapSize() - 1)
	{
		temp.x = 0;
	}
	else if (temp.x < 0)
	{
		temp.x = this->map.getMapSize() - 1;
	}
	if (temp.y > this->map.getMapSize() - 1)
	{
		temp.y = 0;
	}
	else if (temp.y < 0)
	{
		temp.y = this->map.getMapSize() - 1;
	}
	if (this->map.CompareTexture(temp, 2))
	{
		lua_getglobal(this->L, "isOnWater");
		lua_pushboolean(this->L, true);
		lua_pcall(this->L, 1, 0, 0);
	}
	else
	{
		lua_getglobal(this->L, "isOnWater");
		lua_pushboolean(this->L, false);
		lua_pcall(this->L, 1, 0, 0);
	}
	for (int i = 0; i < 4; i++)
	{
		if (this->et.getPlayer().getHitbox().getGlobalBounds().intersects(this->map.getBarrier(i)->getGlobalBounds()))
		{
			this->collisionBarrier(dir, i);
		}
	}

	lua_getglobal(L, "setCanMove");
	lua_pushboolean(L, canMoveUp);
	lua_pushboolean(L, canMoveDown);
	lua_pushboolean(L, canMoveLeft);
	lua_pushboolean(L, canMoveRight);
	lua_pcall(L, 4, 0, 0);


	lua_getglobal(L, "getCanMove");
	lua_pcall(L, 0, 4, 0);
	canMoveUp = lua_toboolean(L, -4);
	canMoveDown = lua_toboolean(L, -3);
	canMoveLeft = lua_toboolean(L, -2);
	canMoveRight = lua_toboolean(L, -1);
}

Vector2i Game::getPlayArea()
{
	int x = (int)this->et.getPlayer().getHitbox().getPosition().x + 8;
	int y = (int)this->et.getPlayer().getHitbox().getPosition().y + 9;
	Vector2i result;
	Vector2i startPos = Vector2i(32, 32);
	result.y = ((x - startPos.x) / 16) % this->map.getMapSize();
	result.x = ((y - startPos.y) / 16) % this->map.getMapSize();
	return result;
}

void Game::resizeWindow(RenderWindow &window, int size)
{
	sf::View view;

	switch (size)
	{
	case 16:
		window.setSize(Vector2u(320, 320));
		view = View(FloatRect(0, 0, 320, 320));
		break;
	case 32:
		window.setSize(Vector2u(576, 576));
		view = View(FloatRect(0, 0, 576, 576));
		break;
	case 46:
		window.setSize(Vector2u(800, 800));
		view = View(FloatRect(0, 0, 800, 800));
		break;
	}
	window.setView(view);
}

void Game::drawText(RenderWindow &window)
{
	if (startStateOn)
	{
		window.draw(playerKills);
		window.draw(wave);
	}
	else if (this->et.isPlayerDead())
	{
		lua_getglobal(this->L, "getKills");
		lua_pcall(this->L, 0, 1, 0);
		if (lua_isinteger(this->L, -1))
		{
			int tempKills = lua_tointeger(this->L, -1);
			lua_pop(this->L, 1);

			stringstream temp;
			temp << "Game Over! \nYou got " << tempKills << " kills. \nYou reached Wave: " << this->et.getWave();
			this->playerKills.setString(temp.str());
			this->playerKills.setPosition(window.getSize().x / 2 - temp.str().length(), (window.getSize().y / 2) - 16);

		
			window.draw(this->playerKills);
		}
	}
}

void Game::updateKills(lua_State* L)
{
	lua_getglobal(L, "getKills");
	lua_pcall(L, 0, 1, 0);
	if (lua_isinteger(L, -1))
	{
		int tempKills = lua_tointeger(L, -1);
		lua_pop(L, 1);

		stringstream temp;
		temp << "kills: " << tempKills;
		this->playerKills.setString(temp.str());
	}
}

void Game::updateWave()
{

	stringstream temp;
	temp << "Wave: " << this->et.getWave();
	this->wave.setString(temp.str());

}

void Game::displayDeadScreen(RenderWindow& window)
{
	this->startStateOn = false;
	this->editorStateOn = false;

	window.clear();
	this->drawText(window);
	window.display();

	system("Pause");

	this->et.setPlayerDead(false);
}

void Game::collisionTile(Vector2f dir, Vector2i tile)
{
	Vector2f pos;
	if (dir.y < 0.0)
	{
		canMoveUp = false;
		pos.x = this->et.getPlayer().getSprite().getPosition().x;
		pos.y = this->map.tileBottom(tile.x, tile.y) - 2;
		this->et.setPlayerPos(L, pos);
	}
	else if (dir.y > 0.0) //Down
	{
		canMoveDown = false;
		pos.x = this->et.getPlayer().getSprite().getPosition().x;
		pos.y = this->map.tileTop(tile.x, tile.y) - 16;
		this->et.setPlayerPos(L, pos);
	}
	else if (dir.x < 0.0) //Left
	{
		canMoveLeft = false;
		pos.y = this->et.getPlayer().getSprite().getPosition().y;
		pos.x = this->map.tileRight(tile.x, tile.y) - 3;
		this->et.setPlayerPos(L, pos);
	}
	else if (dir.x > 0.0) //Right
	{
		canMoveRight = false;
		pos.y = this->et.getPlayer().getSprite().getPosition().y;
		pos.x = this->map.tileLeft(tile.x, tile.y) - 13;
		this->et.setPlayerPos(L, pos);
	}
}

void Game::collisionBarrier(Vector2f dir, int i)
{
	Vector2f pos;
	if (dir.y < 0.0)
	{
		canMoveUp = false;
		pos.x = this->et.getPlayer().getSprite().getPosition().x;
		pos.y = this->map.getBarrier(i)->getPosition().x + 16 - 2;
		this->et.setPlayerPos(L, pos);
	}
	else if (dir.y > 0.0) //Down
	{
		canMoveDown = false;
		pos.x = this->et.getPlayer().getSprite().getPosition().x;
		pos.y = this->map.getBarrier(i)->getPosition().y - 16;
		this->et.setPlayerPos(L, pos);
	}
	else if (dir.x < 0.0) //Left
	{
		canMoveLeft = false;
		pos.y = this->et.getPlayer().getSprite().getPosition().y;
		pos.x = this->map.getBarrier(i)->getPosition().x + 16 - 3;
		this->et.setPlayerPos(L, pos);
	}
	else if (dir.x > 0.0) //Right
	{
		canMoveRight = false;
		pos.y = this->et.getPlayer().getSprite().getPosition().y;
		pos.x = this->map.getBarrier(i)->getPosition().x - 13;
		this->et.setPlayerPos(L, pos);
	}
}