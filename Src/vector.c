/*
 * vector.c
 *
 *  Created on: 17 нояб. 2018 г.
 *      Author: Олег Высоцкий
 */
#include "vector.h"

/**
 * @brief Заполняет вектор нулями
 * @param v Указатель на вектор
 */
void Vector3f_InitZero(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 0.0f; v->s.z = 0.0f;
}

/**
 * @brief Еденичный вектор X
 * @param v Указатель на вектор
 */
void Vector3f_InitUnitX(Vector3f * v)
{
    v->s.x = 1.0f; v->s.y = 0.0f; v->s.z = 0.0f;
}

/**
 * @brief Еденичный вектор Y
 * @param v Указатель на вектор
 */
void Vector3f_InitUnitY(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 1.0f; v->s.z = 0.0f;
}

/**
 * @brief Еденичный вектор Z
 * @param v Указатель на вектор
 */
void Vector3f_InitUnitZ(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 0.0f; v->s.z = 1.0f;
}


/**
 * @brief Заполняет вектор еденицами
 * @param v Указатель на вектор
 */
void Vector3f_InitOne(Vector3f * v)
{
    v->s.x = 1.0f; v->s.y = 1.0f; v->s.z = 1.0f;
}

/**
 * @brief Еденичный вектор, указывающий вверх (0, 1, 0)
 * @param v Указатель на вектор
 */
void Vector3f_InitUp(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 1.0f; v->s.z = 0.0f;
}

/**
 * @brief Еденичный вектор, указывающий вниз (0, -1, 0)
 * @param v Указатель на вектор
 */
void Vector3f_InitDown(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = -1.0f; v->s.z = 0.0f;
}

/**
 * @brief Еденичный вектор, указывающий влево (-1, 0, 0)
 * @param v Указатель на вектор
 */
void Vector3f_InitLeft(Vector3f * v)
{
    v->s.x = -1.0f; v->s.y = 0.0f; v->s.z = 0.0f;
}

/**
 * @brief Еденичный вектор, указывающий вправо (1, 0, 0)
 * @param v Указатель на вектор
 */
void Vector3f_InitRight(Vector3f * v)
{
    v->s.x = 1.0f; v->s.y = 0.0f; v->s.z = 0.0f;
}

/**
 * @brief Еденичный вектор, указывающий назад в
 * правосторонней системе координат (0, 0, -1)
 * @param v Указатель на вектор
 */
void Vector3f_InitForwardRH(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 0.0f; v->s.z = -1.0f;
}

/**
 * @brief Еденичный вектор, указывающий назад в
 * левосторонней системе координат (0, 0, 1)
 * @param v Указатель на вектор
 */
void Vector3f_InitForwardLH(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 0.0f; v->s.z = 1.0f;
}

/**
 * @brief Еденичный вектор, указывающий вперёд в
 * правосторонней системе координат (0, 0, -1)
 * @param v Указатель на вектор
 */
void Vector3f_InitBackwardRH(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 0.0f; v->s.z = 1.0f;
}

/**
 * @brief Еденичный вектор, указывающий вперёд в
 * левосторонней системе координат (0, 0, -1)
 * @param v Указатель на вектор
 */
void Vector3f_InitBackwardLH(Vector3f * v)
{
    v->s.x = 0.0f; v->s.y = 0.0f; v->s.z = -1.0f;
}

/**
 * @brief Заполняет вектор \c v значением \c scalar
 * @param v Указатель на вектор
 * @param scalar Значение для заполнения
 */
void Vector3f_InitScalar(Vector3f * v, float32_t scalar)
{
    v->s.x = scalar; v->s.y = scalar; v->s.z = scalar;
}


/**
 * @brief Расчитывает длину вектора
 * @param v Указатель на вектор
 * @return Длина вектора
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
 * @brief Расчитывает квадрат длины вектора
 * @param v Указатель на вектор
 * @return Квадрат длины вектора
 */
float32_t Vector3f_LengthSquared(const Vector3f * v)
{
    float dot;
    arm_dot_prod_f32(v->a, v->a, 3, &dot);
    return dot;
}

/**
 * @brief Преобразует вектор в еденичный вектор
 * @param v Указатель на вектор
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
 * @brief Записывает сумму векторов \c l и \c r в вектор \c o
 * @param[in] l Указатель на первый вектор
 * @param[in] r Указатель на второй вектор
 * @param[out] o Указатель на вектор, куда запишется сумма
 */
void Vector3f_InitAdd(const Vector3f * l,const Vector3f * r, Vector3f * o)
{
    o->s.x = l->s.x + r->s.x;
    o->s.y = l->s.y + r->s.y;
    o->s.z = l->s.z + r->s.z;
}

/**
 * @brief Прибавляет к вектору \c v вектор \c a
 * @param[in, out] v Указатель на вектор, к которому прибавится значение
 * @param[in] a Указатель на вектора, который нужно прибавить
 */
void Vector3f_Add(Vector3f * v,const Vector3f * a)
{
    v->s.x += a->s.x;
    v->s.y += a->s.y;
    v->s.z += a->s.z;
}

/**
 * @brief Записывает сумму вектора \c l и скаляра \c scalar в вектор \c o
 * @param[in] l Указатель на первый вектор
 * @param[in] scalar Скалярное значение, которое необходимо прибавить
 * @param[out] o Указатель на вектор с увеличением каждого элемета
 * на скалярную величину
 */
void Vector3f_InitAddScalar(const Vector3f * l, float scalar, Vector3f * o)
{
    o->s.x = l->s.x + scalar;
    o->s.y = l->s.y + scalar;
    o->s.z = l->s.z + scalar;
}

/**
 * @brief Прибавляет к вектору \c v скаляр \c scalar
 * @param[in, out] v Указатель на вектор, к которому прибавится значение
 * @param[in] scalar Скалярное значение, которое необходимо прибавить
 */
void Vector3f_AddScalar(Vector3f * v,float scalar)
{
    v->s.x += scalar;
    v->s.y += scalar;
    v->s.z += scalar;
}


/**
 * @brief Записывает разность векторов \c l и \c r в вектор \c o
 * @param[in] l Указатель на первый вектор
 * @param[in] r Указатель на второй вектор
 * @param[out] o Указатель на вектор, куда запишется разность
 */
void Vector3f_InitSubtract(const Vector3f * l, const Vector3f * r, Vector3f * o)
{
    o->s.x = l->s.x - r->s.x;
    o->s.y = l->s.y - r->s.y;
    o->s.z = l->s.z - r->s.z;
}

/**
 * @brief Отнимает от вектора \c v вектор \c a
 * @param[in, out] v Указатель на вектор, от которого отнимется значение
 * @param[in] a Указатель на вектора, который нужно отнять
 */
void Vector3f_Subtract(Vector3f * v, const Vector3f * a)
{
    v->s.x -= a->s.x;
    v->s.y -= a->s.y;
    v->s.z -= a->s.z;
}

/**
 * @brief Записывает разнось вектора \c l и скаляра \c scalar в вектор \c o
 * @param[in] l Указатель на первый вектор
 * @param[in] scalar Скалярное значение, которое необходимо отнять
 * @param[out] o Указатель на вектор с уменьшением каждого элемета
 * на скалярную величину
 */
void Vector3f_InitSubtractScalar(const Vector3f * l, float scalar, Vector3f * o)
{
    o->s.x = l->s.x - scalar;
    o->s.y = l->s.y - scalar;
    o->s.z = l->s.z - scalar;
}

/**
 * @brief Отнимает от вектора \c v скаляр \c scalar
 * @param[in, out] v Указатель на вектор, от которого отнимется значение
 * @param[in] scalar Скалярное значение, которое необходимо отнять
 */
void Vector3f_SubtractScalar(Vector3f * v, float scalar)
{
    v->s.x -= scalar;
    v->s.y -= scalar;
    v->s.z -= scalar;
}

/**
 * @brief Записывает умножение вектора \c l и скаляра \c scalar в вектор \c o
 * @param[in] l Указатель на первый вектор
 * @param[in] scalar Скалярное значение, на которое необходимо умножить
 * @param[out] o Указатель на вектор с умножением каждого элемета
 * на скалярную величину
 */
void Vector3f_InitMultiplyScalar(const Vector3f * l, float scalar, Vector3f * o)
{
    o->s.x = l->s.x * scalar;
    o->s.y = l->s.y * scalar;
    o->s.z = l->s.z * scalar;
}

/**
 * @brief Умножает вектор \c v на скаляр \c scalar
 * @param[in, out] v Указатель на вектор
 * @param[in] scalar Скалярное значение, на которое необходимо умножить
 */
void Vector3f_MultiplyScalar(Vector3f * v, float scalar)
{
    v->s.x *= scalar;
    v->s.y *= scalar;
    v->s.z *= scalar;
}

