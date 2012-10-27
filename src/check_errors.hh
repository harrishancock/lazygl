#ifndef LAZYGL_CHECK_ERRORS_HH
#define LAZYGL_CHECK_ERRORS_HH

#include <boost/preprocessor/stringize.hpp>

#ifndef LAZYGL_NDEBUG
#define LAZYGL_CHECK_ERRORS(symbol) \
    ::lazygl::check_errors(__FILE__, __LINE__, BOOST_PP_STRINGIZE(symbol));
#else
#define LAZYGL_CHECK_ERRORS(symbol)
#endif

namespace lazygl {

void check_errors (const char* file, int line, const char* symbol) {
    /* TODO */
}

} // namespace lazygl

#endif
