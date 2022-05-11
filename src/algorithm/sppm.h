#ifndef TEAM32_SPPM_H
#define TEAM32_SPPM_H

#include "vector.h"
#include "camera.h"
#include "scene.h"
#include "intersection.h"
#include "mesh.h"
#include "array.h"
#include "arrayfloat.h"
#include "arrayint.h"
#include "arraypointer.h"
#include "arrayvector.h"
#include "arrayfixed2d.h"
#include "bitmap.h"

#ifndef _SPPM_RADIUS_MULT
#define _SPPM_RADIUS_MULT 2.0
#endif

#ifndef _SPPM_RADIUS_TYPE
#define _SPPM_RADIUS_TYPE 0
#endif

struct PixelData {
    FloatArray radius;
    IntArray num_photons;
    VectorArray tau;
    VectorArray direct_radiance;

    // refreshed every iteration
    IntArray cur_photons;
    VectorArray cur_flux;

    // struct visible point
    VectorArray cur_vp_attenuation;
    Array cur_vp_intersection; // struct intersection
};

struct PixelDataLookup {
    size_t fixed_size;
    IntArray *hash_table;
    float grid_res;
    Vector3f grid_min;
    Vector3f grid_max;
};

struct SPPM {
    int num_iterations;
    int ray_max_depth;
    int num_photons;
    float initial_radius;
    float alpha;
    Vector background;
    Scene *scene;
    Camera *camera;
};

typedef struct VisiblePoint VisiblePoint;
typedef struct PixelData PixelData;
typedef struct PixelDataLookup PixelDataLookup;
typedef struct SPPM SPPM;

void sppm_init(SPPM *sppm, int num_iterations, int ray_max_depth, int photon_num_iter, float initial_radius, Scene *scene, Camera *camera,
               Vector background);

void sppm_pixel_data_init();

void sppm_pixel_data_lookup_init(PixelDataLookup *lookup, size_t init_size);

void sppm_pixel_data_lookup_assign(PixelDataLookup *lookup, float grid_size, Vector grid_min, Vector grid_max);

void sppm_pixel_data_lookup_clear(PixelDataLookup *lookup);

void sppm_pixel_data_lookup_free(PixelDataLookup *lookup);

void sppm_pixel_data_free(PixelData *pixel_datas);

size_t sppm_pixel_data_lookup_hash(PixelDataLookup *lookup, Vector3u *loc);

Vector3u sppm_pixel_data_lookup_to_grid(PixelDataLookup *lookup, Vector *loc);

void sppm_pixel_data_lookup_store(PixelDataLookup *lookup, Vector3u *loc_3d, int pd_index);

void sppm_build_pixel_data_lookup(PixelDataLookup *lookup, PixelData *pixel_datas, size_t H, size_t W);

void sppm_camera_pass_pixel(SPPM *sppm, int x, int y, Vector* direct_radiance, Vector* vp_attenuation, Intersection* vp_intersection);

void sppm_camera_pass(SPPM *sppm, PixelData *pixel_datas);

void sppm_photon_pass_photon(SPPM *sppm, PixelDataLookup *lookup, PixelData *pixel_datas);

void sppm_photon_pass(SPPM *sppm, PixelDataLookup *lookup, PixelData *pixel_datas);

void sppm_consolidate(PixelData *pixel_datas, float alpha, size_t H, size_t W);

void sppm_store(PixelData *pixel_datas, int num_iters, int num_photons, size_t H, size_t W, Bitmap *bitmap);

void sppm_render(SPPM *sppm, Bitmap *bitmap);

#endif //TEAM32_SPPM_H
