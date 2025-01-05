#include "Variable.h"

bool operator>(std::shared_ptr<Variable> g1, std::shared_ptr<Variable> g2) {
  return g1->getRaw() > g2->getRaw();
}

bool operator<(std::shared_ptr<Variable> g1, std::shared_ptr<Variable> g2) {
  return g1->getRaw() < g2->getRaw();
}

bool operator==(std::shared_ptr<Variable> g1, std::shared_ptr<Variable> g2) {
  return g1->getRaw() == g2->getRaw();
}
