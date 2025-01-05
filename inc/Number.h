#pragma once
#include <Group.h>
#include <iostream>
#include <memory>
#define FLOAT_TYPE double
// stopping. Rename group to function, and have functions operate on functions,
// numbers, and variables indiscriminately is this needed or can we do template
// stuff?
// template<class E> concept Numeric = std::is_arithmetic_v<E>;
// template<typename T> requires Numeric<T>
class Number : public Base<Number> {
public:
  Number(float n) { local = n; }
  Number(double n) { local = n; }
  Number(short n) { local = n; }
  Number(long n) { local = n; }
  Number(int n) { local = n; }
  Number(const Number *n) { local = n->local; }
  Number(std::vector<std::shared_ptr<Group>> &elements){ local =-1;}

  bool linear() const override{
    return true;
  } 
  
  std::shared_ptr<Group> apply(std::vector<std::shared_ptr<Group>> &elements) const override {
    return std::make_shared<Number>(*this);
  }

  std::shared_ptr<Group> distribute() const override {
    return std::make_shared<Number>(*this);
  }

  std::shared_ptr<Group> distribute(std::vector<std::shared_ptr<Group>> &elements) const override {
    return std::make_shared<Number>(*this);
  }
  FLOAT_TYPE getRaw() { return local; }

  std::ostream &print(std::ostream &stream) const override {
    stream << local;
    return stream;
  }

  std::vector<std::shared_ptr<Group>> get_elements() const override{
    return std::vector<std::shared_ptr<Group>>{std::make_shared<Number>(this)};
  }

  std::ostream &latex(std::ostream &stream) const override {
    print(stream);
    return stream;
  }

private:
  FLOAT_TYPE local;
};

bool operator >(std::shared_ptr<Number> g1,std::shared_ptr<Number> g2);

bool operator <(std::shared_ptr<Number> g1,std::shared_ptr<Number> g2);

bool operator ==(std::shared_ptr<Number> g1,std::shared_ptr<Number> g2);
