#include "cell.h"
#include "piece.h"
// #include <iostream>
using namespace std;

Cell::Cell(){}

Cell::Cell(int x, int y):
  x{x},
  y{y}
{}

Cell::Cell(int x, int y, shared_ptr<Piece> piece):
  x{x},
  y{y},
  piece{piece}
{}

bool Cell::isEmpty(){
  if (piece == nullptr) {
    return true;
  }
  return false;
}

shared_ptr<Piece> Cell::getPiece(){
  return piece;
}

int Cell::getX(){
  return x;
}

int Cell::getY(){
  return y;
}

void Cell::setPiece(shared_ptr<Piece> thePiece){
  piece = thePiece;
}

void Cell::setX(int theX){
  x = theX;
}

void Cell::setY(int theY){
  y = theY;
}


