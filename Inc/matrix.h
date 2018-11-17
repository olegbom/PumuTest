/*
 * matrix.h
 *
 *  Created on: 29 июн. 2018 г.
 *      Author: Олег Высоцкий
 */

#ifndef MATRIX_H_
#define MATRIX_H_

/// @brief Размез матрицы в байтах
#define MATRIX4X4F_SIZE 16*4

/**
 * @brief Обьединение для Матрицы 4x4 типа float
 */
typedef union
{
    struct
    {
      float M11;  /**< Значение 1-го ряда 1-го стобца матрицы */
      float M12;  /**< Значение 1-го ряда 2-го стобца матрицы */
      float M13;  /**< Значение 1-го ряда 3-го стобца матрицы */
      float M14;  /**< Значение 1-го ряда 4-го стобца матрицы */
      float M21;  /**< Значение 2-го ряда 1-го стобца матрицы */
      float M22;  /**< Значение 2-го ряда 2-го стобца матрицы */
      float M23;  /**< Значение 2-го ряда 3-го стобца матрицы */
      float M24;  /**< Значение 2-го ряда 4-го стобца матрицы */
      float M31;  /**< Значение 3-го ряда 1-го стобца матрицы */
      float M32;  /**< Значение 3-го ряда 2-го стобца матрицы */
      float M33;  /**< Значение 3-го ряда 3-го стобца матрицы */
      float M34;  /**< Значение 3-го ряда 4-го стобца матрицы */
      float M41;  /**< Значение 4-го ряда 1-го стобца матрицы */
      float M42;  /**< Значение 4-го ряда 2-го стобца матрицы */
      float M43;  /**< Значение 4-го ряда 3-го стобца матрицы */
      float M44;  /**< Значение 4-го ряда 4-го стобца матрицы */
    } s;          /**< Структура для удобного доступа к каждому элементу матрицы */
    float a[16];  /**< Указатель на массив из 16-ти float */
} Matrix4x4f;

void Matrix_InitZero(Matrix4x4f *m);
void Matrix_Identity(Matrix4x4f *m);


Matrix4x4f Matrix_OneVal(float value);
Matrix4x4f Matrix_OneVal(float value);
float Determinant(Matrix4x4f *matrix);
void Invert(Matrix4x4f *value, Matrix4x4f *result);

#endif /* MATRIX_H_ */
