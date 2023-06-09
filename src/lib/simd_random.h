#ifndef TEAM32_SIMD_RANDOM_C_H
#define TEAM32_SIMD_RANDOM_C_H

#include "common.h"

#ifdef __arm64__

#define SIMD_RAND_MAX RAND_MAX

#else

#include <immintrin.h>
#include <stdint.h>

#define SIMD_RAND_MAX_FULL 0x7fffffff
#define SIMD_RAND_MAX 0xffffffff

typedef struct{
    uint32_t states[64] __attribute__((aligned(64)));
    int cur_state;
} SimdRandomState;

extern SimdRandomState simd_random_state_get_arb;
extern SimdRandomState simd_random_state_get_full;

#endif

static inline uint32_t simd_rand(){
#ifdef __arm64__
    // Fallback on ARM mac
    return (uint32_t) rand();
#else
    if(simd_random_state_get_arb.cur_state < 64){
        return simd_random_state_get_arb.states[simd_random_state_get_arb.cur_state++];
    }else{
        __m256i cur_state0, t00, t10, t20, t30, t40, t50;
        __m256i cur_state1, t01, t11, t21, t31, t41, t51;
        __m256i cur_state2, t02, t12, t22, t32, t42, t52;
        __m256i cur_state3, t03, t13, t23, t33, t43, t53;
        __m256i cur_state4, t04, t14, t24, t34, t44, t54;
        __m256i cur_state5, t05, t15, t25, t35, t45, t55;
        __m256i cur_state6, t06, t16, t26, t36, t46, t56;
        __m256i cur_state7, t07, t17, t27, t37, t47, t57;
        cur_state0 = _mm256_load_si256((__m256i*)&simd_random_state_get_arb.states[0]);
        cur_state1 = _mm256_load_si256((__m256i*)&simd_random_state_get_arb.states[8]);
        cur_state2 = _mm256_load_si256((__m256i*)&simd_random_state_get_arb.states[16]);
        cur_state3 = _mm256_load_si256((__m256i*)&simd_random_state_get_arb.states[24]);
        cur_state4 = _mm256_load_si256((__m256i*)&simd_random_state_get_arb.states[32]);
        cur_state5 = _mm256_load_si256((__m256i*)&simd_random_state_get_arb.states[40]);
        cur_state6 = _mm256_load_si256((__m256i*)&simd_random_state_get_arb.states[48]);
        cur_state7 = _mm256_load_si256((__m256i*)&simd_random_state_get_arb.states[56]);
        t00 = _mm256_slli_epi32(cur_state0, 13);
        t01 = _mm256_slli_epi32(cur_state1, 13);
        t02 = _mm256_slli_epi32(cur_state2, 13);
        t03 = _mm256_slli_epi32(cur_state3, 13);
        t04 = _mm256_slli_epi32(cur_state4, 13);
        t05 = _mm256_slli_epi32(cur_state5, 13);
        t06 = _mm256_slli_epi32(cur_state6, 13);
        t07 = _mm256_slli_epi32(cur_state7, 13);
        t10 = _mm256_xor_si256(cur_state0, t00);
        t11 = _mm256_xor_si256(cur_state1, t01);
        t12 = _mm256_xor_si256(cur_state2, t02);
        t13 = _mm256_xor_si256(cur_state3, t03);
        t14 = _mm256_xor_si256(cur_state4, t04);
        t15 = _mm256_xor_si256(cur_state5, t05);
        t16 = _mm256_xor_si256(cur_state6, t06);
        t17 = _mm256_xor_si256(cur_state7, t07);
        t20 = _mm256_srli_epi32(t10, 17);
        t21 = _mm256_srli_epi32(t11, 17);
        t22 = _mm256_srli_epi32(t12, 17);
        t23 = _mm256_srli_epi32(t13, 17);
        t24 = _mm256_srli_epi32(t14, 17);
        t25 = _mm256_srli_epi32(t15, 17);
        t26 = _mm256_srli_epi32(t16, 17);
        t27 = _mm256_srli_epi32(t17, 17);
        t30 = _mm256_xor_si256(t10, t20);
        t31 = _mm256_xor_si256(t11, t21);
        t32 = _mm256_xor_si256(t12, t22);
        t33 = _mm256_xor_si256(t13, t23);
        t34 = _mm256_xor_si256(t14, t24);
        t35 = _mm256_xor_si256(t15, t25);
        t36 = _mm256_xor_si256(t16, t26);
        t37 = _mm256_xor_si256(t17, t27);
        t40 = _mm256_slli_epi32(t30, 5);
        t41 = _mm256_slli_epi32(t31, 5);
        t42 = _mm256_slli_epi32(t32, 5);
        t43 = _mm256_slli_epi32(t33, 5);
        t44 = _mm256_slli_epi32(t34, 5);
        t45 = _mm256_slli_epi32(t35, 5);
        t46 = _mm256_slli_epi32(t36, 5);
        t47 = _mm256_slli_epi32(t37, 5);
        t50 = _mm256_xor_si256(t30, t40);
        t51 = _mm256_xor_si256(t31, t41);
        t52 = _mm256_xor_si256(t32, t42);
        t53 = _mm256_xor_si256(t33, t43);
        t54 = _mm256_xor_si256(t34, t44);
        t55 = _mm256_xor_si256(t35, t45);
        t56 = _mm256_xor_si256(t36, t46);
        t57 = _mm256_xor_si256(t37, t47);
        _mm256_store_si256((__m256i*)&simd_random_state_get_arb.states[0], t50);
        _mm256_store_si256((__m256i*)&simd_random_state_get_arb.states[8], t51);
        _mm256_store_si256((__m256i*)&simd_random_state_get_arb.states[16], t52);
        _mm256_store_si256((__m256i*)&simd_random_state_get_arb.states[24], t53);
        _mm256_store_si256((__m256i*)&simd_random_state_get_arb.states[32], t54);
        _mm256_store_si256((__m256i*)&simd_random_state_get_arb.states[40], t55);
        _mm256_store_si256((__m256i*)&simd_random_state_get_arb.states[48], t56);
        _mm256_store_si256((__m256i*)&simd_random_state_get_arb.states[56], t57);

        simd_random_state_get_arb.cur_state = 1;
        return simd_random_state_get_arb.states[0];
    }
#endif
}

#ifndef __arm64__
static inline __m256i simd_rand_full(){
    if(simd_random_state_get_full.cur_state < 8){
        int prev_state = simd_random_state_get_full.cur_state++;
        return _mm256_load_si256((__m256i*)&simd_random_state_get_full.states[8*prev_state]);
    }else{
        __m256i cur_state0, t00, t10, t20, t30, t40, t50;
        __m256i cur_state1, t01, t11, t21, t31, t41, t51;
        __m256i cur_state2, t02, t12, t22, t32, t42, t52;
        __m256i cur_state3, t03, t13, t23, t33, t43, t53;
        __m256i cur_state4, t04, t14, t24, t34, t44, t54;
        __m256i cur_state5, t05, t15, t25, t35, t45, t55;
        __m256i cur_state6, t06, t16, t26, t36, t46, t56;
        __m256i cur_state7, t07, t17, t27, t37, t47, t57;
        cur_state0 = _mm256_load_si256((__m256i*)&simd_random_state_get_full.states[0]);
        cur_state1 = _mm256_load_si256((__m256i*)&simd_random_state_get_full.states[8]);
        cur_state2 = _mm256_load_si256((__m256i*)&simd_random_state_get_full.states[16]);
        cur_state3 = _mm256_load_si256((__m256i*)&simd_random_state_get_full.states[24]);
        cur_state4 = _mm256_load_si256((__m256i*)&simd_random_state_get_full.states[32]);
        cur_state5 = _mm256_load_si256((__m256i*)&simd_random_state_get_full.states[40]);
        cur_state6 = _mm256_load_si256((__m256i*)&simd_random_state_get_full.states[48]);
        cur_state7 = _mm256_load_si256((__m256i*)&simd_random_state_get_full.states[56]);
        t00 = _mm256_slli_epi32(cur_state0, 13);
        t01 = _mm256_slli_epi32(cur_state1, 13);
        t02 = _mm256_slli_epi32(cur_state2, 13);
        t03 = _mm256_slli_epi32(cur_state3, 13);
        t04 = _mm256_slli_epi32(cur_state4, 13);
        t05 = _mm256_slli_epi32(cur_state5, 13);
        t06 = _mm256_slli_epi32(cur_state6, 13);
        t07 = _mm256_slli_epi32(cur_state7, 13);
        t10 = _mm256_xor_si256(cur_state0, t00);
        t11 = _mm256_xor_si256(cur_state1, t01);
        t12 = _mm256_xor_si256(cur_state2, t02);
        t13 = _mm256_xor_si256(cur_state3, t03);
        t14 = _mm256_xor_si256(cur_state4, t04);
        t15 = _mm256_xor_si256(cur_state5, t05);
        t16 = _mm256_xor_si256(cur_state6, t06);
        t17 = _mm256_xor_si256(cur_state7, t07);
        t20 = _mm256_srli_epi32(t10, 17);
        t21 = _mm256_srli_epi32(t11, 17);
        t22 = _mm256_srli_epi32(t12, 17);
        t23 = _mm256_srli_epi32(t13, 17);
        t24 = _mm256_srli_epi32(t14, 17);
        t25 = _mm256_srli_epi32(t15, 17);
        t26 = _mm256_srli_epi32(t16, 17);
        t27 = _mm256_srli_epi32(t17, 17);
        t30 = _mm256_xor_si256(t10, t20);
        t31 = _mm256_xor_si256(t11, t21);
        t32 = _mm256_xor_si256(t12, t22);
        t33 = _mm256_xor_si256(t13, t23);
        t34 = _mm256_xor_si256(t14, t24);
        t35 = _mm256_xor_si256(t15, t25);
        t36 = _mm256_xor_si256(t16, t26);
        t37 = _mm256_xor_si256(t17, t27);
        t40 = _mm256_slli_epi32(t30, 5);
        t41 = _mm256_slli_epi32(t31, 5);
        t42 = _mm256_slli_epi32(t32, 5);
        t43 = _mm256_slli_epi32(t33, 5);
        t44 = _mm256_slli_epi32(t34, 5);
        t45 = _mm256_slli_epi32(t35, 5);
        t46 = _mm256_slli_epi32(t36, 5);
        t47 = _mm256_slli_epi32(t37, 5);
        t50 = _mm256_xor_si256(t30, t40);
        t51 = _mm256_xor_si256(t31, t41);
        t52 = _mm256_xor_si256(t32, t42);
        t53 = _mm256_xor_si256(t33, t43);
        t54 = _mm256_xor_si256(t34, t44);
        t55 = _mm256_xor_si256(t35, t45);
        t56 = _mm256_xor_si256(t36, t46);
        t57 = _mm256_xor_si256(t37, t47);
        _mm256_store_si256((__m256i*)&simd_random_state_get_full.states[0], t50);
        _mm256_store_si256((__m256i*)&simd_random_state_get_full.states[8], t51);
        _mm256_store_si256((__m256i*)&simd_random_state_get_full.states[16], t52);
        _mm256_store_si256((__m256i*)&simd_random_state_get_full.states[24], t53);
        _mm256_store_si256((__m256i*)&simd_random_state_get_full.states[32], t54);
        _mm256_store_si256((__m256i*)&simd_random_state_get_full.states[40], t55);
        _mm256_store_si256((__m256i*)&simd_random_state_get_full.states[48], t56);
        _mm256_store_si256((__m256i*)&simd_random_state_get_full.states[56], t57);

        simd_random_state_get_full.cur_state = 1;
        return t50;
    }
}
#endif

static inline void simd_seed(int seed){
    srand(seed);
#ifndef __arm64__
    simd_random_state_get_arb.cur_state = 64;
    for(int i = 0; i < 64; i++){
        simd_random_state_get_arb.states[i] = rand();
    }

    simd_random_state_get_full.cur_state = 8;
    for(int i = 0; i < 64; i++){
        simd_random_state_get_full.states[i] = rand();
    }
#endif
}
#endif //TEAM32_SIMD_RANDOM_C_H
