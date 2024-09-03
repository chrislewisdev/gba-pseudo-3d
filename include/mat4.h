#pragma once

#include "vec3.h"

namespace sp3d {
    class mat4 {
        public:
            vec3 a, b, c, d;

            static mat4 identity;

            mat4() {}
            mat4(vec3 _a, vec3 _b, vec3 _c, vec3 _d): a(_a), b(_b), c(_c), d(_d) {}
    };

    mat4 operator*(const mat4& lhs, const mat4& rhs);
    vec3 operator*(const vec3& lhs, const mat4& rhs); 
}

