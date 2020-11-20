from oneflow_api import demo
foo = demo.Foo()
doo = demo.Foo()
print("foo == doo: ", foo == doo)
print("foo < doo: ", foo < doo)
print("---------[ default value ]--------")
print("foo.name():", foo.name())
print("foo.bar().nickname():", foo.bar().nickname())
print("---------[ set value ]--------")
foo.set_name("Jonathan")
foo.mutable_bar().set_nickname("Jonty")
print("foo.name():", foo.name())
print("foo.bar().nickname():", foo.bar().nickname())

print("foo == doo: ", foo == doo)
print("doo < foo: ", doo < foo)
foo.mutable_bars().Add().set_nickname("nice nickname")
foo.mutable_bars().Add().set_nickname("good nickname")
print([x.nickname() for x in foo.bars()])
print([x.nickname() for x in foo.Move().bars()])
print([x.nickname() for x in foo.bars()])

m = foo.mutable_map_int_int()

print(foo.map_int_int_size())

m[1]=1
m[2]=5

print(foo.map_int_int_size())
print(dict(m))

print("=================================")
bar = demo.Bar()
bar.set_name("Jack")
bar.set_nickname("Honey")
bar.set_of_int_value(10)
print(bar)

print(bar == foo.bar())

foo = demo.Foo()
foo.set_name("Tom")
foo.set_opt_int_value(20)
(foo.mutable_bar()).CopyFrom(bar)

print("operator==", bar == foo.mutable_bar())
foo.set_of_int_value(25)
foo.set_of_string_value("binbin")
foo.mutable_of_bar().set_nickname("hongyu")
foo.mutable_bar().set_nickname("hongyu")
print("operator<", bar < foo.mutable_bar())

print(foo)
