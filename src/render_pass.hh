#ifndef LAZYGL_RENDER_PASS_HH
#define LAZYGL_RENDER_PASS_HH

namespace lazygl {

struct render_pass {
public:

private:
    std::shared_ptr<vertex_array> m_vao;
    std::shared_ptr<program> m_program;
    boost::variant<std::shared_ptr<transform_feedback>,
                   std::shared_ptr<framebuffer>> m_output;
};

} // namespace lazygl

#endif
