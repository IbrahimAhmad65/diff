#pragma once
#include "Group.h"
#include "Number.h"
#include "Negation.h"
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>
class Addition : public Group {
public:
  Addition(const std::vector<std::shared_ptr<Group>> &elems);
  Addition(const Addition *a);

  std::shared_ptr<Group> apply(std::vector<std::shared_ptr<Group>> &elements) const override;
  std::ostream &print(std::ostream &stream) const override;
  std::ostream &latex(std::ostream &stream) const override;
};
