#include "king.h"
#include "colour.h"
#include "piecetype.h"
#include "board.h"
#include "move.h"
#include "cell.h"
#include <vector>
using namespace std;

King::King(COLOUR colour, bool moved, PIECETYPE piecetype):
  Piece{colour, moved, PIECETYPE::KING},
  castled{false}
{}

vector<shared_ptr<Move>> King::getMoves(int x, int y, shared_ptr<Board> chessBoard){
  int rows = chessBoard->getRows();
  int cols = chessBoard->getCols();
  
  auto fromCell = chessBoard->getCell(x, y);  
  vector<shared_ptr<Move>> availableMoves;
  // move up one square
  int toY = y + 1;
  if(0 <= toY && toY <= (rows-1)){ 
    auto toCell = chessBoard->getCell(x, toY);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  // move down one square
  toY = y - 1;
  if(0 <= toY && toY <= (rows-1)){ 
    auto toCell = chessBoard->getCell(x, toY);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  // move right one square
  int toX = x + 1;
  if(0 <= toX && toX <= (cols-1)){ 
    auto toCell = chessBoard->getCell(toX, y);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  // move left one square
  toX = x - 1;
  if(0 <= toX && toX <= (cols-1)){ 
    auto toCell = chessBoard->getCell(toX, y);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  // move up right one square
  toY = y + 1;
  toX = x + 1;
  if(toX <= (cols-1) && toY <= (rows-1)){ 
    auto toCell = chessBoard->getCell(toX, toY);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }
  // move up left one square
  toY = y + 1;
  toX = x - 1;
  if(0 <= toX && toY <= (rows-1)){ 
    auto toCell = chessBoard->getCell(toX, toY);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  // move down right one square
  toY = y - 1;
  toX = x + 1;
  if(toX <= (cols-1) && 0 <= toY){ 
    auto toCell = chessBoard->getCell(toX, toY);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  // move down left one square
  toX = x - 1;
  toY = y - 1;
  if(0 <= toX && 0 <= toY){ 
    auto toCell = chessBoard->getCell(toX, toY);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  // Castle left
  if(!isMoved()){
    toX = x - 1;
    // check if at least two cells to the left are unoccupied and if there is a rook
    if(0 <= toX){
      auto curPiece = chessBoard->getCell(toX, y)->getPiece();
      
      while(0 <= toX && !curPiece){
        curPiece = chessBoard->getCell(toX, y)->getPiece();
        --toX;
      }
      ++toX;
      if((x-toX) > 2 && curPiece && curPiece->getPieceType() == PIECETYPE::ROOK){
        auto toCell = chessBoard->getCell(toX, y);
        auto newMove = buildMove(fromCell, toCell);
        newMove->setCastleMove();
        availableMoves.emplace_back(newMove);
      }
    }
  }
  // Castle right
  if(!isMoved()){
    toX = x + 1;
    if(toX <= (cols-1)){
      auto curPiece = chessBoard->getCell(toX, y)->getPiece();
      while(toX <= (cols-1) && !curPiece){
        curPiece = chessBoard->getCell(toX, y)->getPiece();
        ++toX;
      }
            
      --toX;
      if((toX-x) > 2 && curPiece && curPiece->getPieceType() == PIECETYPE::ROOK){
        auto toCell = chessBoard->getCell(toX, y);
        auto newMove = buildMove(fromCell, toCell);
        newMove->setCastleMove();
        availableMoves.emplace_back(newMove);
      }
    }
  }
  return availableMoves;
}