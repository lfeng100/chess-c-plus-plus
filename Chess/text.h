#ifndef _TEXT_H_
#define _TEXT_H_

#include "observer.h"
#include <vector>
#include <memory>

class Board;
class Cell;

class Text : public Observer {
  int r;
  int c;
  std::shared_ptr<Board> boardState;
public:
  Text(int row, int col, std::shared_ptr<Board> theBoardState);
  ~Text();

  void notify(std::vector<std::shared_ptr<Cell>> cells) override;
};

#endif