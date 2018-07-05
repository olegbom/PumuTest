#include <stdint.h>

            typedef struct _tGLYPH
            {
                uint8_t Y0;
                uint8_t Y1;
                uint8_t Width;
                uint32_t Index;
            } MyGLYPH;

            typedef struct _tFont
            {
                const uint32_t* table;
                const MyGLYPH* glyphTable;
                uint8_t Height;
                uint8_t Letter_spacing;
            } MyFONT;

extern MyFONT PT_Sans13;

extern MyFONT PT_Sans7;