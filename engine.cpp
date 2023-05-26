#include <memory>

#include "engine.h"
#include "time_utils.h"

Engine::Engine(void (*const on_tick)(void),
	       const int ticks_in_frame) :
window(0),
sprites(sprites_cmp),
on_tick(on_tick),
ticks_in_frame(ticks_in_frame)
{
}

Engine::~Engine(void)
{
}

void Engine::add_sprite(std::shared_ptr<Sprite> sprite)
{
	this->sprites.insert(sprite);
}

void Engine::unlink_sprite(std::shared_ptr<Sprite> sprite)
{
	this->sprites.erase(sprite);
}

void Engine::bind_window(std::shared_ptr<GameWindow> window)
{
	/* TODO: Walidacja. */

	this->window = window;
}

void Engine::update_sprites(timestamp_t time_up)
{
	std::set<std::shared_ptr<Sprite> >::iterator s;

	for (s = sprites.begin();
	     s != sprites.end(); s++)
		(*s)->update(time_up);
}

void Engine::draw(void)
{
	std::set<std::shared_ptr<Sprite> >::iterator s;

	window->clear();
	for (s = sprites.begin();
	     s != sprites.end(); s++)
		(*s)->draw(window);
	window->display();
}

void Engine::exec(void)
{
	timestamp_t time_up;
	timestamp_t delta;

	sf::Event event;
	sf::View view;

	std::set<std::shared_ptr<Sprite> >::const_iterator s;
	static bool lock_click = false;
	sf::Vector2f mouse_pos;
	sf::Vector2i mouse_pos_raw;

	if (!window) {
		throw std::runtime_error(
			"Can not execute "
			"engine without bound "
			"window.");
	}

	/* TODO: Lepsza walidacja. */

	while (window->get_state() == GW_ACTIVE) {
		time_up = timestamp();

		this->on_tick();

		update_sprites(time_up);
		draw();

		view = window->get_default_view();
		while (window->poll_event(event)) {
			if (event.type ==
			    sf::Event::Closed) {
				window->set_state(GW_DESTROYED);
			} else if (event.type ==
			    sf::Event::Resized) {
				view.setSize({
					static_cast<float>(
						event.size.width),
					static_cast<float>(
						event.size.height)
				});
				view.setCenter(window->get_size_x()/2,
					       window->get_size_y()/2);
				window->set_view(view);
				window->set_ext_size(event.size.width,
						     event.size.height);
				draw();
			}

			if (event.type ==
			    sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button ==
				    sf::Mouse::Left &&
				    lock_click != true) {
					lock_click = true;
					mouse_pos_raw = sf::Mouse::
						getPosition(
						window->get_window());
					mouse_pos.x = mouse_pos_raw.x;
					mouse_pos.y = mouse_pos_raw.y;

					for (s = sprites.begin();
					     s != sprites.end(); s++) {
						if ((*s)->get_sfml_sprite().getGlobalBounds().contains(mouse_pos))
						(*s)->on_click();
					}
				}
			}

			if (event.type ==
			    sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button ==
				    sf::Mouse::Left) {
					lock_click = false;
				}
			}
		}
		
		delta = timestamp() - time_up;
		while (delta < ticks_in_frame) {
			delta = timestamp() - time_up;
			__sync_synchronize();
		}
	}
}
