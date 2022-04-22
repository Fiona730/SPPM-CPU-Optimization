#include "warping.h"

Vector2f square_to_uniform_disk(Vector2f sample) {
    float phi = 2 * M_PI * sample.x, r = sqrtf(sample.y);
    return (Vector2f) {r * cosf(phi), r * sinf(phi)};
}

Vector square_to_cosine_hemisphere(Vector2f sample, const Vector *ez) {
    Vector2f d = square_to_uniform_disk(sample);
    float z = sqrtf(fmaxf(0.0f, 1 - d.x * d.x - d.y * d.y));
    // normal = z axis
    Vector ex = fabsf(vv_dot(ez, &UNIT_Y)) < 0.9 ? vv_cross(ez, &UNIT_Y) : vv_cross(ez, &UNIT_Z);
    v_normalize(&ex);
    Vector ey = vv_cross(ez, &ex);
    Vector d_world = vs_mul(&ex, d.x);
    vvs_fmaeq(&d_world, &ey, d.y);
    vvs_fmaeq(&d_world, ez, z);
    return d_world;
}

Vector square_to_uniform_sphere(Vector2f sample) {
    float phi = 2 * M_PI * sample.x, z = 1 - 2 * sample.y, r = sqrtf(1 - z * z);
    return (Vector) {r * cosf(phi), r * sinf(phi), z};
}
