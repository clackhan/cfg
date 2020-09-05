import demo
foo = demo.Foo()
print("---------[ default value ]--------")
print("foo.name():", foo.name())
print("foo.bar().nickname():", foo.bar().nickname())
print("---------[ set value ]--------")
foo.set_name("Jonathan")
foo.mutable_bar().set_nickname("Jonty")
print("foo.name():", foo.name())
print("foo.bar().nickname():", foo.bar().nickname())
foo.bars().ConstCast().Add().set_nickname("nice nickname")
foo.mutable_bars().Add().set_nickname("good nickname")
print([x.nickname() for x in foo.bars()])
