#ifndef _PAWN_H_
#define _PAWN_H_

#include "piece.h"
#include <string>
#include <memory>

class Pawn : public Piece{
public:
  Pawn(COLOUR colour, bool moved, PIECETYPE piecetype);
  // Pawn moves and captures pieces (including pawn capture en passent)
  virtual std::vector<std::shared_ptr<Move>> getMoves(int x, int y, std::shared_ptr<Board> chessBoard) override;
};

#endif