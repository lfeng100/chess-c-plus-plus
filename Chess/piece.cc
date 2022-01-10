#include "piece.h"
#include "move.h"
#include "cell.h"
#include <memory>
using namespace std;

Piece::Piece(COLOUR colour, bool moved, PIECETYPE pieceType)
  : colour{colour},
    moved{moved},
    pieceType{pieceType},
    promoted{false}
{}

shared_ptr<Move> Piece::buildMove(shared_ptr<Cell> fromCell, shared_ptr<Cell> toCell){
  auto capturedPiece = toCell->getPiece();
  auto newMove = make_shared<Move>(fromCell, toCell, (capturedPiece ? capturedPiece : nullptr));
  newMove->setCapturedPiece(capturedPiece);
  return newMove;
}

COLOUR Piece::getColour(){
  return colour;
}

PIECETYPE Piece::getPieceType(){
  return pieceType;
}

bool Piece::isMoved(){
  return moved;
}

void Piece::setMoved(bool theMoved){
  moved = theMoved;
}

void Piece::setPromoted(bool thePromoted){
  promoted = thePromoted;
}