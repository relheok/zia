//
// EPITECH PROJECT, 2018
// ModuleManager
// File description:
// juniqu_v
//

#include "module_manager/ModuleManager.hpp"

//Core method

bool		ModuleManager::run()
{
	return (true);
}

bool		ModuleManager::init_start()
{
	std::cout << _mod_name.back() << std::endl;
	std::cout << _mod_path.back() << std::endl;
	return (true);
}

//Cannonique Forme
ModuleManager::ModuleManager(ModuleManager const &p)
{
	_mod_name = p.getModName();
	_mod_path = p.getModPath();
	return ;
}

ModuleManager::ModuleManager(const std::vector<std::string> &mod_name,
							 const std::vector<std::string> &mod_path)
{
	_mod_name = mod_name;
	_mod_path = mod_path;
	return ;
}

ModuleManager::~ModuleManager()
{
	std::cout << "ModuleManager stop is work" << std::endl;
	return ;
}

ModuleManager	&ModuleManager::operator=(ModuleManager const &p)
{
	_mod_name = p.getModName();
	_mod_path = p.getModPath();
	return (*this);
}

// Getter
std::vector<std::string>	ModuleManager::getModName() const
{
	return (_mod_name);
}

std::vector<std::string>	ModuleManager::getModPath() const
{
	return (_mod_path);
}

// Setter
void		ModuleManager::setModName(std::vector<std::string> const &mod_name)
{
	_mod_name = mod_name;
	return ;
}

void		ModuleManager::setModPath(std::vector<std::string> const &mod_path)
{
	_mod_path = mod_path;
	return ;
}
