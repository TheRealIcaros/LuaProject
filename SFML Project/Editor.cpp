#include "Editor.hpp"

Editor::Editor()
{
	if (!this->grassTexture.loadFromFile("../Images/grass.png"))
	{
		cout << "Wall image not found!" << endl;
	}
	this->grass.setTexture(this->grassTexture);
	this->grass.setPosition(0.0f, 0.0f);
	this->grass.setTextureRect(sf::IntRect(0, 0, 16, 16));
	this->grass.scale(2.0f, 2.0f);

	if (!this->wallTexture.loadFromFile("../Images/wall.png"))
	{
		cout << "Grass image not found!" << endl;
	}
	this->wall.setTexture(this->wallTexture);
	this->wall.setPosition(32.0f, 0.0f);
	this->wall.setTextureRect(sf::IntRect(0, 0, 16, 16));
	this->wall.scale(2.0f, 2.0f);

	if (!this->waterTexture.loadFromFile("../Images/water.png"))
	{
		cout << "Water image not found!" << endl;
	}
	this->water.setTexture(this->waterTexture);
	this->water.setPosition(64.0f, 0.0f);
	this->water.setTextureRect(sf::IntRect(0, 0, 16, 16));
	this->water.scale(2.0f, 2.0f);

	if (!this->spawnEnemyTexture.loadFromFile("../Images/spawnpoint.png"))
	{
		cout << "Spawnpoint enemy image not found!" << endl;
	}
	this->spawnEnemy.setTexture(this->spawnEnemyTexture);
	this->spawnEnemy.setPosition(96.0f, 0.0f);
	this->spawnEnemy.setTextureRect(sf::IntRect(0, 0, 16, 16));
	this->spawnEnemy.scale(2.0f, 2.0f);

	if (!this->spawnPlayerTexture.loadFromFile("../Images/playerspawn.png"))
	{
		cout << "Spawnpoint player image not found!" << endl;
	}
	this->spawnPlayer.setTexture(this->spawnPlayerTexture);
	this->spawnPlayer.setPosition(128.0f, 0.0f);
	this->spawnPlayer.setTextureRect(sf::IntRect(0, 0, 16, 16));
	this->spawnPlayer.scale(2.0f, 2.0f);

	//Border
	this->border.setSize(Vector2f(32.0f, 32.0f));
	this->border.setPosition(Vector2f(-32.0f, 0.0f));
	this->border.setFillColor(Color::Transparent);
	this->border.setOutlineColor(Color::Blue);
	this->border.setOutlineThickness(-3.0f);

	//Save, Load and New Map Button
	this->saveTexture.loadFromFile("../Images/Save.png");
	this->saveButton.setTexture(this->saveTexture);
	this->saveButton.setPosition(Vector2f(768, 0));

	this->loadTexture.loadFromFile("../Images/Load.png");
	this->loadButton.setTexture(this->loadTexture);
	this->loadButton.setPosition(Vector2f(736, 0));

	this->newTexture.loadFromFile("../Images/Reset.png");
	this->newButton.setTexture(this->newTexture);
	this->newButton.setPosition(Vector2f(704, 0));


	//Resize Map Buttons
	this->smallTexture.loadFromFile("../Images/Size16.png");
	this->smallButton.setTexture(this->smallTexture);
	this->smallButton.setPosition(Vector2f(400, 0));

	this->mediumTexture.loadFromFile("../Images/Size32.png");
	this->mediumButton.setTexture(this->mediumTexture);
	this->mediumButton.setPosition(Vector2f(432, 0));

	this->largeTexture.loadFromFile("../Images/Size46.png");
	this->largeButton.setTexture(this->largeTexture);
	this->largeButton.setPosition(Vector2f(464, 0));

	this->materialSelected = -1;

	this->E = luaL_newstate();
	luaL_openlibs(this->E);
	int error = luaL_loadfile(this->E, "../Lua Scripts/Editor.lua") || lua_pcall(this->E, 0, 0, 0);
	if (error)
	{
		cout << "Editor Load Error msg: " << lua_tostring(this->E, -1) << endl;
		lua_pop(this->E, 1);
	}

	lua_getglobal(E, "Start");
	lua_pcall(this->E, 0, 0, 0);
	this->sizeXY = 16;

	reloadVectors();
}

Editor::~Editor()
{
	clearVector();
	

	lua_close(this->E);
}

void Editor::update(RenderWindow &window)
{
	this->checkMaterials(window);
	this->getMousePos(window);

	this->saveOnFile(this->E, window);
	this->loadFromFile(this->E, window);
	this->newMap(this->E, window);

	this->changeMapSize(E, window);
}

void Editor::draw(RenderTarget &target, RenderStates states)const
{
	target.draw(this->grass, states);
	target.draw(this->wall, states);
	target.draw(this->water, states);
	target.draw(this->spawnEnemy, states);
	target.draw(this->spawnPlayer, states);

	target.draw(this->border, states);
	target.draw(this->saveButton, states);
	target.draw(this->loadButton, states);
	target.draw(this->newButton, states);

	target.draw(this->smallButton, states);
	target.draw(this->mediumButton, states);
	target.draw(this->largeButton, states);

	for (int y = 0; y < this->map.size(); y++)
	{
		for (int x = 0; x < this->map[y].size(); x++)
		{
			target.draw(*this->map[y][x], states);
		}
	}
}

void Editor::checkMaterials(RenderWindow &window)
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		if (this->grass.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && this->materialSelected != 0)
		{
			this->border.setPosition(0.0f, 0.0f);

			system("CLS");
			cout << "Grass Selected" << endl;
			this->materialSelected = 0;
		}
		if (this->wall.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && this->materialSelected != 1)
		{
			this->border.setPosition(32.0f, 0.0f);

			system("CLS");
			cout << "Wall  Selected" << endl;
			this->materialSelected = 1;
		}
		if (this->water.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && this->materialSelected != 2)
		{
			this->border.setPosition(64.0f, 0.0f);

			system("CLS");
			cout << "Water Selected" << endl;
			this->materialSelected = 2;
		}
		if (this->spawnEnemy.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && this->materialSelected != 3)
		{
			this->border.setPosition(96.0f, 0.0f);

			system("CLS");
			cout << "Spawn Enemy Selected" << endl;
			this->materialSelected = 3;
		}
		if (this->spawnPlayer.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && this->materialSelected != 4)
		{
			this->border.setPosition(128.0f, 0.0f);

			system("CLS");
			cout << "Spawn Player Selected" << endl;
			this->materialSelected = 4;
		}
	}
}

void Editor::getMousePos(RenderWindow &window)
{
	Vector2i mousePos = Mouse::getPosition(window);

	bool found = false;
	if (Mouse::isButtonPressed(Mouse::Right))
	{
		for (int y = 0; y < this->map.size(); y++ && !found)
		{
			for (int x = 0; x < this->map[y].size(); x++ && !found)
			{
				if (this->map[y][x]->getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
				{
					lua_getglobal(this->E, "setMaterial");
					lua_pushinteger(this->E, x);
					lua_pushinteger(this->E, y);
					lua_pushinteger(this->E, this->materialSelected);
					lua_pcall(this->E, 3, 0, 0);

					switch (this->materialSelected)
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

					found = true;
				}
			}
		}
	}

}

int Editor::getMaterialSelected()
{
	return this->materialSelected;
}

void Editor::saveOnFile(lua_State* E, RenderWindow &window)
{
	if (Mouse::isButtonPressed(Mouse::Left) && this->saveButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
	{
		int found = 0;
		for (int y = 0; y < this->map.size(); y++ && found <= 1)
		{
			for (int x = 0; x < this->map[y].size(); x++ && found <= 1)
			{
				if (this->map[x][y]->getTexture() == &this->spawnPlayerTexture)
				{
					found++;
				}
			}
		}

		if (found > 1)
		{
			system("CLS");
			cout << "To many player spawns [Blue Spawn Point]. Only 1 works." << endl;
		}
		else if (found == 0)
		{
			system("CLS");
			cout << "No player spawns found [Blue Spawn Point]. Only 1 works." << endl;
		}
		else
		{
			system("CLS");
			cout << "Write a name on the map: ";
			string input;
			cin >> input;
			cout << endl;

			lua_getglobal(E, "printToTxt");
			lua_pushstring(E, input.c_str());
			int error = lua_pcall(E, 1, 0, 0);
			if (error)
			{
				cout << "Save Error msg: " << lua_tostring(this->E, -1) << endl;
				lua_pop(this->E, 1);
			}
		}
	}
}

void Editor::loadFromFile(lua_State* E, RenderWindow &window)
{
	if (Mouse::isButtonPressed(Mouse::Left) && this->loadButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
	{
		cout << "Write a name of the map: ";
		string input;
		cin >> input;
		cout << endl;

		lua_getglobal(E, "loadFromFile");
		lua_pushstring(E, input.c_str());
		int error = lua_pcall(E, 1, 0, 0);
		if (error)
		{
			cout << "load Error msg: " << lua_tostring(this->E, -1) << endl;
			lua_pop(this->E, 1);
		}

		reloadSprites(E);
	}
}

void Editor::reloadSprites(lua_State* E)
{
	lua_getglobal(E, "getMapSize");
	lua_pcall(E, 0, 1, 0);

	this->sizeXY = lua_tointeger(E, -1);
	lua_pop(E, 1);

	clearVector();
	reloadVectors();

	for (int y = 0; y < this->map.size(); y++)
	{
		for (int x = 0; x < this->map[y].size(); x++)
		{
			lua_getglobal(this->E, "getMaterial");
			lua_pushinteger(this->E, x);
			lua_pushinteger(this->E, y);
			int error = lua_pcall(this->E, 2, 1, 0);
			if (error)
			{
				cout << "reload Error msg: " << lua_tostring(this->E, -1) << endl;
				lua_pop(this->E, 1);
			}

			int temp = lua_tointeger(E, -1);
			lua_pop(E, 1);

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

void Editor::reloadVectors()
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

void Editor::clearVector()
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

void Editor::newMap(lua_State* E, RenderWindow &window)
{
	if (Mouse::isButtonPressed(Mouse::Left) && this->newButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
	{
		clearVector();
		reloadVectors();
	}
}

void Editor::changeMapSize(lua_State* E, RenderWindow &window)
{
	if (Mouse::isButtonPressed(Mouse::Left) && this->smallButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
	{
		setMapSize(E, 16);
	}
	else if (Mouse::isButtonPressed(Mouse::Left) && this->mediumButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
	{
		setMapSize(E, 32);
	}
	else if (Mouse::isButtonPressed(Mouse::Left) && this->largeButton.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
	{
		setMapSize(E, 46);
	}
}

void Editor::setMapSize(lua_State* E, int size)
{
	lua_getglobal(E, "setMapSize");
	lua_pushinteger(E, size);
	lua_pcall(E, 1, 0, 0);

	this->sizeXY = size;

	clearVector();
	reloadVectors();
}
