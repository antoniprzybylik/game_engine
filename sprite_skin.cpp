#include <time.h>

#include "sprite_skin.h"

/* Jedna tekstura. */
SpriteSkin::SpriteSkin(sf::Texture *texture) :
animated(false),
frames_cnt(1),
current_frame(0),
a_request_frame(false),
a_requested_frame(0)
{
	this->textures.resize(1);
	this->textures[0] = texture;
}

/* Wiele obrazków. */
SpriteSkin::SpriteSkin(const sf::Image &image,
		       int frames_cnt,
	   	       int current_frame) :
animated(false),
frames_cnt(frames_cnt),
current_frame(current_frame),
a_request_frame(false),
a_requested_frame(0)
{
	int i;
	int frame_width, frame_height;

	frame_width = image.getSize().x / frames_cnt;
	frame_height = image.getSize().y;

	this->textures.resize(frames_cnt);
	for (i = 0; i < frames_cnt; i++) {
		this->textures[i] = new sf::Texture;
		this->textures[i]->loadFromImage(image,
				sf::IntRect(i*frame_width, 0,
					    frame_width,
					    frame_height));
	}
}

/* Animacja. */
SpriteSkin::SpriteSkin(const sf::Image &image,
	   	       int frames_cnt,
	   	       timestamp_t frame_duration,
	   	       int current_frame) :
animated(true),
frames_cnt(frames_cnt),
current_frame(current_frame),
frame_duration(frame_duration),
a_request_frame(false),
a_requested_frame(0)
{
	int i;
	int frame_width, frame_height;

	frame_width = image.getSize().x / frames_cnt;
	frame_height = image.getSize().y;

	this->textures.resize(frames_cnt);
	for (i = 0; i < frames_cnt; i++) {
		this->textures[i] = new sf::Texture;
		this->textures[i]->loadFromImage(image,
				sf::IntRect(i*frame_width, 0,
					    frame_width,
					    frame_height));
	}
}

void SpriteSkin::request_next_frame(void)
{
	if (a_request_frame) {
		a_requested_frame += 1;	
		return;
	}

	a_requested_frame = current_frame + 1;
	if (a_requested_frame >= frames_cnt)
		a_requested_frame = 0;

	a_request_frame = true;
}

void SpriteSkin::request_frame(int frame)
{
	/* TODO: Sprawdzanie poprawności
	 * 	 danych. */

	a_requested_frame = frame;
	a_request_frame = true;
}

void SpriteSkin::update(timestamp_t time)
{
	static timestamp_t last_triggered = -1;

	/* Pierwsze uruchomienie. */
	if (last_triggered < 0) {
		last_triggered = time;
		return;
	}

	/* Żądanie konkretnej ramki. */
	if (a_request_frame) {
		current_frame = a_requested_frame;

		/* Jeżeli skórka jest animowana,
		 * żądana ramka ma być widoczna
		 * przez co najmniej jeden cykl. */
		if (animated)
			last_triggered = time;

		return;
	}

	if (!animated)
		return;

	/* Animacja. */
	if (time - last_triggered >=
	    frame_duration) {
		last_triggered = time;
		current_frame = current_frame + 1;
		if (current_frame >= frames_cnt)
			current_frame = 0;
	}
}

sf::Texture *SpriteSkin::get_current_texture(void) const
{
	return textures[current_frame];
}

SpriteSkin::~SpriteSkin(void)
{
	/* FIXME */
}
