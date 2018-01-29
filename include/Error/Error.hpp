//
// Error.hpp for  in /home/albert_q/rendu/test/cpp/Error
//
// Made by Quentin Albertone
// Login   <albert_q@epitech.net>
//
// Started on  Tue Nov  7 14:52:41 2017 Quentin Albertone
// Last update Mon Jan  8 16:00:44 2018 Quentin Albertone
//

#ifndef ERROR_HPP_
# define ERROR_HPP_

# include <stdexcept>
# include <iostream>
# include <sstream>
# include <string>


namespace		Error
{
  // class ZiaError
  class ZiaError: public std::exception
  {
  public:
    ZiaError(std::string const &msg);
    ZiaError(ZiaError const &other);
    virtual ~ZiaError() throw(); // don't forget to throw
    ZiaError		&operator=(ZiaError const &other);

    char const		*what() const throw();
  private:
    std::string		_msg;
  };

  // Example Exception
  class ExampleError : public ZiaError
  {
  public:
    ThrowError(std::string const &msg);
    ThrowError(ThrowError const &other);
    virtual ~ThrowError() throw();
    ThrowError &operator=(ThrowError const &other);
  };
};

#endif /* !ERROR_HPP_ */
