//
// EPITECH PROJECT, 2018
// ModuleManager
// File description:
// juniqu_v
//

#include "config_manager/ConfigManager.hpp"

namespace zia::api {

void		ConfigManager::ReadFile()
{
	std::ifstream file(_path);
	std::string res( (std::istreambuf_iterator<char>(file)),
                       (std::istreambuf_iterator<char>()));
	std::wstring widestr = std::wstring(res.begin(), res.end());
	const wchar_t* content = widestr.c_str();
	JSONValue *doc = JSON::Parse(content);
	setDoc(doc);
	if (doc == NULL || doc->IsObject() == false)
		throw ConfigError("Is it a json file ?");
}

void		ConfigManager::find_modules(JSONObject mod)
{
	std::vector<std::string> modules;
	std::string 			 tmp;

	if (mod.find(L"modules") != mod.end() && mod[L"modules"]->IsArray())
	{
		JSONArray array = mod[L"modules"]->AsArray();
		for (unsigned int i = 0; i < array.size(); i++)
		{
			tmp = format_wstring(array[i]->Stringify());
			tmp.erase(std::remove(tmp.begin(), tmp.end(), '\"' ), tmp.end());
			modules.push_back(tmp);
		}
		setModules(modules);
	}
}

void		ConfigManager::find_modules_path(JSONObject mod)
{
	std::vector<std::string> modules_path;
	std::string 			 tmp;

	if (mod.find(L"modules_path") != mod.end() && mod[L"modules_path"]->IsArray())
	{
		JSONArray array = mod[L"modules_path"]->AsArray();
		for (unsigned int i = 0; i < array.size(); i++)
		{
			tmp = format_wstring(array[i]->Stringify());
			tmp.erase(std::remove(tmp.begin(), tmp.end(), '\"' ), tmp.end());
			tmp.erase(std::remove(tmp.begin(), tmp.end(), '\\' ), tmp.end());
			modules_path.push_back(tmp);
		}
		setModules_path(modules_path);
	}
}

void		ConfigManager::getModByPath()
{
	std::pair<std::string, std::string> key;

	for (unsigned int i = 0; i < _modules.size(); i++)
	{
		for (unsigned int x = 0; x < _modules_path.size(); x++)
		{
			std::string tmp;
			tmp = _modules_path[x] + "/" + _modules[i];
			if (access(tmp.c_str(), F_OK) == 0)
			{
				key = make_pair(_modules[i],_modules_path[x]);
				_list.push_back(key);
				break ;
			}
		}
	        if (_list.empty() || _list.back().first != _modules[i])
		  std::cerr << "modules: " << _modules[i] << " not found !" << std::endl;
	}
}

void		ConfigManager::CheckPath()
{
	std::regex pattern {"^.*\\.(json)$"};

	if (regex_match(getPath(), pattern) &&
		access(getPath().c_str(), F_OK) == 0)
		return ReadFile();
	else
		throw ConfigError("Need json file");
	return ;
}

static int	check_str(std::string str)
{
	for (unsigned int i = 0; i < str.size(); i++)
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-' || str[i] == '.' || str[i] == '+')
		  continue ;
		else
		  return (0);
	}

	for (unsigned int i = 0; i < str.size(); i++)
	{
		if (str[i] == '.')
		  return (2);

	}
	return (1);
}

ConfValue 	ConfigManager::parse_str(std::string str)
{
	double			res2;
	long long		res1;
	std::string 	res3;
	ConfValue 		ret;

	switch (check_str(str)) {
		case 1 :
			res1 = std::stol(str, NULL, 10);
			ret.v = res1;
			break;
		case 2 :
			res2 = std::stod(str, NULL);
			ret.v = res2;
			break;
		default :
			res3 = str;
			ret.v = res3;
			break;
	}
	return (ret);
}

std::string ConfigManager::format_wstring(std::wstring output)
{
	std::string str;

	for (char x : output)
		str += x;
	return (str);
}

}
