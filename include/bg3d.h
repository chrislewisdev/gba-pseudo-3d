#pragma once

#include "bn_affine_bg_ptr.h"

#include "vec3.h"
#include "camera3d.h"

namespace sp3d {
    class bg3d {
        private:
            vec3 position;
            bn::affine_bg_ptr bg;
            int height;

        public:
            bg3d(const bn::affine_bg_item& bg_item, int _height = 0, int priority = 3);
            void update(sp3d::camera3d& camera);
    };
}
