#include <pybind11/pybind11.h>
#include "oneflow/cfg/pybind_module_registry.h"


PYBIND11_MODULE(oneflow_api, m) {
  ::oneflow::cfg::Pybind11ModuleRegistry().ImportAll(m);
}
