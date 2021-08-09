#include "renderers/masking-renderer.h"
#include "data-structures/grid.h"
#include "easylogging++.h"
#include <vector>

using namespace imaging;
using namespace math;
using namespace raytracer;
using namespace raytracer::renderers;


namespace
{
    class MaskingRenderer : public raytracer::renderers::_private_::RendererImplementation
    {
    public:
        MaskingRenderer(Renderer image_renderer, Renderer mask_renderer)
            : m_image_renderer(image_renderer)
            , m_mask_renderer(mask_renderer)
        {
            // NOP
        }

        std::shared_ptr<imaging::Bitmap> render(const Scene& scene) const override
        {
            auto image = m_image_renderer->render(scene);
            auto mask = m_mask_renderer->render(scene);

            CHECK(image->width() == mask->width());
            CHECK(image->height() == mask->height());

            auto& im = *image;
            auto& m = *mask;
            im.for_each_position([&im, &m](const Position2D& position) {
                im[position] *= m[position];
            });

            return image;
        }

    private:
        Renderer m_image_renderer;
        Renderer m_mask_renderer;
    };
}

Renderer raytracer::renderers::masking(Renderer image_renderer, Renderer mask_renderer)
{
    return Renderer(std::make_shared<MaskingRenderer>(image_renderer, mask_renderer));
}
