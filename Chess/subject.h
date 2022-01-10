#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include <vector>
#include <memory>

class Observer;
class Cell;

class Subject{
  std::vector<Observer*> observers;
 public:
  void attach(Observer *o);
  void detach(Observer *o);
  void notifyObservers(std::vector<std::shared_ptr<Cell>> cells);
  virtual char getState(int row, int col) const = 0;
  virtual ~Subject() = default;
};

#endif