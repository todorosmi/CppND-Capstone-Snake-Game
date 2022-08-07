#include <iostream>
#include <string>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "players_data.h"

using::std::string;

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  PlayersData pData;
  int score1 = 0;
  int score2 = 0;
  Game game(kGridWidth, kGridHeight,pData);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score1:" << game.GetScore1() << "\n";
  std::cout << "Size1: " << game.GetSize1() << "\n";
  score1 = game.GetScore1();
  if(game.GetNumOfPlayers()){
    std::cout << "Score2: " << game.GetScore2() << "\n";
    std::cout << "Size2: " << game.GetSize2() << "\n"; 
    score2 = game.GetScore2();
  }
  pData.scoreTrack(score1,score2);
  return 0;
}