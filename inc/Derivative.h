#pragma once
#include "Group.h"
#include "Multiplication.h"
#include "Addition.h"
#include "Log.h"
#include "Power.h"
#include "Variable.h"
#include "Number.h"

class Derivative{
public:
  static std::shared_ptr<Group> diff(std::shared_ptr<Group> g, std::shared_ptr<Variable> x);
};
