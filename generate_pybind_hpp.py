import render
import demo_pb2 as demo

print(render.JinjaRender(demo, "template.pybind.h", python_module_name='demo1.demo'))
