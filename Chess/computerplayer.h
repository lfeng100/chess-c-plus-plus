#ifndef _COMPUTERPLAYER_H_
#define _COMPUTERPLAYER_H_

#include "player.h"
#include "colour.h"
#include "chessgame.h"

class ComputerPlayer: public Player {
  int level;
public:
  ComputerPlayer(COLOUR colour, bool isCompPlayer, int level);
  int getLevel();
};

#endif

