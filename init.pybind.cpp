#include <pybind11/pybind11.h>
#include "demo.pybind.h"

namespace oneflow {
namespace cfg {

Pybind11ModuleRegistry* GlobalPybind11ModuleRegistry() {
  static Pybind11ModuleRegistry registry;
  return &registry;
}

} // namespace cfg

} // namespace oneflow

PYBIND11_MODULE(cfg, m) {
    ::oneflow::cfg::GlobalPybind11ModuleRegistry()->Import(m);
}
