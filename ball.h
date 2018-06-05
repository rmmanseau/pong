#ifndef BALL_H
#define BALL_H

class Paddle;

#include <iostream>
#include "sfml_includes.h"
#include "helpers.h"

class Ball {

private:
  sf::Vector2f default_position;
  sf::Vector2f size;
  sf::Vector2f position;
  sf::Vector2f velocity;
  bool transparent;

  sf::Vector2f randomVelocity();
  int paddleCollision(Paddle paddle);
  bool windowTopCollision();
  int windowSideCollision();
  void handleBallSkew(Paddle paddle);
  void handlePaddleCollision(Paddle paddle);
  void handleWindowCollision();

public:
  Ball();
  sf::Vector2f getPosition();
  sf::Vector2f getSize();
  void reset();
  void update(Paddle &paddle1, Paddle &paddle2);
  void draw(sf::RenderWindow &win);
};

#endif // BALL_H