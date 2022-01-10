#include "pawn.h"
#include "colour.h"
#include "piecetype.h"
#include "board.h"
#include "cell.h"
#include "move.h"
#include <vector>
using namespace std;

Pawn::Pawn(COLOUR colour, bool moved, PIECETYPE piecetype):
  Piece{colour, moved, PIECETYPE::PAWN}
{}

vector<shared_ptr<Move>> Pawn::getMoves(int x, int y, shared_ptr<Board> chessBoard){
  int moveDirection = 1;

  if(getColour() == COLOUR::BLACK){
    moveDirection = -1;
  }

  int rows = chessBoard->getRows();
  int cols = chessBoard->getCols();
  
  auto fromCell = chessBoard->getCell(x, y);  
  vector<shared_ptr<Move>> availableMoves;

  // move up up one square
  int toY = y+moveDirection;
  if(0 <= toY && toY <= (rows-1)){ 
    auto toCell = chessBoard->getCell(x, toY);
    if(!(toCell->getPiece())){
      auto newMove = buildMove(fromCell, toCell);
      if(toY == 7 || toY == 0){
        newMove->setPawnPromotionMove();
      }
      availableMoves.emplace_back(newMove);
    }
  }

  // move up two squares for first move
  toY = y+moveDirection+moveDirection;
  if(!(isMoved())){ 
    if(0 <= toY && toY <= (rows-1)){ 
      auto toCell = chessBoard->getCell(x, toY);
      if(!(toCell->getPiece())){
        availableMoves.emplace_back(buildMove(fromCell, toCell));
      }
    }
  }

  toY = y+moveDirection;
  int toX = x + 1;
  if(0 <= toY && toY <= (rows-1) && 0 <= toX && toX <= (cols-1)){ 
    auto toCell = chessBoard->getCell(toX, toY);
    auto enPassantCell = chessBoard->getCell(toX, y);
    auto capturePiece = toCell->getPiece();
    auto EPcapturePiece = enPassantCell->getPiece();
    if(capturePiece && capturePiece->getColour() != getColour()){ // must be a opponent piece when capturing
      auto newMove = buildMove(fromCell, toCell);
      newMove->setCapturedPiece(capturePiece); 
      if(toY == 7 || toY == 0){
        newMove->setPawnPromotionMove();
      }
      availableMoves.emplace_back(newMove);
    } else if (!capturePiece && EPcapturePiece && EPcapturePiece->getColour() != getColour()) {
      auto newMove = buildMove(fromCell, toCell);
      newMove->setCapturedPiece(EPcapturePiece); 
      newMove->setEnPassantMove();
      availableMoves.emplace_back(newMove);
    }
  }

  toY = y+moveDirection;
  toX = x - 1;
  if(0 <= toY && toY <= (rows-1) && 0 <= toX && toX <= (cols-1)){ 
    auto toCell = chessBoard->getCell(toX, toY);
    auto enPassantCell = chessBoard->getCell(toX, y);
    auto capturePiece = toCell->getPiece();
    auto EPcapturePiece = enPassantCell->getPiece();
    if(capturePiece && capturePiece->getColour() != getColour()){ // must be a opponent piece when capturing
      auto newMove = buildMove(fromCell, toCell);
      newMove->setCapturedPiece(capturePiece); 
      if(toY == 7 || toY == 0){
        newMove->setPawnPromotionMove();
      }
      availableMoves.emplace_back(newMove);
    } else if (!capturePiece && EPcapturePiece && EPcapturePiece->getColour() != getColour()) {
      auto newMove = buildMove(fromCell, toCell);
      newMove->setCapturedPiece(EPcapturePiece); 
      newMove->setEnPassantMove();
      availableMoves.emplace_back(newMove);
    }
  }

  return availableMoves;
}