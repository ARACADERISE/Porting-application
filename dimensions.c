#include <stdio.h>
#include "dimensions.h"
#include "porter.h"

// Setting up dimension struct
DIM_* default_dimension_setup(PORTS* port) {
    DIM_* dim = calloc(1,sizeof(DIM_*));
    dim->DimensionIndexNumber = 0;

    dim->ports = port->dim_->ports;
    /* 
        dim->dim will be a struct array for storing seperate uses of each dimension in a 
        seperate index number(dim->DimensionIndexNumber)
    */
    dim->dim = calloc(1,sizeof(struct DIMENSIONS**));
    dim->dim[dim->DimensionIndexNumber] = *port->dim_->dim;
    dim->dimension_port = port->dim_->dimension_port;

    /* Setting all modes to void pointer */

    // NormalMode
    dim->NormalMode.port_in_use = (void*)0;
    dim->NormalMode.memory_span = (void*)0;
    dim->NormalMode.from_memory_block = (void*)0;
    dim->NormalMode.memory_usage_blocks = (void*)0;
    // ToDo: Strict mode
    
    return dimension_get_dimension_port(dim); 
}

// This will release a certain block of memory co-relating to a certain dimension instead of releasing memory of the whole DIM_ struct
DIM_* release_normal_mode_memory(DIM_* dim) {
    
    /* 
        Reseting all ideals to void pointers...free function cannot be used on non-void ideals.. 

        port_in_use and memory_span will stay. No need to release some very very basic and useful logic 
        from the dimension.
    */

    // This needs to be done. We cannot store this while the dimension is not in use..will occurr in a memory error
    dim->NormalMode.from_memory_block = (void*)0;
    // Since the user wants to release memory of the Normal Mode dimension, that means we need to clear all memory kept about its memory usage
    dim->NormalMode.memory_usage_blocks = (void*)0;

    return dim;
}

DIM_* dimension_setup_normal_mode(DIM_* dim) {

    /*
        If the memory_usage_blocks is a void pointer, then that means there has been no memory 
        allocations on normal_mode, or it has
        been recently released.
    */
    if(dim->NormalMode.memory_usage_blocks==(void*)0) {
        dim->NormalMode.port_in_use = dim->dimension_port;
        dim->NormalMode.memory_span = NORMAL_DIMENSION;
        dim->NormalMode.from_memory_block = dim->ports->KeyPORT.Memory[0]-dim->NormalMode.memory_span;

        /* Allocating block memory */
        dim->NormalMode.memory_usage_blocks = calloc(
            dim->NormalMode.from_memory_block+1,
            sizeof(int)
        );
        dim->NormalMode.memory_usage_blocks[0] = dim->NormalMode.from_memory_block;
    }
    else {
        // ToDo: Figure out what to do with the already existing information
    }

    return dim;
}
DIM_* dimensions_setup_strict_mode(DIM_* dim) {

    //dim->StrictMode.port_in_use = dim->dimension_port;
    //dim->StrictMode.memory_span = STRICT_DIMENSION;

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