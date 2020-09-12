#ifndef {{ util.module_proto_convert_header_macro_lock(module) }}
#define {{ util.module_proto_convert_header_macro_lock(module) }}

#include "{{ util.module_cfg_header_name(module) }}"
#include "{{ util.module_proto_header_name(module) }}"

namespace oneflow {

{% for enm in util.module_enum_types(module) %}

oneflow::{{ util.enum_name(enm) }} Cfg{{ util.enum_name(enm) }}ToProto{{ util.enum_name(enm) }}(const oneflow::cfg::{{ util.enum_name(enm) }}& cfg_enum);

oneflow::cfg::{{ util.enum_name(enm) }} Proto{{ util.enum_name(enm) }}ToCfg{{ util.enum_name(enm) }}(const oneflow::{{ util.enum_name(enm) }}& proto_enum);
{% endfor %}{# enms #}

{% for cls in util.module_message_types(module) %}

oneflow::cfg::{{ cls.name }} FromProto(const oneflow::{{ cls.name }}& proto_{{ cls.name.lower() }});

oneflow::{{ cls.name }} ToProto(const oneflow::cfg::{{ cls.name }}& cfg_{{ cls.name.lower() }});
{% endfor %}{# cls #}

} // namespace oneflow

#endif  // {{ util.module_proto_convert_header_macro_lock(module) }}