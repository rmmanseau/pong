#include <string>
#include <sstream>

#include "helpers.h"
#include "paddle.h"

float randomFloat(float goal_min, float goal_max, float decimal_points, bool negative) {
  float multiplier = 1.f;
  for (int i = decimal_points; i > 0; i--) {
    multiplier *= 10;
  }
  int int_min = goal_min * multiplier;
  int range = (goal_max - goal_min) * multiplier + 1;

  int int_rand = (int_min + rand() % range);
  if (negative)
    if (rand() % 2 == 0) int_rand *= -1;
  float float_rand = int_rand / multiplier;
  return float_rand;
}

sf::RectangleShape newDecoration(sf::Vector2f shape, 
                                 sf::Vector2f position) 
{
  sf::RectangleShape rect(shape);
  rect.setPosition(position);
  rect.setFillColor(DECORATION_COLOR);

  return rect;
}

void drawDecorations(sf::RenderWindow &win) {
  // Net
  win.draw(newDecoration(sf::Vector2f(NET_WIDTH, WIN_H), 
                         sf::Vector2f(WIN_L / 2, WIN_Y)));
  // Top Border
  win.draw(newDecoration(sf::Vector2f(WIN_L, BORDER_WIDTH),
                         sf::Vector2f(WIN_X, WIN_Y)));
  // Bottom Border
  win.draw(newDecoration(sf::Vector2f(WIN_L, BORDER_WIDTH),
                         sf::Vector2f(WIN_X, WIN_H - BORDER_WIDTH)));
}

void drawScoreBoard(sf::RenderWindow &win, Paddle paddle1, Paddle paddle2,
                    sf::Text paddle1_score, sf::Text paddle2_score) {
  std::ostringstream c1;
  std::ostringstream c2;
  
  c1 << paddle1.getScore();
  paddle1_score.setString(c1.str());

  c2 << paddle2.getScore();
  paddle2_score.setString(c2.str());

  win.draw(paddle1_score);
  win.draw(paddle2_score);
}