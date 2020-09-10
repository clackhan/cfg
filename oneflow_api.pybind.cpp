#include <iostream>
#include <pybind11/pybind11.h>
#include "pybind_module_registry.h"


PYBIND11_MODULE(oneflow_api, m) {
  ::oneflow::cfg::Pybind11ModuleRegistry().Import(m);
}
