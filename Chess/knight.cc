#include "knight.h"
#include "colour.h"
#include "piecetype.h"
#include "board.h"
#include "move.h"
#include "cell.h"
#include <vector>
using namespace std;

Knight::Knight(COLOUR colour, bool moved, PIECETYPE piecetype):
  Piece{colour, moved, PIECETYPE::KNIGHT}
{}

vector<shared_ptr<Move>> Knight::getMoves(int x, int y, shared_ptr<Board> chessBoard){
  int rows = chessBoard->getRows();
  int cols = chessBoard->getCols();

  auto fromCell = chessBoard->getCell(x, y);
  vector<shared_ptr<Move>> availableMoves;

  // move right one, up two
  int toX = x+1;
  int toY = y+2;
  if(toY <= (rows-1) && toX <= (cols-1)){ 
    auto toCell = chessBoard->getCell(toX, toY);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  // move right two, up one
  toX = x+2;
  toY = y+1;
  if(toX <= (cols-1) && toY <= (rows-1)){ 
    auto toCell = chessBoard->getCell(toX, toY);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  // move right two, down one
  toX = x+2;
  toY = y-1;
  if(toX <= (cols-1) && 0 <= toY){ 
    auto toCell = chessBoard->getCell(toX, toY);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  // move right one, down two
  toX = x+1;
  toY = y-2;
  if(toX <= (cols-1) && 0 <= toY){ 
    auto toCell = chessBoard->getCell(toX, toY);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  // move left one, down two
  toX = x-1;
  toY = y-2;
  if(0 <= toX && 0 <= toY){ 
    auto toCell = chessBoard->getCell(toX, toY);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  // move left two, down one
  toX = x-2;
  toY = y-1;
  if(0 <= toX && 0 <= toY){ 
    auto toCell = chessBoard->getCell(toX, toY);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  // move left two, up one
  toX = x-2;
  toY = y+1;
  if(0 <= toX && toY <= (rows-1)){ 
    auto toCell = chessBoard->getCell(toX, toY);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  // move left one, up two
  toX = x-1;
  toY = y+2;
  if(0 <= toX && toY <= (rows-1)){ 
    auto toCell = chessBoard->getCell(toX, toY);
    availableMoves.emplace_back(buildMove(fromCell, toCell));
  }

  return availableMoves;
}