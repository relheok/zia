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
#include <vector>

class	ModuleManager
{
public:
	// Cannonique forme
	ModuleManager() {};
	ModuleManager(const std::vector<std::string> &,
					const std::vector<std::string> &);
	ModuleManager(ModuleManager const &);
	ModuleManager &operator=(ModuleManager const &);
	~ModuleManager();

	//Getter/Setter
	std::vector<std::string>		getModName() const;
	std::vector<std::string>		getModPath() const;
	void							setModName(std::vector<std::string> const &);
	void							setModPath(std::vector<std::string> const &);

	// Core method
	bool							init_start();
	bool							run();
private:
	std::vector<std::string> _mod_name;
	std::vector<std::string> _mod_path;
};

#endif /* !ModuleManager.hpp */
