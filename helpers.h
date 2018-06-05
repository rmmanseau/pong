#pragma once
#include "sfml_includes.h"

class Paddle;

// =============================================================================
// GAME CONSTANTS
// =============================================================================

// GAME_____________
const int WIN_SCORE = 7;

// WINDOW_____________
const int WIN_X = 0;
const int WIN_L = 801;
const int WIN_Y = 0;
const int WIN_H = 400;

// COLOR____________________________________________
const sf::Color PONG_GREEN = sf::Color(0,255,18);
const sf::Color PONG_BLUE  = sf::Color(0,255,235);
const sf::Color PONG_RED   = sf::Color(255,0,28);
const sf::Color PONG_GRAY  = sf::Color(150,150,150);
const sf::Color PONG_PINK  = sf::Color(255,143,173);

const sf::Color DECORATION_COLOR = sf::Color::White;
const sf::Color PADDLE_COLOR = PONG_GREEN;
const sf::Color BALL_COLOR = PONG_GREEN;
const sf::Color SCORE_COLOR = sf::Color::White;
const sf::Color WIN_COLOR = PONG_GREEN;
const sf::Color LOSE_COLOR = PONG_RED;
const sf::Color BACKGROUND_COLOR = sf::Color::Black;

// BALL________________________________________
const int BALL_SIZE = 6;

const float MIN_X_VELOCITY = 2.f;
const float MAX_X_VELOCITY = 3.5f;
const float MIN_Y_VELOCITY = 0.01f;
const float MAX_Y_VELOCITY = 1.5f;

const float X_VELOCITY_LIMIT = 8.f;
const float Y_VELOCITY_LIMIT = 5.f;

const float COLLISION_SPEED_MULTIPLIER = 1.4f;
const float COLLISION_SKEW = 0.9f;


// PADDLE________________________
const int PADDLE_HEIGHT = 60;
const int PADDLE_LENGTH = 6;

const float OFFSET_FROM_WALL = 1;

const float PADDLE_SPEED = 4.f;

// DECORATIONS______________
const int BORDER_WIDTH = 1;
const int NET_WIDTH    = 1;

// TEXT____________________
const int BANNER_HEIGHT = 70;
const int WIN_WIDTH = 198;
const int LOSE_WIDTH = 188;
const int VERTICLE_BUFFER = 5 + BORDER_WIDTH;
const int HORIZONTAL_BUFFER = 20 + OFFSET_FROM_WALL + PADDLE_LENGTH;


// =============================================================================

// =============================================================================

float randomFloat(float goal_min, float goal_max, float decimal_points, bool negative);
sf::RectangleShape newDecoration(sf::Vector2f shape, sf::Vector2f position);
void drawDecorations(sf::RenderWindow &win);
void drawScoreBoard(sf::RenderWindow & win, Paddle paddle1, Paddle paddle2,
                    sf::Text paddle1_score, sf::Text paddle2_score);