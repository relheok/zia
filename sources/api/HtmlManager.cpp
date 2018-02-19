#include "HtmlManager.hpp"

namespace zia::api {
  std::string    HtmlManager::viewDirectory(std::string const &path, std::string const &uri) {
    std::string   body = "";
    body += Utils::readFile("./templates/view_dir_head.html");
    DIR *dir = opendir(path.c_str());
    struct dirent *odir = NULL;
    if (!dir)
      throw FileNotFound("file not found : " + path);
    std::string pathDir = uri.substr(0, uri.find_last_of("/") + 1);
    body += "<h1>Index of " + pathDir + "</h1>";
    body += "<ul>";
    while ((odir = readdir(dir)) != NULL) {
      if (odir->d_name[0] != '.')
        body += "<li><a href=\"" + pathDir + odir->d_name + "\">" + std::string(odir->d_name) + "</a></li>";
    }
    body += "</ul></body></html>";
    closedir(dir);
    return body;
  }
} /* zia::api */
