#include "game.h"
#include <iostream>
#include "SDL.h"
#include "renderer.h"
#include "players_data.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, PlayersData &pData)
    : _snake1(grid_width, grid_height),
      _snake2(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  NumOfPlayersInput(pData);
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    if(_numOfPlayers == true){
      controller.HandleInput(running, _snake1, _snake2);
    }
    else
    {
      controller.HandleInput(running, _snake1);
    }
    
    SnakeBites();
    Update();
   

    renderer.Render(_snake1, _snake2, food, this);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(_score1, _score2, _numOfPlayers, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!_snake1.SnakeCell(x, y) && !_snake2.SnakeCell(x,y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if ((!_snake1.alive) || (!_snake2.alive)) {return;}

  _snake1.Update();
  _snake2.Update();

  int new_x1 = static_cast<int>(_snake1.head_x);
  int new_y1 = static_cast<int>(_snake1.head_y);
  int new_x2 = static_cast<int>(_snake2.head_x);
  int new_y2 = static_cast<int>(_snake2.head_y);

  // Check if there's food over here
  if (food.x == new_x1 && food.y == new_y1) {
    _score1++;
    PlaceFood();
    // Grow snake and increase speed.
    _snake1.GrowBody();
    _snake1.speed += 0.01;
  }

  if (food.x == new_x2 && food.y == new_y2){
    _score2++;
    PlaceFood();
    _snake2.GrowBody();
    _snake2.speed += 0.01;
  }
}

bool Game::GetNumOfPlayers() const {return _numOfPlayers;}

void Game::SetNumOfPlayers(bool numOfPlayers) {_numOfPlayers = numOfPlayers;}

void Game::NumOfPlayersInput(PlayersData &p){
  std::string numOfPlayers;
  std::cout << "One player or two players?\n";
  std::cin >> numOfPlayers;
  string name1, name2;
   while(true){
    if( numOfPlayers == "one" || numOfPlayers == "One" || numOfPlayers == "ONE" || numOfPlayers == "1"){
      SetNumOfPlayers(false);
      std::cout << "Name of the player ";
      std::cin >> name1;
      p.setName1(name1);

      break;
    }
    else if( numOfPlayers == "two" || numOfPlayers == "Two" || numOfPlayers == "TWO" || numOfPlayers == "2"){
      SetNumOfPlayers(true);
      std::cout << "Name of the first player ";
      std::cin >> name1;
      std::cout << "\n"; std::cout << "Name of the second player ";
      std::cin >> name2;
      p.setName1(name1); p.setName2(name2);
      break;
    }
    else {
      std::cout << "Invalid input, please enter '1' / 'one' / '2' / 'two'" << std::endl;
      std::cin >> numOfPlayers;
    } 
  }
}

void Game::SnakeBites(){
  int new_x1 = static_cast<int>(_snake1.head_x);
  int new_y1 = static_cast<int>(_snake1.head_y);
  int new_x2 = static_cast<int>(_snake2.head_x);
  int new_y2 = static_cast<int>(_snake2.head_y);
  int i = 0;
  int j = 0;

  while(i<_snake1.body.size()){
    if(new_x2 == _snake1.body[i].x && new_y2 == _snake1.body[i].y){
      _score2--;
      _snake1.size--;
      _snake1.body.pop_back();
      break;
    }
    i++;
  }
  while(j<_snake2.body.size()){
    if(new_x1 == _snake2.body[j].x && new_y1 == _snake2.body[j].y){
      _score1--;
      _snake2.size--;
      _snake2.body.pop_back();
      break;
    }
    j++;
  }

}

int Game::GetScore1() const { return _score1; }
int Game::GetSize1() const { return _snake1.size; }
int Game::GetScore2() const { return _score2; }
int Game::GetSize2() const { return _snake2.size; }