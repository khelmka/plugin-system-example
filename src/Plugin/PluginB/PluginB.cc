#include <iostream>

#include "Plugin/PluginBase.h"

namespace ps {
class PluginB final : public PluginBase {
 public:
  bool initialize() override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return true;
  }

  void shutdown() override { std::cout << __PRETTY_FUNCTION__ << std::endl; }

  void run() override { std::cout << __PRETTY_FUNCTION__ << std::endl; }

  const char* getName() const override { return "ps::PluginB"; }
};
}  // namespace ps

extern "C" PLUGIN_EXPORT ps::PluginBase* create_plugin() {
  return new ps::PluginB();
}

extern "C" PLUGIN_EXPORT void destroy_plugin(ps::PluginBase* plugin) {
  delete plugin;
}