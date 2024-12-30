#pragma once
#include <Group.h>
#include <iostream>
#include <memory>
#define CHAR_TYPE char
// stopping. Rename group to function, and have functions operate on functions,
// numbers, and variables indiscriminately is this needed or can we do template
// stuff?
// template<class E> concept Numeric = std::is_arithmetic_v<E>;
// template<typename T> requires Numeric<T>
class Variable : public Group {
public:
  Variable(CHAR_TYPE n) { local = n; }
  Variable(const Variable *n) { local = n->local; }
  std::shared_ptr<Group> clone() override{
    return std::make_shared<Variable>(*this);
  }
  std::shared_ptr<Group>
  apply(std::vector<std::shared_ptr<Group>> &elements) const override {
    return std::make_shared<Variable>(this);
  }
  CHAR_TYPE getRaw() { return local; }

  std::ostream &print(std::ostream &stream) const override {
    stream << local;
    return stream;
  }

private:
  CHAR_TYPE local;
};
