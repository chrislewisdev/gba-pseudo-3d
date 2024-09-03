#include "vec3.h"

#include "bn_math.h"

namespace sp3d {
    vec3 vec3::zero;
    vec3 vec3::right(1, 0, 0);
    vec3 vec3::up(0, 1, 0);
    vec3 vec3::forward(0, 0, 1);

    bn::fixed vec3::magnitude() const {
        return bn::sqrt(x*x + y*y + z*z);
    }

    bn::fixed vec3::magnitude_squared() const {
        return x*x + y*y + z*z;
    }

    bn::fixed vec3::dot(const vec3& rhs) const {
        return x*rhs.x + y*rhs.y + z*rhs.z;
    }

    vec3 vec3::cross(const vec3& rhs) const {
        return vec3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
    }

    bn::fixed_point vec3::to_point() const {
        return bn::fixed_point(x, z);
    }

    bool operator==(const vec3& lhs, const vec3& rhs) {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
    }

    vec3 operator+(const vec3& lhs, const vec3& rhs) {
        return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }

    vec3 operator-(const vec3& lhs, const vec3& rhs) {
        return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }

    vec3 operator*(const vec3& lhs, const bn::fixed& rhs) {
        return vec3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
    }

    vec3 operator/(const vec3& lhs, const bn::fixed& rhs) {
        return vec3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
    }

    vec3 operator-(const vec3& lhs) {
        return vec3(-lhs.x, -lhs.y, -lhs.z);
    }

    vec3 normalise(const vec3& v) {
        return v / v.magnitude();
    }
}
