//
// EPITECH PROJECT, 2018
// ModuleManager
// File description:
// juniqu_v
//

#include "config_manager/ConfigManager.hpp"
namespace zia::api {
//Core method

void		ConfigManager::ReadFile()
{
	std::ifstream file(_path);
	std::string	line;

	while (std::getline(file, line))
		_file.push_back(line);
	return ;
}

void		ConfigManager::CheckPath()
{
	std::regex pattern {"^.*\\.(json)$"};

	if (regex_match(_path, pattern) &&
		access(_path.c_str(), F_OK) == 0)
		return ReadFile();
	else
		throw ConfigError("Need json file");
	return ;
}

//Cannonique Forme
ConfigManager::ConfigManager(const std::string &path)
{
	_path = path;
	return ;
}

ConfigManager::ConfigManager(ConfigManager const &p)
{
	_path = p.getPath();
	return ;
}

ConfigManager::~ConfigManager()
{
	std::cout << "ConfigManager stop is work" << std::endl;
	return ;
}

ConfigManager	&ConfigManager::operator=(ConfigManager const &p)
{
	(void)p;
	return (*this);
}

// Getter
std::string					ConfigManager::getPath() const
{
	return (_path);
}

std::vector<std::string>	ConfigManager::getModName() const
{
	return (_mod_name);
}

std::vector<std::string>	ConfigManager::getModPath() const
{
	return (_mod_path);
}

// Setter
void		ConfigManager::setModName(std::vector<std::string> const &mod_name)
{
	_mod_name = mod_name;
	return ;
}

void		ConfigManager::setModPath(std::vector<std::string> const &mod_path)
{
	_mod_path = mod_path;
	return ;
}

void		ConfigManager::setPath(std::string const &path)
{
	_path = path;
	return ;
}

}