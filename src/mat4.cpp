#include "mat4.h"

namespace sp3d {
    mat4 mat4::identity(vec3(1, 0, 0), vec3(0, 1, 0), vec3(0, 0, 1), vec3(0, 0, 0));

    mat4 operator*(const mat4& lhs, const mat4& rhs) {
        vec3 a = vec3(
            lhs.a.x*rhs.a.x + lhs.a.y*rhs.b.x + lhs.a.z*rhs.c.x,
            lhs.a.x*rhs.a.y + lhs.a.y*rhs.b.y + lhs.a.z*rhs.c.y,
            lhs.a.x*rhs.a.z + lhs.a.y*rhs.b.z + lhs.a.z*rhs.c.z
        );
        vec3 b = vec3(
            lhs.b.x*rhs.a.x + lhs.b.y*rhs.b.x + lhs.b.z*rhs.c.x,
            lhs.b.x*rhs.a.y + lhs.b.y*rhs.b.y + lhs.b.z*rhs.c.y,
            lhs.b.x*rhs.a.z + lhs.b.y*rhs.b.z + lhs.b.z*rhs.c.z
        );
        vec3 c = vec3(
            lhs.c.x*rhs.a.x + lhs.c.y*rhs.b.x + lhs.c.z*rhs.c.x,
            lhs.c.x*rhs.a.y + lhs.c.y*rhs.b.y + lhs.c.z*rhs.c.y,
            lhs.c.x*rhs.a.z + lhs.c.y*rhs.b.z + lhs.c.z*rhs.c.z
        );
        vec3 d = vec3(
            lhs.d.x*rhs.a.x + lhs.d.y*rhs.b.x + lhs.d.z*rhs.c.x + rhs.d.x,
            lhs.d.x*rhs.a.y + lhs.d.y*rhs.b.y + lhs.d.z*rhs.c.y + rhs.d.y,
            lhs.d.x*rhs.a.z + lhs.d.y*rhs.b.z + lhs.d.z*rhs.c.z + rhs.d.z
        );

        return mat4(a, b, c, d);
    }

    vec3 operator*(const vec3& lhs, const mat4& rhs) {
        return vec3(
            lhs.x*rhs.a.x + lhs.y*rhs.b.x + lhs.z*rhs.c.x + rhs.d.x,
            lhs.x*rhs.a.y + lhs.y*rhs.b.y + lhs.z*rhs.c.y + rhs.d.y,
            lhs.x*rhs.a.z + lhs.y*rhs.b.z + lhs.z*rhs.c.z + rhs.d.z
        );
    }
}

