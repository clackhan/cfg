#!/bin/bash
~/oneflow/third_party/protobuf/bin/protoc demo.proto --python_out=./
~/oneflow/third_party/protobuf/bin/protoc demo.proto --cpp_out=./
python3 template_convert.py              \
       --dst_hpp_path=demo.cfg.h         \
       --dst_cpp_path=demo.cfg.cpp       \
       --dst_pybind_path=demo.pybind.cpp \
       --of_proto_python_dir=./          \
       --sub_module_path=demo_pb2
# python3 generate_hpp.py
# python3 generate_cpp.py
# python3 generate_pybind.py
# python3 generate_hpp.py > demo.cfg.h
# python3 generate_cpp.py > demo.cfg.cpp
# python3 generate_pybind.py > demo.pybind.cpp
# g++ -O3 -Wall -shared -std=c++11 -fPIC \
#   `python3 -m pybind11 --includes` pybind_module_registry.cpp demo.pb.cc demo.cfg.cpp demo.pybind.cpp oneflow_api.pybind.cpp \
#   -lglog -lgflags -lpthread -I include -I ~/oneflow/third_party/protobuf/include \
#   ~/oneflow/third_party/protobuf/lib/libprotobuf.a  -o oneflow_api`python3-config --extension-suffix`

# g++ -std=c++11 demo.pb.cc demo.cfg.cpp test.cpp -I include -I ~/oneflow/third_party/protobuf/include \
#   ~/oneflow/third_party/protobuf/lib/libprotobuf.a -o test

g++ -O3 -Wall -shared -std=c++11 -fPIC \
  `python3 -m pybind11 --includes` pybind_module_registry.cpp demo.pb.cc demo.cfg.cpp demo.pybind.cpp oneflow_api.pybind.cpp \
  -I include -I ~/oneflow/third_party/protobuf/include \
  ~/oneflow/third_party/protobuf/lib/libprotobuf.a  -o oneflow_api`python3-config --extension-suffix`

g++ -std=c++11 demo.pb.cc demo.cfg.cpp test.cpp -I include -I ~/oneflow/third_party/protobuf/include \
  ~/oneflow/third_party/protobuf/lib/libprotobuf.a -o test

./test

python3 test.py
