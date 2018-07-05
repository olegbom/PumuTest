/*
 * matrix.h
 *
 *  Created on: 29 θών. 2018 γ.
 *      Author: Oleg
 */

#ifndef MATRIX_H_
#define MATRIX_H_

typedef struct
{
  float M11;
  float M12;
  float M13;
  float M14;
  float M21;
  float M22;
  float M23;
  float M24;
  float M31;
  float M32;
  float M33;
  float M34;
  float M41;
  float M42;
  float M43;
  float M44;
} matrix_f32;


matrix_f32 Matrix_OneVal(float value);
matrix_f32 Matrix_OneVal(float value);
float Determinant(matrix_f32 *matrix);
void Invert(matrix_f32 *value, matrix_f32 *result);

#endif /* MATRIX_H_ */
