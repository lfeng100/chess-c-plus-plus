#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "chessgame.h"
#include "board.h"
#include "cell.h"
#include "move.h"

#include "colour.h"
#include "gamestatus.h"

#include "text.h"
#include "graphics.h"
using namespace std;

int isValidPiece(char c){
  if(c == 'b' || c == 'k' || c == 'n' || c == 'p' || c == 'q' || c == 'r' || c == 'B' || c == 'K' || c == 'N' || c == 'P' || c == 'Q' || c == 'R') {
    return 1;
  }
  return 0;
}

int isValidCell(string cell){ // We always send in a length 2 string
  char letter = cell.at(0);
  char number = cell.at(1);
  if(letter >= 'a' && letter <= 'h') { // a-h are valid inputs (ASCII)
    if(number >= '1' && number <= '8'){ // 1-8 are valid inputs (ASCII)
      return 1;
    }
  }
  return 0;
}

int main() {
  const int GAME_ROWS = 8;
  const int GAME_COLS = 8;
  // store observers
  
  auto chessGame = make_shared<ChessGame>(); 
  auto theBoard = make_shared<Board>(GAME_ROWS, GAME_COLS);
  chessGame->setBoard(theBoard);
  auto textObserver = make_shared<Text>(GAME_ROWS, GAME_COLS, theBoard);
  COLOUR goesFirst = COLOUR::WHITE;
  auto graphicsObserver = make_shared<Graphics>(theBoard);

  bool inGame = false;
  bool customBoard = false;

  srand(time(0)); // set random seed for random moves
  
  string command;
  
  cout << "ENTER MENU COMMAND (game, setup, quit): " << endl;
  while (cin >> command) {
    if (command == "game" ) { 
      if(!inGame){
        cout << "PREPARING game" << endl;

        string p1,p2;
        cin >> p1 >> p2;

        bool valid_input = true;

        int p1_length = p1.length();
        int p2_length = p2.length();

        // check if valid input (human or computer[1-4]) which is 5 or 9 letters
        if(p1_length != 5 && p1_length != 9){
          cout << "INVALID COMMAND: " << p1 << endl;
          valid_input = false;
        }

        if(p2_length != 5 && p2_length != 9){
          cout << "INVALID COMMAND: " << p2 << endl;
          valid_input = false;
        }

        int p1_cpu_level = 0;
        int p2_cpu_level = 0;

        if(valid_input){
          // extract the computer level if it exists for p1
          if(p1_length == 9){
            char tmp = p1.at(p1_length-1); // get last char
            // check if valid cpu level [1-3] with ASCII
            if(tmp >= '1' && tmp <= '3'){
              p1_cpu_level = tmp - '0';
              p1.pop_back(); // remove last char
            } else {
              cout << "INVALID COMMAND: " << p1 << "(Choose level 1-3)" << endl;
              valid_input = false;
            }
          }

          // extract the computer level if it exists for p2
          if(p2_length == 9){
            char tmp = p2.at(p2_length-1); // get last char
            // check if valid cpu level [1-4] with ASCII
            if(tmp >= '1' && tmp <= '4'){
              p2_cpu_level = tmp - '0';
              p2.pop_back(); // remove last char
            } else {
              cout << "INVALID COMMAND: " << p2 << "(Choose level 1-3)" << endl;
              valid_input = false;
            }
          }
        }

        // check if entered valid input and produce outputs about the game players if it's valid.
        if(valid_input){
          if(p1 == "human"){
            if (p2 == "human"){
              cout << p1 << " vs " << p2 << endl;
            } else if (p2 == "computer"){
              cout << p1 << " vs " << p2 << " level:" << p2_cpu_level << endl;
            } else {
              valid_input = false;
              cout << "INVALID COMMAND: " << p2 << endl;
            }
          } else if (p1 == "computer"){
            if (p2 == "human"){
              cout << p1 << " level:" << p1_cpu_level << " vs " << p2 << endl;
            } else if (p2 == "computer"){
              cout << p1 << " level:" << p1_cpu_level << " vs " << p2 << " level:" << p2_cpu_level << endl;
            } else {
              valid_input = false;
              cout << "INVALID COMMAND: " << p2 << endl;
            }
          } else {
            valid_input = false;
            cout << "INVALID COMMAND: " << p1 << endl;
          }
        }

        if(valid_input){
          // start game here
          if(!customBoard){
            theBoard->initStandard();
          }
          cout << "GAME START: " << endl;
          chessGame->init(p1_cpu_level, p2_cpu_level);

          string toMove = (chessGame->getTurn() == COLOUR::WHITE ? "WHITE" : "BLACK");
          cout << toMove <<" TO MOVE (move/resign): " << endl;
          inGame = true;
        }
      } else {
        cout << "Already in a game" << endl;
      }
    }
    else if (command == "resign") { 
      if(inGame){
        chessGame->endGame();
        cout << "Play Again (Y/N)?" << endl;
        while (cin >> command) {
          if(command == "Y" || command == "y"){
            chessGame->reset();
            chessGame->setTurn(goesFirst);

            string toMove = (chessGame->getTurn() == COLOUR::WHITE ? "WHITE" : "BLACK");
            cout << toMove <<" TO MOVE (move/resign): " << endl;
            break;
          } else if (command == "N" || command == "n"){
            goesFirst = COLOUR::WHITE;
            theBoard->clearBoard();
            customBoard = false;
            inGame = false;
            break;
          }
        }
      } else {
        cout << "Not currently in a game" << endl;
      }
    }
    else if (command == "move") { 
      if(inGame){
        string fromCellString, toCellString;

        bool isCpu = chessGame->isCurrentPlayerCPU();

        if(isCpu){
          chessGame->makeCPUMove();
        } else {
          cin >> fromCellString >> toCellString;
          if(fromCellString.length() == 2 && isValidCell(fromCellString)){
            if(toCellString.length() == 2 && isValidCell(toCellString)){
              chessGame->playerMove(fromCellString, toCellString); // TRY TO MAKE MOVE
            } else {
              cout << "INVALID COMMAND: " << toCellString << endl;
            }
          } else {
            cout << "INVALID COMMAND: " << fromCellString << endl;
          }
        }
        if(chessGame->getGameStatus() == GAMESTATUS::BLACK_IS_MATED || chessGame->getGameStatus() == GAMESTATUS::WHITE_IS_MATED || chessGame->getGameStatus() == GAMESTATUS::STALEMATE){
          chessGame->endGame();
          cout << "Play Again (Y/N)?" << endl;
          while (cin >> command) {
            if(command == "Y"){
              chessGame->reset();
              chessGame->setTurn(goesFirst);

              string toMove = (chessGame->getTurn() == COLOUR::WHITE ? "WHITE" : "BLACK");
              cout << toMove <<" TO MOVE (move/resign): " << endl;
              break;
            } else if (command == "N"){
              goesFirst = COLOUR::WHITE;
              theBoard->clearBoard();
              customBoard = false;
              inGame = false;
              break;
            }
          }
        } else {
          string toMove = (chessGame->getTurn() == COLOUR::WHITE ? "WHITE" : "BLACK");
          if(chessGame->getGameStatus() == GAMESTATUS::IN_CHECK){
            cout << toMove <<" IS IN CHECK!" << endl;
          }
          cout << toMove <<" TO MOVE (move/resign): " << endl;
        }
      } else {
        cout << "Not currently in a game" << endl;
      }
    }
    else if (command == "undo") { // extra feature
      if(inGame){
        chessGame->undoLastMove();  
        string toMove = (chessGame->getTurn() == COLOUR::WHITE ? "WHITE" : "BLACK");
          cout << toMove << " TO MOVE (move/resign): " << endl;   
      } else {
        cout << "Not currently in a game" << endl;
      }
    }
    else if (command == "setup") {
      if(!inGame){
        cout << "-- IN SETUP --" << endl;
        string setupCmd;
        cout << "ENTER SETUP COMMAND (+,-,=,done,cancel): " << endl;
        while (cin >> setupCmd) {
          if (setupCmd == "+"){
            string piece, cell;
            cin >> piece >> cell;

            if(piece.length() == 1 && isValidPiece(piece.at(0))){
              if(cell.length() == 2 && isValidCell(cell)){
                cout << "Placing: " << piece << endl;
                cout << "To cell: " << cell << endl;
                theBoard->addPiece(piece, cell);
              } else {
                cout << "INVALID SETUP COMMAND: " << cell << endl;
              }
            } else {
              cout << "INVALID SETUP COMMAND: " << piece << endl;
            }
            // make changes to board here
          }
          else if (setupCmd == "-"){
            string cell;
            cin >> cell;

            if(cell.length() == 2 && isValidCell(cell)){
              theBoard->removePiece(cell);
              cout << "REMOVED PIECE ON CELL: " << cell << endl;
            } else {
              cout << "INVALID SETUP COMMAND: " << cell << endl;
            }
          } else if (setupCmd == "="){
            string colour;
            cin >> colour;
            if(colour == "black"){
              goesFirst = COLOUR::BLACK;
              chessGame->setTurn(COLOUR::BLACK);
              cout << "BLACK GOES FIRST" << endl;
            } else if (colour == "white") {
              goesFirst = COLOUR::WHITE;
              chessGame->setTurn(COLOUR::WHITE);
              cout << "WHITE GOES FIRST" << endl;
            } else {
              cout << "INVALID SETUP COMMAND: " << colour << endl;
            }
          } 
          else if (setupCmd == "done"){
            if(chessGame->checkValidBoard()){
              customBoard = true;
              cout << "exiting setup" << endl;
              break;
            } else {
              cout << "INVALID BOARD STATE" << endl;
            } 
          } 
          else if (setupCmd == "cancel"){
            theBoard->clearBoard();
	    break;
          }
          else {
            cout << "INVALID SETUP COMMAND: " << setupCmd << endl;
          }
          cout << "ENTER SETUP COMMAND (+,-,=,done,cancel): " << endl;
        }
      } else {
        cout << "Cannot enter setup in game" << endl;
      }
    }
    else if (command == "q" || command == "quit") {
      break;
    }
    else {
      cout << "INVALID COMMAND: " << command << endl;
    }
    if(!inGame){
      cout << "ENTER MENU COMMAND (game, setup, quit): " << endl;
    } 
  }
  cout << "Final Score: " << endl;
  chessGame->printScore();
}
