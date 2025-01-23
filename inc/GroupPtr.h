#include "Group.h"
#include "Number.h"
#include "Negation.h"

struct GroupPtr{
  std::shared_ptr<Group> ptr;
  GroupPtr(){}
  GroupPtr(const GroupPtr& g){
    ptr = g.ptr; 
  }
  GroupPtr(std::shared_ptr<Group> g){
    ptr = g; 
  };
  template<typename N> requires std::is_arithmetic_v<N>
  GroupPtr(N n){
    ptr = std::make_shared<Number>(n);
  }

  GroupPtr(Group& n){
    ptr = n.clone(); 
  }
  friend std::ostream &operator<<(std::ostream &stream, const GroupPtr &g) {
    return g.ptr->print(stream);
  }
  GroupPtr operator/(const GroupPtr g) const {
    return GroupPtr(ptr / g.ptr);
  }

  GroupPtr operator+(const GroupPtr g) const {
    return GroupPtr(ptr + g.ptr);
  }

  GroupPtr operator*(const GroupPtr g) const {
    return GroupPtr(ptr * g.ptr);
  }

  GroupPtr operator-(const GroupPtr g) const {
    return GroupPtr(ptr - g.ptr);
  }

  GroupPtr operator-() const {
    Negation n(ptr);
    return GroupPtr(n);
  }

};


namespace Eigen {
  typedef GroupPtr Real;
  typedef GroupPtr NonInteger;
  typedef GroupPtr Nested;
  template<> struct NumTraits<GroupPtr> : GenericNumTraits<GroupPtr>{
    enum {
      IsComplex = 0,
      IsInteger = 0,
      IsSigned = 1,
      RequireInitialization = 0,
      ReadCost = 1,
      AddCost = 3,
      MulCost = 3
    };
  };
  namespace internal{
  template<> struct default_digits_impl<GroupPtr,false,false>{
    static int run(){
      return 12;
    }
  };
  }
}

