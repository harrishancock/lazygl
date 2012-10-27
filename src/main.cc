#include <GL/glew.h>
#include <cstdio>
#include "buffer.hh"

namespace gl = lazygl;

int main () {
    {
        gl::buffer b;
        {
            gl::buffer c (b);
        }
    }
    printf("done\n");
    return 0;
}
