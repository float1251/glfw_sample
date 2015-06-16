#ifndef _MATRIX4F_
#define _MATRIX4F_

#define MATRIX4F_X_AXIS 0
#define MATRIX4F_Y_AXIS 1
#define MATRIX4F_Z_AXIS 2

void Matrix4f_mul(float mata[16], float matb[16], float out[16]);
void Matrix4f_create(float out[16]);
void Matrix4f_identity(float out[16], float val);
void Matrix4f_rotateX(float out[16], float angle);
void Matrix4f_rotateY(float out[16], float angle);
void Matrix4f_rotateZ(float out[16], float angle);
void Matrix4f_scale(float out[16], float scale);

#endif
