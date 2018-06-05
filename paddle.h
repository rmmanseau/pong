#ifndef PADDLE_H
#define PADDLE_H

class Ball;

#include "sfml_includes.h"
#include "helpers.h"

class Paddle {

private:
  int paddle_id;
  bool player_controlled;
  float shift;
  sf::Vector2f size;
  sf::Vector2f position;
  int score;

  float autoMove(Ball ball);
  bool hitWindowBoundry();

public:
  Paddle(float x, float y, bool player, int id);
  void playerControlled(bool player);
  sf::Vector2f getSize();
  sf::Vector2f getPosition();
  void scored();
  int getScore();
  void resetScore();
  int getId();
  void moveUp();
  void moveDown();
  void update(Ball ball);
  void draw(sf::RenderWindow &win);
};

#endif // PADDLE_H