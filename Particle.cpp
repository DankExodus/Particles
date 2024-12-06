#include "Particle.h"

Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition) : m_A(2, numPoints)
{
	m_ttl = TTL;
	m_numPoints = numPoints;
	m_radiansPerSec = (float)rand() / (RAND_MAX) * M_PI;
	m_cartesianPlane.setCenter(0, 0);
	m_cartesianPlane.setSize(target.getSize().x, (-1.0) * target.getSize().y);
	m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane);
	m_vx = rand() % 2;
	if (m_vx != 0) 
	{
		m_vx *= -1;
	}
	m_vy = 400;
	m_color1 = Color::Blue;
	m_color2 = Color::Green;
	double theta = (float)rand() / (RAND_MAX) * M_PI / 2;
	double dtheta = 2 * M_PI / (numPoints - 1);
	for (auto j = 0; j < numPoints; j++)
	{
		int min = 20, max = 80;
		int r = min + (rand() % (max - min + 1));
		double dx = r * cos(theta);
		double dy = r * sin(theta);
		m_A(0, j) = m_centerCoordinate.x + dx;
		m_A(1, j) = m_centerCoordinate.y + dy;
		theta += dtheta;
	}
	
}
virtual void Particle::draw(RenderTarget& target, RenderStates states) const override
{

}
void Particle::update(float dt)
{

}

bool Particle::almostEqual(double a, double b, double eps = 0.0001)
{

}
void Particle::unitTests()
{

}

void Particle::rotate(double theta)
{

}

void Particle::scale(double c)
{

}

void Particle::translate(double xShift, double yShift)
{

}