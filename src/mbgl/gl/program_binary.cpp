#include <mbgl/gl/vertex_array.hpp>

namespace mbgl {
namespace gl {

ExtensionFunction<
    void(GLuint program, GLsizei bufSize, GLsizei* length, GLenum* binaryFormat, GLvoid* binary)>
    GetProgramBinary({
        { "GL_OES_get_program_binary", "glGetProgramBinaryOES" },
        { "GL_ARB_get_program_binary", "glGetProgramBinary" },
    });

ExtensionFunction<void(GLuint program, GLenum binaryFormat, const GLvoid* binary, GLint length)>
    ProgramBinary({
        { "GL_OES_get_program_binary", "glProgramBinaryOES" },
        { "GL_ARB_get_program_binary", "glProgramBinary" },
    });

} // namespace gl
} // namespace mbgl
