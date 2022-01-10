#ifndef _ROOK_H_
#define _ROOK_H_

#include "piece.h"
#include <string>
#include <memory>

class Rook : public Piece{
public:
  Rook(COLOUR colour, bool moved, PIECETYPE piecetype);
  // Rook moves and captures pieces
  virtual std::vector<std::shared_ptr<Move>> getMoves(int x, int y, std::shared_ptr<Board> chessBoard) override;
};

#endif