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
    _err = "Module loader error : " + err + ".";
  }
  virtual ~ModuleLoaderError() throw() {}

  virtual const char  *what() const throw() { return (_err.c_str()); }

  private:
      std::string         _err;
};

class                 ModuleNotFoundError : public std::exception {
public:
  ModuleNotFoundError(std::string const &name) throw() {
    _err = "Module " + name + " isn't loaded.";
  }
  virtual ~ModuleNotFoundError() throw() {}

  virtual const char  *what() const throw() { return (_err.c_str()); }

  private:
      std::string         _err;
};

class                 ModuleManagerError : public std::exception {
public:
  ModuleManagerError(std::string const &err) throw() {
    _err = "Module manager error : " + err + ".";
  }
  virtual ~ModuleManagerError() throw() {}

  virtual const char  *what() const throw() { return (_err.c_str()); }

  private:
      std::string         _err;
};

class                 ConfigError : public std::exception {
public:
  ConfigError(std::string const &err) throw() {
    _err = "Config error : " + err + ".";
  }
  virtual ~ConfigError() throw() {}

  virtual const char  *what() const throw() { return (_err.c_str()); }

  private:
      std::string         _err;
};

#endif /* !Error.hpp */
