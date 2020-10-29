import render
import importlib

demo = importlib.import_module('demo_pb2')


dst_file = open("demo.pybind.cpp", 'w')
dst_file.write(render.JinjaRender(demo, "template.pybind.cpp"))
dst_file.close()
