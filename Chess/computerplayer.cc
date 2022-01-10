#include "computerplayer.h"
#include "player.h"
#include "colour.h"

ComputerPlayer::ComputerPlayer(COLOUR colour, bool isCompPlayer, int level)
  : Player{colour, isCompPlayer},
    level{level}
{}

int ComputerPlayer::getLevel(){
  return level;
}
