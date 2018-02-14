//
// EPITECH PROJECT, 2018
// ModuleManager
// File description:
// juniqu_v
//

#ifndef _CONFIGMANAGER_HPP_
 #define _CONFIGMANAGER_HPP_

//#include <rapidjson/istreamwrapper.h>
//#include "rapidjson/document.h"
#include "api/module.h"
#include "api/net.h"
#include "error/Error.hpp"
#include "config_manager/json-lib/JSON.h"
#include "config_manager/json-lib/JSONValue.h"
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <cstdio>
#include <unistd.h>
#include <time.h>
#include <sstream>

//using namespace rapidjson;

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
			ConfArray						getConfAr() const;
			std::string						getPath() const;
			std::vector<std::string>		getModules() const;
			std::vector<std::string>		getModules_path() const;
			JSONValue*						getDoc() const;
			void							setPath(std::string const &);
			void							setModules(std::vector<std::string> const &);
			void							setModules_path(std::vector<std::string> const &);
			void							setDoc(JSONValue* const &doc);
			// Core method
			std::string						format_wstring(JSONArray array, unsigned int i);
			void							find_modules(JSONObject mod);
			void							find_modules_path(JSONObject mod);
			void							CheckPath();
			void							ReadFile();
			void							ParseDoc();
			bool							browser_conf();
	private:
		ConfArray				 _conf;
		std::string				 _path;
		std::vector<std::string> _modules;
		std::vector<std::string> _modules_path;
		JSONValue*				 _doc;
	};
}

#endif /* !ConfigManager.hpp */