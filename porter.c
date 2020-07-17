#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "porter.h"
#include "dimensions.h"

int PRINT_PORT_ENTRY_POINTS;

int KEY_PORT = KeyPort;
int ALLOC_PORT = AllocPort;
int MEM_PORT = MEMPort;
int PRINT_PORT_START = PrintPortSTART;
int PRINT_PORT_END = PrintPortEND;

PORTS* key_port_starter() {

    p* kp = malloc(sizeof(p));

    kp->i = 0;
    kp->E_P.entry_points = PrintPortEntryPoints+1;
    kp->E_P.PPEntryPoints = calloc(kp->E_P.entry_points,sizeof(char));

    static char CHARACTER = 0x41;
    for(int i = 0; i < PrintPortEntryPoints; i++) {
      if(i==27) break;
      if(!(CHARACTER==0x5A)) {
        memset(&kp->E_P.PPEntryPoints[i],CHARACTER,sizeof(char));
        CHARACTER++;
      } else {
        memset(&kp->E_P.PPEntryPoints[i],0x5A,sizeof(char));
      }
    }

    struct DIMENSIONS *DIMENSIONS_ = calloc(4,sizeof(struct DIMENSIONS));

    /* NORMAL DIMENSION: A:2640 */
    DIMENSIONS_[0].DIMENSION_NUMBER = Normal_Dim_Mode;
    DIMENSIONS_[0].LETTER = kp->E_P.PPEntryPoints[0];
    /* HIGH DIMENSION: B:2785 */
    DIMENSIONS_[1].DIMENSION_NUMBER = High_Dim_Mode;
    DIMENSIONS_[1].LETTER = kp->E_P.PPEntryPoints[1];
    /* LOW DIMENSIONS: C:3088 */
    DIMENSIONS_[2].DIMENSION_NUMBER = Low_Dim_Mode;
    DIMENSIONS_[2].LETTER = kp->E_P.PPEntryPoints[2];
    /* STRICT DIMENSION: D:3313 */
    DIMENSIONS_[3].DIMENSION_NUMBER = Strict_Dim_Mode;
    DIMENSIONS_[3].LETTER = kp->E_P.PPEntryPoints[3];

    kp->dim = calloc(4,sizeof(DIMENSIONS_));
    for(int i = 0; i < 4; i++) {
        kp->dim[i].DIMENSION_NUMBER = DIMENSIONS_[i].DIMENSION_NUMBER;
        kp->dim[i].LETTER = DIMENSIONS_[i].LETTER;
    }
    // No longer needed
    free(DIMENSIONS_);

    /* Booted into Normal Dimension Mode: A - 65 */
    kp->E_P.booted_dimension = kp->dim[0].LETTER;
    kp->E_P.default_port = MEM_PORT;

    /* For KeyPORT */
    kp->KeyPORT.KEY_PORT_ = KEY_PORT;
    kp->KeyPORT.Memory[kp->i] = DefaultMemSize;

    /* For port information. This will have the KEY_PORT number as the first index. */
    kp->KeyPORT.PortInformation.PrevPortNumbers[kp->i] = KEY_PORT;
    kp->KeyPORT.PortInformation.MemoryFromPort[kp->i] = 0;
    
#undef PrintPortEntryPoints
#define PrintPortEntryPoints PrintPortEND - PrintPortSTART - 26

    /* Re-Allocating all 26 elements */
    kp->E_P.PPEntryPoints = realloc(
        kp->E_P.PPEntryPoints, 
        (PrintPortEntryPoints + 26)*sizeof(p)
    );

    /* Assigned after re-defining PrintPortEntryPoints since PRINT_PORT_ENTRY_POINTS is static and keeps its value. */
    PRINT_PORT_ENTRY_POINTS = PrintPortEntryPoints;

    /* Last but not least, assigning port and dimension */
    kp->port=KEY_PORT; // Default: 4000
    kp->dimension=NORM_DIM; // Default: 2640-A

    key_port_setup_dim(kp);

    kp->i++;

    return kp;
}

struct DIM_STRUCT* key_port_setup_dim(PORTS* port) {
    /* Setting this up for dimensions.c */
    port->dim_ = malloc(sizeof(port->dim_)); // We want a simple block of memory
    port->dim_->ports = port;
    port->dim_->dim = &port->dim;
    port->dim_->dimension_id = port->dimension;

    default_dimension_setup(port,port->dim_->dimension_id);
    // Releasing dim_ struct. dim struct needs to stay..it stores DIMENSION_NUMBER and each dimensions letter symbol
    free(port->dim_);

    return port->dim_;
}