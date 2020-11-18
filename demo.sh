#!/bin/bash
~/oneflow/third_party/protobuf/bin/protoc demo.proto --python_out=./
~/oneflow/third_party/protobuf/bin/protoc demo.proto --cpp_out=./
python3 template_convert.py              \
       --dst_hpp_path=demo.cfg.h         \
       --dst_cpp_path=demo.cfg.cpp       \
       --dst_pybind_path=demo.cfg.pybind.cpp \
       --of_proto_python_dir=./          \
       --sub_module_path=demo_pb2

g++ -O3 -Wall -shared -std=c++11 -fPIC \
  `python3 -m pybind11 --includes` pybind_module_registry.cpp demo.pb.cc demo.cfg.cpp demo.cfg.pybind.cpp oneflow_api.pybind.cpp \
  -I include -I ~/oneflow/third_party/protobuf/include \
  ~/oneflow/third_party/protobuf/lib/libprotobuf.a  -o oneflow_api`python3-config --extension-suffix`

g++ -std=c++11 demo.pb.cc demo.cfg.cpp test.cpp -I include -I ~/oneflow/third_party/protobuf/include \
  ~/oneflow/third_party/protobuf/lib/libprotobuf.a -o test

./test

python3 test.py
