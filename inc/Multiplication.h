#pragma once
#include <Group.h>
#include <Number.h>
#include <Negation.h>
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>
class Multiplication : public Group {
public:
  Multiplication(const std::vector<std::shared_ptr<Group>> &elems);
  Multiplication(const Multiplication *a);

  std::shared_ptr<Group> clone() override{
    return std::make_shared<Multiplication>(*this);
  }
  std::shared_ptr<Group>
  apply(std::vector<std::shared_ptr<Group>> &elements) const override;
  std::ostream &print(std::ostream &stream) const override;
  std::ostream &latex(std::ostream &stream) const override;
};
