#include <iostream>
#include <string>

using namespace std;

// Declarations

class Player {
protected:
  string name;

public:
  Player(const string &n);
  virtual ~Player();

  virtual const string & getType() const = 0;
  virtual Move play(const State &s) = 0;

  friend ostream & operator << (ostream &out, const Player &player);
};

class GreedyPlayer : public Player {
protected:
  string type;

public:
  GreedyPlayer(const string &n);
  virtual ~GreedyPlayer() override;

  virtual const string & getType() const override;
  virtual Move play(const State &s) override;
};

class SpartanPlayer : public Player {
protected:
  string type;

public:
  SpartanPlayer(const string &n);
  virtual ~SpartanPlayer() override;

  virtual const string & getType() const override;
  virtual Move play(const State &s) override;
};

class SneakyPlayer : public Player {
protected:
  string type;

public:
  SneakyPlayer(const string &n);
  virtual ~SneakyPlayer() override;

  virtual const string & getType() const override;
  virtual Move play(const State &s) override;
};

class RighteousPlayer : public Player {
protected:
  string type;

public:
  RighteousPlayer(const string &n);
  virtual ~RighteousPlayer() override;

  virtual const string & getType() const override;
  virtual Move play(const State &s) override;
};

// Player Methods

Player::Player(const string &n) { name = n; }

Player::~Player() { name.clear(); }

ostream & operator << (ostream &out, const Player &player) {
  out << player.getType() << " player " << player.name;
  return out;
}

// Greedy Player Methods

GreedyPlayer::GreedyPlayer(const string &n) : Player(n) { type = "Greedy"; }

GreedyPlayer::~GreedyPlayer() {
  name.clear();
  type.clear();
}

const string & GreedyPlayer::getType() const { return type; }

Move GreedyPlayer::play(const State &s) {
  int largestHeap = 0;
  for(int i = 0; i < s.getHeaps(); i++) {
    if(s.getCoins(i) > s.getCoins(largestHeap))
      largestHeap = i;
  }

  Move greedyMove(largestHeap, s.getCoins(largestHeap), 0, 0);
  return greedyMove;
}

// Spartan Player Methods

SpartanPlayer::SpartanPlayer(const string &n) : Player(n) { type = "Spartan"; }

SpartanPlayer::~SpartanPlayer() {
  name.clear();
  type.clear();
}

const string & SpartanPlayer::getType() const { return type; }

Move SpartanPlayer::play(const State &s) {
  int largestHeap = 0;
  for(int i = 0; i < s.getHeaps(); i++) {
    if(s.getCoins(i) > s.getCoins(largestHeap))
      largestHeap = i;
  }

  Move spartanMove(largestHeap, 1, 0, 0);
  return spartanMove;
}

// Sneaky Player Methods

SneakyPlayer::SneakyPlayer(const string &n) : Player(n) { type = "Sneaky"; }

SneakyPlayer::~SneakyPlayer() {
  name.clear();
  type.clear();
}

const string & SneakyPlayer::getType() const { return type; }

Move SneakyPlayer::play(const State &s) {
  int i = 0, smallestHeap;

  while(s.getCoins(i) == 0)
    i++;

  smallestHeap = i;

  for(i = smallestHeap + 1; i < s.getHeaps(); i++) {
    if(s.getCoins(i) != 0 && s.getCoins(i) < s.getCoins(smallestHeap))
      smallestHeap = i;
  }

  Move sneakyMove(smallestHeap, s.getCoins(smallestHeap), 0, 0);
  return sneakyMove;
}

// Righteous Player Methods

RighteousPlayer::RighteousPlayer(const string &n) : Player(n) { type = "Righteous"; }

RighteousPlayer::~RighteousPlayer() {
  name.clear();
  type.clear();
}

const string & RighteousPlayer::getType() const { return type; }

Move RighteousPlayer::play(const State &s) {
  int largestHeap = 0, smallestHeap = 0, coins;
  for(int i = 0; i < s.getHeaps(); i++) {
    if(s.getCoins(i) > s.getCoins(largestHeap))
      largestHeap = i;
    if(s.getCoins(i) < s.getCoins(smallestHeap))
      smallestHeap = i;
  }

  if(s.getCoins(largestHeap) % 2 == 0)
    coins = s.getCoins(largestHeap) / 2;
  else
    coins = s.getCoins(largestHeap) / 2 + 1;

  Move r1(largestHeap, coins, smallestHeap + 1, coins - 1);
  Move r2(largestHeap, coins, smallestHeap, coins - 1);

  if(smallestHeap == largestHeap)
    return r1;
  else
    return r2;
}
