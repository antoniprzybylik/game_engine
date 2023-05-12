#include <SFML/Graphics.hpp>

#include "game_window.h"

GameWindow::GameWindow() :
window(std::make_unique<sf::RenderWindow>()),
u_rect(sf::Vector2f(0, 0)),
r_rect(sf::Vector2f(0, 0)),
b_rect(sf::Vector2f(0, 0)),
l_rect(sf::Vector2f(0, 0)),
state(GW_UNINITIALIZED)
{
	u_rect.setFillColor(sf::Color(255, 255, 255));
	r_rect.setFillColor(sf::Color(255, 255, 255));
	b_rect.setFillColor(sf::Color(255, 255, 255));
	l_rect.setFillColor(sf::Color(255, 255, 255));
}

GameWindow::~GameWindow(void)
{
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
	u_rect.setSize(sf::Vector2f(ext_size_x, ext_size_y/2));
	u_rect.setPosition(sf::Vector2f(-ext_size_x/2 + size_x/2, -ext_size_y/2));
	r_rect.setSize(sf::Vector2f(ext_size_x/2, ext_size_y));
	r_rect.setPosition(sf::Vector2f(size_x, 0));
	b_rect.setSize(sf::Vector2f(ext_size_x, ext_size_y/2));
	b_rect.setPosition(sf::Vector2f(0, size_y));
	l_rect.setSize(sf::Vector2f(ext_size_x/2, ext_size_y));
	l_rect.setPosition(sf::Vector2f(-ext_size_x/2, 0));

	window->draw(u_rect, sf::RenderStates::Default);
	window->draw(r_rect, sf::RenderStates::Default);
	window->draw(b_rect, sf::RenderStates::Default);
	window->draw(l_rect, sf::RenderStates::Default);

	window->display();
}

void GameWindow::draw(const sf::Drawable &drawable,
		      const sf::RenderStates &states)
{
	window->draw(drawable, states);
}

void GameWindow::set_size(double size_x, double size_y)
{
	this->size_x = size_x;
	this->size_y = size_y;

	if (window) {
		window->setSize(sf::Vector2u(size_x,
					     size_y));
	}
}

void GameWindow::set_ext_size(double size_x, double size_y)
{
	this->ext_size_x = size_x;
	this->ext_size_y = size_y;
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

void GameWindow::set_view(sf::View view)
{
	window->setView(view);
}

double GameWindow::get_size_x(void)
{
	return this->size_x;
}

double GameWindow::get_size_y(void)
{
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

sf::View GameWindow::get_default_view(void)
{
	return window->getDefaultView();
}

const sf::RenderWindow &GameWindow::get_window(void)
{
	return *window;
}
