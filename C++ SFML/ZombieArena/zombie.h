#ifndef Zombie_HEADER
#define Zombie_HEADER

#include <SFML/Graphics.hpp>

using namespace sf;

class Zombie
{
private:
	const float BLOATER_SPEED = 40, CHASER_SPEED = 85, CRAWLER_SPEED = 60;
	const float BLOATER_HEALTH = 5, CHASER_HEALTH = 1, CRAWLER_HEALTH = 3;
	const int MAX_VARIANCE = 30;
	const int OFFSET = 101 - MAX_VARIANCE;

	Vector2f m_Position;
	Sprite m_Sprite;
	float m_Speed;
	float m_Health;
	bool m_Alive;

public:
	bool hit();
	bool isAlive();
	void spawn(float startX, float startY, int type, int seed);
	FloatRect getPosition();
	Sprite getSprite();
	void update(float elapsedTime, Vector2f playerLocation);
};
#endif