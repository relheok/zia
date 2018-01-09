#ifndef ERROR_HPP_
# define ERROR_HPP_

# include <iostream>
# include <exception>

class                 ModuleError : public std::exception {
public:
  ModuleError(std::string const &err) throw() {
    _err = "Module error : " + err + ".";
  }
  virtual ~ModuleError() throw() {}

  virtual const char  *what() const throw() { return (_err.c_str()); }
private:
    std::string         _err;
};

#endif /* end of include guard: ERROR_HPP_ */
