#pragma once
#include <Group.h>
#include <iostream>
#include <memory>
// stopping. Rename group to function, and have functions operate on functions,
// numbers, and variables indiscriminately is this needed or can we do template
// stuff?
// template<class E> concept Numeric = std::is_arithmetic_v<E>;
// template<typename T> requires Numeric<T>
class Power : public Group {
public:
  Power(std::vector<std::shared_ptr<Group>> elems)  : Group(elems){}
  Power(Group& g) : Group(group->get_elements()){}
  Power(const Power *n) : Power(*n) {}
  std::shared_ptr<Group> clone() override{
    return std::make_shared<Power>(*this);
  }
  std::shared_ptr<Group>
  apply(std::vector<std::shared_ptr<Group>> &elements) const override {
    return std::make_shared<Power>(this);
  }
  std::shared_ptr<Group> getRaw() { return local; }

  std::ostream &print(std::ostream &stream) const override {
    stream <<"-"<< *local;
    return stream;
  }

  std::ostream &latex(std::ostream &stream) const override {
    print(stream);
    return stream;
  }

private:
  std::shared_ptr<Group> local;
};
