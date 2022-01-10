#ifndef _BISHOP_H_
#define _BISHOP_H_

#include "piece.h"
#include <string>
#include <memory>

class Bishop : public Piece{
public:
  Bishop(COLOUR colour, bool moved, PIECETYPE piecetype);
  // bishop moves and captures pieces diagonally
  virtual std::vector<std::shared_ptr<Move>> getMoves(int x, int y, std::shared_ptr<Board> chessBoard) override;
};

#endif