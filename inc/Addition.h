#pragma once
#include "Group.h"
#include "Number.h"
#include "Negation.h"
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>
#include <unordered_map>
class Addition : public Group {
public:
  Addition(const std::vector<std::shared_ptr<Group>> &elems);
  Addition(const Addition *a);
  std::shared_ptr<Group> clone() const override{
    return std::make_shared<Addition>(*this);
  }

  std::shared_ptr<Group> build(std::vector<std::shared_ptr<Group>> elems) const override{
    return std::make_shared<Addition>(Addition(elems));
  }
  std::shared_ptr<Group> apply(std::vector<std::shared_ptr<Group>> &elements) const override;
  std::shared_ptr<Group> distribute(std::vector<std::shared_ptr<Group>> &elements) const override;
  std::shared_ptr<Group> distribute() const override;
  std::ostream &print(std::ostream &stream) const override;
  std::ostream &latex(std::ostream &stream) const override;
  std::shared_ptr<Group> sanitize_distribute(const std::shared_ptr<Group> sop) const;
};
