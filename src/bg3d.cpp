#include "bg3d.h"

#include "bn_affine_bg_item.h"

namespace nos {
    bg3d::bg3d(const bn::affine_bg_item& bg_item, int _height) :
        bg(bg_item.create_bg(0, 0)),
        height(_height)
    {
    bg.set_wrapping_enabled(false);     
    }

    void bg3d::update(nos::camera3d& camera) {
        vec3 bg_position = position - camera.get_position() * camera.get_world_transform() * camera.get_scale();
        bg.set_position(bg_position.x, -bg_position.y + bn::degrees_lut_sin(camera.get_pitch()) * camera.get_scale() * -height);
        bg.set_mat_attributes(camera.get_affine_transform_xy());
    }
}
