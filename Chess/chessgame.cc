#include "chessgame.h"
#include "board.h"
#include "player.h"
#include "colour.h"
#include "move.h"
#include "cell.h"
#include "piece.h"
#include "gamestatus.h"
#include "computerplayer.h"
#include "humanplayer.h"
#include <vector>
#include <memory>
#include <string>
using namespace std;

ChessGame::ChessGame(){
  turn = COLOUR::WHITE;
  setGameStatus(GAMESTATUS::NOT_IN_GAME);
}

void ChessGame::init(int p1Level, int p2Level){
  players.clear();

  if(p1Level){ // p1Level and p2Level is 0 if human player
    auto p1 = make_shared<ComputerPlayer>(COLOUR::WHITE, true, p1Level);
    players.emplace_back(p1);
  } else {
    auto p1 = make_shared<HumanPlayer>(COLOUR::WHITE, false);
    players.emplace_back(p1);
  }
  
  if(p2Level){
    auto p2 = make_shared<ComputerPlayer>(COLOUR::BLACK, true, p2Level);
    players.emplace_back(p2);
  } else {
    auto p2 = make_shared<HumanPlayer>(COLOUR::BLACK, false);
    players.emplace_back(p2);
  }
  setGameStatus(GAMESTATUS::PREPROCESSING);
  vector<shared_ptr<Cell>> cells;
  for(int i = 0; i < chessBoard->getCols(); ++i){
    for(int j = 0; j < chessBoard->getRows(); ++j){
      cells.emplace_back(make_shared<Cell>(i,j));
    }
  }
  chessBoard->printBoard(cells);
  updateMoves();
  updateGameStatus();
}

void ChessGame::reset(){
  int count = 0;
  while(!pastMoves.empty()){
    undoMove();
    switchTurns();
    ++count;
  }
  setGameStatus(GAMESTATUS::PREPROCESSING);

  vector<shared_ptr<Cell>> cells;
  for(int i = 0; i < chessBoard->getCols(); ++i){
    for(int j = 0; j < chessBoard->getRows(); ++j){
      cells.emplace_back(make_shared<Cell>(i,j));
    }
  }
  chessBoard->printBoard(cells);
  updateMoves();
  updateGameStatus();
}

void ChessGame::updateGameStatus(){
  if(chessBoard->isKingInCheck(turn)){
    setGameStatus(GAMESTATUS::IN_CHECK);
  } else if (chessBoard->countPieces() <= 2){
    setGameStatus(GAMESTATUS::STALEMATE);
  } else {
    setGameStatus(GAMESTATUS::IN_GAME);
  }
  if(availableMoves.empty()){ // if no more available moves, game ends
    if(gameStatus == GAMESTATUS::IN_CHECK){ // if in check, then checkmate
      if(turn == COLOUR::WHITE){
        setGameStatus(GAMESTATUS::WHITE_IS_MATED);
      } else {
        setGameStatus(GAMESTATUS::BLACK_IS_MATED);
      }
    } else { // if not in check, then stalemate
      setGameStatus(GAMESTATUS::STALEMATE);
    }
  }
}

bool ChessGame::checkValidBoard(){
  setGameStatus(GAMESTATUS::PREPROCESSING);
  updateMoves();

  if(availableMoves.empty()){
    return false;
  } else if (chessBoard->isKingInCheck(COLOUR::WHITE)) {
    return false;
  } else if (chessBoard->isKingInCheck(COLOUR::BLACK)) {
    return false;
  }
  return chessBoard->checkValidPieces();
}

void ChessGame::endGame(){
  if(gameStatus == GAMESTATUS::BLACK_IS_MATED){
    cout << "CHECKMATE! PLAYER 1 (WHITE) WINS" << endl;
    players[0]->addScore(1);
  } else if(gameStatus == GAMESTATUS::WHITE_IS_MATED) {
    cout << "CHECKMATE! PLAYER 2 (BLACK) WINS" << endl;
    players[1]->addScore(1);
  } else if(gameStatus == GAMESTATUS::STALEMATE){
    cout << "STALEMATE!" << endl;
    players[0]->addScore(0.5);
    players[1]->addScore(0.5);
  } else {
    cout << "RESIGNED" << endl;
    if(turn == COLOUR::WHITE){
      players[1]->addScore(1);
    } else {
      players[0]->addScore(1);
    }
  }
  cout << "Current Score: " << endl;
  printScore();
}

void ChessGame::switchTurns(){
  if(turn == COLOUR::WHITE){
    turn = COLOUR::BLACK;
  } else {
    turn = COLOUR::WHITE;
  }
}

void ChessGame::getUpdatedCells(vector<shared_ptr<Cell>> & cells, shared_ptr<Move> theMove){
  int fromX = theMove->getFromCell()->getX()-1;
  int fromY = theMove->getFromCell()->getY()-1;
  int toX = theMove->getToCell()->getX()-1;
  int toY = theMove->getToCell()->getY()-1;
  cells.emplace_back(make_shared<Cell>(fromX, fromY));
  cells.emplace_back(make_shared<Cell>(toX, toY));
  if(theMove->isEnPassantMove()){
    if(turn == COLOUR::WHITE){
      cells.emplace_back(make_shared<Cell>(toX, toY-1));
    } else {
      cells.emplace_back(make_shared<Cell>(toX, toY+1));
    }
  } else if (theMove->isCastleMove()){
    if(toX > fromX){ // right castle 
      cells.emplace_back(make_shared<Cell>(fromX+1, toY));
      cells.emplace_back(make_shared<Cell>(fromX+3, toY));
    } else {
      cells.emplace_back(make_shared<Cell>(fromX-1, toY));
      cells.emplace_back(make_shared<Cell>(fromX-3, toY));
      cells.emplace_back(make_shared<Cell>(fromX-4, toY));
    }
  }
  cout << "SIZE: " << cells.size() << endl;
}

void ChessGame::removeNonSafeMoves(vector<shared_ptr<Move>> & moveVector){
  for (int i = (moveVector.size() - 1); i >= 0 ; --i) {
    auto curMove = moveVector[i];
    if(!curMove->isCastleMove()){
      auto curPiece = curMove->getFromCell()->getPiece();   
      auto toCell = curMove->getToCell();
      
      makeMove(curMove);
      switchTurns();
      if(chessBoard->isPieceAttacked(curPiece->getColour(),toCell->getX()-1,toCell->getY()-1)){
        moveVector.erase(moveVector.begin() + i);
      }
      undoMove();

      switchTurns();
    }
  }
}

void ChessGame::removeNonCheckOrCaptureMoves(vector<shared_ptr<Move>> & moveVector){
  for (int i = (moveVector.size() - 1); i >= 0 ; --i) {
    auto curMove = moveVector[i];
    auto targetPiece = curMove->getCapturedPiece();
    if(!targetPiece || targetPiece->getColour() == turn){
      makeMove(curMove);
      switchTurns();
      if(!chessBoard->isKingInCheck(turn)){
        moveVector.erase(moveVector.begin() + i);
      }

      undoMove();
      switchTurns();
    }
  }
}

void ChessGame::addCaptureMoves(vector<shared_ptr<Move>> & moveVector){
  addMoves(moveVector);
  for (int i = (moveVector.size() - 1); i >= 0 ; --i) {
    auto targetPiece = moveVector[i]->getCapturedPiece();
    if(!targetPiece || targetPiece->getColour() == turn){
      moveVector.erase(moveVector.begin() + i);
    }
  }
}

void ChessGame::addMoves(vector<shared_ptr<Move>> & moveVector){
  int rows = chessBoard->getRows();
  int cols = chessBoard->getCols();
  for(int i = 0; i < cols; ++i){
    for(int j = 0; j < rows; ++j){
      auto curPiece = chessBoard->getCell(j,i)->getPiece();
      // must be a piece of current player's colour
      if(curPiece && curPiece->getColour() == turn){
        vector<shared_ptr<Move>> newMoves = curPiece->getMoves(j, i, chessBoard);

        for (auto n : newMoves) {
          auto fromCell = n->getFromCell();
          auto toCell = n->getToCell();
          auto movedPiece = fromCell->getPiece();
          auto targetCellPiece = toCell->getPiece();
          auto targetPiece = n->getCapturedPiece();
          // Not valid if piece targets own colour piece unless castle move

          if(!targetPiece || (targetPiece && targetPiece->getColour() != turn) || n->isCastleMove()){
            // check if it is a pawn that moved diagonal (capture move) and there is no piece there
            if(!movedPiece || (movedPiece && movedPiece->getPieceType() != PIECETYPE::PAWN) || fromCell->getX() == toCell->getX() || targetCellPiece){
              moveVector.emplace_back(n);
            } else {
              if(pastMoves.size() > 0){
                auto lastMove = pastMoves.back();
                auto lastMoveFromCell = lastMove->getFromCell();
                auto lastMoveToCell = lastMove->getToCell();
                // if target piece isn't a pawn that just moved two squares, not a valid en passant

                // en passant capture move must be against pawn that has just moved two squares
                // there is a piece adjacent to this pawn in the direction of its movement
                if(lastMoveToCell->getPiece()->getPieceType() == PIECETYPE::PAWN && (lastMove->getYChange() == 2) && (turn == COLOUR::WHITE ? (toCell->getY()-1 == lastMoveToCell->getY()) : (toCell->getY()+1 == lastMoveToCell->getY()))){
                    moveVector.emplace_back(n);
                }
              }
            }
          }
        } 
      }
    }
  }
}

void ChessGame::playerMove(string fromCellString, string toCellString){
  int fromX = fromCellString.at(0) - 'a';
  int fromY = fromCellString.at(1) - '0' - 1;
  int toX = toCellString.at(0) - 'a';
  int toY = toCellString.at(1) - '0' -1;

  auto fromCell = chessBoard->getCell(fromX, fromY);
  auto toCell = chessBoard->getCell(toX, toY);
  auto movedPiece = fromCell->getPiece();
  auto targetPiece = toCell->getPiece();
  

  // edit Castling move for logic
  if(movedPiece && movedPiece->getPieceType() == PIECETYPE::KING){
    if(turn == COLOUR::WHITE){
      if(toX == 2 && toY == 0){
        toCell = chessBoard->getCell(0, toY);
      } else if (toX == 6 && toY == 0){
        toCell = chessBoard->getCell(7, toY);
      }
    } else {
      if(toX == 2 && toY == 7){
        toCell = chessBoard->getCell(0, toY);
      } else if (toX == 6 && toY == 7){
        toCell = chessBoard->getCell(7, toY);
      }
    }
  }

  auto theMove = make_shared<Move>(fromCell, toCell, (targetPiece ? targetPiece : nullptr));

  if(checkMove(theMove)){ // make vector of updated cells for observer pattern
    makeMove(theMove);

    vector<shared_ptr<Cell>> cells;
    getUpdatedCells(cells, theMove);
    
    chessBoard->printBoard(cells);
    setGameStatus(GAMESTATUS::PREPROCESSING);
    switchTurns();
    updateMoves(); // moves are checked after each moves
    updateGameStatus();
  } else {
    cout << "Invalid Move" << endl;
  }
}


void ChessGame::makeCPUMove(){
  ComputerPlayer* curPlayer =  dynamic_cast<ComputerPlayer*>(turn == COLOUR::WHITE ? players[0].get() : players[1].get());
  int cpuLevel = curPlayer->getLevel();
  
  switch(cpuLevel){
    case 3: {
      vector<shared_ptr<Move>> safeCaptureOrCheckMoves = availableMoves;
      removeNonCheckOrCaptureMoves(safeCaptureOrCheckMoves);
      removeNonSafeMoves(safeCaptureOrCheckMoves);
      if(!safeCaptureOrCheckMoves.empty()){
        int randomIndex = rand() % safeCaptureOrCheckMoves.size();
        auto randomMove = safeCaptureOrCheckMoves[randomIndex]; 
        makeMove(randomMove);
        break;
      }

      vector<shared_ptr<Move>> safeNormalMoves = availableMoves;
      removeNonSafeMoves(safeNormalMoves);
      if(!safeNormalMoves.empty()){
        int randomIndex = rand() % safeNormalMoves.size();
        auto randomMove = safeNormalMoves[randomIndex]; 
        makeMove(randomMove);
        break;
      }
    }
    case 2: {
      vector<shared_ptr<Move>> captureOrCheckMoves = availableMoves;
      removeNonCheckOrCaptureMoves(captureOrCheckMoves);
      if(!captureOrCheckMoves.empty()){
        int randomIndex = rand() % captureOrCheckMoves.size();
        auto randomMove = captureOrCheckMoves[randomIndex]; 
        makeMove(randomMove);
        break;
      }
    }
    case 1: {
      int randomIndex = rand() % availableMoves.size();
      auto randomMove = availableMoves[randomIndex]; 
      makeMove(randomMove);
      break;
    }
  }
  vector<shared_ptr<Cell>> cells;
  auto lastMove = pastMoves.back();
  getUpdatedCells(cells, lastMove);
  
  chessBoard->printBoard(cells);
  setGameStatus(GAMESTATUS::PREPROCESSING);
  switchTurns();
  updateMoves();
  updateGameStatus();
}

// Takes O(N^2) time where N is number of available moves
void ChessGame::updateMoves(){
  setGameStatus(GAMESTATUS::PREPROCESSING);
  vector<shared_ptr<Move>> moveVector;
  addMoves(moveVector);
  availableMoves.clear();
  // Only add moves that won't put own King in check 
  for(auto n : moveVector){
    auto fromCell = n->getFromCell();
    auto toCell = n->getToCell();
    auto curPiece = fromCell->getPiece();
    COLOUR curCol = turn;
    makeMove(n);
    switchTurns();
    
    if(!chessBoard->isKingInCheck(curCol)){
      availableMoves.emplace_back(n);
    }

    undoMove();
    switchTurns();
  }
}

bool ChessGame::checkMove(shared_ptr<Move> move){
  auto fromCell = move->getFromCell();
  auto toCell = move->getToCell();
  auto movedPiece = fromCell->getPiece();
  auto targetPiece = move->getCapturedPiece();

  // Not valid if not in availableMoves vector
  for (auto n : availableMoves) {    
    auto correctFromCell = n->getFromCell();
    auto correctToCell = n->getToCell();
    if(correctFromCell->getX() == fromCell->getX()
      && correctFromCell->getY() == fromCell->getY()
      && correctToCell->getX() == toCell->getX()
      && correctToCell->getY() == toCell->getY()){
      if(n->isEnPassantMove()){
        move->setEnPassantMove();
        move->setCapturedPiece(n->getCapturedPiece());
      } else if (n->isCastleMove()) {
        move->setCastleMove();
      }  else if (n->isPawnPromotionMove()) {
        move->setPawnPromotionMove();
      }
      return true;
    }
  }
  return false;
}

// move is assumed to be valid when this function is called
void ChessGame::makeMove(shared_ptr<Move> move){
  auto fromCell = move->getFromCell();
  auto toCell = move->getToCell();
  auto movedPiece = fromCell->getPiece();
  auto targetPiece = move->getCapturedPiece();
  auto targetCellPiece = toCell->getPiece();
  if(move->isCastleMove()){
    int fromCellX = fromCell->getX();
    int toCellX = toCell->getX();
    int fromCellY = fromCell->getY();

    int kingXChange = (fromCellX > toCellX ? -3 : 1);
    int rookXChange = (fromCellX > toCellX ? -2 : 0);

    auto kingCell = chessBoard->getCell(fromCellX + kingXChange,fromCellY -1);

    auto rookCell = chessBoard->getCell(fromCellX + rookXChange,fromCellY - 1);

    kingCell->setPiece(movedPiece);
    rookCell->setPiece(targetCellPiece);

    toCell->setPiece(nullptr);
    movedPiece->setMoved(true);
  } else if(move->isEnPassantMove()) { // En Passant
    auto capturedCell = chessBoard->getCell(toCell->getX()-1,((turn == COLOUR::WHITE) ? (toCell->getY() - 2) : (toCell->getY())));

    capturedCell->setPiece(nullptr);
    toCell->setPiece(movedPiece);
  } else if(move->isPawnPromotionMove()) {
    string command;
    if(gameStatus == GAMESTATUS::PREPROCESSING  || isCurrentPlayerCPU()){
      command = (turn == COLOUR::WHITE ? "Q" : "q");
    } else {
      cout << "Enter piece to promote to: " << endl;
      while(cin >> command){
        char thePiece = command[0];
        if((thePiece != 'Q' && thePiece != 'q' && thePiece != 'R' && thePiece != 'r' && thePiece != 'B' && thePiece != 'b' && thePiece != 'N' && thePiece != 'n') || ((turn == COLOUR::WHITE && thePiece > 'Z') || (turn == COLOUR::BLACK && thePiece < 'a'))){
          cout << "Invalid Piece To Promote To: " << command << " (Try Q/R/B/N/q/r/b/n)" << endl;
        } else {
          break;
        }
      }
      
    }
    
    char toCellX = 'a' + toCell->getX() - 1;
    char toCellY = '0' + toCell->getY();
    string cell = "";
    cell += toCellX;
    cell += toCellY;

    chessBoard->addPiece(command, cell, true);
  } else {
    toCell->setPiece(movedPiece);
    movedPiece->setMoved(true);
  }
  
  fromCell->setPiece(nullptr);
  pastMoves.emplace_back(move);
}

void ChessGame::undoMove(){ // undo move without printing board
  auto lastMove = pastMoves.back();
  auto lastMoveFromCell = lastMove->getFromCell();
  auto lastMoveToCell = lastMove->getToCell();
  auto movedPiece = lastMoveToCell->getPiece();

  if(lastMove->isCastleMove()){
    int fromCellX = lastMoveFromCell->getX();
    int toCellX = lastMoveToCell->getX();
    int fromCellY = lastMoveFromCell->getY();

    int kingXChange = (fromCellX > toCellX ? -3 : 1); // queen side castle
    int rookXChange = (fromCellX > toCellX ? -2 : 0); // king side castle

    auto kingCell = chessBoard->getCell(fromCellX + kingXChange,fromCellY - 1);
    auto rookCell = chessBoard->getCell(fromCellX + rookXChange,fromCellY - 1);

    auto kingPiece = kingCell->getPiece();
    auto rookPiece = rookCell->getPiece();

    lastMoveFromCell->setPiece(kingPiece);
    lastMoveToCell->setPiece(rookPiece);
    kingCell->setPiece(nullptr);
    rookCell->setPiece(nullptr);

    kingPiece->setMoved(false);
    rookPiece->setMoved(false);
  } else if(lastMove->isEnPassantMove()){
    auto enPassantCell = chessBoard->getCell(lastMoveToCell->getX()-1, ((turn == COLOUR::WHITE) ? (lastMoveToCell->getY()) : (lastMoveToCell->getY()-2)));

    auto capturedPiece = lastMove->getCapturedPiece();

    enPassantCell->setPiece(capturedPiece);
    lastMoveToCell->setPiece(nullptr);
    lastMoveFromCell->setPiece(movedPiece);
    

  } else if(lastMove->isPawnPromotionMove()) {
    auto capturedPiece = lastMove->getCapturedPiece();

    string pawnString = (turn == COLOUR::WHITE ? "p" : "P");
    char toCellX = 'a' + lastMoveFromCell->getX() - 1;
    char toCellY = '0' + lastMoveFromCell->getY();
    string cell = "";
    cell += toCellX;
    cell += toCellY;
    chessBoard->addPiece(pawnString, cell, true);

    if(capturedPiece){
      lastMoveToCell->setPiece(capturedPiece);
    } else {
      lastMoveToCell->setPiece(nullptr);
    }
  } else {
    auto capturedPiece = lastMove->getCapturedPiece();
    
    // 2nd or 7th rank is first move
    if(movedPiece && movedPiece->getPieceType() == PIECETYPE::PAWN && (lastMoveFromCell->getY() == 7 || lastMoveFromCell->getY() == 2)){
      movedPiece->setMoved(false);
    }

    // Check if after undoing move, King has not moved
    if(movedPiece && movedPiece->getPieceType() == PIECETYPE::KING && (lastMoveFromCell->getX() == 5 && (lastMoveFromCell->getY() == 1 || lastMoveFromCell->getY() == 8))){
      int count = 0;
      for(auto n : pastMoves){ // King only travelled once
        auto fromCell = n->getFromCell();

        if(fromCell->getX() == 5 && ((turn == COLOUR::BLACK && fromCell->getY() == 1) || (turn == COLOUR::WHITE && fromCell->getY() == 8))){
          ++count;
        }
      }
      if(count <= 1){
        movedPiece->setMoved(false);
      }
    }

    // If pawn promotion undo promotion
    lastMoveFromCell->setPiece(movedPiece);
    if(capturedPiece){
      lastMoveToCell->setPiece(capturedPiece);
    } else {
      lastMoveToCell->setPiece(nullptr);
    }
  }

  pastMoves.pop_back();
}


void ChessGame::undoLastMove(){ // undo move and print the resulting board
  if(pastMoves.size() > 0){
    vector<shared_ptr<Cell>> cells;
    auto lastMove = pastMoves.back();
    getUpdatedCells(cells, lastMove);

    undoMove();
    chessBoard->printBoard(cells);
    setGameStatus(GAMESTATUS::PREPROCESSING);
    switchTurns();
    updateMoves();
    updateGameStatus();
  } else {
    cout << "At starting position" << endl;
  }
  
}

void ChessGame::printScore(){
  if(!players.empty()){
    cout << "White: " << players[0]->getScore() << endl;
    cout << "Black: " << players[1]->getScore() << endl;
  } else {
    cout << "White: " << 0 << endl;
    cout << "Black: " << 0 << endl;
  }
}

COLOUR ChessGame::getTurn(){
  return turn;
}
GAMESTATUS ChessGame::getGameStatus(){
  return gameStatus;
}

bool ChessGame::isCurrentPlayerCPU(){
  if(turn == COLOUR::WHITE && players[0]->isCompPlayer()){
    return true;
  } else if(turn == COLOUR::BLACK && players[1]->isCompPlayer()){
    return true;
  }
  return false;
}

void ChessGame::setTurn(COLOUR theColour){
  turn = theColour;
}

void ChessGame::setGameStatus(GAMESTATUS theGameStatus){
  gameStatus = theGameStatus;
}

void ChessGame::setBoard(shared_ptr<Board> theBoard){
    chessBoard = theBoard;
}
