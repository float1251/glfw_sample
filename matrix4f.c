#include "matrix4f.h"
#include <math.h>

enum MM {
    m0 = 0
};

inline void copy(float mat[16], float out[16]) { int i; for(i=0; i<16; i++) {
        out[i] = mat[i];
    }
}


void Matrix4f_mul(float mata[16], float matb[16], float out[16]) {
    // out[0] = mata[0]*matb[0] + mata[1]*matb[4]
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
    mat[0] = cos(angle); mat[1] = sin(angle);
    mat[4] = -sin(angle);
    mat[5] = cos(angle);
    mat[10] = 1;
    mat[15] = 1;
    // 行列計算用に配列の値をコピーする
    copy(out, matb); 
    Matrix4f_mul(mat, matb, out);
}

void Matrix4f_scale(float out[16], float scale) {
    out[0] = scale;
    out[5] = scale;
    out[10] = scale;
    out[15] = 1;
}
