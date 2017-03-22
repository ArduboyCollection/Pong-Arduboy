#include "game.hpp"
#include "paddle.hpp"

#define AI_REACT 85
#define AI_RAND 15

void PaddleBase::draw() const
{
	arduboy.fillRect(x, y, PADDLE_WIDTH, PADDLE_HEIGHT, WHITE);
}

void PaddleBase::move(int16_t distance)
{
	int16_t newY = y + distance;
	if (newY <= 0)
	{
		y = 1;
	}
	else if (newY > HEIGHT - PADDLE_HEIGHT - 1)
	{
		y = HEIGHT - PADDLE_HEIGHT - 1;
	}
	else
	{
		y = newY;
	}
}

void Player::move_impl()
{
	if (arduboy.pressed(UP_BUTTON))
	{
		PaddleBase::move(-1);
	}
	if (arduboy.pressed(DOWN_BUTTON))
	{
		PaddleBase::move(1);
	}
}

void Computer::move_impl()
{
	// bother the paddle if the ball is close or a random time
	if (ball.position.getX() > AI_REACT || !random(AI_RAND))
	{
		// move up if the ball is higher
		if (ball.position.getY() <= y)
		{
			PaddleBase::move(-1);
		}
		// move down if the ball is lower
		if (ball.position.getY() + BALL_SIZE >= y + PADDLE_HEIGHT)
		{
			PaddleBase::move(1);
		}
	}
}
