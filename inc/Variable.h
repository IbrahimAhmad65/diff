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
class Variable: public Base<Variable> {
public:
  Variable(CHAR_TYPE n) { local = n; }
  Variable(const Variable *n) { local = n->local; }
  Variable(std::vector<std::shared_ptr<Group>> elems) {local = -1;}
  /*std::shared_ptr<Group> clone() const override{
    return std::make_shared<Variable>(*this);
  }*/


  bool linear() const override{
    return false;
  } 
  
  std::shared_ptr<Group> apply(std::vector<std::shared_ptr<Group>> &elements) const override {
    return std::make_shared<Variable>(this);
  }
  CHAR_TYPE getRaw() { return local; }

  std::shared_ptr<Group> distribute() const override{
    return std::make_shared<Variable>(*this);
  }
  std::shared_ptr<Group> distribute(std::vector<std::shared_ptr<Group>> &elements) const override{
    return std::make_shared<Variable>(*this);
  }

  std::vector<std::shared_ptr<Group>> get_elements() const override{
    return std::vector<std::shared_ptr<Group>>{std::make_shared<Variable>(*this)};
  }
  std::ostream &print(std::ostream &stream) const override {
    stream << local;
    return stream;
  }


private:
  CHAR_TYPE local;
};
bool operator >(std::shared_ptr<Variable> g1,std::shared_ptr<Variable> g2);

bool operator <(std::shared_ptr<Variable> g1,std::shared_ptr<Variable> g2);

bool operator ==(std::shared_ptr<Variable> g1,std::shared_ptr<Variable> g2);
