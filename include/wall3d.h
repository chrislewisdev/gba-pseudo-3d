#pragma once

#include "sprite3d.h"

namespace sp3d {
    class wall3d : public sprite3d {
        private:
            vec3 facing;

        public:
            wall3d(vec3 position, vec3 facing);

            void update(camera3d& camera);
    };
}
