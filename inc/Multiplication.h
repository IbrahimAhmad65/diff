#pragma once
#include <Group.h>
#include <Number.h>
#include <Addition.h>
#include <Negation.h>
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>
class Multiplication : public Group {
public:
  Multiplication(const std::vector<std::shared_ptr<Group>> &elems);
  Multiplication(const Multiplication *a);
  Multiplication(std::shared_ptr<Group>& g);

  std::shared_ptr<Group> clone() const override{
    return std::make_shared<Multiplication>(*this);
  }
  std::shared_ptr<Group> apply(std::vector<std::shared_ptr<Group>> &elements) const override;
  std::shared_ptr<Group> distribute(std::vector<std::shared_ptr<Group>> &elements) const override;
  std::ostream &print(std::ostream &stream) const override;
  std::ostream &latex(std::ostream &stream) const override;
};
