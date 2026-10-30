#include <iostream>

#include "Plugin/PluginBase.h"

namespace ps {
class PluginC final : public PluginBase {
 public:
  virtual bool initialize() override {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return true;
  }

  virtual void shutdown() override { std::cout << __PRETTY_FUNCTION__ << std::endl; }

  virtual void run() override { std::cout << __PRETTY_FUNCTION__ << std::endl; }

  const char* getName() const override { return "ps::PluginC"; }
};
}  // namespace ps

extern "C" PLUGIN_EXPORT ps::PluginBase* create_plugin() {
  return new ps::PluginC();
}

extern "C" PLUGIN_EXPORT void destroy_plugin(ps::PluginBase* plugin) {
  delete plugin;
}