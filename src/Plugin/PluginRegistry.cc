#include "Plugin/PluginRegistry.h"

#include <iostream>

#if defined(_WIN32)
#include <libloaderapi.h>
#include <minwindef.h>
#else
#include <dlfcn.h>
#endif

namespace ps {
PluginRegistry::~PluginRegistry() {
  unloadAll();
}

bool PluginRegistry::loadPlugin(const std::filesystem::path& path) noexcept {
#if defined(_WIN32)
  HMODULE handle = LoadLibraryA(path.generic_string().c_str());
  if (!handle) {
    return false;
  }

  auto createFn = (PluginConstructor)GetProcAddress(handle, "create_plugin");
  auto destroyFn = (PluginDestructor)GetProcAddress(handle, "destroy_plugin");
#else
  void* handle = dlopen(path.c_str(), RTLD_LAZY);
  if (!handle) {
    std::cerr << "dlopen error: " << dlerror() << std::endl;
    return false;
  }

  auto createFn = (PluginConstructor)dlsym(handle, "create_plugin");
  auto destroyFn = (PluginDestructor)dlsym(handle, "destroy_plugin");
#endif

  if (!createFn || !destroyFn) {
    std::cerr << "Failed to retrieve symbols 'create_plugin' and 'destroy_plugin'";
    std::cerr << " from " << path << std::endl;
#if defined(_WIN32)
    FreeLibrary(handle);
#else
    dlclose(handle);
#endif
    return false;
  }

  ps::PluginBase* instance = createFn();
  if (!instance || !instance->initialize()) {
    if (instance) {
      destroyFn(instance);
    }
    
#if defined(_WIN32)
    FreeLibrary(handle);
#else
    dlclose(handle);
#endif
    return false;
  }

  plugins.emplace_back(path, handle, instance, destroyFn);
  std::cout << "Successfully loaded: " << std::quoted(instance->getName());
  std::cout << " from: " << path << std::endl;
  
  return true;
}

void PluginRegistry::runAllActivePlugins() noexcept {
  for (auto& p : plugins) {
    if (p.instance) {
      p.instance->run();
    }
  }
}

void PluginRegistry::unloadAll() noexcept {
  for (auto& p : plugins) {
    if (p.instance && p.destructor) {
      p.instance->shutdown();
      p.destructor(p.instance);
    }

#if defined(_WIN32)
    if (p.handle) {
      FreeLibrary((HMODULE)p.handle);
    }
#else
    if (p.handle) {
      dlclose(p.handle);
    }
#endif
  }
  plugins.clear();
}
}  // namespace ps