#include "mat2.h"

#include "bn_math.h"

namespace nos {
    mat2 mat2::identity(1, 0, 0, 1);

    mat2 mat2::scale(bn::fixed x, bn::fixed y) {
        return mat2(x, 0, 0, y);
    }

    mat2 mat2::scale_inverse(bn::fixed x, bn::fixed y) {
        return scale(1/x, 1/y);
    }

    mat2 mat2::rotate(bn::fixed degrees) {
        return mat2(
            bn::degrees_lut_cos(degrees),
            -bn::degrees_lut_sin(degrees),
            bn::degrees_lut_sin(degrees),
            bn::degrees_lut_cos(degrees)
        );
    }

    mat2 mat2::rotate_inverse(bn::fixed degrees) {
        return rotate(360 - degrees);
    }

    mat2 operator*(const mat2& lhs, const mat2& rhs) {
        return mat2(
            lhs.a*rhs.a + lhs.b*rhs.c,
            lhs.a*rhs.b + lhs.b*rhs.d,
            lhs.c*rhs.a + lhs.d*rhs.c,
            lhs.c*rhs.b + lhs.d*rhs.d
        );
    }

    mat2 operator/(const mat2& lhs, const bn::fixed_t<16> rhs) {
        return mat2(lhs.a/rhs, lhs.b/rhs, lhs.c/rhs, lhs.d/rhs);
    }

    mat2 operator-(const mat2& lhs) {
        return mat2(-lhs.a, -lhs.b, -lhs.c, -lhs.d);
    }

    mat2 inverse(const mat2& m) {
        bn::fixed denominator = m.a*m.d - m.b*m.c;

        // For now, it seems fine to just do this.
        if (denominator == 0) return mat2::identity;

        return mat2(m.d, -m.b, -m.c, m.a) / denominator;
    }
}

