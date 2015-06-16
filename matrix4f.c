#include "matrix4f.h"
#include <math.h>
#include <stdio.h>

const static int M00 = 0;
const static int M01 = 4;
const static int M02 = 8;
const static int M03 = 12;
const static int M04 = 1;
const static int M05 = 5;
const static int M06 = 9;
const static int M07 = 13;
const static int M08 = 2;
const static int M09 = 6;
const static int M10 = 10;
const static int M11 = 14;
const static int M12 = 3;
const static int M13 = 7;
const static int M14 = 11;
const static int M15 = 15;

inline void copy(float mat[16], float out[16]) { 
    int i; 
    for(i=0; i<16; i++) {
        out[i] = mat[i];
    }
}

inline void showMatrix(float mat[16]) {
    int i=0;
    puts("matb----------------");
    for(i=0;i<16;i+=4) {
        printf("%f, %f, %f, %f\n",mat[i], mat[i+1], mat[i+2], mat[i+3]);
    }
    puts("----------------");
}

void Matrix4f_mul(float mata[16], float matb[16], float out[16]) {
    out[M00] = mata[M00]*matb[M00]+mata[M01]*matb[M04]+mata[M02]*matb[M08]+mata[M03]*matb[M12];
    out[M01] = mata[M00]*matb[M01]+mata[M01]*matb[M05]+mata[M02]*matb[M09]+mata[M03]*matb[M13];
    out[M02] = mata[M00]*matb[M02]+mata[M01]*matb[M06]+mata[M02]*matb[M10]+mata[M03]*matb[M14];
    out[M03] = mata[M00]*matb[M03]+mata[M01]*matb[M07]+mata[M02]*matb[M11]+mata[M03]*matb[M15];

    out[M04] = mata[M04]*matb[M00]+mata[M05]*matb[M04]+mata[M06]*matb[M08]+mata[M07]*matb[M12];
    out[M05] = mata[M04]*matb[M01]+mata[M05]*matb[M05]+mata[M06]*matb[M09]+mata[M07]*matb[M13];
    out[M06] = mata[M04]*matb[M02]+mata[M05]*matb[M06]+mata[M06]*matb[M10]+mata[M07]*matb[M14];
    out[M07] = mata[M04]*matb[M03]+mata[M05]*matb[M07]+mata[M06]*matb[M11]+mata[M07]*matb[M15];

    out[M08] = mata[M08]*matb[M00]+mata[M09]*matb[M04]+mata[M10]*matb[M08]+mata[M11]*matb[M12];
    out[M09] = mata[M08]*matb[M01]+mata[M09]*matb[M05]+mata[M10]*matb[M09]+mata[M11]*matb[M13];
    out[M10] = mata[M08]*matb[M02]+mata[M09]*matb[M06]+mata[M10]*matb[M10]+mata[M11]*matb[M14];
    out[M11] = mata[M08]*matb[M03]+mata[M09]*matb[M07]+mata[M10]*matb[M11]+mata[M11]*matb[M15];

    out[M12] = mata[M12]*matb[M00]+mata[M13]*matb[M04]+mata[M14]*matb[M08]+mata[M15]*matb[M12];
    out[M13] = mata[M12]*matb[M01]+mata[M13]*matb[M05]+mata[M14]*matb[M09]+mata[M15]*matb[M13];
    out[M14] = mata[M12]*matb[M02]+mata[M13]*matb[M06]+mata[M14]*matb[M10]+mata[M15]*matb[M14];
    out[M15] = mata[M12]*matb[M03]+mata[M13]*matb[M07]+mata[M14]*matb[M11]+mata[M15]*matb[M15];

    showMatrix(out);
}

void Matrix4f_identify(float mat[16]) {
    Matrix4f_identifyValue(mat, 1);
}

void Matrix4f_identifyValue(float mat[16], float val) {
    mat[M00] = val;
    mat[M05] = val;
    mat[M10] = val;
    mat[M15] = val;
}

/**
 * 4x4の行列を作成する.
 * @param out 長さ16の配列のポインタ
 */
void  Matrix4f_create(float out[16]) {
    int i=0;
    for(i=0;i<16;i++) {
        out[i] = 0;
    }
}

void Matrix4f_rotateZ(float out[16], float angle) {
    float mat[16], matb[16];
    Matrix4f_create(mat);
    mat[M00] = cos(angle); mat[1] = sin(angle);
    mat[M04] = -sin(angle);
    mat[M05] = cos(angle);
    mat[M10] = 1;
    mat[M15] = 1;
    // 行列計算用に配列の値をコピーする
    copy(out, matb); 
    Matrix4f_mul(mat, matb, out);
}

void Matrix4f_scale(float out[16], float scale) {
    float mat[16], cpy[16];
    Matrix4f_create(mat);
    Matrix4f_identifyValue(mat, scale);
    mat[M15] = 1;
    copy(out, cpy);
    Matrix4f_mul(cpy, mat, out);
}
