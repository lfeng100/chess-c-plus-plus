#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "cell.h"
#include "graphics.h"
using namespace std;

Graphics::Graphics(shared_ptr<Board> b):
  window{600,600},
  boardstate{b}
{
  window.fillRectangle(0, 0, 600, 600, Xwindow::Blue);
  for (int i = 0; i < 8; ++i) { 
    for (int j = 0; j < 8; ++j) {
      if ((i + j) % 2 == 0) {
        window.fillRectangle((50 * i) + 50, 50 * j + 110, 50, 50, 0);
      } else {
          window.fillRectangle((50 * i) + 50, 50 * j + 110, 50, 50, 1);
      }
    }
  }
  boardstate->attach(this);
}

Graphics::~Graphics(){
  boardstate->detach(this);
}

void Graphics::notify(vector<shared_ptr<Cell>> cells){
  int rows = boardstate->getRows();
  // int cols = boardstate->getCols();
  char b;

  for(auto n : cells){
    int i = n->getX();
    int j = n->getY();
    b = boardstate->getState(i, j);
    if (b == 'E'){
      if ((i + j) % 2 != 0){
        window.fillRectangle((i * 50) + 50, ((rows - j - 1) * 50) + 110, 50, 50, Xwindow::White);
      } else {
        window.fillRectangle((i * 50) + 50, ((rows - j - 1) * 50) + 110, 50, 50, Xwindow::Black);  
      }
    } else if (isupper(b)){
      if ((i + j) % 2 != 0){
        window.fillRectangle((i * 50) + 50, ((rows - j - 1) * 50) + 110, 50, 50, Xwindow::White);
      } else {
        window.fillRectangle((i * 50) + 50, ((rows - j - 1) * 50) + 110, 50, 50, Xwindow::Black);
      }
      if (b == 'K'){
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
        window.fillRectangle(i * 50 + 65, (rows - j - 1) * 50 + 126, 10, 10, Xwindow::Red);
        window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 122, 10, 10, Xwindow::Red);
        window.fillRectangle(i * 50 + 85, (rows - j - 1) * 50 + 118, 10, 10, Xwindow::Red);
        window.fillRectangle(i * 50 + 65, (rows - j - 1) * 50 + 130, 10, 10, Xwindow::Red);
        window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 134, 10, 10, Xwindow::Red);
        window.fillRectangle(i * 50 + 85, (rows - j - 1) * 50 + 138, 10, 10, Xwindow::Red);
      } else if (b == 'Q'){
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
        window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Red);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 150, 45, 10, Xwindow::Red);
      } else if (b == 'R'){
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
        window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 20, Xwindow::Red);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Red);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 135, 35, 10, Xwindow::Red);
        window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 135, 10, 20, Xwindow::Red);
      } else if (b == 'N'){
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
        window.fillRectangle(i * 50 + 85, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
        window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 135, 10, 10, Xwindow::Red);
        window.fillRectangle(i * 50 + 65, (rows - j - 1) * 50 + 125, 10, 10, Xwindow::Red);
      } else if (b == 'B'){
        window.fillRectangle(i* 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
        window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 20, Xwindow::Red);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Red);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 133, 43, 10, Xwindow::Red);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 150, 43, 10, Xwindow::Red);
        window.fillRectangle(i * 50 + 88, (rows - j - 1) * 50 + 133, 10, 20, Xwindow::Red);
      } else if (b == 'P'){
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
        window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 20, Xwindow::Red);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Red);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 135, 35, 10, Xwindow::Red);
      }
    } else if (islower(b)){
      if ((i + j) % 2 != 0){
        window.fillRectangle((i * 50) + 50, ((rows - j - 1) * 50) + 110, 50, 50, Xwindow::White);
      } else {
        window.fillRectangle((i * 50) + 50, ((rows - j - 1) * 50) + 110, 50, 50, Xwindow::Black);
      }
      if (b == 'k'){
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
        window.fillRectangle(i * 50 + 65, (rows - j - 1) * 50 + 126, 10, 10, Xwindow::Green);
        window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 122, 10, 10, Xwindow::Green);
        window.fillRectangle(i * 50 + 85, (rows - j - 1) * 50 + 118, 10, 10, Xwindow::Green);
        window.fillRectangle(i * 50 + 65, (rows - j - 1) * 50 + 130, 10, 10, Xwindow::Green);
        window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 134, 10, 10, Xwindow::Green);
        window.fillRectangle(i * 50 + 85, (rows - j - 1) * 50 + 138, 10, 10, Xwindow::Green);
      } else if (b == 'q'){
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
        window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Green);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 150, 45, 10, Xwindow::Green);   
      } else if (b == 'r'){
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
        window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 20, Xwindow::Green);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Green);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 135, 35, 10, Xwindow::Green);
        window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 135, 10, 20, Xwindow::Green);
      } else if (b == 'n'){
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
        window.fillRectangle(i * 50 + 85, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
        window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 135, 10, 10, Xwindow::Green);
        window.fillRectangle(i * 50 + 65, (rows - j - 1) * 50 + 125, 10, 10, Xwindow::Green);
      } else if (b == 'b'){
        window.fillRectangle(i* 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
        window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 20, Xwindow::Green);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Green);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 133, 43, 10, Xwindow::Green);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 150, 43, 10, Xwindow::Green);
        window.fillRectangle(i * 50 + 88, (rows - j - 1) * 50 + 133, 10, 20, Xwindow::Green);
      } else if (b == 'p'){
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
        window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 20, Xwindow::Green);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Green);
        window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 135, 35, 10, Xwindow::Green);
      }
    }
  }

  // for (int i = 0; i < rows; i++){
  //   for (int j = 0; j < cols; j++){
  //     b = boardstate->getState(i, j);
  //     if (b == 'E'){
  //       if ((i + j) % 2 != 0){
  //         window.fillRectangle((i * 50) + 50, ((rows - j - 1) * 50) + 110, 50, 50, Xwindow::White);
  //       } else {
  //         window.fillRectangle((i * 50) + 50, ((rows - j - 1) * 50) + 110, 50, 50, Xwindow::Black);  
  //       }
  //     } else if (isupper(b)){
  //       if (b == 'K'){
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 65, (rows - j - 1) * 50 + 126, 10, 10, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 122, 10, 10, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 85, (rows - j - 1) * 50 + 118, 10, 10, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 65, (rows - j - 1) * 50 + 130, 10, 10, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 134, 10, 10, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 85, (rows - j - 1) * 50 + 138, 10, 10, Xwindow::Red);
  //       } else if (b == 'Q'){
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 150, 45, 10, Xwindow::Red);
  //       } else if (b == 'R'){
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 20, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 135, 35, 10, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 135, 10, 20, Xwindow::Red);
  //       } else if (b == 'N'){
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 85, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 135, 10, 10, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 65, (rows - j - 1) * 50 + 125, 10, 10, Xwindow::Red);
  //       } else if (b == 'B'){
  //         window.fillRectangle(i* 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 20, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 133, 43, 10, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 150, 43, 10, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 88, (rows - j - 1) * 50 + 133, 10, 20, Xwindow::Red);
  //       } else if (b == 'P'){
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 20, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Red);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 135, 35, 10, Xwindow::Red);
  //       }
  //     } else if (islower(b)){
  //       if (b == 'k'){
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 65, (rows - j - 1) * 50 + 126, 10, 10, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 122, 10, 10, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 85, (rows - j - 1) * 50 + 118, 10, 10, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 65, (rows - j - 1) * 50 + 130, 10, 10, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 134, 10, 10, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 85, (rows - j - 1) * 50 + 138, 10, 10, Xwindow::Green);
  //       } else if (b == 'q'){
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 150, 45, 10, Xwindow::Green);   
  //       } else if (b == 'r'){
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 20, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 135, 35, 10, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 135, 10, 20, Xwindow::Green);
  //       } else if (b == 'n'){
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 85, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 75, (rows - j - 1) * 50 + 135, 10, 10, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 65, (rows - j - 1) * 50 + 125, 10, 10, Xwindow::Green);
  //       } else if (b == 'b'){
  //         window.fillRectangle(i* 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 20, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 133, 43, 10, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 150, 43, 10, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 88, (rows - j - 1) * 50 + 133, 10, 20, Xwindow::Green);
  //       } else if (b == 'p'){
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 10, 40, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 80, (rows - j - 1) * 50 + 115, 10, 20, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 115, 25, 10, Xwindow::Green);
  //         window.fillRectangle(i * 50 + 55, (rows - j - 1) * 50 + 135, 35, 10, Xwindow::Green);
  //       }
  //     }
  //   }
  // }
}
