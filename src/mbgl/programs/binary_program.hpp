#pragma once

#include <mbgl/gl/types.hpp>

#include <string>
#include <unordered_map>

namespace mbgl {

class BinaryProgram {
public:
    // Initialize a BinaryProgram object from a serialized represenation.
    BinaryProgram(std::string&& data);

    template <class NamedAttributeLocations, class NamedUniformLocations>
    BinaryProgram(gl::BinaryProgramFormat binaryFormat_,
                  std::string&& binaryCode_,
                  const std::string& binaryIdentifier_,
                  NamedAttributeLocations&& attributes_,
                  NamedUniformLocations&& uniforms_)
        : binaryFormat(binaryFormat_),
          binaryCode(std::move(binaryCode_)),
          binaryIdentifier(binaryIdentifier_),
          attributes(attributes_.begin(), attributes_.end()),
          uniforms(uniforms_.begin(), uniforms_.end()) {
    }

    std::string serialize() const;

    gl::BinaryProgramFormat format() const {
        return binaryFormat;
    }
    const std::string& code() const {
        return binaryCode;
    }
    const std::string& identifier() const {
        return binaryIdentifier;
    }
    gl::AttributeLocation attributeLocation(const std::string& name) const;
    gl::UniformLocation uniformLocation(const std::string& name) const;

private:
    gl::BinaryProgramFormat binaryFormat = 0;
    std::string binaryCode;
    std::string binaryIdentifier;
    std::unordered_map<std::string, gl::AttributeLocation> attributes;
    std::unordered_map<std::string, gl::UniformLocation> uniforms;
};

} // namespace mbgl
