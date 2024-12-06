#include "Engine.h"

void Engine::input() 
{
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			m_Window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			m_Window.close();
		}
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			for (int i = 0; i < 5; i++)
			{
				int MIN = 25, MAX = 50;
				int numPoints = MIN + (rand() % (MAX - MIN + 1));
				Particle p(m_Window, numPoints, { event.mouseButton.x, event.mouseButton.y });
			}
		}
	}
}
void Engine::update(float dtAsSeconds) 
{
	for (auto i = m_particles.begin(); i != m_particles.end();)
	{
		if (i->getTTL() > 0.0)
		{
			i->update(dtAsSeconds);
			i++;
		}
		else
		{
			i = m_particles.erase(i);
		}
	}

}
void Engine::draw() 
{
	m_Window.clear();

	for (auto& particle : m_particles)
	{
		m_Window.draw(particle);
	}

	m_Window.display();
}
Engine::Engine() 
{
	VideoMode vm(VideoMode::getDesktopMode());
	m_Window.create(vm, "Particles", Style::Default);
}
void Engine::run() 
{
	Clock clock;
	float dt;
	
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		clock.restart();
		Time time1 = clock.getElapsedTime();
		dt = time1.asSeconds();
		input();
		update(dt);
		draw();
	}

}
