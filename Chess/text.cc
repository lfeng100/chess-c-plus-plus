#include "text.h"
#include "board.h"
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// Text::Text(int row, int col):
//   r{row},
//   c{col}
// {
//   cout << "in" << endl;
//   boardState->attach(this);
//   cout << "out" << endl;
// }

Text::Text(int row, int col, shared_ptr<Board> boardState):
  r{row},
  c{col},
  boardState{boardState}
{
  boardState->attach(this);
}

Text::~Text() {
  boardState->detach(this);
}

// Cell (a 1) -> 1 1; Cell (a 2) -> 1 2; Cell (b 5) -> 2 5
void Text::notify(vector<shared_ptr<Cell>> cells){
  for (int i = 0; i < r; ++i) {
    cout << r-i << " ";
    for (int j = 0; j < c; ++j) {
      char theChar = boardState->getState(j,c-i-1);
      if(theChar == 'E'){
        if((i+j)%2 == 0){
          cout << " ";
        } else {
          cout << "_";
        }
      } else {
        cout << theChar;
      }
    }
    cout << endl;
  }
  cout << "\n  abcdefgh" << endl;
}

// void Text::setBoardState(shared_ptr<Board> theboardState){
//   boardState = theboardState;
// }