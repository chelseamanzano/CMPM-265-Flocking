#include "Vehicle.h"

RenderWindow window;


int main()
{
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "CMPM-265 | Flocking | Chelsea Manzano");
	srand(static_cast<unsigned>(time(NULL)));
	Clock clock;

	Vehicle v(Vector2f(200, 300));
	v.create();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		v.setTarget(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y));

		float dt = clock.restart().asSeconds();

		window.clear();
		v.update(dt);
		v.draw();
		window.display();
	}
	return 0;
}
