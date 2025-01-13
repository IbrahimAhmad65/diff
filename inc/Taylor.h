#pragma once
#include "Group.h"
#include "Multiplication.h"
#include "Division.h"
#include "Subtraction.h"
#include "Substitute.h"
#include "Addition.h"
#include "Log.h"
#include "Ln.h"
#include "Power.h"
#include "Variable.h"
#include "Number.h"
#include "Derivative.h"
#include <initializer_list>

inline int factorial(int n){
  return n == 0 ? 1 :n * factorial(n -1); 
}

class Taylor{
public:
  static std::shared_ptr<Group> taylor(std::shared_ptr<Group> g, int depth, std::vector<std::shared_ptr<Variable>> a_args);
  static std::shared_ptr<Group> taylor(std::shared_ptr<Group> g, int depth, std::initializer_list<std::shared_ptr<Variable>> a_args);
};
