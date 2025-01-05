#pragma once
#include <cstdarg>
#include <memory>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cxxabi.h>

class Addition;
class Multiplication;

class Group{
public:
  Group();
  Group(const std::vector<std::shared_ptr<Group>> &elems);
  Group(const std::shared_ptr<Group> &g);
  Group(const Group *g);

  virtual std::shared_ptr<Group> distributeDeep() const;
  virtual std::shared_ptr<Group> apply(std::vector<std::shared_ptr<Group>> &elements) const = 0;
  virtual std::shared_ptr<Group> distribute(std::vector<std::shared_ptr<Group>> &elements) const = 0;
  virtual std::shared_ptr<Group> distribute() const = 0;
  virtual std::shared_ptr<Group> formatDeep() const;
  virtual std::vector<std::shared_ptr<Group>> get_elements() const;

  virtual std::ostream &print(std::ostream &stream) const ;
  virtual std::ostream &latex(std::ostream &stream) const;

  friend std::ostream &operator<<(std::ostream &stream, const Group &g) {
    return g.print(stream);
  } 
  
  virtual std::shared_ptr<Group> build(std::vector<std::shared_ptr<Group>> elems) const = 0;
  std::ostream &build_latex(std::ostream &stream);
  std::shared_ptr<Group> applyDeep() const;
  virtual bool linear() const  = 0;

  virtual std::size_t get_name() const = 0;

  virtual std::shared_ptr<Group> clone() const =0;
protected:
  std::vector<std::shared_ptr<Group>> elements;
};
bool comparison(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2);
std::shared_ptr<Group> operator+(Group& g1, Group& g2);
std::shared_ptr<Group> operator+(std::shared_ptr<Group> g1, Group& g2);
std::shared_ptr<Group> operator+(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2);

template<typename T> requires std::is_arithmetic_v<T>
std::shared_ptr<Group> operator+(std::shared_ptr<Group> g1,T g2);

template<typename T> requires std::is_arithmetic_v<T>
std::shared_ptr<Group> operator+(Group& g1,T g2);

template<typename T> requires std::is_arithmetic_v<T>
std::shared_ptr<Group> operator*(std::shared_ptr<Group> g1,T g2);

template<typename T> requires std::is_arithmetic_v<T>
std::shared_ptr<Group> operator*(Group& g1,T g2);


std::shared_ptr<Group> operator*(Group& g1, Group& g2);
std::shared_ptr<Group> operator*(std::shared_ptr<Group> g1, Group& g2);
std::shared_ptr<Group> operator*(Group &g1, std::shared_ptr<Group> g2);
std::shared_ptr<Group> operator*(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2);

std::shared_ptr<Group> operator-(Group& g1);
std::shared_ptr<Group> operator-(std::shared_ptr<Group> g1);

bool operator==(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2);
bool operator!=(std::shared_ptr<Group> g1, std::shared_ptr<Group> g2);

namespace std {
  template <>
  struct hash<std::shared_ptr<Group>> {
    size_t operator()(const std::shared_ptr<Group>& p) const {
      auto k = p->formatDeep();   
      ostringstream oss;
      oss << *k;
      string s = oss.str();
      return std::hash<string>()(s);
    }
  };
}

constexpr std::size_t hashString(const char* str, std::size_t h = 0) {
    return (*str) ? hashString(str + 1, static_cast<std::size_t>(*str) + 31 * h) : h;
}

template<typename Derived>
class Base : public Group{
public:

  Base(){
    elements = std::vector<std::shared_ptr<Group>>();
  }

  Base(const std::vector<std::shared_ptr<Group>> &elems) {
    elements = elems;
  }

  Base(const std::shared_ptr<Group> &g){
    elements = g->elements;
  }

  Base(const Base *g){
    elements = g->elements;
  }

  std::shared_ptr<Group> clone() const override{
    return std::make_shared<Derived>(static_cast<const Derived&>(*this));
  }   

  std::shared_ptr<Group> build(std::vector<std::shared_ptr<Group>> elems) const override{
    return std::make_shared<Derived>(Derived(elems));
  }
  
  constexpr std::size_t get_name() const override{
    return hashString(typeid(Derived).name());
  }
};
