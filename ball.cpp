#include "ball.h"
#include "paddle.h"

Ball::Ball() {
  size = sf::Vector2f(BALL_SIZE, BALL_SIZE);
  default_position = sf::Vector2f((WIN_L / 2) - (BALL_SIZE / 2),
                                  (WIN_H / 2) - (BALL_SIZE / 2));
  position = default_position;
  velocity = randomVelocity();
  transparent = false;
}

sf::Vector2f Ball::randomVelocity() {
                                //min  max   decimals
  return sf::Vector2f(randomFloat(MIN_X_VELOCITY, MAX_X_VELOCITY, 3, true),
                      randomFloat(MIN_Y_VELOCITY, MAX_Y_VELOCITY, 3, true));
}

sf::Vector2f Ball::getPosition() {
  return position;
}

sf::Vector2f Ball::getSize() {
  return size;
}
                                           //  ___
// Functions detecting ball collisions     // | _ |
int Ball::paddleCollision(Paddle paddle) { // || ||  |
  float ball_left   = position.x;          // || ||  |
  float ball_right  = position.x + size.x; // || ||  |
  float ball_top    = position.y;          // ||_||  V
  float ball_bottom = position.y + size.y; // |___|

  float paddle_left      = paddle.getPosition().x;
  float paddle_left_in   = paddle_left + 1;
  float paddle_right     = paddle.getPosition().x + paddle.getSize().x;
  float paddle_right_in  = paddle_right + 1;
  float paddle_top       = paddle.getPosition().y;
  float paddle_top_in    = paddle_top + 1;
  float paddle_bottom    = paddle.getPosition().y + paddle.getSize().y;
  float paddle_bottom_in = paddle_bottom + 1;

  if (transparent)
    return 0;

  if      (ball_left     < paddle_right
          && ball_right  > paddle_right_in
          && ball_bottom > paddle_top_in
          && ball_top    < paddle_bottom_in)
    return 1;
  else if (ball_left     < paddle_left_in
          && ball_right  > paddle_left
          && ball_bottom > paddle_top_in
          && ball_top    < paddle_bottom_in)
    return 1;
  else if (ball_left     < paddle_right
          && ball_right  > paddle_left
          && ball_bottom > paddle_top
          && ball_top    < paddle_top_in)
    return 2;
  else if (ball_left     < paddle_right
          && ball_right  > paddle_left
          && ball_bottom > paddle_bottom_in
          && ball_top    < paddle_bottom)
    return 3;
  else
    return 0;
}

bool Ball::windowTopCollision() {
  if (position.y < WIN_Y || position.y + size.y > WIN_H)
    return true;
  else
    return false;
}

int Ball::windowSideCollision() {
  if (position.x + size.x < WIN_X)
    return 1;
  else if (position.x > WIN_L)
    return 2;
  else
    return 0;
}

// Functions handling collision with Paddle
void Ball::handleBallSkew(Paddle paddle) {
  // if ()
    if (paddle.getId() == 1) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        velocity.y -= COLLISION_SKEW;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        velocity.y += COLLISION_SKEW;
    }
    if (paddle.getId() == 2) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        velocity.y -= COLLISION_SKEW;
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        velocity.y += COLLISION_SKEW;
    }
}

void Ball::handlePaddleCollision(Paddle paddle) {
  int collision_type = paddleCollision(paddle);
  if (collision_type == 1) {
    velocity.x *= -1;

    if (velocity.x < X_VELOCITY_LIMIT && velocity.x > -X_VELOCITY_LIMIT) 
      velocity.x *= COLLISION_SPEED_MULTIPLIER;

    if (velocity.y < Y_VELOCITY_LIMIT && velocity.y > -Y_VELOCITY_LIMIT)
      handleBallSkew(paddle);
  }
  else {
    transparent = true;
    if (collision_type == 2)
      velocity.y = (PADDLE_SPEED * -1) - 0.02f;
    else
      velocity.y = PADDLE_SPEED + 0.02f;
  }
}

void Ball::reset() {
  transparent = false;
  position = default_position;
  velocity = randomVelocity();
}


// Updates ball attributes for game loop
void Ball::update(Paddle &paddle1, Paddle &paddle2) {

  if (paddleCollision(paddle1) != 0)
    handlePaddleCollision(paddle1);
  if (paddleCollision(paddle2) != 0)
    handlePaddleCollision(paddle2);

  if (windowTopCollision())
    velocity.y *= -1;

  int side_collision = windowSideCollision();
  if (side_collision != 0) {
    reset();
    if (side_collision == 1)
      paddle2.scored();
    if (side_collision == 2)
      paddle1.scored();
  }

  position.x += velocity.x;
  position.y += velocity.y;

}

// Draws ball to window
void Ball::draw(sf::RenderWindow &win) {
  sf::RectangleShape ball;
  ball.setSize(size);
  ball.setPosition(position);

  ball.setFillColor(BALL_COLOR);

  win.draw(ball);
}