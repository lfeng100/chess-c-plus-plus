#ifndef _PIECE_H_
#define _PIECE_H_

#include <vector>
#include <string>
#include <memory>

#include "colour.h"
#include "piecetype.h"

class Board;
class Move;
class Cell;

class Piece{
  COLOUR colour;
  bool moved;
  PIECETYPE pieceType;
  bool promoted;
public:
  Piece(COLOUR colour, bool moved, PIECETYPE pieceType);
  virtual std::vector<std::shared_ptr<Move>> getMoves(int x, int y, std::shared_ptr<Board> chessBoard) = 0;
  std::shared_ptr<Move> buildMove(std::shared_ptr<Cell> fromCell, std::shared_ptr<Cell> toCell);

  COLOUR getColour();
  PIECETYPE getPieceType();
  bool isMoved();

  void setMoved(bool theMoved);
  void setPromoted(bool thePromoted);
};

#endif