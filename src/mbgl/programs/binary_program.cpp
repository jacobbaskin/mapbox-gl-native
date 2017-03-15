#include <mbgl/programs/binary_program.hpp>

#include <protozero/pbf_reader.hpp>
#include <protozero/pbf_writer.hpp>

template <class Binding>
static std::pair<std::string, Binding> parseBinding(protozero::pbf_reader&& pbf) {
    std::pair<std::string, Binding> binding;
    while (pbf.next()) {
        switch (pbf.tag()) {
        case 1: // format
            binding.first = pbf.get_string();
            break;
        case 2: // code
            binding.second = pbf.get_uint32();
            break;
        default:
            pbf.skip();
            break;
        }
    }
    return binding;
}

namespace mbgl {

BinaryProgram::BinaryProgram(std::string&& data) {
    bool hasFormat = false, hasCode = false;
    protozero::pbf_reader pbf(data);
    while (pbf.next()) {
        switch (pbf.tag()) {
        case 1: // format
            binaryFormat = pbf.get_uint32();
            hasFormat = true;
            break;
        case 2: // code
            binaryCode = pbf.get_bytes();
            hasCode = true;
            break;
        case 3: // variable
            attributes.insert(parseBinding<gl::AttributeLocation>(pbf.get_message()));
            break;
        case 4: // uniform
            uniforms.insert(parseBinding<gl::UniformLocation>(pbf.get_message()));
            break;
        case 5: // identifier
        default:
            binaryIdentifier = pbf.get_string();
            break;
        }
    }

    if (!hasFormat || !hasCode) {
        throw std::runtime_error("BinaryProgram is missing required fields");
    }
}

std::string BinaryProgram::serialize() const {
    std::string data;
    data.reserve(32 + binaryCode.size() + uniforms.size() * 32 + attributes.size() * 32);
    protozero::pbf_writer pbf(data);
    pbf.add_uint32(1 /* format */, binaryFormat);
    pbf.add_bytes(2 /* code */, binaryCode.data(), binaryCode.size());
    for (const auto& binding : attributes) {
        protozero::pbf_writer pbf_binding(pbf, 3 /* attribute */);
        pbf_binding.add_string(1 /* name */, binding.first);
        pbf_binding.add_uint32(2 /* value */, binding.second);
    }
    for (const auto& binding : uniforms) {
        protozero::pbf_writer pbf_binding(pbf, 4 /* uniform */);
        pbf_binding.add_string(1 /* name */, binding.first);
        pbf_binding.add_uint32(2 /* value */, binding.second);
    }
    if (!binaryIdentifier.empty()) {
        pbf.add_string(5 /* identifier */, binaryIdentifier);
    }
    return data;
}


gl::AttributeLocation BinaryProgram::attributeLocation(const std::string& name) const {
    auto it = attributes.find(name);
    if (it != attributes.end()) {
        return it->second;
    } else {
        return {};
    }
}

gl::UniformLocation BinaryProgram::uniformLocation(const std::string& name) const {
    auto it = uniforms.find(name);
    if (it != uniforms.end()) {
        return it->second;
    } else {
        return {};
    }
}

} // namespace mbgl
