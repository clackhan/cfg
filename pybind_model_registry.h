#ifndef CFG_PYBIND_REGISTRY_H_
#define CFG_PYBIND_REGISTRY_H_

#include <glog/logging.h>
#include <pybind11/pybind11.h>
#include <map>
#include <memory>
#include <assert.h>

namespace oneflow {
namespace cfg {

class Pybind11ModuleRegistry {
 public:
  Pybind11ModuleRegistry() = default;
  ~Pybind11ModuleRegistry() = default;
  void Register(std::string module_path, std::function<void(pybind11::module&)> build_sub_module);
  void Import(pybind11::module& m);
 private:
  std::map<std::string, std::function<void(pybind11::module&)>> sub_module_;
};

void BuildSubModule(const std::string& module_path,  pybind11::module& m,
                    std::function<void(pybind11::module&)> build_sub_module);

inline void Pybind11ModuleRegistry::Register(std::string module_path, 
                                             std::function<void(pybind11::module&)> build_sub_module) {
  CHECK(sub_module_.emplace(module_path, build_sub_module).second) << "Registered failed";
}

inline void Pybind11ModuleRegistry::Import(pybind11::module& m) {
  for (auto& pair : sub_module_) {
    BuildSubModule(pair.first, m, pair.second);
  }
}

void BuildSubModule(const std::string& module_path,  pybind11::module& m,
                    std::function<void(pybind11::module&)> build_sub_module) {
  size_t dot_pos = module_path.find(".");
  if (dot_pos == std::string::npos) {
    pybind11::module sub_module = m.def_submodule((char*)module_path.data());
    build_sub_module(sub_module);
  } else {
    const std::string& sub_module_name = module_path.substr(0, dot_pos);
    pybind11::module sub_module = m.def_submodule((char*)sub_module_name.data());
    BuildSubModule(module_path.substr(dot_pos + 1), sub_module, build_sub_module);
  }
}

Pybind11ModuleRegistry* GlobalPybind11ModuleRegistry();


} // namespace cfg

} // namespace oneflow


#define ONEFLOW_PYBIND11_MODEL(module_path, m)                    \
  static void OneflowPythonModel##__LINE__(pybind11::module&);    \
  namespace {                                                     \
  struct RegistryInit {                                           \
    RegistryInit() {                                              \
        ::oneflow::cfg::GlobalPybind11ModuleRegistry()            \
          ->Register(#module_path, &OneflowPythonModel##__LINE__);\
    }                                                             \
  };                                                              \
  RegistryInit registry_init;                                     \
  }                                                               \
  static void OneflowPythonModel##__LINE__(pybind11::module& m)

#endif // CFG_PYBIND_REGISTRY_H_
