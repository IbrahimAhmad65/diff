#include "Group.h"
#include "Number.h"
#include "Variable.h"
#include "Log.h"
#include "Ceil.h"
#include "Addition.h"
#include "Multiplication.h"
#include "Subtraction.h"

inline const std::shared_ptr<Group>& conj(const std::shared_ptr<Group>& x)  { return x; }
inline const std::shared_ptr<Group>& real(const std::shared_ptr<Group>& x)  { return x; }
inline const std::shared_ptr<Group>& imag(const std::shared_ptr<Group>& x)  { 
  auto c = Number(0);
  return c.clone(); 
}


inline const std::shared_ptr<Group>& log2(const std::shared_ptr<Group>& x)  { 
  auto c = Log(2,x);
  return c.clone(); 
}


inline const std::shared_ptr<Group>& ceil(const std::shared_ptr<Group>& x)  { 
  auto c = Ceil(x);
  return c.clone(); 
}


