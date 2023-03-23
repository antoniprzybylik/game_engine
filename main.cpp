#include <iostream>
#include <vector>

#include "engine.h"
#include "sprite.h"
#include "sprite_skin.h"
#include "game_window.h"
#include "algebra.h"
#include "time_utils.h"

Engine *game_init(void)
{
	GameWindow *window;

	sf::Image *tiles;
	Sprite *sprite;
	SpriteSkin *skin;

	Engine *engine;

	int win_x, win_y;

	/* Okno gry. */
	window = new GameWindow();

	window->set_size(200, 200);
	window->set_title(std::string("Engine test."));
	window->set_state(GW_ACTIVE);

	/* Nasz duszek. */
	tiles = new sf::Image();
	if(!tiles->loadFromFile("rc/blocks.png")) {
		std::cerr << "Error: Loading recources failure.\n";
		return 0;
	}

	win_x = window->get_size_x();
	win_y = window->get_size_y();

	skin = new SpriteSkin(*tiles, 3, 500, 1);
	sprite = new Sprite(skin,
			    Rect(0, 0, win_x, win_y),
			    BA_BOUNCE);
	sprite->set_position(Rect(100, 100, 75, 75));
	sprite->set_velocity(Vector(120, 250));

	/* Silnik. */
	engine = new Engine();
	engine->bind_window(window);
	engine->add_sprite(sprite);

	return engine;
}

int main(void)
{
	Engine *engine;

	engine = game_init();
	if (!engine) {
		std::cerr << "Error: Game "
			     "initialization failed.\n";
		return(-1);
	}

	engine->exec();

	return(0);
}
