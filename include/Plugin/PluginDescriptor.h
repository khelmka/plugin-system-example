#pragma once

#include <filesystem>

#include "Plugin/PluginBase.h"

namespace ps {
struct PluginDescriptor {
  std::filesystem::path path;
  void* handle{};
  class PluginBase* instance{};
  PluginDestructor destructor{};
};
}  // namespace ps
