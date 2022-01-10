#include <memory>
#include "move.h"
#include "piece.h"
#include "cell.h"
#include "piecetype.h"
#include <iostream>
using namespace std;

Move::Move(shared_ptr<Cell> fromCell, shared_ptr<Cell> toCell, std::shared_ptr<Piece> capturedPiece):
  fromCell{fromCell},
  toCell{toCell},
  capturedPiece{capturedPiece},
  castleMove{false},
  enPassantMove{false},
  pawnPromotionMove{false}
  // piece{piece},
  // capturedPiece{capturedPiece}
{
  // if(fromCell->getPiece()){
  //   if(fromCell->getPiece()->getPieceType() == PIECETYPE::KING && this->getXChange() >= 2){
  //     castleMove = true;
  //   } else {
  //     castleMove = false;
  //   }
  // }
}

shared_ptr<Cell> Move::getFromCell(){
  return fromCell;
}

shared_ptr<Cell> Move::getToCell(){
  return toCell;
}

int Move::getXChange(){
  int xChange = fromCell->getX() - toCell->getX();
  return ((xChange > 0) ? xChange : (xChange * -1));
}

int Move::getYChange(){
  int yChange = fromCell->getY() - toCell->getY();
  return ((yChange > 0) ? yChange : (yChange * -1));
}

shared_ptr<Piece> Move::getCapturedPiece(){
  return capturedPiece;
}

bool Move::isCastleMove(){
  return castleMove;
}

bool Move::isEnPassantMove(){
  return enPassantMove;
}

bool Move::isPawnPromotionMove(){
  return pawnPromotionMove;
}

void Move::setCastleMove(){
  castleMove = true;
}

void Move::setEnPassantMove(){
  enPassantMove = true;
}

void Move::setPawnPromotionMove(){
  pawnPromotionMove = true;
}

void Move::setCapturedPiece(shared_ptr<Piece> thePiece){
 capturedPiece = thePiece;
}
