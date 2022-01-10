#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "colour.h"

class Player{
  COLOUR colour;
  bool compPlayer;
  float score;
  public:
    Player(COLOUR colour, bool compPlayer);
    virtual ~Player() = 0;

    bool isCompPlayer();
    float getScore();
    void addScore(float points);
};

#endif