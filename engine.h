#ifndef ENGINE_H_
#define ENGINE_H_

#include <SFML/Graphics.hpp>
#include <memory>
#include <set>

#include "sprite.h"

/* Klasa Engine.
 *
 * Reprezentuje silnik
 * gry.
 */
class Engine {
private:
	std::shared_ptr<GameWindow> window;

	std::set<std::shared_ptr<Sprite>,
		 bool(*)(std::shared_ptr<Sprite>,
			 std::shared_ptr<Sprite>)> sprites;

	void update_sprites(timestamp_t);
	void draw(void);

	void (*const on_tick)(void);
	const int ticks_in_frame;

public:
	Engine(void (*const on_tick)(),
	       const int ticks_in_frame);
	~Engine(void);

	void add_sprite(std::shared_ptr<Sprite>);
	void unlink_sprite(std::shared_ptr<Sprite>);
	void bind_window(std::shared_ptr<GameWindow>);

	void exec(void);
};

#endif /* ENGINE_H_ */
