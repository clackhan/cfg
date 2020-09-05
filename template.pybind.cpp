#include <pybind11/pybind11.h>
#include "{{ util.module_cfg_header_name(module) }}"

PYBIND11_MODULE({{ python_module_name }}, m) {
{% if util.module_has_package(module) %}
  using namespace {{ "::".join(util.module_package_list(module)) }}::cfg;
{% else %}
  using namespace cfg;
{% endif %}
{% for cls in util.module_message_types(module) %}
{% for field in util.message_type_fields(cls) %}
{# no duplicated python class registered for each repeated field type #}
{% if util.field_has_repeated_label(field) and util.add_visited_repeated_field_type_name(field) %}
  {
    pybind11::class_<Const{{ util.field_repeated_container_name(field) }}, std::shared_ptr<Const{{ util.field_repeated_container_name(field) }}>> registry(m, "Const{{ util.field_repeated_container_name(field) }}");
    registry.def("__len__", &Const{{ util.field_repeated_container_name(field) }}::size);
    // a python analogue to const_cast<T>()
    registry.def("ConstCast", &Const{{ util.field_repeated_container_name(field) }}::__ConstCast__);
{% if util.field_is_message_type(field) %}
    registry.def("__getitem__", (::std::shared_ptr<Const{{ util.field_type_name(field) }}> (Const{{ util.field_repeated_container_name(field) }}::*)(::std::size_t) const)&Const{{ util.field_repeated_container_name(field) }}::__SharedConst__);
    registry.def("Get", (::std::shared_ptr<Const{{ util.field_type_name(field) }}> (Const{{ util.field_repeated_container_name(field) }}::*)(::std::size_t) const)&Const{{ util.field_repeated_container_name(field) }}::__SharedConst__);
{% else %}
    registry.def("__getitem__", &Const{{ util.field_repeated_container_name(field) }}::Get);
    registry.def("Get", &Const{{ util.field_repeated_container_name(field) }}::Get);
{% endif %}
  }
  {
    pybind11::class_<{{ util.field_repeated_container_name(field) }}, std::shared_ptr<{{ util.field_repeated_container_name(field) }}>> registry(m, "{{ util.field_repeated_container_name(field) }}");
    registry.def("__len__", &{{ util.field_repeated_container_name(field) }}::size);
    registry.def("__setitem__", &{{ util.field_repeated_container_name(field) }}::Set);
    registry.def("Set", &{{ util.field_repeated_container_name(field) }}::Set);
    registry.def("Clear", &{{ util.field_repeated_container_name(field) }}::Clear);
    registry.def("CopyFrom", (void ({{ util.field_repeated_container_name(field) }}::*)(const Const{{ util.field_repeated_container_name(field) }}&))&{{ util.field_repeated_container_name(field) }}::CopyFrom);
    registry.def("CopyFrom", (void ({{ util.field_repeated_container_name(field) }}::*)(const {{ util.field_repeated_container_name(field) }}&))&{{ util.field_repeated_container_name(field) }}::CopyFrom);
    registry.def("Add", (void ({{ util.field_repeated_container_name(field) }}::*)(const {{ util.field_type_name(field) }}&))&{{ util.field_repeated_container_name(field) }}::Add);
{% if util.field_is_message_type(field) %}
    registry.def("__getitem__", (::std::shared_ptr<{{ util.field_type_name(field) }}> ({{ util.field_repeated_container_name(field) }}::*)(::std::size_t))&{{ util.field_repeated_container_name(field) }}::__SharedMutable__);
    registry.def("Get", (::std::shared_ptr<{{ util.field_type_name(field) }}> ({{ util.field_repeated_container_name(field) }}::*)(::std::size_t))&{{ util.field_repeated_container_name(field) }}::__SharedMutable__);
    registry.def("Add", &{{ util.field_repeated_container_name(field) }}::__SharedAdd__);
{% else %}
    registry.def("__getitem__", &{{ util.field_repeated_container_name(field) }}::Get);
    registry.def("Get", &{{ util.field_repeated_container_name(field) }}::Get);
{% endif %}
  }
{% endif %}{# field type #}
{% endfor %}{# field #}
{% endfor %}{# cls #}
{% for cls in util.module_message_types(module) %}
  {
    pybind11::class_<Const{{ cls.name }}, std::shared_ptr<Const{{ cls.name }}>> registry(m, "Const{{ cls.name }}");
    // a python analogue to const_cast<T>()
    registry.def("ConstCast", &Const{{ cls.name }}::__ConstCast__);
{% for field in util.message_type_fields(cls) %}

{% if util.field_has_required_or_optional_label(field) %}
    registry.def("has_{{ util.field_name(field) }}", &Const{{ cls.name }}::has_{{ util.field_name(field) }});
{% if util.field_is_message_type(field) %}
    registry.def("{{ util.field_name(field) }}", &Const{{ cls.name }}::shared_const_{{ util.field_name(field) }});
{% else %}
    registry.def("{{ util.field_name(field) }}", &Const{{ cls.name }}::{{ util.field_name(field) }});
{% endif %}
{% elif util.field_has_repeated_label(field) %}
    registry.def("{{ util.field_name(field) }}_size", &Const{{ cls.name }}::{{ util.field_name(field) }}_size);
    registry.def("{{ util.field_name(field) }}", (::std::shared_ptr<Const{{ util.field_repeated_container_name(field) }}> (Const{{ cls.name }}::*)())&Const{{ cls.name }}::shared_const_{{ util.field_name(field) }});
{% if util.field_is_message_type(field) %}
    registry.def("{{ util.field_name(field) }}", (::std::shared_ptr<Const{{ util.field_type_name(field) }}> (Const{{ cls.name }}::*)(::std::size_t))&Const{{ cls.name }}::shared_const_{{ util.field_name(field) }});
{% else %}
    registry.def("{{ util.field_name(field) }}", (const {{ util.field_type_name(field) }}& (Const{{ cls.name }}::*)(::std::size_t) const)&Const{{ cls.name }}::{{ util.field_name(field) }});
{% endif %}
{% endif %}{# field label type #}
{% endfor %}{# field #}
  }
  {
    pybind11::class_<{{ cls.name }}, std::shared_ptr<{{ cls.name }}>> registry(m, "{{ cls.name }}");
    registry.def(pybind11::init<>());
    registry.def("Clear", &{{ cls.name }}::Clear);
    registry.def("CopyFrom", (void ({{ cls.name }}::*)(const Const{{ cls.name }}&))&{{ cls.name }}::CopyFrom);
    registry.def("CopyFrom", (void ({{ cls.name }}::*)(const {{ cls.name }}&))&{{ cls.name }}::CopyFrom);
{% for field in util.message_type_fields(cls) %}

{% if util.field_has_required_or_optional_label(field) %}
    registry.def("has_{{ util.field_name(field) }}", &{{ cls.name }}::has_{{ util.field_name(field) }});
    registry.def("clear_{{ util.field_name(field) }}", &{{ cls.name }}::clear_{{ util.field_name(field) }});
{% if util.field_is_message_type(field) %}
    registry.def("{{ util.field_name(field) }}", &{{ cls.name }}::shared_const_{{ util.field_name(field) }});
    registry.def("mutable_{{ util.field_name(field) }}", &{{ cls.name }}::shared_mutable_{{ util.field_name(field) }});
{% else %}
    registry.def("{{ util.field_name(field) }}", &{{ cls.name }}::{{ util.field_name(field) }});
    registry.def("set_{{ util.field_name(field) }}", &{{ cls.name }}::set_{{ util.field_name(field) }});
{% endif %}
{% elif util.field_has_repeated_label(field) %}
    registry.def("{{ util.field_name(field) }}_size", &{{ cls.name }}::{{ util.field_name(field) }}_size);
    registry.def("clear_{{ util.field_name(field) }}", &{{ cls.name }}::clear_{{ util.field_name(field) }});
    registry.def("mutable_{{ util.field_name(field) }}", (::std::shared_ptr<{{ util.field_repeated_container_name(field) }}> ({{ cls.name }}::*)())&{{ cls.name }}::shared_mutable_{{ util.field_name(field) }});
    registry.def("{{ util.field_name(field) }}", (::std::shared_ptr<Const{{ util.field_repeated_container_name(field) }}> ({{ cls.name }}::*)())&{{ cls.name }}::shared_const_{{ util.field_name(field) }});
{% if util.field_is_message_type(field) %}
    registry.def("{{ util.field_name(field) }}", (::std::shared_ptr<Const{{ util.field_type_name(field) }}> ({{ cls.name }}::*)(::std::size_t))&{{ cls.name }}::shared_const_{{ util.field_name(field) }});
    registry.def("mutable_{{ util.field_name(field) }}", (::std::shared_ptr<{{ util.field_type_name(field) }}> ({{ cls.name }}::*)(::std::size_t))&{{ cls.name }}::shared_mutable_{{ util.field_name(field) }});
{% else %}
    registry.def("{{ util.field_name(field) }}", (const {{ util.field_type_name(field) }}& ({{ cls.name }}::*)(::std::size_t) const)&{{ cls.name }}::{{ util.field_name(field) }});
    registry.def("add_{{ util.field_name(field) }}", &{{ cls.name }}::add_{{ util.field_name(field) }});
{% endif %}{# field message type #}
{% endif %}{# field label type #}
{% endfor %}{# field #}
  }
{% endfor %}{# cls #}
}
