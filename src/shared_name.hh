#ifndef LAZYGL_SHARED_NAME_HH
#define LAZYGL_SHARED_NAME_HH

#include <atomic>
#include <utility>

namespace lazygl {

template <typename Object>
struct shared_name {
public:
    explicit shared_name (GLuint name)
                : m_name(name), m_refcount(new std::atomic_uint) {
        m_refcount->store(0);
    }

    shared_name (shared_name&& other)
            : m_name(0), m_refcount(nullptr) noexcept {
        swap(*this, other);
    }

    shared_name (const shared_name& other)
            : m_name(other.m_name), m_refcount(other.m_refcount) noexcept {
        m_refcount->fetch_add(1);
    }

    ~shared_name () {
        /* null m_refcount means we aren't managing a name */
        if (m_refcount && !m_refcount->fetch_sub(1)) {
            printf("deleting!\n");
            Object::delete_name(m_name);
            delete m_refcount;
        }
    }

    shared_name& operator= (shared_name other) noexcept {
        swap(*this, other);
        return *this;
    }

    GLuint get () const {
        return m_name;
    }

    friend void swap (shared_name& lhs, shared_name& rhs) noexcept {
        using std::swap;

        swap(lhs.m_name, rhs.m_name);
        swap(lhs.m_refcount, rhs.m_refcount);
    }

private:
    GLuint m_name;
#if ATOMIC_INT_LOCK_FREE != 2
#warning std::atomic_uint may not be lock-free!
#endif
    std::atomic_uint* m_refcount;
};

} // namespace lazygl

#endif
