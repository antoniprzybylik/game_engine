#ifndef GAME_WINDOW_H_
#define GAME_WINDOW_H_

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

#include "algebra.h"

/* Stan okna gry:
 *
 * UNINITIALIZED
 *   Obiekt stworzony, okno
 *   nie zostało utworzone.
 *
 * ACTIVE
 *   Okno stworzone.
 *
 * DESTROYED
 *   Okno zamknięte.
 */
enum game_window_state {
	GW_UNINITIALIZED,
	GW_ACTIVE,
	GW_DESTROYED,
};

/* Klasa GameWindow.
 *
 * Reprezentuje okno gry.
 */
class GameWindow {
private:
	std::unique_ptr<sf::RenderWindow> window;

	sf::RectangleShape u_rect;
	sf::RectangleShape r_rect;
	sf::RectangleShape b_rect;
	sf::RectangleShape l_rect;

	double size_x;
	double size_y;
	double ext_size_x;
	double ext_size_y;
	std::string title;
	/* TODO: Ikonka. */

	enum game_window_state state;

	void create(void);
	void destroy(void);

public:
	GameWindow(void);
	~GameWindow(void);

	bool poll_event(sf::Event &event);

	void clear(void);
	void display(void);
	void draw(const sf::Drawable &drawable,
		  const sf::RenderStates &states=
		  		sf::RenderStates::Default);

	void set_size(Vector size);
	void set_size(double size_x, double size_y);
	void set_ext_size(double size_x, double size_y);
	void set_title(std::string title);
	void set_state(enum game_window_state);
	void set_view(sf::View);

	double get_size_x(void);
	double get_size_y(void);
	std::string get_title(void);
	enum game_window_state get_state(void);
	sf::View get_default_view(void);
	sf::RenderWindow &get_window(void);
};

#endif /* GAME_WINDOW_H_ */
