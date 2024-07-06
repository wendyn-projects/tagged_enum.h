#include <stdio.h>
#include <stddef.h>
#include "tagged_union.h"

typedef struct {
    float mLength;
    float mDirection;
} Line;

struct Square {
    float mSide;
};

#define Shape(entry, ...) \
    entry(LINE, Line) \
    entry(SQUARE, struct Square) \
    entry(NUMBER, float) \
    entry(TRIANGLE, struct { float mA, mB, mC; })

tagged_union(Shape)

int main(void)
{
    size_t i;
    Shape lShapes[] = {
        tu_new(LINE,     { 1, 2 }    ),
        tu_new(TRIANGLE, { 3, 5, 6 } ),
        tu_new(NUMBER,     7         ),
        tu_new(SQUARE,   { 8 }       )
    };
    
    for (i = 0; i < sizeof(lShapes) / sizeof(*lShapes); i++)
    {
        tu_match (Shape, lShapes + i)
            on_tag (LINE, line,
                line->mDirection = 0;
                printf("len: %f dir: %f\n", line->mLength, line->mDirection);
            )
            on_tag (TRIANGLE, triangle,
                printf("sides: %f %f %f\n", triangle->mA, triangle->mB, triangle->mC);
            )
            on_tag (NUMBER, num,
                printf("%f\n", *num);
            )
        tu_end
    }
    return 0;
}
