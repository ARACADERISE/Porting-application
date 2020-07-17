#include <stdio.h>
#include "dimensions.h"
#include "porter.h"

// Setting up dimension struct
DIM_* default_dimension_setup(PORTS* port,int dim_port) {
    DIM_** dim = calloc(5,sizeof(DIM_**)); // the index of zero will be the "extra"
    /*
        Memory allocation still needs to happend so we allocate a chunk of memory
    */
    dim[0] = malloc(sizeof(DIM_**));
    dim[1] = malloc(sizeof(DIM_**));
    dim[2] = malloc(sizeof(DIM_**));
    dim[3] = malloc(sizeof(DIM_**));
    dim[4] = malloc(sizeof(DIM_**));

    dim[0]->DimensionIndexNumber = 0;

    dim[0]->ports = port->dim_->ports;
    dim[0]->ports->dim_->dimension_id = dim_port; /*
        For some reason, when we allocate memory for the dim struct array, the dimension_port changes to 
        49(from its default value of 2640:a, the default dimension bootup)
    */

    /* 
        dim->dim will be a struct array for storing seperate uses of each dimension in a 
        seperate index number(dim->DimensionIndexNumber)
    */
    dim[0]->dim = calloc(1,sizeof(struct DIMENSIONS**));
    dim[0]->dim[dim[0]->DimensionIndexNumber] = *port->dim_->dim;
    dim[0]->dimension_id = dim[0]->ports->dim_->dimension_id;

    /* Setting all modes to void pointer */

    // NormalMode
    dim[1]->NormalMode.port_in_use = (void*)0;
    dim[1]->NormalMode.memory_span = (void*)0;
    dim[1]->NormalMode.from_memory_block = (void*)0;
    // ToDo: Strict mode
    
    return dimension_get_dimension_port(dim); 
}

// This will release a certain block of memory co-relating to a certain dimension instead of releasing memory of the whole DIM_ struct
DIM_* release_normal_mode_memory(DIM_** dim) {
    
    /* 
        Reseting all ideals to void pointers...free function cannot be used on non-void ideals.. 

        port_in_use and memory_span will stay. No need to release some very very basic and useful logic 
        from the dimension.
    */

    // This needs to be done. We cannot store this while the dimension is not in use..will occurr in a memory error
    dim[1]->NormalMode.from_memory_block = (void*)0;
    // Since the user wants to release memory of the Normal Mode dimension, that means we need to clear all memory kept about its memory usage
    free(dim[1]->NormalMode.memory_usage_blocks); // Free it
    dim[1]->NormalMode.memory_usage_blocks = (void*)0; // Set it to a void pointer

    return *dim;
}

// Test Function
DIM_* dimension_update_normal_mode(DIM_** dim) {
    return *dim;
}

DIM_* dimension_setup_normal_mode(DIM_** dim) {

    /*
        If the memory_usage_blocks is a void pointer, then that means there has been no memory 
        allocations on normal_mode, or it has
        been recently released.
    */
    if(dim[1]->NormalMode.from_memory_block==(void*)0) {
        //dim[1]->NormalMode.port_in_use = dim[0]->dimension_port;
        dim[1]->NormalMode.memory_span = NORMAL_DIMENSION;
        dim[1]->NormalMode.from_memory_block = dim[0]->ports->KeyPORT.Memory[0]-dim[1]->NormalMode.memory_span;

        /* Allocating block memory */
        dim[1]->NormalMode.memory_usage_blocks = calloc(
            dim[1]->NormalMode.from_memory_block+1,
            sizeof(dim[1]->NormalMode.memory_usage_blocks)
        );
        dim[1]->NormalMode.memory_usage_blocks[0] = dim[1]->NormalMode.from_memory_block;
    }
    else {
        // ToDo: Figure out what to do with the already existing information
        return dimension_update_normal_mode(dim);
    }

    return *dim;
}
DIM_* dimensions_setup_strict_mode(DIM_** dim) {

    //dim->StrictMode.port_in_use = dim->dimension_port;
    //dim->StrictMode.memory_span = STRICT_DIMENSION;

    return *dim;
}
DIM_* dimensions_setup_high_mode(DIM_** dim) {
    return *dim;
}
DIM_* dimension_setup_low_mode(DIM_** dim) {
    return *dim;
}

DIM_* dimension_get_dimension_port(DIM_** dim) {

    switch(dim[0]->dimension_id) {
        case Normal_Dim_Mode: dimension_setup_normal_mode(dim);break;
        case Strict_Dim_Mode: dimensions_setup_strict_mode(dim);break;
        case High_Dim_Mode: dimensions_setup_high_mode(dim);break;
        case Low_Dim_Mode: dimension_setup_low_mode(dim);break;
    }

    return *dim;
}