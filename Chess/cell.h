#ifndef _CELL_H_
#define _CELL_H_

#include <iostream>
#include <memory>
#include "piece.h"

class Piece;

class Cell{
  int x;
  int y;
  std::shared_ptr<Piece> piece;
public:
  Cell();
  Cell(int y, int x);
  Cell(int y, int x, std::shared_ptr<Piece> piece);
  bool isEmpty();

  std::shared_ptr<Piece> getPiece();
  int getX();
  int getY();

  void setPiece(std::shared_ptr<Piece> piece);
  void setX(int theX);
  void setY(int theY);
};

#endif