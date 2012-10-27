#ifndef LAZYGL_BUFFER_HH
#define LAZYGL_BUFFER_HH

#include "shared_name.hh"
#include "check_errors.hh"

#include <cassert>

namespace lazygl {

struct buffer {
public:
    buffer () : m_name(gen_name()) {
        assert(m_name.get());
    }

    static GLuint gen_name () {
        GLuint n;
        glGenBuffers(1, &n);
        LAZYGL_CHECK_ERRORS(glGenBuffers);
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
