#include <iostream>
#include "demo.cfg.h"
#include "demo.pb.h"

int main() {
  oneflow::cfg::Foo foo;
  oneflow::cfg::Bar bar;
  bar.set_name("Jack");
  bar.set_nickname("baobao");
  foo.set_name("Tom");
  std::cout << foo.name() << std::endl;
  std::string* name = foo.mutable_name();
  name = new std::string("Iris");
  std::cout << *name << std::endl;
  std::cout << foo.bar().nickname() << std::endl;
  foo.mutable_bar()->set_nickname("Jacky");
  std::cout << foo.bar().nickname() << std::endl;
  *foo.mutable_bar() = oneflow::cfg::Bar();
  std::cout << "After = " << foo.bar().nickname() << std::endl;
  std::cout << foo.optional_bar().nickname() << std::endl;
  foo.mutable_optional_bar()->set_nickname("Jacky");
  std::cout << foo.optional_bar().nickname() << std::endl;
  std::cout << "Just init ..." << std::endl;
  std::cout << foo.oneof_type_case() << std::endl;
  std::cout << foo.of_int_value() << std::endl;
  std::cout << foo.has_of_int_value() << std::endl;
  std::cout << "After set int value(20)  ..." << std::endl;
  foo.set_of_int_value(20);
  std::cout << foo.oneof_type_case() << std::endl;
  std::cout << foo.of_int_value() << std::endl;
  std::cout << foo.has_of_int_value() << std::endl;
  std::cout << "After set enum value(Enum::kEnum0)  ..." << std::endl;
  foo.set_of_enum_value(oneflow::cfg::Enum::kEnum0);
  std::cout << foo.oneof_type_case() << std::endl;
  std::cout << foo.of_enum_value() << std::endl;
  std::cout << foo.has_of_enum_value() << std::endl;
  std::cout << "After set string value(binbin)  ..." << std::endl;
  foo.set_of_string_value(std::string("binbin"));
  std::cout << foo.oneof_type_case() << std::endl;
  std::cout << foo.of_string_value() << std::endl;
  std::cout << foo.has_of_string_value() << std::endl;
  std::cout << "After set bytes value(xinqi)  ..." << std::endl;
  foo.set_of_bytes_value(std::string("xinqi"));
  std::cout << foo.oneof_type_case() << std::endl;
  std::cout << foo.of_bytes_value() << std::endl;
  std::cout << foo.has_of_bytes_value() << std::endl;
  std::cout << "After mutable_of_bar()..." << std::endl;
  foo.mutable_of_bar()->set_nickname("hongyu");
  std::cout << foo.oneof_type_case() << std::endl;
  std::cout << foo.of_bar().nickname() << std::endl;
  std::cout << foo.has_of_bar() << std::endl;
  std::cout << "After clear_of_bar()..." << std::endl;
  foo.clear_of_bar();
  std::cout << foo.oneof_type_case() << std::endl;

  std::cout << foo.map_int_int().size() << std::endl;
  auto* m = foo.mutable_map_int_int();
  (*m)[0] = 1;
  (*m)[2] = 3;
  auto& n = *foo.mutable_map_bar();
  n[1] = bar;

  for (const auto& pair: foo.map_int_int())
  {
    std::cout << pair.first << " " << pair.second << std::endl;
  }

  for (const auto& pair: foo.map_bar())
  {
    std::cout << pair.first << " " << pair.second.DebugString() << std::endl;
  }

  std::cout << foo.map_int_int().size() << std::endl;
  std::cout << foo.map_bar().size() << std::endl;
  std::cout << foo.DebugString() << std::endl;
  
  
  std::cout << "======================================" << std::endl;
  std::cout << "bar: " << std::endl;
  std::cout << bar.DebugString() << std::endl;
  std::cout << "--------------------------------------" << std::endl;
  oneflow::Bar pro_bar;
  bar.ToProto(&pro_bar);
  std::cout << "pro_bar: " << std::endl;
  std::cout << pro_bar.DebugString() << std::endl;
  std::cout << "--------------------------------------" << std::endl;
  oneflow::cfg::Bar cfg_bar(pro_bar);
  std::cout << "cfg_bar: " << std::endl;
  std::cout << cfg_bar.DebugString() << std::endl;

  std::cout << "======================================" << std::endl;
  std::cout << "foo: " << std::endl;
  std::cout << foo.DebugString() << std::endl;
  std::cout << "--------------------------------------" << std::endl;
  oneflow::Foo pro_foo;
  foo.ToProto(&pro_foo);
  std::cout << "pro_foo: " << std::endl;
  std::cout << pro_foo.DebugString() << std::endl;
  oneflow::cfg::Foo cfg_foo(pro_foo);
  std::cout << "--------------------------------------" << std::endl;
  std::cout << "cfg_foo: " << std::endl;
  std::cout << cfg_foo.DebugString() << std::endl;

  return 0;
}
