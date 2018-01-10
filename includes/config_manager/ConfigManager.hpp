//
// EPITECH PROJECT, 2018
// ModuleManager
// File description:
// juniqu_v
//

#ifndef _CONFIGMANAGER_HPP_
 #define _CONFIGMANAGER_HPP_

#include "api/module.h"
#include "api/net.h"
#include "api/Error.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <unistd.h>

namespace zia::api {
	class	ConfigManager
		{
		public:
			// Cannonique forme
			ConfigManager() {};
			ConfigManager(const std::string &);
			ConfigManager(ConfigManager const &);
			ConfigManager &operator=(ConfigManager const &);
			~ConfigManager();

			//Getter/Setter
			std::vector<std::string>		getModName() const;
			std::vector<std::string>		getModPath() const;
			std::string						getPath() const;
			void							setModName(std::vector<std::string> const &);
			void							setModPath(std::vector<std::string> const &);
			void							setPath(std::string const &);

			// Core method
			void							CheckPath();
			void							ReadFile();
	private:
		std::vector<std::string> _file;
		std::vector<std::string> _mod_name;
		std::vector<std::string> _mod_path;
		std::string				 _path;
	};
}

#endif /* !ConfigManager.hpp */