#ifndef ENGINE_H_
#define ENGINE_H_

#include <set>

#include "sprite.h"

/* Klasa Engine.
 *
 * Reprezentuje silnik
 * gry.
 */
class Engine {
private:
	GameWindow *window;

	std::set<Sprite*,
		 bool(*)(Sprite*, Sprite*)> sprites;

	void update_sprites(timestamp_t);
	void draw(void);

public:
	Engine(void);
	~Engine(void);

	void add_sprite(Sprite*);
	void unlink_sprite(Sprite*);
	void bind_window(GameWindow *window);

	void exec(void);
};

#endif /* ENGINE_H_ */
