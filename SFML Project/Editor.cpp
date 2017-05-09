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

	this->materialSelected = -1;

	this->E = luaL_newstate();
	/*int error = luaL_loadfile(this->E, "../Lua Scripts/Editor.lua") || lua_pcall(this->E, 0, 1, 0);
	if (error)
	{
		cout << "Error msg: " << lua_tostring(this->E, -1) << endl;
		lua_pop(this->E, 1);
	}*/

	Vector2i startPos = Vector2i(50, 50);
	vector <Node*> mapRow;
	for (int x = 0; x < 16; x++)
	{
		this->map.push_back(mapRow);
		for (int y = 0; y < 16; y++)
		{
			this->map[x].push_back(new Node());
			this->map[x][y]->setPosition(startPos.x + (x * 16), startPos.y + (y * 16));
		}
	}
}

Editor::~Editor()
{
	for (int x = 0; x < this->map.size(); x++)
	{
		for (int y = 0; y < 16; y++)
		{
			delete this->map[x][y];
		}
	}
	lua_close(this->E);
}

void Editor::update(RenderWindow &window)
{
	this->checkMaterials(window);
	this->getMousePos(window);
}

void Editor::draw(RenderTarget &target, RenderStates states)const
{
	target.draw(this->grass, states);
	target.draw(this->wall, states);
	target.draw(this->water, states);

	target.draw(this->border, states);

	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			target.draw(*this->map[x][y], states);
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
		for (int x = 0; x < 16; x++ && !found)
		{
			for (int y = 0; y < 16; y++ && !found)
			{
				if (this->map[x][y]->getSprite().getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
				{
					this->map[x][y]->setMaterial(this->materialSelected);
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