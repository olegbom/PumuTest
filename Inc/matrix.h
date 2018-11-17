/*
 * matrix.h
 *
 *  Created on: 29 ���. 2018 �.
 *      Author: ���� ��������
 */

#ifndef MATRIX_H_
#define MATRIX_H_

/// @brief ������ ������� � ������
#define MATRIX4X4F_SIZE 16*4

/**
 * @brief ����������� ��� ������� 4x4 ���� float
 */
typedef union
{
    struct
    {
      float M11;  /**< �������� 1-�� ���� 1-�� ������ ������� */
      float M12;  /**< �������� 1-�� ���� 2-�� ������ ������� */
      float M13;  /**< �������� 1-�� ���� 3-�� ������ ������� */
      float M14;  /**< �������� 1-�� ���� 4-�� ������ ������� */
      float M21;  /**< �������� 2-�� ���� 1-�� ������ ������� */
      float M22;  /**< �������� 2-�� ���� 2-�� ������ ������� */
      float M23;  /**< �������� 2-�� ���� 3-�� ������ ������� */
      float M24;  /**< �������� 2-�� ���� 4-�� ������ ������� */
      float M31;  /**< �������� 3-�� ���� 1-�� ������ ������� */
      float M32;  /**< �������� 3-�� ���� 2-�� ������ ������� */
      float M33;  /**< �������� 3-�� ���� 3-�� ������ ������� */
      float M34;  /**< �������� 3-�� ���� 4-�� ������ ������� */
      float M41;  /**< �������� 4-�� ���� 1-�� ������ ������� */
      float M42;  /**< �������� 4-�� ���� 2-�� ������ ������� */
      float M43;  /**< �������� 4-�� ���� 3-�� ������ ������� */
      float M44;  /**< �������� 4-�� ���� 4-�� ������ ������� */
    } s;          /**< ��������� ��� �������� ������� � ������� �������� ������� */
    float a[16];  /**< ��������� �� ������ �� 16-�� float */
} Matrix4x4f;

void Matrix_InitZero(Matrix4x4f *m);
void Matrix_Identity(Matrix4x4f *m);


Matrix4x4f Matrix_OneVal(float value);
Matrix4x4f Matrix_OneVal(float value);
float Determinant(Matrix4x4f *matrix);
void Invert(Matrix4x4f *value, Matrix4x4f *result);

#endif /* MATRIX_H_ */
