#ifndef _BOARD_H_
#define _BOARD_H_

#include <string>
#include <memory>
#include "subject.h"
#include "colour.h"

class Cell;
class Piece;

class Board: public Subject {
  int rows;
  int cols;
  std::vector<std::vector<std::shared_ptr<Cell>>> cells;

  void setCell(int x, int y, std::shared_ptr<Piece> piece);
public:
  Board(int theRows, int theCols);

  void clearBoard();
  // Fill board with standard layout
  void initStandard();
  // Add piece for setup
  void addPiece(std::string piece, std::string cell, bool promoted = false);
  void removePiece(std::string cell);
  bool checkValidPieces();
  int countPieces();
  bool isPieceAttacked(COLOUR colour, int x, int y);
  bool isKingInCheck(COLOUR colour);
  void printBoard(std::vector<std::shared_ptr<Cell>> cells);

  std::shared_ptr<Cell> getCell(int x, int y);
  int getRows();
  int getCols();
  
  virtual char getState(int row, int col) const override;
};

#endif