#include "pch.h"
#include "Engine.h"

bool Engine::detectCollisions(PlayableCharacter& character)
{
	bool reachedGoal = 0;

	FloatRect detectionZone = character.getPosition();
	FloatRect block;

	block.width = TILE_SIZE;
	block.height = TILE_SIZE;

	int startX = (int)(detectionZone.left / TILE_SIZE) - 1;
	int startY = (int)(detectionZone.top / TILE_SIZE) - 1;
	int endX = (int)(detectionZone.left / TILE_SIZE) + 2;
	int endY = (int)(detectionZone.top / TILE_SIZE) + 3;

	if (startX < 0) startX = 0;
	if (startY < 0) startY = 0;
	if (endX > m_LM.getLevelSize().x) endX = m_LM.getLevelSize().x;
	if (endY > m_LM.getLevelSize().y) endY = m_LM.getLevelSize().y;

	FloatRect level(0, 0, m_LM.getLevelSize().x * TILE_SIZE, m_LM.getLevelSize().y * TILE_SIZE);
	if (!character.getPosition().intersects(level))
	{
		character.spawn(m_LM.getStartPosition(), GRAVITY);
	}

	for (int x = startX; x < endX; x++)
	{
		for (int y = startY; y < endY; y++)
		{
			block.left = x * TILE_SIZE;
			block.top = y * TILE_SIZE;

			// Fire and Water
			if (m_ArrayLevel[y][x] == 2 || m_ArrayLevel[y][x] == 3)
			{
				if (character.getHead().intersects(block))
				{
					if (!m_PS.running()) 
					{
						m_PS.emitParticles(character.getCenter());
					}
					character.spawn(m_LM.getStartPosition(), GRAVITY);
					if (m_ArrayLevel[y][x] == 2)
					{
						// Burned
						m_SM.playFallInFire();
					}
					else
					{
						// Drowned
						m_SM.playFallInWater();
					}
				}
			}

			// Regular block
			if (m_ArrayLevel[y][x] == 1)
			{
				if (character.getRight().intersects(block))
				{
					character.stopRight(block.left);
				}
				else if (character.getLeft().intersects(block))
				{
					character.stopLeft(block.left);
				}

				if (character.getFeet().intersects(block))
				{
					character.stopFalling(block.top);
				}
				else if (character.getHead().intersects(block))
				{
					character.stopJump();
				}
			}

			// Goal
			if (m_ArrayLevel[y][x] == 4)
			{
				reachedGoal = 1;
			}
		}
	}

	return reachedGoal;
}