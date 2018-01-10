//
// EPITECH PROJECT, 2018
// config_error
// File description:
// juniqu_v
//

#ifndef _ERROR_HPP_
 #define _ERROR_HPP_

#include <exception>
#include <iostream>

class ConfigError : public std::exception
{
public:
	ConfigError(std::string const &err) throw() {
		_err = "Config error : " + err + ".";};
	virtual ~ConfigError() throw() {};
  	virtual const char  *what() const throw() { return (_err.c_str()); };

private:
    std::string         _err;
};

#endif /* !Error.hpp */