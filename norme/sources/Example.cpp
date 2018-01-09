#include "Example.hpp"

Example::Example() {
  initComponent();
}

Example::Example(const Example &copy) {
  _ptr.reset(new Example(copy._ptr.get()));
  _name = copy.getName();
}

Example &Example::operator=(const Example &copy) {
  _ptr.reset(new Example(copy._ptr.get()));
  _name = copy.getName();
  return (*this);
}

Example::~Example() {}

bool  Example::initComponent() {
  _ptr.reset(new Example);
  _name = "Example";
}

std::string   &Example::getName() const {
  return (_name);
}

void    setName(std::string const &name) {
  _name = name;
}
