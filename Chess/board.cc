#include "board.h"
#include "colour.h"
#include "piecetype.h"
#include "cell.h"
#include "piece.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "king.h"
#include "queen.h"
#include "pawn.h"
#include "player.h"
#include <vector>
#include <memory>
#include <iostream>
using namespace std;

Board::Board(int theRows, int theCols){
  rows = theRows;
  cols = theCols;

  for(int i = 1; i <= rows; ++i){
    vector<shared_ptr<Cell>> curCol;

    for(int j = 1; j <= cols; ++j){
      curCol.emplace_back(make_shared<Cell>(i, j));
    }

    cells.emplace_back(curCol);
  }
}

void Board::clearBoard(){
  cells.clear();
  
  for(int i = 1; i <= rows; ++i){
    vector<shared_ptr<Cell>> curCol;

    for(int j = 1; j <= cols; ++j){
      curCol.emplace_back(make_shared<Cell>(i, j));
    }

    cells.emplace_back(curCol);
  }
  vector<shared_ptr<Cell>> cells;
  for(int i = 0; i < getCols(); ++i){
    for(int j = 0; j < getRows(); ++j){
      cells.emplace_back(make_shared<Cell>(i,j));
    }
  }
  printBoard(cells);
}

// setup standard board
void Board::initStandard(){
  // WHITE PIECES
  cells[0][0]->setPiece(make_shared<Rook>(COLOUR::WHITE, false, PIECETYPE::ROOK));
  cells[1][0]->setPiece(make_shared<Knight>(COLOUR::WHITE, false, PIECETYPE::KNIGHT));
  cells[2][0]->setPiece(make_shared<Bishop>(COLOUR::WHITE, false, PIECETYPE::BISHOP));
  cells[3][0]->setPiece(make_shared<Queen>(COLOUR::WHITE, false, PIECETYPE::QUEEN));
  cells[4][0]->setPiece(make_shared<King>(COLOUR::WHITE, false, PIECETYPE::KING));
  cells[5][0]->setPiece(make_shared<Bishop>(COLOUR::WHITE, false, PIECETYPE::BISHOP));
  cells[6][0]->setPiece(make_shared<Knight>(COLOUR::WHITE, false, PIECETYPE::KNIGHT));
  cells[7][0]->setPiece(make_shared<Rook>(COLOUR::WHITE, false, PIECETYPE::ROOK));

  for(int i = 0; i < cols; ++i){
    cells[i][1]->setPiece(make_shared<Pawn>(COLOUR::WHITE, false, PIECETYPE::PAWN));
  }

  // BLACK PIECES
  cells[0][7]->setPiece(make_shared<Rook>(COLOUR::BLACK, false, PIECETYPE::ROOK));
  cells[1][7]->setPiece(make_shared<Knight>(COLOUR::BLACK, false, PIECETYPE::KNIGHT));
  cells[2][7]->setPiece(make_shared<Bishop>(COLOUR::BLACK, false, PIECETYPE::BISHOP));
  cells[3][7]->setPiece(make_shared<Queen>(COLOUR::BLACK, false, PIECETYPE::QUEEN));
  cells[4][7]->setPiece(make_shared<King>(COLOUR::BLACK, false, PIECETYPE::KING));
  cells[5][7]->setPiece(make_shared<Bishop>(COLOUR::BLACK, false, PIECETYPE::BISHOP));
  cells[6][7]->setPiece(make_shared<Knight>(COLOUR::BLACK, false, PIECETYPE::KNIGHT));
  cells[7][7]->setPiece(make_shared<Rook>(COLOUR::BLACK, false, PIECETYPE::ROOK));

  for(int i = 0; i < cols; ++i){
    cells[i][6]->setPiece(make_shared<Pawn>(COLOUR::BLACK, false, PIECETYPE::PAWN));
  }
}

void Board::addPiece(string piece, string cell, bool promoted){
  char pieceChar = piece[0];
  int x = cell[0] - 'a';
  int y = cell[1] - '1';

  switch(pieceChar){
    case 'K':{
      auto thePiece = make_shared<King>(COLOUR::WHITE, false, PIECETYPE::KING);
      setCell(x, y, thePiece);
      break;
    }
    case 'k':{
      auto thePiece = make_shared<King>(COLOUR::BLACK, false, PIECETYPE::KING);
      setCell(x, y, thePiece);
      break;
    }
    case 'Q':{
      auto thePiece = make_shared<Queen>(COLOUR::WHITE, false, PIECETYPE::KING);
      setCell(x, y, thePiece);
      if(promoted){
        thePiece->setPromoted(true);
      }
      break;
    }
    case 'q':{
      auto thePiece = make_shared<Queen>(COLOUR::BLACK, false, PIECETYPE::KING);
      setCell(x, y, thePiece);
      if(promoted){
        thePiece->setPromoted(true);
      }
      break;
    }
    case 'R':{
      auto thePiece = make_shared<Rook>(COLOUR::WHITE, false, PIECETYPE::KING);
      setCell(x, y, thePiece);
      if(promoted){
        thePiece->setPromoted(true);
      }
      break;
    }
    case 'r':{
      auto thePiece = make_shared<Rook>(COLOUR::BLACK, false, PIECETYPE::KING);
      setCell(x, y, thePiece);
      if(promoted){
        thePiece->setPromoted(true);
      }
      break;
    }
    case 'B':{
      auto thePiece = make_shared<Bishop>(COLOUR::WHITE, false, PIECETYPE::KING);
      setCell(x, y, thePiece);
      if(promoted){
        thePiece->setPromoted(true);
      }
      break;
    }
    case 'b':{
      auto thePiece = make_shared<Bishop>(COLOUR::BLACK, false, PIECETYPE::KING);
      setCell(x, y, thePiece);
      if(promoted){
        thePiece->setPromoted(true);
      }
      break;
    }
    case 'N':{
      auto thePiece = make_shared<Knight>(COLOUR::WHITE, false, PIECETYPE::KING);
      setCell(x, y, thePiece);
      if(promoted){
        thePiece->setPromoted(true);
      }
      break;
    }
    case 'n':{
      auto thePiece = make_shared<Knight>(COLOUR::BLACK, false, PIECETYPE::KING);
      setCell(x, y, thePiece);
      if(promoted){
        thePiece->setPromoted(true);
      }
      break;
    }
    case 'P':{
      auto thePiece = make_shared<Pawn>(COLOUR::WHITE, false, PIECETYPE::KING);
      setCell(x, y, thePiece);
      break;
    }
    case 'p':{
      auto thePiece = make_shared<Pawn>(COLOUR::BLACK, false, PIECETYPE::KING);
      setCell(x, y, thePiece);
      break;
    }
  }
  
  vector<shared_ptr<Cell>> cells{make_shared<Cell>(x,y)};
  if(!promoted){
    printBoard(cells);
  }
}

int Board::countPieces(){
  int count = 0;
  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < cols; ++j){
      auto curPiece = cells[i][j]->getPiece();
      if(curPiece){
        count++;
      }
    }
  }
  return count;
}

void Board::removePiece(string cell){
  int x = cell[0] - 'a';
  int y = cell[1] - '1';
  setCell(x, y, nullptr);

  vector<shared_ptr<Cell>> cells{make_shared<Cell>(x,y)};
  printBoard(cells);
}

bool Board::checkValidPieces(){
  int whiteKing = 0;
  int blackKing = 0;
  int otherPieces = 0;

  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < cols; ++j){
      auto curPiece = cells[i][j]->getPiece();
      if(curPiece){
        PIECETYPE pieceType = curPiece->getPieceType();
        if(pieceType == PIECETYPE::PAWN && (j == 0 || j == 7)){
          return false;
        } else if (pieceType == PIECETYPE::KING){
          COLOUR pieceColour = curPiece->getColour();
          if(pieceColour == COLOUR::BLACK){
            blackKing++;
          } else {
            whiteKing++;
          }
        } else {
          otherPieces++;
        }
      }
    }
  }

  if(whiteKing != 1 || blackKing != 1 || otherPieces == 0){
    return false;
  }

  // check neither king in check
  return true;
}

shared_ptr<Cell> Board::getCell(int x, int y){
  return cells[x][y];
}

int Board::getRows(){
  return rows;
}

int Board::getCols(){
  return cols;
}

void Board::setCell(int x, int y, shared_ptr<Piece> piece) {
  if(piece){
    if(piece->getPieceType() == PIECETYPE::PAWN){
      if(y != 1 && y != 6){ // set moved if Pawn not on 2nd/7th rank
        piece->setMoved(true);
      }
    } else if (piece->getPieceType() == PIECETYPE::KING){
      if(y != 0 && y != 7){ // set moved if King not on 1st/8th rank
        piece->setMoved(true);
      }
    }
  }

  cells[x][y]->setPiece(piece);
}

void Board::printBoard(vector<shared_ptr<Cell>> cells){
  notifyObservers(cells);
}

char Board::getState(int row, int col) const{
  auto thePiece = cells[row][col]->getPiece();
  COLOUR theColour = COLOUR::NONE;
  PIECETYPE thePieceType = PIECETYPE::NONE;

  if(thePiece){ // if piece is not null
   theColour = thePiece->getColour();
   thePieceType = thePiece->getPieceType();
  }
  
  char theState = 'E'; // default empty state

  if(thePieceType == PIECETYPE::PAWN){
    theState = 'p';
  } else if(thePieceType == PIECETYPE::KNIGHT) {
    theState = 'n';
  } else if(thePieceType == PIECETYPE::BISHOP) {
    theState = 'b';
  } else if(thePieceType == PIECETYPE::ROOK) {
    theState = 'r';
  } else if(thePieceType == PIECETYPE::QUEEN) {
    theState = 'q';
  } else if(thePieceType == PIECETYPE::KING) {
    theState = 'k';
  }

  // make lowercase by updating ASCII ('a' - 'A' = 32)
  if(theColour == COLOUR::WHITE){ 
    theState = theState - 32;
  }

  return theState;
}

bool Board::isPieceAttacked(COLOUR colour, int i, int j){
  // PAWN CHECKS
  int pawnDirection = 1;

  if(colour == COLOUR::BLACK){
    pawnDirection = -1;
  }
  // pawn to the right
  int toX = i + 1;
  int toY = j + pawnDirection;
  if(0 <= toY && toY <= (rows-1) && toX <= (cols-1)){ 
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece && thePiece->getColour() != colour && thePiece->getPieceType() == PIECETYPE::PAWN){
      return true;
    }
  }

  // pawn to the left
  toX = i - 1;
  toY = j + pawnDirection;
  if(0 <= toY && toY <= (rows-1) && 0 <= toX){ 
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece && thePiece->getColour() != colour && thePiece->getPieceType() == PIECETYPE::PAWN){
      return true;
    }
  }
  // KNIGHT CHECKS

  // right one, up two
  toX = i+1;
  toY = j+2;
  if(toX <= (cols-1) && toY <= (rows-1)){ 
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece && thePiece->getColour() != colour && thePiece->getPieceType() == PIECETYPE::KNIGHT){
      return true;
    }
  }
  // right two, up one
  toX = i+2;
  toY = j+1;
  if(0 <= toY && toY <= (rows-1) && 0 <= toX && toX <= (cols-1)){ 
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece && thePiece->getColour() != colour && thePiece->getPieceType() == PIECETYPE::KNIGHT){
      return true;
    }
  }

  // right two, down one
  toX = i+2;
  toY = j-1;
  if(0 <= toY && toY <= (rows-1) && 0 <= toX && toX <= (cols-1)){ 
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece && thePiece->getColour() != colour && thePiece->getPieceType() == PIECETYPE::KNIGHT){
      return true;
    }
  }

  // move right one, down two
  toX = i+1;
  toY = j-2;
  if(0 <= toY && toY <= (rows-1) && 0 <= toX && toX <= (cols-1)){ 
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece && thePiece->getColour() != colour && thePiece->getPieceType() == PIECETYPE::KNIGHT){
      return true;
    }
  }

  // move left one, down two
  toX = i-1;
  toY = j-2;
  if(0 <= toY && toY <= (rows-1) && 0 <= toX && toX <= (cols-1)){ 
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece && thePiece->getColour() != colour && thePiece->getPieceType() == PIECETYPE::KNIGHT){
      return true;
    }
  }

  // move left two, down one
  toX = i-2;
  toY = j-1;
  if(0 <= toY && toY <= (rows-1) && 0 <= toX && toX <= (cols-1)){ 
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece && thePiece->getColour() != colour && thePiece->getPieceType() == PIECETYPE::KNIGHT){
      return true;
    }
  }

  // move left two, up one
  toX = i-2;
  toY = j+1;
  if(0 <= toY && toY <= (rows-1) && 0 <= toX && toX <= (cols-1)){ 
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece && thePiece->getColour() != colour && thePiece->getPieceType() == PIECETYPE::KNIGHT){
      return true;
    }
  }
  // move left one, up two
  toX = i-1;
  toY = j+2;
  if(0 <= toY && toY <= (rows-1) && 0 <= toX && toX <= (cols-1)){ 
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece && thePiece->getColour() != colour && thePiece->getPieceType() == PIECETYPE::KNIGHT){
      return true;
    }
  }

  // ROOK/QUEEN CHECKS

  // up direction
  toX=i;
  for(int toY = j+1; toY <= (rows-1); ++toY){
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece){
      if(thePiece->getColour() != colour &&(thePiece->getPieceType() == PIECETYPE::ROOK || thePiece->getPieceType() == PIECETYPE::QUEEN)){
        return true;
      } else {
        break;
      }
    }
  }
  // down direction
  toX=i;
  for(int toY = j-1; 0 <= toY; --toY){
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece){
      if(thePiece->getColour() != colour &&(thePiece->getPieceType() == PIECETYPE::ROOK || thePiece->getPieceType() == PIECETYPE::QUEEN)){
        return true;
      } else {
        break;
      }
    }
  }

  // left direction
  toY=j;
  for(int toX = i-1; 0 <= toX; --toX){
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece){
      if(thePiece->getColour() != colour &&(thePiece->getPieceType() == PIECETYPE::ROOK || thePiece->getPieceType() == PIECETYPE::QUEEN)){
        return true;
      } else {
        break;
      }
    }
  }
  // right direction
  toY=j;
  for(int toX = i+1; toX <= (cols-1); ++toX){
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece){
      if(thePiece->getColour() != colour &&(thePiece->getPieceType() == PIECETYPE::ROOK || thePiece->getPieceType() == PIECETYPE::QUEEN)){
        return true;
      } else {
        break;
      }
    }
  }
  // up right direction
  toX = i+1;
  toY = j+1;
  while(toX <= (cols-1) && toY <= (rows-1)){
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece){
      if(thePiece->getColour() != colour &&(thePiece->getPieceType() == PIECETYPE::BISHOP || thePiece->getPieceType() == PIECETYPE::QUEEN)){
        return true;
      } else {
        break;
      }
    }
    ++toX;
    ++toY;
  }
  // down right direction
  toX = i+1;
  toY = j-1;
  while(toX <= (cols-1) && 0 <= toY){
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece){
      if(thePiece->getColour() != colour &&(thePiece->getPieceType() == PIECETYPE::BISHOP || thePiece->getPieceType() == PIECETYPE::QUEEN)){
        return true;
      } else {
        break;
      }
    }
    ++toX;
    --toY;
  }
  // up left direction
  toX = i-1;
  toY = j+1;
  while(0 <= toX && toY <= (rows-1)){
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece){
      if(thePiece->getColour() != colour &&(thePiece->getPieceType() == PIECETYPE::BISHOP || thePiece->getPieceType() == PIECETYPE::QUEEN)){
        return true;
      } else {
        break;
      }
    }
    --toX;
    ++toY;
  }
  // down left direction
  toX = i-1;
  toY = j-1;
  while(0 <= toX && 0 <= toY){
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece){
      if(thePiece->getColour() != colour &&(thePiece->getPieceType() == PIECETYPE::BISHOP || thePiece->getPieceType() == PIECETYPE::QUEEN)){
        return true;
      } else {
        break;
      }
    }
    --toX;
    --toY;
  }

  // down left direction
  // MAKE SURE NOT TOUCHING OTHER KING
  toX = i+1;
  if(toX <= (cols-1)){
    auto thePiece = getCell(toX, j)->getPiece();
    if(thePiece && thePiece->getPieceType() == PIECETYPE::KING){
      return true;
    }
  }
  toX = i-1;
  if(0 <= toX){
    auto thePiece = getCell(toX, j)->getPiece();
    if(thePiece && thePiece->getPieceType() == PIECETYPE::KING){
      return true;
    }
  }
  toY = j+1;
  if(toY <= (rows-1)){
    auto thePiece = getCell(i, toY)->getPiece();
    if(thePiece && thePiece->getPieceType() == PIECETYPE::KING){
      return true;
    }
  }
  toY = j-1;
  if(0 <= toY){
    auto thePiece = getCell(i, toY)->getPiece();
    if(thePiece && thePiece->getPieceType() == PIECETYPE::KING){
      return true;
    }
  }
  toX = i+1;
  toY = j+1;
  if(toX <= (cols-1) && toY <= (rows-1)){
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece && thePiece->getPieceType() == PIECETYPE::KING){
      return true;
    }
  }
  toX = i-1;
  toY = j+1;
  if(0 <= toX && toY <= (rows-1)){
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece && thePiece->getPieceType() == PIECETYPE::KING){
      return true;
    }
  }
  toX = i+1;
  toY = j-1;
  if(toX <= (cols-1) && 0 <= toY){
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece && thePiece->getPieceType() == PIECETYPE::KING){
      return true;
    }
  }
  toX = i-1;
  toY = j-1;
  if(0 <= toX && 0 <= toY){
    auto thePiece = getCell(toX, toY)->getPiece();
    if(thePiece && thePiece->getPieceType() == PIECETYPE::KING){
      return true;
    }
  }

  return false;
}

bool Board::isKingInCheck(COLOUR colour){
  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < cols; ++j){ // locate King of correct colour
      auto curPiece = cells[i][j]->getPiece();
      if(curPiece){
        PIECETYPE pieceType = curPiece->getPieceType();
        if (pieceType == PIECETYPE::KING){
          COLOUR pieceColour = curPiece->getColour();
          if(pieceColour == colour){
            return isPieceAttacked(colour, i,j);
          }
        }
      }
    }
  }
  return false;
}
