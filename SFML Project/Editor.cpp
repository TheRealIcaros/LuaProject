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

	this->border.setSize(Vector2f(32.0f, 32.0f));
	this->border.setPosition(Vector2f(-32.0f, 0.0f));
	this->border.setFillColor(Color::Transparent);
	this->border.setOutlineColor(Color::Blue);
	this->border.setOutlineThickness(-3.0f);

	this->saveButton.setSize(Vector2f(32, 32));
	this->saveButton.setPosition(Vector2f(768, 0));
	this->saveButton.setFillColor(Color::Yellow);

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

	//while (!(this->sizeXY == 16 || this->sizeXY == 32 || this->sizeXY == 46))
	//{
	//	cout << "Select a map size [16, 32, 46]: ";
	//	cin >> this->sizeXY;
	//	cout << endl;
	//}
	//lua_getglobal(this->E, "setMapSize");
	//lua_pushinteger(this->E, this->sizeXY);
	//error = lua_pcall(this->E, 1, 0, 0);
	//if (error)
	//{
	//	cout << "MapSize Error msg: " << lua_tostring(this->E, -1) << endl;
	//	lua_pop(this->E, 1);
	//}

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

Editor::~Editor()
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
	

	lua_close(this->E);
}

void Editor::update(RenderWindow &window)
{
	this->checkMaterials(window);
	this->getMousePos(window);

	this->saveOnFile(this->E, window);
}

void Editor::draw(RenderTarget &target, RenderStates states)const
{
	target.draw(this->grass, states);
	target.draw(this->wall, states);
	target.draw(this->water, states);

	target.draw(this->border, states);
	target.draw(this->saveButton, states);

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

			cout << "Grass Selected" << endl;
			this->materialSelected = 0;
		}
		if (this->wall.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && this->materialSelected != 1)
		{
			this->border.setPosition(32.0f, 0.0f);

			cout << "Wall  Selected" << endl;
			this->materialSelected = 1;
		}
		if (this->water.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) && this->materialSelected != 2)
		{
			this->border.setPosition(64.0f, 0.0f);

			cout << "Water Selected" << endl;
			this->materialSelected = 2;
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