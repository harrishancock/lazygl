#include "check_errors.hh"

#include <cstdio>

namespace lazygl {

namespace {

const char* error_code_to_string (GLenum code) {
    switch (code) {
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY";
        case GL_STACK_UNDERFLOW:
            return "GL_STACK_UNDERFLOW";
        case GL_STACK_OVERFLOW:
            return "GL_STACK_OVERFLOW";
        default:
            break;
    }
    return "<unrecognized GL error>";
}

} // file scope namespace

void check_errors (const char* file, int line, const char* symbol) {
    auto err = glGetError();
    if (GL_NO_ERROR == err) {
        return;
    }

    fprintf(stderr, "%s:%d (after %s): %s\n", file, line, symbol,
            error_code_to_string(err));
    check_errors(file, line, symbol);
}

} // namespace lazygl
