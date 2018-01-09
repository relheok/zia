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
	ModuleManager(ModuleManager const &);
	ModuleManager &operator=(ModuleManager const &);
	~ModuleManager();

	std::string		getTest() const;
	void			setTest(std::string const &);
private:
	std::string _test;
};

#endif /* !ModuleManager.hpp */
