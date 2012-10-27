#ifndef LAZYGL_SHARED_NAME_HH
#define LAZYGL_SHARED_NAME_HH

#include <atomic>

namespace lazygl {

template <typename Object>
struct shared_name {
public:
    explicit shared_name (GLuint name)
                : m_name(name), m_refcount(new std::atomic_uint) {
        // initialization is not atomic--store is
        m_refcount->store(0);
        printf("shared_name(%d)\n", name);
    }

    shared_name (const shared_name& other) {
        other.m_refcount->fetch_add(1);
        m_name = other.m_name;
        m_refcount = other.m_refcount;
        printf("shared_name(shared_name)\n");
    }

    ~shared_name () {
        printf("~shared_name()\n");
        if (!m_refcount->fetch_sub(1)) {
            printf("deleting!\n");
            Object::delete_name(m_name);
            delete m_refcount;
        }
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
