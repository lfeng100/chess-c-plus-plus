#include "bishop.h"
#include "colour.h"
#include "piecetype.h"
#include "board.h"
#include "move.h"
#include "cell.h"
#include <vector>
using namespace std;

Bishop::Bishop(COLOUR colour, bool moved, PIECETYPE piecetype):
  Piece{colour, moved, PIECETYPE::BISHOP}
{}

vector<shared_ptr<Move>> Bishop::getMoves(int x, int y, shared_ptr<Board> chessBoard){
  auto fromCell = chessBoard->getCell(x, y);
  vector<shared_ptr<Move>> availableMoves;

  int rows = chessBoard->getRows();
  int cols = chessBoard->getCols();
  
  // up right direction
  int toX = x+1;
  int toY = y+1;
  while(toY <= (rows-1) && toX <= (cols-1)){
    auto toCell = chessBoard->getCell(toX, toY);
    // auto capturedPiece = toCell->getPiece();
    if(toCell->getPiece()){
      availableMoves.emplace_back(buildMove(fromCell, toCell));
      break;
    }
    availableMoves.emplace_back(buildMove(fromCell, toCell));

    ++toX;
    ++toY;
  }
  // down right direction
  toX = x+1;
  toY = y-1;
  while(0 <= toY && toX <= (cols-1)){
    auto toCell = chessBoard->getCell(toX, toY);
    if(toCell->getPiece()){
      availableMoves.emplace_back(buildMove(fromCell, toCell));
      break;
    }
    availableMoves.emplace_back(buildMove(fromCell, toCell));

    ++toX;
    --toY;
  }
  // up left direction
  toX = x-1;
  toY = y+1;
  while(toY <= (rows-1) && 0 <= toX){
    auto toCell = chessBoard->getCell(toX, toY);
    if(toCell->getPiece()){
      availableMoves.emplace_back(buildMove(fromCell, toCell));
      break;
    }
    availableMoves.emplace_back(buildMove(fromCell, toCell));
    --toX;
    ++toY;
  }
  // down left direction
  toX = x-1;
  toY = y-1;
  while(0 <= toY && 0 <= toX){
    auto toCell = chessBoard->getCell(toX, toY);
    if(toCell->getPiece()){
      availableMoves.emplace_back(buildMove(fromCell, toCell));
      break;
    }
    availableMoves.emplace_back(buildMove(fromCell, toCell));
    --toX;
    --toY;
  }

  // for (auto n : availableMoves) {
  //   cout << "FROM: X: " << n->getFromCell()->getX() << "Y: ";
  //   cout << n->getFromCell()->getY() << endl;
  //   cout << "To: X: " << n->getToCell()->getX() << "Y: ";
  //   cout << n->getToCell()->getY() << endl;
  // }
  return availableMoves;
}