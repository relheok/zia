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
	const wchar_t* test = widestr.c_str();
	JSONValue *doc = JSON::Parse(test);
	setDoc(doc);
}

void		ConfigManager::ParseDoc()
{
	if (_doc == NULL || _doc->IsObject() == false)
		throw ConfigError("Is it a json file ?");
	else
	{
		JSONObject mod;
		mod = getDoc()->AsObject();
		find_modules(mod);
		find_modules_path(mod);
		// find any other key it's here !
 	}
}

void		ConfigManager::find_modules(JSONObject mod)
{
	std::vector<std::string> modules;
	std::string 			 tmp;
	JSONArray array = mod[L"modules"]->AsArray();

	if (mod.find(L"modules") != mod.end() && mod[L"modules"]->IsArray())
	{
		for (unsigned int i = 0; i < array.size(); i++)
		{
			tmp = format_wstring(array, i);
			tmp.erase(std::remove(tmp.begin(), tmp.end(), '\"' ), tmp.end());
			tmp.erase(std::remove(tmp.begin(), tmp.end(), '\\' ), tmp.end());
			modules.push_back(tmp);
		}
		setModules(modules);
	}
}

void		ConfigManager::find_modules_path(JSONObject mod)
{
	std::vector<std::string> modules_path;
	std::string 			 tmp;
	JSONArray array = mod[L"modules_path"]->AsArray();

	if (mod.find(L"modules_path") != mod.end() && mod[L"modules_path"]->IsArray())
	{
		for (unsigned int i = 0; i < array.size(); i++)
		{
			tmp = format_wstring(array, i);
			tmp.erase(std::remove(tmp.begin(), tmp.end(), '\"' ), tmp.end());
			tmp.erase(std::remove(tmp.begin(), tmp.end(), '\\' ), tmp.end());
			modules_path.push_back(tmp);
		}
		setModules_path(modules_path);
	}
}

std::string ConfigManager::format_wstring(JSONArray array, unsigned int i)
{
	std::string str;
	std::wstring output;

	output = array[i]->Stringify();
	for (char x : output)
		str += x;
	return (str);
}

bool		ConfigManager::browser_conf()
{
	try 
	{
		CheckPath();
		ParseDoc();
		if (_modules.empty() == true || _modules_path.empty() == true)
			return (true);
		else
		{
			return (true);
			//getModByPath();
		}
		return (true);
	}
	catch (std::exception &err)
	{
		std::cerr << err.what() << std::endl;
		return (false);
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
	_conf = p.getConfAr();
	_modules = p.getModules();
	_modules_path = p.getModules_path();
	return (*this);
}

// Getter
std::string					ConfigManager::getPath() const
{
	return (_path);
}

ConfArray					ConfigManager::getConfAr() const
{
	return (_conf);
}

std::vector<std::string>	ConfigManager::getModules() const
{
	return (_modules);
}

std::vector<std::string>	ConfigManager::getModules_path() const
{
	return (_modules_path);
}

JSONValue*					ConfigManager::getDoc() const
{
	return (_doc);
}
// Setter

void		ConfigManager::setModules(std::vector<std::string>const &modules)
{
	for (unsigned int i = 0; i < modules.size(); i++)
		_modules.push_back(modules[i]);
}

void		ConfigManager::setModules_path(std::vector<std::string>const &modules_path)
{
	for (unsigned int i = 0; i < modules_path.size(); i++)
		_modules_path.push_back(modules_path[i]);
}

void		ConfigManager::setPath(std::string const &path)
{
	_path = path;
	return ;
}

void		ConfigManager::setDoc(JSONValue* const &doc)
{
	_doc = doc;
	return ;
}

}