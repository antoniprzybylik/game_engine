#ifndef SPRITE_SKIN_H_
#define SPRITE_SKIN_H_

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "time_utils.h"

class SpriteSkin {
public:
	virtual ~SpriteSkin(void) {};
	virtual void  update(timestamp_t) = 0;
	virtual std::shared_ptr<sf::Texture> get_current_texture(void) const = 0;
};

class TextureSkin : public SpriteSkin {
private:
	std::vector<std::shared_ptr<sf::Texture> > textures;

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
	TextureSkin(std::shared_ptr<sf::Texture>);

	/* Wiele obrazków. */
	TextureSkin(const sf::Image &image,
		    int frames_cnt,
		    int current_frame = 0);

	/* Animacja. */
	TextureSkin(const sf::Image &image,
		    int frames_cnt,
		    timestamp_t frame_duration,
		    int current_frame = 0);

	~TextureSkin(void) override;

	void request_next_frame(void);
	void request_frame(int);

	void update(timestamp_t time_up) override;
	std::shared_ptr<sf::Texture> get_current_texture(void) const override;
};

class LabelSkin : public SpriteSkin {
private:
	sf::RenderTexture rtex;
	std::shared_ptr<sf::Texture> tex;

	std::string *text_str;
	sf::RectangleShape rect;
	sf::Font font;
	sf::Text text;

public:
	LabelSkin(std::string*);
	~LabelSkin(void) override;

	void update(timestamp_t) override;
	std::shared_ptr<sf::Texture> get_current_texture(void) const override;
};

#endif /* SPRITE_SKIN_H_ */
