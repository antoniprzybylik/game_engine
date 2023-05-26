#include <ctime>
#include <cstdint>

#include "sprite_skin.h"

/* Jedna tekstura. */
TextureSkin::TextureSkin(std::shared_ptr<sf::Texture> texture) :
animated(false),
frames_cnt(1),
current_frame(0),
a_request_frame(false),
a_requested_frame(0)
{
	this->textures.resize(1);
	this->textures[0] = texture;
	this->textures[0]->setSmooth(false);
}

/* Wiele obrazków. */
TextureSkin::TextureSkin(const sf::Image &image,
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
		this->textures[i] = std::make_shared<sf::Texture>();
		this->textures[i]->loadFromImage(image,
				sf::IntRect(i*frame_width, 0,
					    frame_width,
					    frame_height));
		this->textures[i]->setSmooth(false);
	}
}

/* Animacja. */
TextureSkin::TextureSkin(const sf::Image &image,
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
		this->textures[i] = std::make_shared<sf::Texture>();
		this->textures[i]->loadFromImage(image,
				sf::IntRect(i*frame_width, 0,
					    frame_width,
					    frame_height));
		this->textures[i]->setSmooth(false);
	}
}

void TextureSkin::request_next_frame(void)
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

void TextureSkin::request_frame(int frame)
{
	if (frame >= frames_cnt) {
		throw std::invalid_argument(
			"Frame number too big.");
	}

	a_requested_frame = frame;
	a_request_frame = true;
}

void TextureSkin::update(timestamp_t time)
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

std::shared_ptr<sf::Texture> TextureSkin::get_current_texture(void) const
{
	return textures[current_frame];
}

TextureSkin::~TextureSkin(void)
{
}

extern char _binary_font_arial_ttf_start[];
extern char _binary_font_arial_ttf_end[];

LabelSkin::LabelSkin(std::string *text_str) :
tex(std::make_shared<sf::Texture>()),
text_str(text_str),
rect(sf::Vector2f(260.0f, 20.0f))
{
	rect.setFillColor(sf::Color(255, 0, 0));

	font.loadFromMemory(_binary_font_arial_ttf_start,
			    (size_t)
			    ((uint64_t) _binary_font_arial_ttf_end -
			     (uint64_t) _binary_font_arial_ttf_start));

	rtex.create(260, 20);

	text = sf::Text(sf::String(*text_str),
			font, text_str->size());
	text.setCharacterSize(16);
	rtex.draw(rect);
	rtex.draw(text);
	rtex.display();
	*(this->tex) = this->rtex.getTexture();
}

LabelSkin::~LabelSkin(void)
{
}

void LabelSkin::update(timestamp_t timestamp)
{
	text = sf::Text(sf::String(*text_str),
			font, text_str->size());
	text.setCharacterSize(16);
	rtex.draw(rect);
	rtex.draw(text);
	rtex.display();
	*(this->tex) = this->rtex.getTexture();
}

std::shared_ptr<sf::Texture> LabelSkin::get_current_texture(void) const
{
	return this->tex;
}
