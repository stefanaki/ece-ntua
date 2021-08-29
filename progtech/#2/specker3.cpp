#include <iostream>
#include <stdexcept>

using namespace std;

class Game {
private:
  Player **Players;
  int *Coins;
  int h, p;
  int heapsIndex, playersIndex;

public:
  Game(int heaps, int players);
  ~Game();

  void addHeap(int coins) throw(logic_error);
  void addPlayer(Player *player) throw(logic_error);
  void play(ostream &out) throw(logic_error);
};

Game::Game(int heaps, int players) {
  Players = new Player* [players];
  Coins = new int[heaps];
  h = heaps;
  p = players;
  heapsIndex = playersIndex = 0;
}

Game::~Game() {
  delete[] Players;
  delete[] Coins;
  heapsIndex = playersIndex = h = p = 0;
}

void Game::addHeap(int coins) throw(logic_error) {
  if(heapsIndex == h)
    throw logic_error("number of heaps exceeded");

  Coins[heapsIndex++] = coins;
}

void Game::addPlayer(Player *player) throw(logic_error) {
  if(playersIndex == p)
    throw logic_error("number of players exceeded");

  Players[playersIndex++] = player;
}

void Game::play(ostream &out) throw(logic_error) {
  if(playersIndex != p)
    throw logic_error("not enough players inserted");
  if(heapsIndex != h)
    throw logic_error("not enough heaps inserted");

  State gameState(h, Coins);
  int turn = 0;

  while(!gameState.winning()) {
    out << "State: " << gameState << endl;
    out << *Players[turn] << " " << Players[turn]->play(gameState) << endl;
    gameState.next(Players[turn]->play(gameState));
    turn = (turn + 1) % p;
  }

  out << "State: " << gameState << endl;

  if(turn == 0)
    turn = p - 1;
  else
    turn -= 1;

  out << *Players[turn] << " wins" << endl;
}
