#include <iostream>
#include <stdexcept>

using namespace std;

class Move {
private:
  int sourceHeap, sourceCoins, targetHeap, targetCoins;

public:
  // Take sc coins from heap sh and put tc coins to heap th.
  Move(int sh, int sc, int th, int tc);

  int getSource() const;
  int getSourceCoins() const;
  int getTarget() const;
  int getTargetCoins() const;

  friend ostream & operator << (ostream &out, const Move &move);
};

class State {
private:
  int maxHeaps, *coins;

public:
  // State with h heaps, where the i-th heap starts with c[i] coins.
  State(int h, const int c[]);
  ~State();

  void next(const Move &move) throw(logic_error);
  bool winning() const;

  int getHeaps() const;
  int getCoins(int h) const throw(logic_error);

  friend ostream & operator << (ostream &out, const State &state);
};

Move::Move(int sh, int sc, int th, int tc) {
  sourceHeap = sh;
  sourceCoins = sc;
  targetHeap = th;
  targetCoins = tc;
}

int Move::getSource() const { return sourceHeap; }

int Move::getSourceCoins() const { return sourceCoins; }

int Move::getTarget() const { return targetHeap; }

int Move::getTargetCoins() const { return targetCoins; }

ostream & operator << (ostream &out, const Move &move) {
  out << "takes " << move.sourceCoins << " coins from heap "
      << move.sourceHeap << " and puts ";
  if(move.targetCoins == 0)
    out << "nothing";
  else
    out << move.targetCoins << " coins to heap " << move.targetHeap;
  return out;
}

State::State(int h, const int c[]) {
  maxHeaps = h;
  coins = new int[h];

  for(int i = 0; i < h; i++) {
    coins[i] = c[i];
  }
}

State::~State() {
  delete[] coins;
  maxHeaps = 0;
}

void State::next(const Move &move) throw(logic_error) {
  if(move.getSource() < 0 || move.getSource() >= maxHeaps)
    throw logic_error("invalid heap");
  if(move.getTarget() < 0 || move.getTarget() >= maxHeaps)
    throw logic_error("invalid heap");
  if(move.getSourceCoins() <= 0 || move.getTargetCoins() < 0)
    throw logic_error("invalid number of coins");
  if(move.getSourceCoins() > coins[move.getSource()])
    throw logic_error("not enough coins");
  if(move.getSourceCoins() <= move.getTargetCoins())
    throw logic_error("invalid number of coins");

  coins[move.getSource()] -= move.getSourceCoins();
  coins[move.getTarget()] += move.getTargetCoins();
}

bool State::winning() const {
  int i = 0;

  while(coins[i] == 0 && i < maxHeaps)
    i++;

  if(i == maxHeaps)
    return true;
  else
    return false;
}

int State::getHeaps() const { return maxHeaps; }

int State::getCoins(int h) const throw(logic_error) {
  if(h < 0 || h >= maxHeaps)
    throw logic_error("invalid heap");

  return coins[h];
}

ostream & operator << (ostream &out, const State &state) {
  for(int i = 0; i < state.maxHeaps - 1; i++) {
    out << state.coins[i] << ", ";
  }
  out << state.coins[state.maxHeaps - 1];

  return out;
}
