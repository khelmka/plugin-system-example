#pragma once

#include <string>

#if defined(_WIN32)
#define PLUGIN_EXPORT __declspec(dllexport)
#else
#define PLUGIN_EXPORT __attribute__((visibility("default")))
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

typedef ps::PluginBase* (*PluginConstructorFn)();
typedef void (*PluginDestructorFn)(ps::PluginBase*);