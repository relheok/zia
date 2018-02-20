#include "HtmlManager.hpp"

namespace zia::api {
  std::string    HtmlManager::viewDirectory(std::string const &path, std::string uri) {
    std::string   body = Utils::readFile(VIEW_DIR_FILE);
    DIR *dir = opendir(path.c_str());
    struct dirent *odir = NULL;
    if (!dir)
      throw FileNotFound("file not found : " + path);
    body.replace(body.find("[path]"), 6, uri);
    if (uri[uri.size() - 1] != '/')
      uri += "/";
    std::string list = "<ul>";
    while ((odir = readdir(dir)) != NULL) {
      if (odir->d_name[0] != '.')
        list += "<li><a href=\"" + uri + odir->d_name + "\">" + std::string(odir->d_name) + "</a></li>";
    }
    list += "</ul>";
    body.replace(body.find("[list]"), 6, list);
    closedir(dir);
    return body;
  }
} /* zia::api */
