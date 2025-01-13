#include "Taylor.h"

std::shared_ptr<Group> Taylor::taylor(std::shared_ptr<Group> g, int depth, std::vector<std::shared_ptr<Variable>> vars) {
  auto num = Number(0);
  auto c = num.clone_t();
  std::shared_ptr<Group> sum = std::make_shared<Number>(0);
  std::vector<std::shared_ptr<Group>> deriv = std::vector<std::shared_ptr<Group>>();
  deriv.reserve(vars.size());

  for (const auto &a : vars) {
    sum = sum + substitute(g, a, c);
    deriv.push_back(g);
  }

  for (int i = 1; i <= depth; ++i) {
    for (int j = 0; j < deriv.size(); ++j) {
      deriv[j] = Derivative::diff(deriv[j], vars[j]);
      auto sub = substitute(deriv[j], vars[j], c);
      auto pow = Power(vars[j], i);
      sum = sum + sub / factorial(i) * pow;
    }
  }
  return sum;
}

std::shared_ptr<Group> Taylor::taylor(std::shared_ptr<Group> g, int depth, std::initializer_list<std::shared_ptr<Variable>> a_args) {
  auto num = Number(0);
  auto c = num.clone_t();
  std::shared_ptr<Group> sum = std::make_shared<Number>(0);
  std::vector<std::shared_ptr<Group>> deriv = std::vector<std::shared_ptr<Group>>();
  std::vector<std::shared_ptr<Variable>> vars = std::vector<std::shared_ptr<Variable>>();
  deriv.reserve(a_args.size());

  for (const auto &a : a_args) {
    sum = sum + substitute(g, a, c);
    deriv.push_back(g);
    vars.push_back(a);
  }

  for (int i = 1; i <= depth; ++i) {
    for (int j = 0; j < deriv.size(); ++j) {
      deriv[j] = Derivative::diff(deriv[j], vars[j]);
      auto sub = substitute(deriv[j], vars[j], c);
      auto pow = Power(vars[j], i);
      sum = sum + sub / factorial(i) * pow;
    }
  }
  return sum;
}

/*
std::shared_ptr<Group> Taylor::taylor(std::shared_ptr<Group> g, std::shared_ptr<Variable> x, int depth) {
  auto num = Number(0);
  auto c = num.clone_t();
  std::shared_ptr<Group> sum = substitute(g, x, c);

  std::shared_ptr<Group> old_ptr = g;
  for (int i = 1; i <= depth; ++i) {
    old_ptr = Derivative::diff(old_ptr, x);
    auto sub = substitute(old_ptr, x, c);
    auto pow = Power(x, i);
    sum = sum + sub / factorial(i) * pow;
  }
  return sum;
}
*/
