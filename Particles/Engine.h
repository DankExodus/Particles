#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Particle.h"
#include <sstream>

using namespace sf;
using namespace std;

class Engine
{
private:
	// A regular RenderWindow
	RenderWindow m_Window;

	//vector for Particles
	vector<Particle> m_particles;

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	virtual void draw();

	float randX = rand() % 1770, randY = (rand() % 710) + 30, stoppingPoint = 1557;

	Texture gameTexture, santaTexture, gameBackground;
	SoundBuffer buffer, buffer2;
	Sound oof, yay;
	Music music;
	FloatRect bounds;
	Sprite gameTarget, Santa, background;
	int scoreCount;
	Clock turkeyTravel, timer, loseWin;
	Font font;
	Text scoreText, gameOver;
	string text;
	bool failState;




public:
	// The Engine constructor
	Engine(); //: buffer() {}

	// Run will call all the private functions
	void run();

};