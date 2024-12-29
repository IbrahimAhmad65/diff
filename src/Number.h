#pragma once
#include <Group.h>
#define FLOAT_TYPE double
// stopping. Rename group to function, and have functions operate on functions, numbers, and variables indiscriminately
// is this needed or can we do template stuff?
//template<class E> concept Numeric = std::is_arithmetic_v<E>;
//template<typename T> requires Numeric<T>
class Number : public Group{
public: 
  Number(FLOAT_TYPE n){
    local = n;
  }
  Group apply(std::vector<Group>& elements){
    return *this;
  }
  FLOAT_TYPE getRaw(){
    return local;
  }
private:
  FLOAT_TYPE local; 
};
