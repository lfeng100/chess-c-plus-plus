#ifndef _KNIGHT_H_
#define _KNIGHT_H_

#include "piece.h"
#include <string>
#include <memory>

class Knight : public Piece{
public:
  Knight(COLOUR colour, bool moved, PIECETYPE piecetype);
  // Knight moves and captures pieces.
  virtual std::vector<std::shared_ptr<Move>> getMoves(int x, int y, std::shared_ptr<Board> chessBoard) override;
};

#endif