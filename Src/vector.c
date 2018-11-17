/*
 * vector.c
 *
 *  Created on: 17 ����. 2018 �.
 *      Author: ���� ��������
 */
#include "vector.h"

/**
 * @brief ��������� ������ ������
 * @param v ��������� �� ������
 */
void Vector3f_InitZero(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 0.0f; v->s.z = 0.0f;
}

/**
 * @brief ��������� ������ X
 * @param v ��������� �� ������
 */
void Vector3f_InitUnitX(Vector3f * v)
{
    v->s.x = 1.0f; v->s.y = 0.0f; v->s.z = 0.0f;
}

/**
 * @brief ��������� ������ Y
 * @param v ��������� �� ������
 */
void Vector3f_InitUnitY(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 1.0f; v->s.z = 0.0f;
}

/**
 * @brief ��������� ������ Z
 * @param v ��������� �� ������
 */
void Vector3f_InitUnitZ(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 0.0f; v->s.z = 1.0f;
}


/**
 * @brief ��������� ������ ���������
 * @param v ��������� �� ������
 */
void Vector3f_InitOne(Vector3f * v)
{
    v->s.x = 1.0f; v->s.y = 1.0f; v->s.z = 1.0f;
}

/**
 * @brief ��������� ������, ����������� ����� (0, 1, 0)
 * @param v ��������� �� ������
 */
void Vector3f_InitUp(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 1.0f; v->s.z = 0.0f;
}

/**
 * @brief ��������� ������, ����������� ���� (0, -1, 0)
 * @param v ��������� �� ������
 */
void Vector3f_InitDown(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = -1.0f; v->s.z = 0.0f;
}

/**
 * @brief ��������� ������, ����������� ����� (-1, 0, 0)
 * @param v ��������� �� ������
 */
void Vector3f_InitLeft(Vector3f * v)
{
    v->s.x = -1.0f; v->s.y = 0.0f; v->s.z = 0.0f;
}

/**
 * @brief ��������� ������, ����������� ������ (1, 0, 0)
 * @param v ��������� �� ������
 */
void Vector3f_InitRight(Vector3f * v)
{
    v->s.x = 1.0f; v->s.y = 0.0f; v->s.z = 0.0f;
}

/**
 * @brief ��������� ������, ����������� ����� �
 * �������������� ������� ��������� (0, 0, -1)
 * @param v ��������� �� ������
 */
void Vector3f_InitForwardRH(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 0.0f; v->s.z = -1.0f;
}

/**
 * @brief ��������� ������, ����������� ����� �
 * ������������� ������� ��������� (0, 0, 1)
 * @param v ��������� �� ������
 */
void Vector3f_InitForwardLH(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 0.0f; v->s.z = 1.0f;
}

/**
 * @brief ��������� ������, ����������� ����� �
 * �������������� ������� ��������� (0, 0, -1)
 * @param v ��������� �� ������
 */
void Vector3f_InitBackwardRH(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 0.0f; v->s.z = 1.0f;
}

/**
 * @brief ��������� ������, ����������� ����� �
 * ������������� ������� ��������� (0, 0, -1)
 * @param v ��������� �� ������
 */
void Vector3f_InitBackwardLH(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 0.0f; v->s.z = -1.0f;
}

/**
 * @brief ��������� ������ \c v ��������� \c scalar
 * @param v ��������� �� ������
 * @param scalar �������� ��� ����������
 */
void Vector3f_InitScalar(Vector3f * v, float32_t scalar)
{
    v->s.x = scalar; v->s.y = scalar; v->s.z = scalar;
}


/**
 * @brief ����������� ����� �������
 * @param v ��������� �� ������
 * @return ����� �������
 */
float32_t Vector3f_Length(const Vector3f * v)
{
    float value;
    float dot;
    arm_dot_prod_f32(v->a, v->a, 3, &dot);
    arm_sqrt_f32(dot ,&value);
    return value;
}

/**
 * @brief ����������� ������� ����� �������
 * @param v ��������� �� ������
 * @return ������� ����� �������
 */
float32_t Vector3f_LengthSquared(const Vector3f * v)
{
    float dot;
    arm_dot_prod_f32(v->a, v->a, 3, &dot);
    return dot;
}

/**
 * @brief ����������� ������ � ��������� ������
 * @param v ��������� �� ������
 */
void Vector3f_Normalize(Vector3f * v)
{
    float length = Vector3f_Length(&v);
    if (length != 0)
    {
        float inv = 1.0f / length;
        v->s.x *= inv;
        v->s.y *= inv;
        v->s.z *= inv;
    }
}

/**
 * @brief ���������� ����� �������� \c l � \c r � ������ \c o
 * @param[in] l ��������� �� ������ ������
 * @param[in] r ��������� �� ������ ������
 * @param[out] o ��������� �� ������, ���� ��������� �����
 */
void Vector3f_InitAdd(const Vector3f * l,const Vector3f * r, Vector3f * o)
{
    o->s.x = l->s.x + r->s.x;
    o->s.y = l->s.y + r->s.y;
    o->s.z = l->s.z + r->s.z;
}

/**
 * @brief ���������� � ������� \c v ������ \c a
 * @param[in, out] v ��������� �� ������, � �������� ���������� ��������
 * @param[in] a ��������� �� �������, ������� ����� ���������
 */
void Vector3f_Add(Vector3f * v,const Vector3f * a)
{
    v->s.x += a->s.x;
    v->s.y += a->s.y;
    v->s.z += a->s.z;
}

/**
 * @brief ���������� ����� ������� \c l � ������� \c scalar � ������ \c o
 * @param[in] l ��������� �� ������ ������
 * @param[in] scalar ��������� ��������, ������� ���������� ���������
 * @param[out] o ��������� �� ������ � ����������� ������� �������
 * �� ��������� ��������
 */
void Vector3f_InitAddScalar(const Vector3f * l, float scalar, Vector3f * o)
{
    o->s.x = l->s.x + scalar;
    o->s.y = l->s.y + scalar;
    o->s.z = l->s.z + scalar;
}

/**
 * @brief ���������� � ������� \c v ������ \c scalar
 * @param[in, out] v ��������� �� ������, � �������� ���������� ��������
 * @param[in] scalar ��������� ��������, ������� ���������� ���������
 */
void Vector3f_AddScalar(Vector3f * v,float scalar)
{
    v->s.x += scalar;
    v->s.y += scalar;
    v->s.z += scalar;
}


/**
 * @brief ���������� �������� �������� \c l � \c r � ������ \c o
 * @param[in] l ��������� �� ������ ������
 * @param[in] r ��������� �� ������ ������
 * @param[out] o ��������� �� ������, ���� ��������� ��������
 */
void Vector3f_InitSubtract(const Vector3f * l, const Vector3f * r, Vector3f * o)
{
    o->s.x = l->s.x - r->s.x;
    o->s.y = l->s.y - r->s.y;
    o->s.z = l->s.z - r->s.z;
}

/**
 * @brief �������� �� ������� \c v ������ \c a
 * @param[in, out] v ��������� �� ������, �� �������� ��������� ��������
 * @param[in] a ��������� �� �������, ������� ����� ������
 */
void Vector3f_Subtract(Vector3f * v, const Vector3f * a)
{
    v->s.x -= a->s.x;
    v->s.y -= a->s.y;
    v->s.z -= a->s.z;
}

/**
 * @brief ���������� ������� ������� \c l � ������� \c scalar � ������ \c o
 * @param[in] l ��������� �� ������ ������
 * @param[in] scalar ��������� ��������, ������� ���������� ������
 * @param[out] o ��������� �� ������ � ����������� ������� �������
 * �� ��������� ��������
 */
void Vector3f_InitSubtractScalar(const Vector3f * l, float scalar, Vector3f * o)
{
    o->s.x = l->s.x - scalar;
    o->s.y = l->s.y - scalar;
    o->s.z = l->s.z - scalar;
}

/**
 * @brief �������� �� ������� \c v ������ \c scalar
 * @param[in, out] v ��������� �� ������, �� �������� ��������� ��������
 * @param[in] scalar ��������� ��������, ������� ���������� ������
 */
void Vector3f_SubtractScalar(Vector3f * v, float scalar)
{
    v->s.x -= scalar;
    v->s.y -= scalar;
    v->s.z -= scalar;
}

/**
 * @brief ���������� ��������� ������� \c l � ������� \c scalar � ������ \c o
 * @param[in] l ��������� �� ������ ������
 * @param[in] scalar ��������� ��������, �� ������� ���������� ��������
 * @param[out] o ��������� �� ������ � ���������� ������� �������
 * �� ��������� ��������
 */
void Vector3f_InitMultiplyScalar(const Vector3f * l, float scalar, Vector3f * o)
{
    o->s.x = l->s.x * scalar;
    o->s.y = l->s.y * scalar;
    o->s.z = l->s.z * scalar;
}

/**
 * @brief �������� ������ \c v �� ������ \c scalar
 * @param[in, out] v ��������� �� ������
 * @param[in] scalar ��������� ��������, �� ������� ���������� ��������
 */
void Vector3f_MultiplyScalar(Vector3f * v, float scalar)
{
    v->s.x *= scalar;
    v->s.y *= scalar;
    v->s.z *= scalar;
}

