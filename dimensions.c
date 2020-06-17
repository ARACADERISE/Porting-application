#include "dimensions.h"
#include "porter.h"

DIM_* default_dimension_setup(PORTS* port) {
    DIM_* dim = malloc(sizeof(DIM_));

    dim->ports = port->dim_->ports;
    dim->dim = port->dim_->dim;
    dim->dimension_port = port->dim_->dimension_port;  
    
    return dim; 
}