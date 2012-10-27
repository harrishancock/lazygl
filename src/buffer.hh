#ifndef LAZYGL_BUFFER_HH
#define LAZYGL_BUFFER_HH

#include "check_errors.hh"

#include <cassert>

#include <utility>

namespace lazygl {

/**
 * Represent an OpenGL buffer object. The Target template parameter is used as
 * the initial binding target to allow the OpenGL driver to optimize the buffer
 * for its intended use. This specification in no way prevents the buffer from
 * being used with other buffer binding targets.
 *
 * TODO assess the code readability impact of specifying Target as a template
 * parameter, rather than a run-time constant. Also assess potential for code
 * bloat.
 */
template <GLenum Target>
struct buffer {
public:
    /* non-copyable */
    buffer (const buffer&) = delete;
    buffer& operator= (const buffer&) = delete;

    /* movable */
    buffer (buffer&& other) : m_name(0) noexcept {
        swap(*this, other);
    }

    buffer& operator= (buffer&& other) noexcept {
        swap(*this, other);
        return *this;
    }

    friend void swap (buffer& lhs, buffer& rhs) noexcept {
        using std::swap;
        swap(lhs.m_name, rhs.m_name);
    }

    //////////////////////////////////////////////////////////////////////////

    buffer () : m_name(0) noexcept {
        glGenBuffers(1, &m_name);
        LAZYGL_CHECK_ERRORS(glGenBuffers);
        assert(m_name);
        glBindBuffer(Target, m_name);
        LAZYGL_CHECK_ERRORS(glBindBuffer);
        glBindBuffer(Target, 0);
        LAZYGL_CHECK_ERRORS(glBindBuffer);
    }

    ~buffer () {
        glDeleteBuffers(1, &m_name);
        LAZYGL_CHECK_ERRORS(glDeleteBuffers);
    }

    //////////////////////////////////////////////////////////////////////////

    void allocate (size_t nbytes, GLenum usage, GLenum target=Target) {
        bind(target);
        glBufferData(target, nbytes, nullptr, usage);
        LAZYGL_CHECK_ERRORS(glBufferData);
    }

private:
    void bind (GLenum target) {
        glBindBuffer(target, m_name);
        LAZYGL_CHECK_ERRORS(glBindBuffer);
    }

    GLuint m_name;
};

} // namespace lazygl

#endif
