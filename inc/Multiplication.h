#pragma once
#include <Group.h>
#include <Number.h>
#include <Variable.h>
#include <Power.h>
#include <Addition.h>
#include <Negation.h>
#include <iostream>
#include <algorithm>
#include <memory>
#include <type_traits>
#include <vector>
#include <unordered_map>
class Multiplication : public Group {
public:
  Multiplication(const std::vector<std::shared_ptr<Group>> &elems);
  Multiplication(const Multiplication *a);
  Multiplication(std::shared_ptr<Group>& g);

  std::shared_ptr<Group> clone() const override{
    return std::make_shared<Multiplication>(*this);
  }

  std::shared_ptr<Group> build(std::vector<std::shared_ptr<Group>> elems) const override{
    return std::make_shared<Multiplication>(Multiplication(elems));
  }
  std::shared_ptr<Group> apply(std::vector<std::shared_ptr<Group>> &elements) const override;

  std::shared_ptr<Group> distribute() const override;
  std::shared_ptr<Group> distribute(std::vector<std::shared_ptr<Group>> &elements) const override;
  std::ostream &print(std::ostream &stream) const override;
  std::ostream &latex(std::ostream &stream) const override;

protected:
  std::shared_ptr<Group> sanitize_distribute(const std::shared_ptr<Group> sop) const;
};
