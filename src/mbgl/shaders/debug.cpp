// NOTE: DO NOT CHANGE THIS FILE. IT IS AUTOMATICALLY GENERATED.

#include <mbgl/shaders/debug.hpp>

namespace mbgl {
namespace shaders {

const char* debug::name = "debug";
const char* debug::hash = "1a5c1afd97bd1393f19f19e68d533ab451b0e8d3";
const char* debug::vertexSource = R"MBGL_SHADER(
attribute vec2 a_pos;

uniform mat4 u_matrix;

void main() {
    gl_Position = u_matrix * vec4(a_pos, step(32767.0, a_pos.x), 1);
}

)MBGL_SHADER";
const char* debug::fragmentSource = R"MBGL_SHADER(
uniform lowp vec4 u_color;

void main() {
    gl_FragColor = u_color;
}

)MBGL_SHADER";

} // namespace shaders
} // namespace mbgl
