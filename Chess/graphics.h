#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <vector>
#include <memory>
#include "observer.h"
#include "board.h"
#include "colour.h"
#include "window.h"

class Board;

class Graphics : public Observer{
  Xwindow window;
  std::shared_ptr<Board> boardstate;
public:
  Graphics(std::shared_ptr<Board> b);
  void notify(std::vector<std::shared_ptr<Cell>> cell) override;
  ~Graphics();
};

#endif
