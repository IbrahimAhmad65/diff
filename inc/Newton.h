#include "Derivative.h"
#include "Substitute.h"

class Newton{
public:
  static std::shared_ptr<Number> newton(std::shared_ptr<Group> expr, std::shared_ptr<Variable> var, std::shared_ptr<Number> guess){
    std::shared_ptr<Number> x = guess;
    auto diff = Derivative::diff(expr,var);
   std::cout << *diff << std::endl;  
    for(int i = 0; i < 100; i++){
      auto c = substitute(diff,var,x); 
      auto k = substitute(expr,var,x); 
      auto n = x - k / c;
      auto g = n->applyDeep();
      x = std::dynamic_pointer_cast<Number>(n->applyDeep());
    }
    return (x);
  }
};
