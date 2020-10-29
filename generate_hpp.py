import render
import importlib

demo = importlib.import_module('demo_pb2')


dst_file = open("demo.cfg.h", 'w')
dst_file.write(render.JinjaRender(demo, "template.cfg.h"))
dst_file.close()

