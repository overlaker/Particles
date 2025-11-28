#include <SFML/Graphics.hpp>
#include <random>
#include "Engine.h"

using namespace sf;
using namespace std;

Engine::Engine()
{
	VideoMode vm(1900, 1000);

	//Construct the RenderWindow
	m_Window.create(vm, "Particles", Style::Default);
}

void Engine::run()
{
	sf::Clock clock;
	//Time dt = clock.getElapsedTime();
	srand(static_cast<unsigned int>(time(nullptr)));

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 }, false);
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;
	//return;		//for unit testing only~

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();

		input();

		/*
		****************************************
		Update the scene
		****************************************
		*/
		update(dt.asSeconds());

		/*
		****************************************
		Draw the scene
		****************************************
		*/
		draw();
	}
}


// Private functions:

void Engine::input()
{
	if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
		m_Window.close();
	}

	/*
	****************************************
	Handle the players input
	****************************************
	*/
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) m_Window.close();
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//cout << "Point(L): ";
				//construct particles
				for (int i = 0; i < 5; i++) {
					//number of vertices in each particle
					int nPts = rand() % 31 + 30;
					Particle p(m_Window, nPts, { event.mouseButton.x, event.mouseButton.y }, false);
					m_particles.push_back(p);
				}
			}
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				//cout << "Point(R): ";
				//construct particles - dark
				for (int i = 0; i < 5; i++) {
					//number of vertices in each particle
					int nPts = rand() % 31 + 30;
					Particle p(m_Window, nPts, { event.mouseButton.x, event.mouseButton.y }, true);
					m_particles.push_back(p);
				}
			}
			//cout << event.mouseButton.x << ", " << event.mouseButton.y << endl;
		}
		else if (event.type == Event::MouseMoved)
		{
			//real-time mouse cursor position
			//cPlane.setMouseLocation({ event.mouseMove.x, event.mouseMove.y });
		}
	}
}

void Engine::update(float dtAsSeconds)
{
	for (vector<Particle>::iterator it = m_particles.begin(); it != m_particles.end(); )
	{
		if (it->getTTL() > 0.0)
		{
			it->update(dtAsSeconds);
			++it;
		}
		else
		{
			it = m_particles.erase(it);
		}
	}
}

void Engine::draw()
{
	m_Window.clear();
	//Loop through each Particle in m_Particles, pass each element into m_Window.draw()
	for (const Particle& p : m_particles)
	{
		m_Window.draw(p);
	}
	m_Window.display();
}