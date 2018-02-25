#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "unitTest/unitTest.hpp"

using namespace zia::api;

TEST_CASE("Openssl certificate test", "[Openssl]") {
  std::string path = "linux/sources/unitTest/example/";

  std::unique_ptr<SSLModule> ssl = std::make_unique<SSLModule>();

  std::unique_ptr<ConfigManager> c = std::make_unique<ConfigManager>(path + "allright.json");
  c.get()->browser_conf();
  REQUIRE( ssl.get()->config(c.get()->getConf()) == true );

  c.reset(new ConfigManager(path + "NotTheGoodPath.json"));
  c.get()->browser_conf();
  REQUIRE( ssl.get()->config(c.get()->getConf()) == false );

  c.reset(new ConfigManager(path + "wrongCert.json"));
  c.get()->browser_conf();
  REQUIRE( ssl.get()->config(c.get()->getConf()) == false );

  c.reset(new ConfigManager(path + "wrongKey.json"));
  c.get()->browser_conf();
  REQUIRE( ssl.get()->config(c.get()->getConf()) == false );

  c.reset(new ConfigManager(path + "diffCertAndKey.json"));
  c.get()->browser_conf();
  REQUIRE( ssl.get()->config(c.get()->getConf()) == false );
}
