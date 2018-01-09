//
// EPITECH PROJECT, 2018
// ModuleManager
// File description:
// juniqu_v
//

#include "module_manager/ModuleManager.hpp"

ModuleManager::ModuleManager()
{
	_test = "const by default.";
	return ;
}

ModuleManager::ModuleManager(ModuleManager const &p)
{
	_test = p.getTest();
	return ;
}

ModuleManager::ModuleManager(const std::string &test)
{
	_test = test;
	return ;
}

ModuleManager::~ModuleManager()
{
	std::cout << "ModuleManager stop is work" << std::endl;
	return ;
}

ModuleManager	&ModuleManager::operator=(ModuleManager const &p)
{
	_test = p.getTest();
	return (*this);
}

std::string	ModuleManager::getTest() const
{
	return (_test);
}

void		ModuleManager::setTest(std::string const &test)
{
	_test = test;
	return ;
}
