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
    v->x = 0.0f; v->y = 0.0f; v->z = 0.0f;
}

/**
 * @brief ��������� ������ X
 * @param v ��������� �� ������
 */
void Vector3f_InitUnitX(Vector3f * v)
{
    v->x = 1.0f; v->y = 0.0f; v->z = 0.0f;
}

/**
 * @brief ��������� ������ Y
 * @param v ��������� �� ������
 */
void Vector3f_InitUnitY(Vector3f * v)
{
    v->x = 0.0f; v->y = 1.0f; v->z = 0.0f;
}

/**
 * @brief ��������� ������ Z
 * @param v ��������� �� ������
 */
void Vector3f_InitUnitZ(Vector3f * v)
{
    v->x = 0.0f; v->y = 0.0f; v->z = 1.0f;
}


/**
 * @brief ��������� ������ ���������
 * @param v ��������� �� ������
 */
void Vector3f_InitOne(Vector3f * v)
{
    v->x = 1.0f; v->y = 1.0f; v->z = 1.0f;
}

/**
 * @brief ��������� ������, ����������� ����� (0, 1, 0)
 * @param v ��������� �� ������
 */
void Vector3f_InitUp(Vector3f * v)
{
    v->x = 0.0f; v->y = 1.0f; v->z = 0.0f;
}

/**
 * @brief ��������� ������, ����������� ���� (0, -1, 0)
 * @param v ��������� �� ������
 */
void Vector3f_InitDown(Vector3f * v)
{
    v->x = 0.0f; v->y = -1.0f; v->z = 0.0f;
}

/**
 * @brief ��������� ������, ����������� ����� (-1, 0, 0)
 * @param v ��������� �� ������
 */
void Vector3f_InitLeft(Vector3f * v)
{
    v->x = -1.0f; v->y = 0.0f; v->z = 0.0f;
}

/**
 * @brief ��������� ������, ����������� ������ (1, 0, 0)
 * @param v ��������� �� ������
 */
void Vector3f_InitRight(Vector3f * v)
{
    v->x = 1.0f; v->y = 0.0f; v->z = 0.0f;
}

/**
 * @brief ��������� ������, ����������� ����� �
 * �������������� ������� ��������� (0, 0, -1)
 * @param v ��������� �� ������
 */
void Vector3f_InitForwardRH(Vector3f * v)
{
    v->x = 0.0f; v->y = 0.0f; v->z = -1.0f;
}

/**
 * @brief ��������� ������, ����������� ����� �
 * ������������� ������� ��������� (0, 0, 1)
 * @param v ��������� �� ������
 */
void Vector3f_InitForwardLH(Vector3f * v)
{
    v->x = 0.0f; v->y = 0.0f; v->z = 1.0f;
}

/**
 * @brief ��������� ������, ����������� ����� �
 * �������������� ������� ��������� (0, 0, -1)
 * @param v ��������� �� ������
 */
void Vector3f_InitBackwardRH(Vector3f * v)
{
    v->x = 0.0f; v->y = 0.0f; v->z = 1.0f;
}

/**
 * @brief ��������� ������, ����������� ����� �
 * ������������� ������� ��������� (0, 0, -1)
 * @param v ��������� �� ������
 */
void Vector3f_InitBackwardLH(Vector3f * v)
{
    v->x = 0.0f; v->y = 0.0f; v->z = -1.0f;
}

/**
 * @brief ��������� ������ \c v ��������� \c scalar
 * @param v ��������� �� ������
 * @param scalar �������� ��� ����������
 */
void Vector3f_InitScalar(Vector3f * v, float32_t scalar)
{
    v->x = scalar; v->y = scalar; v->z = scalar;
}


/**
 * @brief ����������� ����� �������
 * @param v ��������� �� ������
 * @return ����� �������
 */
float32_t Vector3f_Length(Vector3f * v)
{
    float value;
    float dot;
    float *array = (float*)v;
    arm_dot_prod_f32(array, array, 3, &dot);
    arm_sqrt_f32(dot ,&value);
    return value;
}

/**
 * @brief ����������� ������� ����� �������
 * @param v ��������� �� ������
 * @return ������� ����� �������
 */
float32_t Vector3f_LengthSquared(Vector3f * v)
{
    float dot;
    float *array = (float*)v;
    arm_dot_prod_f32(array, array, 3, &dot);
    return dot;
}

/**
 * @brief ����������� ������ � ��������� ������
 * @param[in, out] v ��������� �� ������
 */
void Vector3f_Normalize(Vector3f * v)
{
    float length = Vector3f_Length(v);
    if (length != 0)
    {
        float inv = 1.0f / length;
        v->x *= inv;
        v->y *= inv;
        v->z *= inv;
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
    o->x = l->x + r->x;
    o->y = l->y + r->y;
    o->z = l->z + r->z;
}

/**
 * @brief ���������� � ������� \c v ������ \c a
 * @param[in, out] v ��������� �� ������, � �������� ���������� ��������
 * @param[in] a ��������� �� �������, ������� ����� ���������
 */
void Vector3f_Add(Vector3f * v,const Vector3f * a)
{
    v->x += a->x;
    v->y += a->y;
    v->z += a->z;
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
    o->x = l->x + scalar;
    o->y = l->y + scalar;
    o->z = l->z + scalar;
}

/**
 * @brief ���������� � ������� \c v ������ \c scalar
 * @param[in, out] v ��������� �� ������, � �������� ���������� ��������
 * @param[in] scalar ��������� ��������, ������� ���������� ���������
 */
void Vector3f_AddScalar(Vector3f * v,float scalar)
{
    v->x += scalar;
    v->y += scalar;
    v->z += scalar;
}


/**
 * @brief ���������� �������� �������� \c l � \c r � ������ \c o
 * @param[in] l ��������� �� ������ ������
 * @param[in] r ��������� �� ������ ������
 * @param[out] o ��������� �� ������, ���� ��������� ��������
 */
void Vector3f_InitSubtract(const Vector3f * l, const Vector3f * r, Vector3f * o)
{
    o->x = l->x - r->x;
    o->y = l->y - r->y;
    o->z = l->z - r->z;
}

/**
 * @brief �������� �� ������� \c v ������ \c a
 * @param[in, out] v ��������� �� ������, �� �������� ��������� ��������
 * @param[in] a ��������� �� �������, ������� ����� ������
 */
void Vector3f_Subtract(Vector3f * v, const Vector3f * a)
{
    v->x -= a->x;
    v->y -= a->y;
    v->z -= a->z;
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
    o->x = l->x - scalar;
    o->y = l->y - scalar;
    o->z = l->z - scalar;
}

/**
 * @brief �������� �� ������� \c v ������ \c scalar
 * @param[in, out] v ��������� �� ������, �� �������� ��������� ��������
 * @param[in] scalar ��������� ��������, ������� ���������� ������
 */
void Vector3f_SubtractScalar(Vector3f * v, float scalar)
{
    v->x -= scalar;
    v->y -= scalar;
    v->z -= scalar;
}


/**
 * @brief ���������� �������������� ��������� ������� \c l
 * �� ������ \c r � ������ \c o
 * @param[in] l ��������� �� ������ ������
 * @param[in] r ��������� �� ������ ������
 * @param[out] o ��������� �� ������, ���� ��������� ��������� ���������
 */
void Vector3f_InitMultiply(const Vector3f * l, const Vector3f * r, Vector3f * o)
{
    o->x = l->x * r->x;
    o->y = l->y * r->y;
    o->z = l->z * r->z;
}

/**
 * @brief �������� ������������� ������ \c v �� ������ \c a
 * @param[in, out] v ��������� �� ������, ������� ����������
 * @param[in] a ��������� �� �������, �� ������� ����� ��������
 */
void Vector3f_Multiply(Vector3f * v, const Vector3f * a)
{
    v->x *= a->x;
    v->y *= a->y;
    v->z *= a->z;
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
    o->x = l->x * scalar;
    o->y = l->y * scalar;
    o->z = l->z * scalar;
}

/**
 * @brief �������� ������ \c v �� ������ \c scalar
 * @param[in, out] v ��������� �� ������
 * @param[in] scalar ��������� ��������, �� ������� ���������� ��������
 */
void Vector3f_MultiplyScalar(Vector3f * v, float scalar)
{
    v->x *= scalar;
    v->y *= scalar;
    v->z *= scalar;
}

/**
 * @brief ���������� �������������� ������� ������� \c l
 * �� ������ \c r � ������ \c o
 * @param[in] l ��������� �� ������ ������
 * @param[in] r ��������� �� ������ ������
 * @param[out] o ��������� �� ������, ���� ��������� ��������� �������
 */
void Vector3f_InitDivide(const Vector3f * l, const Vector3f * r, Vector3f * o)
{
    o->x = l->x / r->x;
    o->y = l->y / r->y;
    o->z = l->z / r->z;
}

/**
 * @brief ����� ������������� ������ \c v �� ������ \c a
 * @param[in, out] v ��������� �� ������, ������� �������
 * @param[in] a ��������� �� �������, �� ������� ����� ��������
 */
void Vector3f_Divide(Vector3f * v, const Vector3f * a)
{
    v->x -= a->x;
    v->y -= a->y;
    v->z -= a->z;
}

/**
 * @brief ���������� ������� ������� \c l �� ������ \c scalar � ������ \c o
 * @param[in] l ��������� �� ������ ������
 * @param[in] scalar ��������� ��������, �� ������� ���������� ��������
 * @param[out] o ��������� �� ������ � �������� ������� �������
 * �� ��������� ��������
 */
void Vector3f_InitDivideScalar(const Vector3f * l, float scalar, Vector3f * o)
{
    o->x = l->x / scalar;
    o->y = l->y / scalar;
    o->z = l->z / scalar;
}

/**
 * @brief ����� ������ \c v �� ������ \c scalar
 * @param[in, out] v ��������� �� ������
 * @param[in] scalar ��������� ��������, �� ������� ���������� ��������
 */
void Vector3f_DivideScalar(Vector3f * v, float scalar)
{
    v->x /= scalar;
    v->y /= scalar;
    v->z /= scalar;
}

/**
 * @brief ���������� � \c o ������, �������� �� �����������
 * ������� \c v
 * @param v ��������� �� ������
 * @param o �������� �� ����������� ������
 */
void Vector3f_InitNegate(const Vector3f * v, Vector3f * o)
{
    o->x = -v->x;
    o->y = -v->y;
    o->z = -v->z;
}

/**
 * @brief �������� ����������� ������� \c v �� ��������
 * @param v ��������� �� ������
 */
void Vector3f_Negate(Vector3f * v)
{
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}


/**
 * @brief ���������� � ������ \c o ���������� �����, ���������
 * � ���������������� ����������� ������������
 * ���������� ������������
 * @param[in] v1 1-� ���������� ������� ������������
 * @param[in] v2 2-� ���������� ������� ������������
 * @param[in] v3 3-� ���������� ������� ������������
 * @param[in] amount1 ���������������� ���������� b2,
 * ������� �������� ������� ����������� �� ��������� � ������� 2
 * @param[in] amount2 ���������������� ���������� b3,
 * ������� �������� ������� ����������� �� ��������� � ������� 3
 * @param[out] o ������������ ��������
 */
void Vector3f_InitBarycentric(const Vector3f * v1,
        const Vector3f * v2, const Vector3f * v3,
        float amount1, float amount2, Vector3f *o)
{
    o->x = v1->x + amount1 * (v2->x - v1->x) + amount2 * (v3->x - v1->x);
    o->y = v1->y + amount1 * (v2->y - v1->y) + amount2 * (v3->y - v1->y);
    o->z = v1->z + amount1 * (v2->z - v1->z) + amount2 * (v3->z - v1->z);
}

/**
 * @brief ������������ �������� � ������ ���������� ���������
 * @param[in] v ������, ������� ����� ����������
 * @param[in] min ����������� ��������
 * @param[in] max 3-� ������������ ��������
 * @param[in] amount1 ���������������� ���������� b2,
 * ������� �������� ������� ����������� �� ��������� � ������� 2
 * @param[in] amount2 ���������������� ���������� b3,
 * ������� �������� ������� ����������� �� ��������� � ������� 3
 * @param[out] o ������������ ��������
 */
void Vector3f_InitClamp(const Vector3f * v,
        const Vector3f * min, const Vector3f * max,
        Vector3f *o)
{
   /* o->x = v1->x + amount1 * (v2->x - v1->x) + amount2 * (v3->x - v1->x);
    o->y = v1->y + amount1 * (v2->y - v1->y) + amount2 * (v3->y - v1->y);
    o->z = v1->z + amount1 * (v2->z - v1->z) + amount2 * (v3->z - v1->z);*/
}

