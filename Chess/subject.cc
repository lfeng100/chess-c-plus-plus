#include "subject.h"
#include "observer.h"
#include <vector>
#include <memory>
#include "cell.h"
using namespace std;

void Subject::attach(Observer *o) { observers.emplace_back(o); }

void Subject::detach(Observer *o) {
  for (auto it = observers.begin(); it != observers.end(); ) {
    if (*it == o) it = observers.erase(it);
    else ++it;
  }
}

void Subject::notifyObservers(vector<shared_ptr<Cell>> cells) {
  for (auto &ob : observers) ob->notify(cells);
}
