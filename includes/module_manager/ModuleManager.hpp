//
// EPITECH PROJECT, 2018
// ModuleManager
// File description:
// juniqu_v
//

#ifndef _MODULEMANAGER_HPP_
 #define _MODULEMANAGER_HPP_

#include "api/module.h"
#include "api/net.h"
#include <iostream>

class	ModuleManager
{
public:
	ModuleManager();
	ModuleManager(const std::string &);
	ModuleManager(ModuleManager &);
	ModuleManager &operator=(ModuleManager &);
	~ModuleManager();

	std::string		&getTest();
	void			setTest(std::string const &);
private:
	std::string _test;
};

#endif /* !ModuleManager.hpp */
