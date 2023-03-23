#include <SFML/Graphics.hpp>

#include "game_window.h"

GameWindow::GameWindow()
{
	this->window = new sf::RenderWindow();
	this->state = GW_UNINITIALIZED;
}

GameWindow::~GameWindow(void)
{
	delete this->window;
}

void GameWindow::create(void)
{
	window->create(sf::VideoMode(size_x, size_y),
		       sf::String(title));
}

void GameWindow::destroy(void)
{
	window->close();
}

bool GameWindow::poll_event(sf::Event &event)
{
	return window->pollEvent(event);
}

void GameWindow::clear(void)
{
	window->clear();
}

void GameWindow::display(void)
{
	window->display();
}

void GameWindow::draw(const sf::Drawable &drawable,
		      const sf::RenderStates &states)
{
	window->draw(drawable, states);
}

void GameWindow::set_size(int size_x, int size_y)
{
	this->size_x = size_x;
	this->size_y = size_y;

	if (window) {
		window->setSize(sf::Vector2u(size_x,
					     size_y));
	}
}

void GameWindow::set_title(std::string title)
{
	this->title = title;

	if (window)
		window->setTitle(sf::String(title));
}

void GameWindow::set_state(
		enum game_window_state state)
{
	if (this->state == GW_UNINITIALIZED &&
	    state == GW_ACTIVE) {
		this->state = state;
		this->create();
	} else if (this->state == GW_ACTIVE &&
		   state == GW_DESTROYED) {
		this->state = state;
		this->destroy();
	} else {
		/* FIXME: Zabronione. */
	}
}

int GameWindow::get_size_x(void)
{
	/* Update size. */
	this->size_x = window->getSize().x;

	return this->size_x;
}

int GameWindow::get_size_y(void)
{
	/* Update size. */
	this->size_y = window->getSize().y;

	return this->size_y;
}

std::string GameWindow::get_title(void)
{
	return this->title;
}

enum game_window_state GameWindow::get_state(void)
{
	return state;
}
