#ifndef _KING_H_
#define _KING_H_

#include "piece.h"
#include <string>
#include <memory>

class King : public Piece{
  bool castled;
public:
  King(COLOUR colour, bool moved, PIECETYPE piecetype);
  // King normally moves and captures pieces.
  virtual std::vector<std::shared_ptr<Move>> getMoves(int x, int y, std::shared_ptr<Board> chessBoard) override;
  // castling
  bool castleMoves();
};

#endif