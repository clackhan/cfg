import render
import importlib

demo = importlib.import_module('demo_pb2')

dst_file = open("demo.cfg.cpp", 'w')
dst_file.write(render.JinjaRender(demo, "template.cfg.cpp"))
dst_file.close()
