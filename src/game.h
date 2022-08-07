#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "players_data.h"

class Renderer;

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, PlayersData &pData);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore1() const;
  int GetSize1() const;
  int GetScore2() const;
  int GetSize2() const;
  bool GetNumOfPlayers() const;
  void SetNumOfPlayers(bool numOfPlayers);
  void NumOfPlayersInput(PlayersData &pData);

 private:
  Snake _snake1;
  Snake _snake2;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int _score1{0};
  int _score2{0};
  
  void PlaceFood();
  void Update();
  void SnakeBites();
  bool _numOfPlayers{false};
};

#endif