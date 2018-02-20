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
#include "module_manager/ModuleManager.hpp"
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
			Conf							getConf() const;
			std::string						getPath() const;
			std::vector<std::string>		getModules() const;
			std::vector<std::string>		getModules_path() const;
			JSONValue*						getDoc() const;
			zia::api::ModulePathList		getListModules() const;
			void							setPath(std::string const &);
			void							setModules(std::vector<std::string> const &);
			void							setModules_path(std::vector<std::string> const &);
			void							setDoc(JSONValue* const &doc);
			
			// Utils method
			ConfValue 						parse_str(std::string);
			std::string						format_wstring(std::wstring);
			void							CheckPath();
			void							ReadFile();
			void							getModByPath();
			void							find_modules(JSONObject);
			void							find_modules_path(JSONObject);

			// Manager main method
			/*
				refresh all conf with browser_conf (check if _path is not null or empty)
				get all
				refresh or add Default value with defaultvalue method
			*/
			bool							browser_conf();
			void							DefaultValue(); 

			//Parser method		
			void							getKey();
			void							add_default(std::string, std::string);
				// for obj
			ConfObject						add_bool_to_obj(std::string, bool, ConfObject);
			ConfObject						add_string_to_obj(std::string, std::wstring str, ConfObject);
			ConfObject						add_obj_to_obj(std::string, JSONValue *, ConfObject);
			void							add_object(std::string, JSONValue *);
			Conf							new_object(JSONValue*);
				// for array
			void							add_array(std::string , JSONValue *);
			ConfValue						new_array(JSONValue*);
			ConfObject						add_array_for_obj(std::string , JSONValue *, ConfObject);
				// for bool and string
			void							add_string(std::string , std::wstring);
			void							add_bool(std::string , bool);
	
	private:
		Conf				 	 _conf;
		std::string				 _path;
		std::vector<std::string> _modules;
		std::vector<std::string> _modules_path;
		JSONValue*				 _doc;
		ModulePathList			 _list;
	};
}

#endif /* !ConfigManager.hpp */