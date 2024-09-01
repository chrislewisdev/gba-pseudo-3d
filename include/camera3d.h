#pragma once

#include "bn_affine_mat_attributes.h"
#include "bn_sprite_affine_mat_ptr.h"

#include "vec3.h"
#include "mat4.h"

namespace nos {
    class camera3d {
        private:
            int pitch, heading;
            bn::fixed scale;
            vec3 position, direction, right_axis;
            mat4 world_transform;
            bn::affine_mat_attributes affine_transform_xz, affine_transform_xy, affine_transform_yz;
            bn::sprite_affine_mat_ptr affine_transform_ptr_xz, affine_transform_ptr_yz;

            void update_transform_xy();
            void update_transform_xz(const vec3& up_axis);
            void update_transform_yz(const vec3& up_axis);

        public:
            camera3d();

            int get_pitch() const;
            int get_heading() const;
            bn::fixed get_scale() const;
            const vec3& get_position() const;
            const vec3& get_direction() const;
            const vec3& get_right_axis() const;
            const mat4& get_world_transform() const;
            const bn::affine_mat_attributes& get_affine_transform_xy() const;
            const bn::affine_mat_attributes& get_affine_transform_xz() const;
            const bn::affine_mat_attributes& get_affine_transform_yz() const;
            const bn::sprite_affine_mat_ptr& get_affine_transform_ptr_xz() const;
            const bn::sprite_affine_mat_ptr& get_affine_transform_ptr_yz() const;

            void update_camera(const vec3& target, int pitch, int heading, bn::fixed scale);
            vec3 to_screen(const vec3& position);
    };
}
