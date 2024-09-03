#include "bg3d.h"

#include "bn_affine_bg_item.h"

namespace sp3d {
    bg3d::bg3d(const bn::affine_bg_item& bg_item, int _height) :
        bg(bg_item.create_bg(0, 0)),
        height(_height)
    {
        bg.set_wrapping_enabled(false);     
    }

    void bg3d::update(sp3d::camera3d& camera) {
        vec3 screen_position = camera.to_screen(position);
        bn::fixed perspective_offset = bn::degrees_lut_sin(camera.get_pitch()) * camera.get_scale() * -height;
        bg.set_position(screen_position.x, -screen_position.y + perspective_offset);
        bg.set_mat_attributes(camera.get_affine_transform_xy());
    }
}
