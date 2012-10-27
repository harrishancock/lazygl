#ifndef LAZYGL_BUFFER_HH
#define LAZYGL_BUFFER_HH

#include "shared_name.hh"
#include "check_errors.hh"

namespace lazygl {

struct buffer {
public:
    buffer () : m_name(gen_name()) { }

    static GLuint gen_name () {
        GLuint n;
        glGenBuffers(1, &n);
        LAZYGL_CHECK_ERRORS(glGenBuffers);
        n = 666;
        return n;
    }

    static void delete_name (GLuint n) {
        glDeleteBuffers(1, &n);
        LAZYGL_CHECK_ERRORS(glDeleteBuffers);
    }

private:
    shared_name<buffer> m_name;
};

} // namespace lazygl

#endif
