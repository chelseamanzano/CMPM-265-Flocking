#include "Vehicle.h"
#include "VehicleSystem.h"

RenderWindow window;


int main()
{
	window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "CMPM-265 | Flocking | Chelsea Manzano");
	srand(static_cast<unsigned>(time(NULL)));
	Clock clock;

	//Vehicle v(Vector2f(200, 300));
	//v.create();
	VehicleSystem* vs = new VehicleSystem();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed &&
				event.key.code == sf::Mouse::Left) {
				vs->addVehicle(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y));
			}
			if (event.type == sf::Event::MouseButtonPressed &&
				event.key.code == sf::Mouse::Right) {
				vs->removeVehicle();
			}
			if (event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Num1) {
				vs->alignment();
			}
			if (event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Num2) {
				vs->separation();
			}
			if (event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Num3) {
				vs->cohesion();
			}
		}

		//v.setTarget(Vector2f(Mouse::getPosition(window).x, Mouse::getPosition(window).y));

		float dt = clock.restart().asSeconds();

		window.clear();
		vs->update(dt);
		vs->draw();
		window.display();
	}
	return 0;
}
