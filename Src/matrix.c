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
    for(int i = 0;i<16;++i)
        m->a[i] = 0.0f;
}


/**
 * @brief ��������� ������� ��� ���������
 * @param[in,out] m ��������� �� �������
 */
void Matrix_Identity(Matrix4x4f * m)
{
    m->s.M11 = 1.0f;  m->s.M12 = 0.0f;  m->s.M13 = 0.0f;  m->s.M14 = 0.0f;
    m->s.M21 = 0.0f;  m->s.M22 = 1.0f;  m->s.M23 = 0.0f;  m->s.M24 = 0.0f;
    m->s.M31 = 0.0f;  m->s.M32 = 0.0f;  m->s.M33 = 1.0f;  m->s.M34 = 0.0f;
    m->s.M41 = 0.0f;  m->s.M42 = 0.0f;  m->s.M43 = 0.0f;  m->s.M44 = 1.0f;
}



