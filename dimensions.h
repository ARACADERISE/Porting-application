#ifndef DIMENSION_H
#define DIMENSION_H
#include "porter.h"

typedef struct DIM_STRUCT {
    int DimensionIndexNumber;
    p* ports;
    struct DIMENSIONS** dim;
    int dimension_id;
    struct {
        int port_in_use;
        size_t memory_span;
        size_t from_memory_block; /* 
            This will be the total ammount of memory leftover from struct PORTS Memory array lists last 
            allocation(index number i) - the total memory in the now active dimension.
        */
        size_t* memory_usage_blocks;
    } NormalMode;
    struct {} StrictMode;
    struct {} HighMode;
    struct {} LowMode;
} DIM_;

#define NORMAL_DIMENSION    0x1AF1 // 6897
#define LOW_DIMENSION       0x1551 // 5617
#define STRICT_DIMENSIOIN   0x0F20 /* 
    3872, will change depending on memory management and or memory ammounts
    being used up.
*/
#define HIGH_DIMENSION      0xDCF2 // 56562

DIM_* default_dimension_setup(PORTS* port, int dim_port);
DIM_* dimension_get_dimension_port(DIM_** dim);

#endif