#ifndef ERROR_HPP_
# define ERROR_HPP_

# include <iostream>
# include <exception>

class                 FatalError : public std::exception {
public:
  FatalError(std::string const &from, std::string const &err) throw() {
    _err = "Fatal error (" + from + ") : " + err + ".";
  }  
  virtual ~FatalError() throw() {}

  virtual const char  *what() const throw() { return (_err.c_str()); }
private:
    std::string         _err;
};

class                 ModuleLoaderError : public std::exception {
public:
  ModuleLoaderError(std::string const &err) throw() {
    _err = "ModuleLoader error : " + err + ".";
  }
  virtual ~ModuleLoaderError() throw() {}

  virtual const char  *what() const throw() { return (_err.c_str()); }
private:
    std::string         _err;
};

#endif /* end of include guard: ERROR_HPP_ */
