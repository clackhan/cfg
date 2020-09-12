#!/bin/bash
protoc demo.proto --python_out=./
python3 generate_hpp.py > demo.cfg.h
python3 generate_cpp.py > demo.cfg.cpp
python3 generate_pybind.py > demo.pybind.cpp
python3 genarate_convert_hpp.py > demo.proto.convert.cfg.h
python3 genarate_convert_cpp.py > demo.proto.convert.cfg.cpp
g++ -O3 -Wall -shared -std=c++11 -fPIC \
  `python3 -m pybind11 --includes` pybind_module_registry.cpp demo.pybind.cpp oneflow_api.pybind.cpp \
  -lglog -lgflags -lpthread -o oneflow_api`python3-config --extension-suffix`
python3 test.py
