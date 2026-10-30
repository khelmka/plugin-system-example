#pragma once

#include <filesystem>
#include <vector>

#include "Plugin/PluginDescriptor.h"

namespace ps {
class PluginRegistry {
 public:
  /// @brief unloads all valid, registered plugins
  ~PluginRegistry() noexcept;

  /// @brief create and add a plugin file into the registry
  /// @param path the system filepath (relative to executable) of the shared library file
  /// @return true if creation was successful
  bool loadPlugin(const std::filesystem::path& path) noexcept;

  /// @brief invoke the execute function on all valid, registered plugins
  void runAllActivePlugins() noexcept;

  /// @brief destroy and remove all the plugins from the registry
  void unloadAll() noexcept;

 private:
  std::vector<PluginDescriptor> plugins;
};
}  // namespace ps