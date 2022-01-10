#ifndef _QUEEN_H_
#define _QUEEN_H_

#include "piece.h"
#include <string>
#include <memory>

class Queen : public Piece{
public:
  Queen(COLOUR colour, bool moved, PIECETYPE piecetype);
  // Queen moves and captures peices
  virtual std::vector<std::shared_ptr<Move>> getMoves(int x, int y, std::shared_ptr<Board> chessBoard) override;
};

#endif