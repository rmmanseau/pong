#include "paddle.h"
#include "ball.h"

Paddle::Paddle(float x, float y, bool player, int id) {
  player_controlled = player;
  paddle_id = id;
  shift = 0;
  score = 0;
  size = sf::Vector2f(PADDLE_LENGTH, PADDLE_HEIGHT);

  position.x = x;
  position.y = y;
}

void Paddle::playerControlled(bool player) {
  player_controlled = player;
}

sf::Vector2f Paddle::getSize() {
  return size;
}

sf::Vector2f Paddle::getPosition() {
  return position;
}

int Paddle::getId() {
  return paddle_id;
}

void Paddle::scored() {
  score++;
}

int Paddle::getScore() {
  return score;
}

void Paddle::resetScore() {
  score = 0;
}

bool Paddle::hitWindowBoundry() {
  bool moving_up = shift < 0;
  bool moving_down = shift > 0;

  if ( (moving_up && position.y > WIN_X)
     ||(moving_down && position.y + size.y < WIN_H) )
    return false;
  else
    return true;
}

float Paddle::autoMove(Ball ball) {
  float paddle_center = position.y + (size.y / 2.f);
  float ball_top      = ball.getPosition().y;
  float ball_bottom   = ball.getPosition().y + ball.getSize().y;

  if (ball.getPosition().x > WIN_L / 10) {
    if (paddle_center < ball_top) {
      return PADDLE_SPEED;
    }
    else if (paddle_center >= ball_top && paddle_center <= ball_bottom) {
      return 0;
    }
    else if (paddle_center > ball_bottom) {
      return -PADDLE_SPEED;
    }
  }
  else
    return 0;
}

void Paddle::moveUp() {
  shift = -PADDLE_SPEED;
}

void Paddle::moveDown() {
  shift = PADDLE_SPEED;
}

void Paddle::update(Ball ball) {
  if (!player_controlled)
    shift = autoMove(ball);

  if(!hitWindowBoundry())
    position.y += shift;

  shift = 0.f;
}

void Paddle::draw(sf::RenderWindow &win) {
  sf::RectangleShape paddle;
  paddle.setSize(size);
  paddle.setPosition(position);
  
  paddle.setFillColor(PADDLE_COLOR);

  win.draw(paddle);
}