#include "engine.h"
#include "time_utils.h"

Engine::Engine(void) :
window(0),
sprites(sprites_cmp)
{
	/* FIXME */
}

Engine::~Engine(void)
{
	/* FIXME */
}

void Engine::add_sprite(Sprite *sprite)
{
	this->sprites.insert(sprite);
}

void Engine::unlink_sprite(Sprite *sprite)
{
	this->sprites.erase(sprite);
}

void Engine::bind_window(GameWindow *window)
{
	/* TODO: Walidacja. */

	this->window = window;
}

void Engine::update_sprites(timestamp_t time_up)
{
	std::set<Sprite*>::iterator s;

	for (s = sprites.begin();
	     s != sprites.end(); s++)
		(*s)->update(time_up);
}

void Engine::draw(void)
{
	std::set<Sprite*>::iterator s;

	window->clear();
	for (s = sprites.begin();
	     s != sprites.end(); s++)
		(*s)->draw(window);
	window->display();
}

void Engine::exec(void)
{
	timestamp_t time_up;
	sf::Event event;

	if (!window) {
		/* FIXME: Błąd. */
	}

	/* TODO: Lepsza walidacja. */

	while (window->get_state() == GW_ACTIVE) {
		time_up = timestamp();

		update_sprites(time_up);
		draw();

		while (window->poll_event(event)) {
			if (event.type ==
			    sf::Event::Closed)
			window->set_state(GW_DESTROYED);
		}
	}
}
