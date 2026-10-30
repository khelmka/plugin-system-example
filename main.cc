#include <memory>

#include "Plugin/PluginRegistry.h"

int main() {
  auto registry = std::make_unique<ps::PluginRegistry>();
  registry->loadPlugin("plugins/libPluginA.dll");
  registry->loadPlugin("plugins/libPluginB.dll");
  registry->loadPlugin("plugins/libPluginC.dll");

  registry->runAllActivePlugins();

  registry->unloadAll();
}