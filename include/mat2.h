#pragma once

#include "bn_core.h"

namespace sp3d {
    class mat2 {
        public:
            bn::fixed_t<16> a, b, c, d;

            static mat2 identity;

            mat2() {}
            mat2(bn::fixed _a, bn::fixed _b, bn::fixed _c, bn::fixed _d): a(_a), b(_b), c(_c), d(_d) {}

            static mat2 scale(bn::fixed x, bn::fixed y);
            static mat2 scale_inverse(bn::fixed x, bn::fixed y);
            static mat2 rotate(bn::fixed degrees);
            static mat2 rotate_inverse(bn::fixed degrees);
    };

    mat2 operator*(const mat2& lhs, const mat2& rhs);
    mat2 operator/(const mat2& lhs, const bn::fixed_t<16> rhs);
    mat2 operator-(const mat2& lhs);
    mat2 inverse(const mat2& m);
}

