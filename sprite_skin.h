#ifndef SPRITE_SKIN_H_
#define SPRITE_SKIN_H_

#include <SFML/Graphics.hpp>
#include <vector>

#include "time_utils.h"

class SpriteSkin {
private:
	std::vector<sf::Texture*> textures;

	bool animated;

	int frames_cnt;
	int current_frame;
	timestamp_t frame_duration;

	/* Zaplanowane do wykonania
	 * synchronicznego. */
	bool a_request_frame;
	int a_requested_frame;

public:
	/* Jedna tekstura. */
	SpriteSkin(sf::Texture *texture);

	/* Wiele obrazków. */
	SpriteSkin(const sf::Image &image,
		   int frames_cnt,
		   int current_frame = 0);

	/* Animacja. */
	SpriteSkin(const sf::Image &image,
		   int frames_cnt,
		   timestamp_t frame_duration,
		   int current_frame = 0);

	~SpriteSkin(void);

	void request_next_frame(void);
	void request_frame(int);

	void update(timestamp_t time_up);
	sf::Texture *get_current_texture(void) const;
};

#endif /* SPRITE_SKIN_H_ */
