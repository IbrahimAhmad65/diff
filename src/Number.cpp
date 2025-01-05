#include "Power.h"

bool operator>(std::shared_ptr<Number> g1, std::shared_ptr<Number> g2) {
  return g1->getRaw() > g2->getRaw();
}

bool operator<(std::shared_ptr<Number> g1, std::shared_ptr<Number> g2) {
  return g1->getRaw() < g2->getRaw();
}

bool operator==(std::shared_ptr<Number> g1, std::shared_ptr<Number> g2) {
  return g1->getRaw() == g2->getRaw();
}
