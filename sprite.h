#ifndef SPRITE_H_
#define SPRITE_H_

#include <SFML/Graphics.hpp>
#include <memory>

#include "sprite_skin.h"
#include "game_window.h"
#include "algebra.h"

/* Akcja wykonywana kiedy
 * duszek dojdzie do krawędzi
 * okna.
 */
enum bounds_action {
	BA_STOP,
	BA_WRAP,
	BA_BOUNCE,
	BA_DIE,
	BA_NONE,
};

enum sprite_action {
	SA_NONE,
	SA_KILL,
	SA_ADDSPRITE,
};

class Sprite;
bool sprites_cmp(std::shared_ptr<Sprite> a,
		 std::shared_ptr<Sprite> b);

class Sprite {
protected:
	std::shared_ptr<SpriteSkin> skin;
	std::unique_ptr<sf::Sprite> sfml_sprite;

	Rect position;
	Vector velocity;

	int z_order;

	Rect bounds;
	enum bounds_action bounds_action;
	bool hidden;

	Vector a_collision; // TODO
	bool a_dying; // TODO
	bool a_one_cycle; // TODO
	bool a_request; // TODO
	bool a_requested; // TODO
	bool a_collision_reduce; // TODO
	
	std::shared_ptr<sf::Texture> a_previous_texture;

	enum sprite_action update_position(timestamp_t);

public:
	Sprite(std::shared_ptr<SpriteSkin> skin, int z_order=0);
	Sprite(std::shared_ptr<SpriteSkin> skin, Rect bounds,
	       enum bounds_action bounds_action,
	       int z_order = 0);
	virtual ~Sprite(void);

	virtual
	enum sprite_action update(timestamp_t time_up);
	void draw(std::shared_ptr<GameWindow>);
	virtual void animate(void);
	virtual void on_click(void);

	bool is_point_inside(double x, double y) const;
	bool test_collision(Sprite *sprite) const;

	Rect get_position(void) const;
	Vector get_velocity(void) const;
	int get_z_order(void) const;
	const sf::Sprite &get_sfml_sprite(void) const;

	void set_position(Rect);
	void set_velocity(Vector);
	void set_hidden(bool);
	void set_z_order(int);

	friend
	bool sprites_cmp(std::shared_ptr<Sprite> a,
			 std::shared_ptr<Sprite> b);
};

#endif /* SPRITE_H_ */
