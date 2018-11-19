/*
 * matrix.c
 *
 *  Created on: 29 ���. 2018 �.
 *      Author: ���� ��������
 */
#include "matrix.h"
#include "math.h"

/**
 * @brief ��������� ������� ������
 * @param[in,out] m ��������� �� �������
 */
void Matrix_InitZero(Matrix4x4f * m)
{
    float *array = (float*)m;
    for(int i = 0;i<16;++i)
        array[i] = 0.0f;
}


/**
 * @brief ��������� ������� ��� ���������
 * @param[in,out] m ��������� �� �������
 */
void Matrix_Identity(Matrix4x4f * m)
{
    m->M11 = 1.0f;  m->M12 = 0.0f;  m->M13 = 0.0f;  m->M14 = 0.0f;
    m->M21 = 0.0f;  m->M22 = 1.0f;  m->M23 = 0.0f;  m->M24 = 0.0f;
    m->M31 = 0.0f;  m->M32 = 0.0f;  m->M33 = 1.0f;  m->M34 = 0.0f;
    m->M41 = 0.0f;  m->M42 = 0.0f;  m->M43 = 0.0f;  m->M44 = 1.0f;
}



