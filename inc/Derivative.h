#pragma once
#include "Group.h"
#include "Multiplication.h"
#include "Division.h"
#include "Subtraction.h"
#include "Addition.h"
#include "Log.h"
#include "Ln.h"
#include "Power.h"
#include "Variable.h"
#include "Number.h"

class Derivative{
public:
  static std::shared_ptr<Group> diff(std::shared_ptr<Group> g, std::shared_ptr<Variable> x);
};
