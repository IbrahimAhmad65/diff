#pragma once
#include "Group.h"
#include "Variable.h"
#include "Number.h"

inline std::shared_ptr<Group> substitute(std::shared_ptr<Group> g,std::shared_ptr<Variable> x, std::shared_ptr<Number> num) {
  if(auto n = std::dynamic_pointer_cast<Variable>(g)){
    if(n == x){
      return num;
    }
    return g;
  }
  if(auto n = std::dynamic_pointer_cast<Number>(g)){
    return g;
  }
  std::vector<std::shared_ptr<Group>> vec = g->get_elements();
  for(int i = 0 ; i < vec.size(); i++){
    if(auto num_t = std::dynamic_pointer_cast<Variable>(vec[i])){
      if(num_t == x){
        vec[i] = num;
      }
    } else {
      vec[i] = substitute(vec[i],x,num);
    }
  }

  return g->build(vec);
}
