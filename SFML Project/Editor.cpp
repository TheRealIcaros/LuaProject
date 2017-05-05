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
}

Editor::~Editor()
{

}

void Editor::update(RenderWindow &window)
{
	this->checkMaterials(window);
}

void Editor::draw(RenderTarget &target, RenderStates states)const
{
	target.draw(this->grass, states);
	target.draw(this->wall, states);
	target.draw(this->water, states);

	target.draw(this->border, states);
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

int Editor::getMaterialSelected()
{
	return this->materialSelected;
}