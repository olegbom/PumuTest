/*
 * vector.h
 *
 *  Created on: 17 ����. 2018 �.
 *      Author: ���� ��������
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include "stm32f407xx.h"
#include "arm_math.h"

/// @brief ������ ������� � ������
#define VECTOR3F_SIZE 3*4

/**
 * @brief ����������� ��� ������� �� 3, ���� float
 */
typedef union
{
    struct
    {
        float32_t x;  /**< X ��������� ������� */
        float32_t y;  /**< Y ��������� ������� */
        float32_t z;  /**< Z ��������� ������� */
    } s;        /**< ��������� ��� �������� ������� � ������� �������� ������� */
    float32_t a[3]; /**< ��������� �� ������ �� 3-� float */
} Vector3f;


void Vector3f_InitZero(Vector3f * v);
void Vector3f_InitUnitX(Vector3f * v);
void Vector3f_InitUnitY(Vector3f * v);
void Vector3f_InitUnitZ(Vector3f * v);
void Vector3f_InitOne(Vector3f * v);
void Vector3f_InitUp(Vector3f * v);
void Vector3f_InitDown(Vector3f * v);
void Vector3f_InitLeft(Vector3f * v);
void Vector3f_InitRight(Vector3f * v);
void Vector3f_InitForwardRH(Vector3f * v);
void Vector3f_InitForwardLH(Vector3f * v);
void Vector3f_InitBackwardRH(Vector3f * v);
void Vector3f_InitBackwardLH(Vector3f * v);

void Vector3f_InitScalar(Vector3f * v, float32_t scalar);

float32_t Vector3f_Length(const Vector3f * v);
float32_t Vector3f_LengthSquared(const Vector3f * v);
void Vector3f_Normalize(Vector3f * v);

void Vector3f_InitAdd(const Vector3f * l, const Vector3f * r, Vector3f * o);
void Vector3f_Add(Vector3f * v, const Vector3f * a);

void Vector3f_InitAddScalar(const Vector3f * l, float scalar, Vector3f * o);
void Vector3f_AddScalar(Vector3f * v,float scalar);

void Vector3f_InitSubtract(const Vector3f * l, const Vector3f * r, Vector3f * o);
void Vector3f_Subtract(Vector3f * v, const Vector3f * a);

void Vector3f_InitSubtractScalar(const Vector3f * l, float scalar, Vector3f * o);
void Vector3f_SubtractScalar(Vector3f * v, float scalar);

void Vector3f_InitMultiplyScalar(const Vector3f * l, float scalar, Vector3f * o);
void Vector3f_MultiplyScalar(Vector3f * v, float scalar);

#endif /* VECTOR_H_ */
