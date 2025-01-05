#include "Derivative.h"

std::shared_ptr<Group> Derivative::diff(std::shared_ptr<Group> g, std::shared_ptr<Variable> x) {
  if (auto num = std::dynamic_pointer_cast<Variable>(g)) {
    if (num == x) {
      return std::make_shared<Number>(Number(1));
    }
    return std::make_shared<Number>(Number(0));
  }
  if (auto num = std::dynamic_pointer_cast<Number>(g)) {
    return std::make_shared<Number>(Number(0));
  }
  if (auto num = std::dynamic_pointer_cast<Addition>(g)) {
    std::vector<std::shared_ptr<Group>> vec = std::vector<std::shared_ptr<Group>>();
    for (const auto &elem : g->get_elements()) {
      vec.push_back(diff(elem, x));
    }
    return std::make_shared<Addition>(Addition(vec));
  }
  if (auto num = std::dynamic_pointer_cast<Multiplication>(g)) {
    std::shared_ptr<Group> answer = g->get_elements()[0];
    for (int i = 1; i < g->get_elements().size(); ++i) {
      answer = answer * diff(g->get_elements()[i], x) + diff(answer, x) * g->get_elements()[i];
    }
    return answer->applyDeep();
  }
  if (auto num = std::dynamic_pointer_cast<Log>(g)) {
    auto f_x = g->get_elements()[0];
    auto g_x = g->get_elements()[1];
    auto log_x = Log(2.718, f_x);
    auto log_g = Log(2.718, g_x);
    std::cout << log_x << std::endl;
    auto pow = Power(log_x, 2);
    return ((log_x * diff(g_x, x) / g_x) + -(diff(f_x, x) * log_g / f_x)) / pow;
  }
  if (auto num = std::dynamic_pointer_cast<Power>(g)) {
    auto g_x = g->get_elements()[0];
    auto f_x = g->get_elements()[1];
    auto f_xp = diff(f_x, x);
    auto g_xp = diff(g_x, x);

    auto one = Power(g_x, f_x + -1);
    auto l = Log(2.718, g_x);
    auto twoone = g_x * f_xp * l;
    auto twotwo = f_x * g_xp;
    auto two = twoone + twotwo;
    return one * two;
    /*
    auto base = g->get_elements()[0];
    if (auto base_var = std::dynamic_pointer_cast<Variable>(base)) {
      if (base_var == x) {
        auto exp = g->get_elements()[1];
        if (auto exp_var = std::dynamic_pointer_cast<Variable>(exp)) {
          if (exp_var == x) {
            std::cout << "Unfinished derivative impl" << std::endl;
            return nullptr;
          }
          auto pow = Power(x, exp_var + -1);
          return std::make_shared<Multiplication>(exp_var * pow);
          // need ln to finish impl sadge
        } else if (auto exp_var = std::dynamic_pointer_cast<Number>(exp)) {
          auto pow = Power(x, exp_var + -1);
          return std::make_shared<Multiplication>(exp_var * pow);
        }
      }
      std::cout << "Unfinished derivative impl" << std::endl;
      return nullptr;
    }
    std::cout << "Unfinished derivative impl" << std::endl;
    return nullptr;
    */
  }
  std::cout << "Unfinished derivative impl" << std::endl;
  return nullptr;
}
