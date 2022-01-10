#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_

#include "player.h"
#include "colour.h"

class HumanPlayer: public Player {
public:
  HumanPlayer(COLOUR colour, bool isCompPlayer);
};

#endif