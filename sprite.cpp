#include <SFML/Graphics.hpp>
#include <memory>

#include "sprite.h"

Sprite::Sprite(std::shared_ptr<SpriteSkin> skin, int z_order) :
position(0, 0, 0, 0),
velocity(0, 0),
bounds(0, 0, 0, 0),
bounds_action(BA_NONE),
hidden(false),
a_collision(false),
a_dying(false),
a_one_cycle(false),
a_request(false),
a_requested(false),
a_collision_reduce(false)
{
	std::shared_ptr<sf::Texture> texture;

	this->skin = skin;
	this->z_order = z_order;

	this->sfml_sprite = std::make_unique<sf::Sprite>();
	
	texture = this->skin->get_current_texture();
	this->sfml_sprite->setTexture(*texture);
	this->a_previous_texture = texture;
}

Sprite::Sprite(std::shared_ptr<SpriteSkin> skin, Rect bounds,
	       enum bounds_action bounds_action,
	       int z_order) :
position(0, 0, 0, 0),
velocity(0, 0),
bounds(bounds),
bounds_action(bounds_action),
hidden(false),
a_collision(false),
a_dying(false),
a_one_cycle(false),
a_request(false),
a_requested(false),
a_collision_reduce(false)
{
	std::shared_ptr<sf::Texture> texture;

	this->skin = skin;
	this->z_order = z_order;

	this->sfml_sprite = std::make_unique<sf::Sprite>();
	
	texture = this->skin->get_current_texture();
	this->sfml_sprite->setTexture(*texture);
	this->a_previous_texture = texture;
}

enum sprite_action Sprite::update_position(timestamp_t time_up)
{
	static timestamp_t last_updated = -1;

	Point new_position;
	Vector new_velocity;

	Vector sprite_size, bounds_size;
	Vector delta_pos;

	double right_limit, left_limit;
	double top_limit, bottom_limit;
	double x, y;

	int delta_time;

	/* Pierwsze uruchomienie. */
	if (last_updated < 0) {
		last_updated = time_up;
		return SA_NONE;
	}

	delta_time = time_up - last_updated;
	last_updated = time_up;

	delta_pos.set_x((delta_time*
			 this->velocity.get_x()) /
			 1000);
	delta_pos.set_y((delta_time*
			 this->velocity.get_y()) /
			 1000);

	new_position = this->position.get_pos();
	new_position += delta_pos;

	new_velocity = velocity;

	sprite_size = this->position.get_dims();
	bounds_size = this->bounds.get_dims();

	switch (bounds_action) {
	case BA_WRAP:
		if (new_position.get_x() + sprite_size.get_x() <
		    bounds.left())
			new_position.set_x(bounds.right());
		else if (new_position.get_x() > bounds.right())
			new_position.set_x(bounds.left() -
					sprite_size.get_x());

		if (new_position.get_y() + sprite_size.get_y() <
		    bounds.top())
			new_position.set_y(bounds.bottom());
		else if (new_position.get_y() > bounds.bottom())
			new_position.set_y(bounds.top() -
					sprite_size.get_y());
		break;

	case BA_BOUNCE:
		if (new_position.get_x() < bounds.left()) {
			new_position.set_x(bounds.left());
			new_velocity.set_x(-new_velocity.get_x());
		} else if (new_position.get_x() > bounds.right()
				- sprite_size.get_x()) {
			new_position.set_x(bounds.right() -
					sprite_size.get_x());
			new_velocity.set_x(-new_velocity.get_x());
		}

		if (new_position.get_y() < bounds.top()) {
			new_position.set_y(bounds.top());
			new_velocity.set_y(-new_velocity.get_y());
		} else if (new_position.get_y() > bounds.bottom()
				- sprite_size.get_y()) {
			new_position.set_y(bounds.bottom() -
					sprite_size.get_y());
			new_velocity.set_y(-new_velocity.get_y());
		}
		break;

	case BA_DIE:
		return SA_KILL;
		break;

	case BA_STOP:
		if (new_position.get_x() < bounds.left() ||
		    new_position.get_x() > bounds.right() -
		    			sprite_size.get_x()) {
			left_limit = bounds.left();
			right_limit = bounds.right() -
				      sprite_size.get_x();
			
			x = std::max(left_limit,
				     std::min(new_position.get_x(),
					      right_limit));
			new_position.set_x(x);

			set_velocity(Vector(0, 0));
		}

		if (new_position.get_y() < bounds.top() ||
		    new_position.get_y() > bounds.bottom() -
		    			sprite_size.get_y()) {
			top_limit = bounds.top();
			bottom_limit = bounds.bottom() -
				       sprite_size.get_y();
			
			y = std::max(top_limit,
				     std::min(new_position.get_y(),
					      bottom_limit));
			new_position.set_y(y);

			set_velocity(Vector(0, 0));
		}

		break;
	
	case BA_NONE:
		break;
	}

	set_position(Rect(new_position,
			  position.get_dims()));
	set_velocity(new_velocity);

	return SA_NONE;
}

enum sprite_action Sprite::update(timestamp_t time_up)
{
	enum sprite_action sprite_action;

	if (a_dying)
		return SA_KILL;

	this->animate();

	sprite_action = update_position(time_up);
	skin->update(time_up);

	return sprite_action;
}

void Sprite::animate(void)
{
}

void Sprite::on_click(void)
{
}

void Sprite::draw(std::shared_ptr<GameWindow> window)
{
	std::shared_ptr<sf::Texture> texture;

	texture = skin->get_current_texture();
	if (texture != a_previous_texture) {
		sfml_sprite->setTexture(*texture);
		a_previous_texture = texture;
	}

	if (!this->hidden)
		window->draw(*sfml_sprite);
}

Rect Sprite::get_position(void) const
{
	return this->position;
}

Vector Sprite::get_velocity(void) const
{
	return this->velocity;
}

const sf::Sprite &Sprite::get_sfml_sprite(void) const
{
	return *sfml_sprite;
}

void Sprite::set_position(Rect position)
{
	double pos_x = position.get_pos_x();
	double pos_y = position.get_pos_y();

	this->position = position;
	this->sfml_sprite->setPosition(pos_x, pos_y);
}

void Sprite::set_velocity(Vector velocity)
{
	this->velocity = velocity;
}

void Sprite::set_hidden(bool hidden)
{
	this->hidden = hidden;
}

Sprite::~Sprite(void)
{
}

bool sprites_cmp(std::shared_ptr<Sprite> a,
		 std::shared_ptr<Sprite> b)
{
	if (a->z_order < b->z_order)
		return 1;

	if (a->z_order > b->z_order)
		return 0;

	return a < b;
}
