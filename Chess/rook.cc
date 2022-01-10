#include "rook.h"
#include "colour.h"
#include "piecetype.h"
#include "board.h"
#include "move.h"
#include "cell.h"
#include <vector>
using namespace std;

Rook::Rook(COLOUR colour, bool moved, PIECETYPE piecetype):
  Piece{colour, moved, PIECETYPE::ROOK}
{}

vector<shared_ptr<Move>> Rook::getMoves(int x, int y, shared_ptr<Board> chessBoard){
  auto fromCell = chessBoard->getCell(x, y);
  vector<shared_ptr<Move>> availableMoves;
  
  int rows = chessBoard->getRows();
  int cols = chessBoard->getCols();

  // up direction
  for(int toY = y+1; toY <= (rows-1); ++toY){
    auto toCell = chessBoard->getCell(x, toY);
    if(toCell->getPiece()){
      availableMoves.emplace_back(buildMove(fromCell, toCell));
      break;
    }
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }
  // down direction
  for(int toY = y-1; 0 <= toY; --toY){
    auto toCell = chessBoard->getCell(x, toY);
    if(toCell->getPiece()){
      availableMoves.emplace_back(buildMove(fromCell, toCell));
      break;
    }
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }
  // left direction
  for(int toX = x-1; 0 <= toX; --toX){
    auto toCell = chessBoard->getCell(toX, y);
    if(toCell->getPiece()){
      availableMoves.emplace_back(buildMove(fromCell, toCell));
      break;
    }
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }
  // right direction
  for(int toX = x+1; toX <= (cols-1); ++toX){
    auto toCell = chessBoard->getCell(toX, y);
    if(toCell->getPiece()){
      availableMoves.emplace_back(buildMove(fromCell, toCell));
      break;
    }
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  return availableMoves;
}