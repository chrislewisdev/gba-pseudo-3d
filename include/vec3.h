#pragma once

#include "bn_core.h"
#include "bn_fixed_point.h"

namespace sp3d {
    class vec3 {
        public:
            bn::fixed_t<16> x, y, z;

            static vec3 zero, up, right, forward;

            constexpr vec3() {}
            constexpr vec3(bn::fixed _x, bn::fixed _y, bn::fixed _z) : x(_x), y(_y), z(_z) {}

            bn::fixed magnitude() const; 
            bn::fixed magnitude_squared() const;
            bn::fixed dot(const vec3& rhs) const;
            vec3 cross(const vec3& rhs) const;

            bn::fixed_point to_point() const;
    };

    bool operator==(const vec3& lhs, const vec3& rhs);
    vec3 operator+(const vec3& lhs, const vec3& rhs);
    vec3 operator-(const vec3& lhs, const vec3& rhs); 
    vec3 operator*(const vec3& lhs, const bn::fixed& rhs);
    vec3 operator/(const vec3& lhs, const bn::fixed& rhs);
    vec3 operator-(const vec3& lhs); 
    vec3 normalise(const vec3& v); 
}

