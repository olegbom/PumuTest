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
    v->x = 0.0f; v->y = 0.0f; v->z = 0.0f;
}

/**
 * @brief Еденичный вектор X
 * @param v Указатель на вектор
 */
void Vector3f_InitUnitX(Vector3f * v)
{
    v->x = 1.0f; v->y = 0.0f; v->z = 0.0f;
}

/**
 * @brief Еденичный вектор Y
 * @param v Указатель на вектор
 */
void Vector3f_InitUnitY(Vector3f * v)
{
    v->x = 0.0f; v->y = 1.0f; v->z = 0.0f;
}

/**
 * @brief Еденичный вектор Z
 * @param v Указатель на вектор
 */
void Vector3f_InitUnitZ(Vector3f * v)
{
    v->x = 0.0f; v->y = 0.0f; v->z = 1.0f;
}


/**
 * @brief Заполняет вектор еденицами
 * @param v Указатель на вектор
 */
void Vector3f_InitOne(Vector3f * v)
{
    v->x = 1.0f; v->y = 1.0f; v->z = 1.0f;
}

/**
 * @brief Еденичный вектор, указывающий вверх (0, 1, 0)
 * @param v Указатель на вектор
 */
void Vector3f_InitUp(Vector3f * v)
{
    v->x = 0.0f; v->y = 1.0f; v->z = 0.0f;
}

/**
 * @brief Еденичный вектор, указывающий вниз (0, -1, 0)
 * @param v Указатель на вектор
 */
void Vector3f_InitDown(Vector3f * v)
{
    v->x = 0.0f; v->y = -1.0f; v->z = 0.0f;
}

/**
 * @brief Еденичный вектор, указывающий влево (-1, 0, 0)
 * @param v Указатель на вектор
 */
void Vector3f_InitLeft(Vector3f * v)
{
    v->x = -1.0f; v->y = 0.0f; v->z = 0.0f;
}

/**
 * @brief Еденичный вектор, указывающий вправо (1, 0, 0)
 * @param v Указатель на вектор
 */
void Vector3f_InitRight(Vector3f * v)
{
    v->x = 1.0f; v->y = 0.0f; v->z = 0.0f;
}

/**
 * @brief Еденичный вектор, указывающий назад в
 * правосторонней системе координат (0, 0, -1)
 * @param v Указатель на вектор
 */
void Vector3f_InitForwardRH(Vector3f * v)
{
    v->x = 0.0f; v->y = 0.0f; v->z = -1.0f;
}

/**
 * @brief Еденичный вектор, указывающий назад в
 * левосторонней системе координат (0, 0, 1)
 * @param v Указатель на вектор
 */
void Vector3f_InitForwardLH(Vector3f * v)
{
    v->x = 0.0f; v->y = 0.0f; v->z = 1.0f;
}

/**
 * @brief Еденичный вектор, указывающий вперёд в
 * правосторонней системе координат (0, 0, -1)
 * @param v Указатель на вектор
 */
void Vector3f_InitBackwardRH(Vector3f * v)
{
    v->x = 0.0f; v->y = 0.0f; v->z = 1.0f;
}

/**
 * @brief Еденичный вектор, указывающий вперёд в
 * левосторонней системе координат (0, 0, -1)
 * @param v Указатель на вектор
 */
void Vector3f_InitBackwardLH(Vector3f * v)
{
    v->x = 0.0f; v->y = 0.0f; v->z = -1.0f;
}

/**
 * @brief Заполняет вектор \c v значением \c scalar
 * @param v Указатель на вектор
 * @param scalar Значение для заполнения
 */
void Vector3f_InitScalar(Vector3f * v, float32_t scalar)
{
    v->x = scalar; v->y = scalar; v->z = scalar;
}


/**
 * @brief Расчитывает длину вектора
 * @param v Указатель на вектор
 * @return Длина вектора
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
 * @brief Расчитывает квадрат длины вектора
 * @param v Указатель на вектор
 * @return Квадрат длины вектора
 */
float32_t Vector3f_LengthSquared(Vector3f * v)
{
    float dot;
    float *array = (float*)v;
    arm_dot_prod_f32(array, array, 3, &dot);
    return dot;
}

/**
 * @brief Преобразует вектор в еденичный вектор
 * @param[in, out] v Указатель на вектор
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
 * @brief Записывает сумму векторов \c l и \c r в вектор \c o
 * @param[in] l Указатель на первый вектор
 * @param[in] r Указатель на второй вектор
 * @param[out] o Указатель на вектор, куда запишется сумма
 */
void Vector3f_InitAdd(const Vector3f * l,const Vector3f * r, Vector3f * o)
{
    o->x = l->x + r->x;
    o->y = l->y + r->y;
    o->z = l->z + r->z;
}

/**
 * @brief Прибавляет к вектору \c v вектор \c a
 * @param[in, out] v Указатель на вектор, к которому прибавится значение
 * @param[in] a Указатель на вектора, который нужно прибавить
 */
void Vector3f_Add(Vector3f * v,const Vector3f * a)
{
    v->x += a->x;
    v->y += a->y;
    v->z += a->z;
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
    o->x = l->x + scalar;
    o->y = l->y + scalar;
    o->z = l->z + scalar;
}

/**
 * @brief Прибавляет к вектору \c v скаляр \c scalar
 * @param[in, out] v Указатель на вектор, к которому прибавится значение
 * @param[in] scalar Скалярное значение, которое необходимо прибавить
 */
void Vector3f_AddScalar(Vector3f * v,float scalar)
{
    v->x += scalar;
    v->y += scalar;
    v->z += scalar;
}


/**
 * @brief Записывает разность векторов \c l и \c r в вектор \c o
 * @param[in] l Указатель на первый вектор
 * @param[in] r Указатель на второй вектор
 * @param[out] o Указатель на вектор, куда запишется разность
 */
void Vector3f_InitSubtract(const Vector3f * l, const Vector3f * r, Vector3f * o)
{
    o->x = l->x - r->x;
    o->y = l->y - r->y;
    o->z = l->z - r->z;
}

/**
 * @brief Отнимает от вектора \c v вектор \c a
 * @param[in, out] v Указатель на вектор, от которого отнимется значение
 * @param[in] a Указатель на вектора, который нужно отнять
 */
void Vector3f_Subtract(Vector3f * v, const Vector3f * a)
{
    v->x -= a->x;
    v->y -= a->y;
    v->z -= a->z;
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
    o->x = l->x - scalar;
    o->y = l->y - scalar;
    o->z = l->z - scalar;
}

/**
 * @brief Отнимает от вектора \c v скаляр \c scalar
 * @param[in, out] v Указатель на вектор, от которого отнимется значение
 * @param[in] scalar Скалярное значение, которое необходимо отнять
 */
void Vector3f_SubtractScalar(Vector3f * v, float scalar)
{
    v->x -= scalar;
    v->y -= scalar;
    v->z -= scalar;
}


/**
 * @brief Записывает покомпонентное умножение вектора \c l
 * на вектор \c r в вектор \c o
 * @param[in] l Указатель на первый вектор
 * @param[in] r Указатель на второй вектор
 * @param[out] o Указатель на вектор, куда запишется результат умножения
 */
void Vector3f_InitMultiply(const Vector3f * l, const Vector3f * r, Vector3f * o)
{
    o->x = l->x * r->x;
    o->y = l->y * r->y;
    o->z = l->z * r->z;
}

/**
 * @brief Умножает покомпонентно вектор \c v на вектор \c a
 * @param[in, out] v Указатель на вектор, который умножается
 * @param[in] a Указатель на вектора, на который нужно умножить
 */
void Vector3f_Multiply(Vector3f * v, const Vector3f * a)
{
    v->x *= a->x;
    v->y *= a->y;
    v->z *= a->z;
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
    o->x = l->x * scalar;
    o->y = l->y * scalar;
    o->z = l->z * scalar;
}

/**
 * @brief Умножает вектор \c v на скаляр \c scalar
 * @param[in, out] v Указатель на вектор
 * @param[in] scalar Скалярное значение, на которое необходимо умножить
 */
void Vector3f_MultiplyScalar(Vector3f * v, float scalar)
{
    v->x *= scalar;
    v->y *= scalar;
    v->z *= scalar;
}

/**
 * @brief Записывает покомпонентное деление вектора \c l
 * на вектор \c r в вектор \c o
 * @param[in] l Указатель на первый вектор
 * @param[in] r Указатель на второй вектор
 * @param[out] o Указатель на вектор, куда запишется результат деления
 */
void Vector3f_InitDivide(const Vector3f * l, const Vector3f * r, Vector3f * o)
{
    o->x = l->x / r->x;
    o->y = l->y / r->y;
    o->z = l->z / r->z;
}

/**
 * @brief Делит покомпонентно вектор \c v на вектор \c a
 * @param[in, out] v Указатель на вектор, который делится
 * @param[in] a Указатель на вектора, на который нужно поделить
 */
void Vector3f_Divide(Vector3f * v, const Vector3f * a)
{
    v->x -= a->x;
    v->y -= a->y;
    v->z -= a->z;
}

/**
 * @brief Записывает деление вектора \c l на скаляр \c scalar в вектор \c o
 * @param[in] l Указатель на первый вектор
 * @param[in] scalar Скалярное значение, на которое необходимо поделить
 * @param[out] o Указатель на вектор с делением каждого элемета
 * на скалярную величину
 */
void Vector3f_InitDivideScalar(const Vector3f * l, float scalar, Vector3f * o)
{
    o->x = l->x / scalar;
    o->y = l->y / scalar;
    o->z = l->z / scalar;
}

/**
 * @brief Делит вектор \c v на скаляр \c scalar
 * @param[in, out] v Указатель на вектор
 * @param[in] scalar Скалярное значение, на которое необходимо поделить
 */
void Vector3f_DivideScalar(Vector3f * v, float scalar)
{
    v->x /= scalar;
    v->y /= scalar;
    v->z /= scalar;
}

/**
 * @brief Записывает в \c o вектор, обратный по направлению
 * вектору \c v
 * @param v Указатель на вектор
 * @param o обратный по направлению вектор
 */
void Vector3f_InitNegate(const Vector3f * v, Vector3f * o)
{
    o->x = -v->x;
    o->y = -v->y;
    o->z = -v->z;
}

/**
 * @brief Изменяет нарпавление вектора \c v на обратное
 * @param v Указатель на вектор
 */
void Vector3f_Negate(Vector3f * v)
{
    v->x = -v->x;
    v->y = -v->y;
    v->z = -v->z;
}


/**
 * @brief Записывает в вектор \c o координаты точки, указанной
 * в барицентрических координатах относительно
 * трёхмерного треугольника
 * @param[in] v1 1-я координата вершины треугольника
 * @param[in] v2 2-я координата вершины треугольника
 * @param[in] v3 3-я координата вершины треугольника
 * @param[in] amount1 Барицентрическая координата b2,
 * которая выражает весовой коэффициент по отношению к вершине 2
 * @param[in] amount2 Барицентрическая координата b3,
 * которая выражает весовой коэффициент по отношению к вершине 3
 * @param[out] o Возвращаемое значение
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
 * @brief Ограничивает значения в рамках указанного диапазона
 * @param[in] v вектор, который нужно ограничить
 * @param[in] min минимальное значение
 * @param[in] max 3-я максимальное значение
 * @param[in] amount1 Барицентрическая координата b2,
 * которая выражает весовой коэффициент по отношению к вершине 2
 * @param[in] amount2 Барицентрическая координата b3,
 * которая выражает весовой коэффициент по отношению к вершине 3
 * @param[out] o Возвращаемое значение
 */
void Vector3f_InitClamp(const Vector3f * v,
        const Vector3f * min, const Vector3f * max,
        Vector3f *o)
{
   /* o->x = v1->x + amount1 * (v2->x - v1->x) + amount2 * (v3->x - v1->x);
    o->y = v1->y + amount1 * (v2->y - v1->y) + amount2 * (v3->y - v1->y);
    o->z = v1->z + amount1 * (v2->z - v1->z) + amount2 * (v3->z - v1->z);*/
}

