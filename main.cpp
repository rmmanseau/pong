#include "sfml_includes.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "helpers.h"
#include "paddle.h"
#include "ball.h"

// All Game Constants located in helpers.h

int main() {

  sf::Clock game_clock;

  const int FRAMES_PER_SECOND = 55;
  const int SKIP_TICKS = 1000 / FRAMES_PER_SECOND;

  unsigned int next_game_tick = game_clock.getElapsedTime().asMilliseconds();

  int sleep_time = 0;

  srand(time(0));
  sf::RenderWindow win(sf::VideoMode(WIN_L, WIN_H, 32), "SFML Pong!", sf::Style::Close);
  win.setVerticalSyncEnabled(true);

  sf::Font digital_font;
  if (!digital_font.loadFromFile("digital-7.tff"))
    std::cout << "WARNING: Could not load font." << std::endl;

  sf::Font message_font;
  if (!message_font.loadFromFile("digital-tech.otf"))
    std::cout << "WARNING: Could not load font." << std::endl;

  int default_height = (WIN_H / 2) - (PADDLE_HEIGHT / 2);
  Paddle paddle_one(OFFSET_FROM_WALL, default_height, true, 1);
  Paddle paddle_two(WIN_L - PADDLE_LENGTH - OFFSET_FROM_WALL, default_height, false, 2);
  Ball ball;

  sf::Text paddle1_score("0", digital_font, 40);
  sf::Text paddle2_score("0", digital_font, 40);
  paddle1_score.setPosition( (WIN_L / 2) - 28, 10);
  paddle1_score.setColor(SCORE_COLOR);
  paddle2_score.setPosition( (WIN_L / 2) + 10, 10);
  paddle2_score.setColor(SCORE_COLOR);

  sf::Text win_banner("Winner!", message_font, 70);
  win_banner.setColor(WIN_COLOR);
  sf::Text lose_banner("Loser!", message_font, 70);
  lose_banner.setColor(LOSE_COLOR);

  while(win.isOpen()) {

    sf::Event event;
    while (win.pollEvent(event)) {

      switch(event.type) {

        case sf::Event::Closed:
          win.close();
          break;

        case sf::Event::KeyReleased:
          switch(event.key.code) {

            case sf::Keyboard::Space:
              paddle_two.playerControlled(false);
              break;

            case sf::Keyboard::F1:
              ball.reset();
              paddle_one.resetScore();
              paddle_two.resetScore();
              break;

            case sf::Keyboard::F2:
              ball.reset();
              break;

            case sf::Keyboard::F7:
              for (int i = 0; i < WIN_SCORE; i++)
                paddle_one.scored();
              break;

            case sf::Keyboard::F8:
              for (int i = 0; i < WIN_SCORE; i++)
                paddle_two.scored();
              break;
          }
          break;
      }
    }

    // while
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
      paddle_one.moveUp();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      paddle_one.moveDown();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      paddle_two.playerControlled(true);
      paddle_two.moveUp();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      paddle_two.playerControlled(true);
      paddle_two.moveDown();
    }

    paddle_one.update(ball);
    paddle_two.update(ball);

    if (paddle_one.getScore() < WIN_SCORE && paddle_two.getScore() < WIN_SCORE)
      ball.update(paddle_one, paddle_two);

    win.clear(BACKGROUND_COLOR);

    drawDecorations(win);
    drawScoreBoard(win, paddle_one, paddle_two, 
                   paddle1_score, paddle2_score);
    paddle_one.draw(win);
    paddle_two.draw(win);
    
    if (paddle_one.getScore() < WIN_SCORE && paddle_two.getScore() < WIN_SCORE)
      ball.draw(win);

    if (paddle_one.getScore() >= WIN_SCORE) {
      win_banner.setPosition(WIN_X + HORIZONTAL_BUFFER,
                             WIN_H - BANNER_HEIGHT - VERTICLE_BUFFER);
      lose_banner.setPosition(WIN_L - LOSE_WIDTH - HORIZONTAL_BUFFER,
                              WIN_H - BANNER_HEIGHT - VERTICLE_BUFFER);
      win.draw(win_banner);
      win.draw(lose_banner);
    }


    if (paddle_two.getScore() >= WIN_SCORE) {
      win_banner.setPosition(WIN_L - WIN_WIDTH - HORIZONTAL_BUFFER,
                             WIN_H - BANNER_HEIGHT - VERTICLE_BUFFER);
      lose_banner.setPosition(WIN_X + HORIZONTAL_BUFFER,
                              WIN_H - BANNER_HEIGHT - VERTICLE_BUFFER);
      win.draw(win_banner);
      win.draw(lose_banner);
    }

    win.display();

    next_game_tick += SKIP_TICKS;
    sleep_time = next_game_tick - game_clock.getElapsedTime().asMilliseconds();

    if (sleep_time >= 0)
      sf::sleep(sf::milliseconds(sleep_time));

    std::cout << sleep_time << std::endl; 
}

return 0;
}