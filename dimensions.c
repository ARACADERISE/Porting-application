#include <stdio.h>
#include "dimensions.h"
#include "porter.h"

DIM_* default_dimension_setup(PORTS* port) {
    DIM_* dim = malloc(sizeof(DIM_));
    dim->DimensionIndexNumber = 0;

    dim->ports = port->dim_->ports;
    /* 
        dim->dim will be a struct array for storing seperate uses of each dimension in a 
        seperate index number(dim->DimensionIndexNumber)
    */
    dim->dim = calloc(1,sizeof(dim->dim));
    dim->dim[dim->DimensionIndexNumber] = *port->dim_->dim;
    dim->dimension_port = port->dim_->dimension_port;
    
    return dimension_get_dimension_port(dim); 
}

DIM_* dimension_setup_normal_mode(DIM_* dim) {

    dim->NormalMode.port_in_use = dim->dimension_port;
    dim->NormalMode.memory_span = NORMAL_DIMENSION;
    dim->NormalMode.from_memory_block = dim->ports->KeyPORT.Memory[0]-dim->NormalMode.memory_span;

    /* Allocating block memory */
    dim->NormalMode.memory_usage_blocks = calloc(
        dim->NormalMode.from_memory_block+1,
        sizeof(int)
    );
    dim->NormalMode.memory_usage_blocks[0] = dim->NormalMode.from_memory_block;

    return dim;
}
DIM_* dimensions_setup_strict_mode(DIM_* dim) {
    return dim;
}
DIM_* dimensions_setup_high_mode(DIM_* dim) {
    return dim;
}
DIM_* dimension_setup_low_mode(DIM_* dim) {
    return dim;
}

DIM_* dimension_get_dimension_port(DIM_* dim) {
    
    switch(dim->dimension_port) {
        case Normal_Dim_Mode: dimension_setup_normal_mode(dim);break;
        case Strict_Dim_Mode: dimensions_setup_strict_mode(dim);break;
        case High_Dim_Mode: dimensions_setup_high_mode(dim);break;
        case Low_Dim_Mode: dimension_setup_low_mode(dim);break;
    }

    return dim;
}