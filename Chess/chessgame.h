#ifndef _CHESSGAME_H_
#define _CHESSGAME_H_

#include <vector>
#include <memory>
#include <string>
#include "colour.h"
#include "gamestatus.h"

class Board;
class Player;
class Move;
class Cell;

class ChessGame {
  std::shared_ptr<Board> chessBoard;
  std::vector<std::shared_ptr<Player>> players;
  COLOUR turn;
  GAMESTATUS gameStatus;
  std::vector<std::shared_ptr<Move>> availableMoves;
  std::vector<std::shared_ptr<Move>> pastMoves;

  void switchTurns();
  void updateMoves();
  void undoMove();
  void updateGameStatus();
  void addMoves(std::vector<std::shared_ptr<Move>> & moveVector);
  void addCaptureMoves(std::vector<std::shared_ptr<Move>> & moveVector);
  void removeNonSafeMoves(std::vector<std::shared_ptr<Move>> & moveVector);
  void removeNonCheckOrCaptureMoves(std::vector<std::shared_ptr<Move>> & moveVector);
  bool checkMove(std::shared_ptr<Move> move); // returns true if move is valid
  void makeMove(std::shared_ptr<Move> move); 
  void getUpdatedCells(std::vector<std::shared_ptr<Cell>> & cells, std::shared_ptr<Move> move); // used to optimize observer

  public: // p1Level and p2Level is 0 if human player
    ChessGame();
    void init(int p1Level, int p2Level);
    void reset();
    bool checkValidBoard();

    void playerMove(std::string fromCellString, std::string toCellString);
    void undoLastMove();
    void endGame();
    void printScore();
    bool isCurrentPlayerCPU();
    void makeCPUMove();

    COLOUR getTurn();
    GAMESTATUS getGameStatus();

    void setTurn(COLOUR theColour);
    void setGameStatus(GAMESTATUS theGameStatus);
    void setBoard(std::shared_ptr<Board> theBoard);
};

#endif