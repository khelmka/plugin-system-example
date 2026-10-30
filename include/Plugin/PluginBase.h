#pragma once

#include <string>

#if defined(_WIN32)
#define PLUGIN_EXPORT __declspec(dllexport)
#define PLUGIN_IMPORT __declspec(dllimport)
#else
#define PLUGIN_EXPORT __attribute__((visibility("default")))
#define PLUGIN_IMPORT
#endif

namespace ps {
class PluginBase {
 public:
  virtual ~PluginBase() = default;

  virtual bool initialize() = 0;
  virtual void shutdown() = 0;
  virtual void run() = 0;

  virtual const char* getName() const = 0;
};
}  // namespace ps

using PluginConstructor = ps::PluginBase* (*)();
using PluginDestructor = void (*)(ps::PluginBase*);