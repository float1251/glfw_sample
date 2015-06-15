#include "matrix4f.h"
#include <math.h>

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
    out[0] = cos(angle);
    out[1] = sin(angle);
    out[4] = -sin(angle);
    out[5] = cos(angle);
    out[10] = 1;
    out[15] = 1;
}

void Matrix4f_scale(float out[16], float scale) {
    out[0] = scale;
    out[5] = scale;
    out[10] = scale;
    out[15] = 1;
}
