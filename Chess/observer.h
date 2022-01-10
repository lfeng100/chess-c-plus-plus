#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include <vector>
#include <memory>
class Subject;
class Cell;

class Observer {
public:
  virtual void notify(std::vector<std::shared_ptr<Cell>> cells) = 0;
  virtual ~Observer() = default;
};

#endif