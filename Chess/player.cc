#include "player.h"
#include "colour.h"

Player::Player(COLOUR colour, bool compPlayer)
  : colour{colour},
    compPlayer{compPlayer},
    score{0}
{}

Player::~Player() {
}

bool Player::isCompPlayer(){
  return compPlayer;
}

float Player::getScore(){
  return score;
}

void Player::addScore(float points){
  score = score + points;
}