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
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (!failState && scoreCount < 30)
				{
					for (int i = 0; i < 5; i++)
					{
						int MIN = 20, MAX = 40;
						int numPoints = MIN + (rand() % (MAX - MIN + 1));
						m_particles.push_back(Particle(m_Window, numPoints, { event.mouseButton.x, event.mouseButton.y }));
					}
				}
				//cout << "mouse x: " << event.mouseButton.x << endl;
				//cout << "mouse y: " << event.mouseButton.y << endl;

				//clicked on turkey
				if (event.mouseButton.x <= bounds.left + bounds.width && event.mouseButton.x >= bounds.left && event.mouseButton.y <= bounds.top + bounds.height && event.mouseButton.y >= bounds.top && !failState  && scoreCount < 30)
				{
					scoreCount += 1; 
					//cout << "Score: " << scoreCount << endl;
					randY = rand() % 710;
					turkeyTravel.restart();
					text = "Score: " + to_string(scoreCount);
					scoreText.setString(text);
					oof.play();
				}
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
		else i = m_particles.erase(i);
	}
}
void Engine::draw() 
{

	m_Window.clear();

	m_Window.draw(background);
	m_Window.draw(Santa);
	m_Window.draw(gameTarget);
	m_Window.draw(scoreText);
	
	if (failState)
	{
		gameOver.setOutlineColor(Color::Red);
		gameOver.setOutlineThickness(5);
		m_Window.draw(gameOver);

		santaTexture.loadFromFile("graphics/deadge.png");
		Santa.setTexture(santaTexture);
	}
	if (scoreCount == 30)
	{
		gameOver.setString("SANTA IS SAVED!");
		gameOver.setPosition(264, 412);
		gameOver.setCharacterSize(145);
		gameOver.setOutlineColor(Color::Green);
		gameOver.setOutlineThickness(5);
		m_Window.draw(gameOver);
		
		santaTexture.loadFromFile("graphics/yippie.png");
		Santa.setTexture(santaTexture);
	}
	
	for (auto& particle : m_particles)
	{
		m_Window.draw(particle);
	}
	m_Window.display();
}
Engine::Engine() 
{
	VideoMode vm(VideoMode::getDesktopMode());
	m_Window.create(vm, "Rafter's Revenge (Particles)", Style::Default);

	scoreCount = 0;

	gameTexture.loadFromFile("graphics/turkey3.png");
	gameTarget.setTexture(gameTexture);	
	
	santaTexture.loadFromFile("graphics/santa2.png");
	Santa.setTexture(santaTexture);
	Santa.setPosition(1620, 390);

	gameBackground.loadFromFile("graphics/snow_background_snow_particles.png");
	background.setTexture(gameBackground);

	text = "Score: " + to_string(scoreCount);
	font.loadFromFile("font/KIN668.TTF");
	scoreText.setFont(font);
	scoreText.setString(text);
	scoreText.setPosition(1720, 0);
	scoreText.setFillColor(Color::Black);

	font.loadFromFile("font/KIN668.TTF");
	gameOver.setFont(font);
	gameOver.setString("GAME OVER");
	gameOver.setFillColor(Color::Black);
	gameOver.setPosition(515, 412);
	gameOver.setCharacterSize(175);

	buffer.loadFromFile("sound/oof.mp3");
	oof.setBuffer(buffer);
    oof.setVolume(10);

	music.openFromFile("sound/rizzmas.mp3");
	music.setVolume(4);
	music.play();

}
void Engine::run() 
{
	Clock clock;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		float dt = clock.restart().asSeconds();
		input();
		update(dt);
		draw();	

		if (bounds.getPosition().x >= stoppingPoint) failState = true;
		if (!failState && scoreCount != 30)
		{
			if (scoreCount < 10) gameTarget.setPosition((turkeyTravel.getElapsedTime().asSeconds() * 1000) - 700, randY);
			else if (scoreCount >= 10) gameTarget.setPosition((turkeyTravel.getElapsedTime().asSeconds() * 1600) - 700, randY);
			else if (scoreCount >= 20) gameTarget.setPosition((turkeyTravel.getElapsedTime().asSeconds() * 2500) - 700, randY);
			else if (scoreCount > 30) gameTarget.setPosition((turkeyTravel.getElapsedTime().asSeconds() * 3000) - 700, randY);
		}

		bounds = gameTarget.getGlobalBounds();
	}

}