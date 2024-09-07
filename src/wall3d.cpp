#include "wall3d.h"

#include "bn_sprite_items_wall_exterior.h"

namespace sp3d {
    wall3d::wall3d(vec3 p, vec3 f) :
        sprite3d(bn::sprite_items::wall_exterior),
        facing(f)
    {
        position = p;
    }

    void wall3d::update(sp3d::camera3d& camera) {
        if (sprite.has_value()) {
            bool is_visible = facing.dot(camera.get_direction()) < 0;
            sprite->set_visible(is_visible);
            if (facing.y != 0) {
                sprite->set_affine_mat(camera.get_affine_transform_ptr_xz());
            } else {
                sprite->set_affine_mat(camera.get_affine_transform_ptr_yz());
            }
        }

        sprite3d::update(camera);
    }
}
