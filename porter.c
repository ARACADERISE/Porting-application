#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "porter.h"
#include "dimensions.h"

int PRINT_PORT_ENTRY_POINTS;

PORTS* key_port_starter() {

    p* kp = (p*)malloc(sizeof(p));

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

    /* ASSIGNING A,B,C,D TO DIMENSION PORTS */
	DIM DIMENSIONS = {
		{Normal_Dim_Mode,kp->E_P.PPEntryPoints[0]},
		{High_Dim_Mode,kp->E_P.PPEntryPoints[1]},
		{Low_Dim_Mode,kp->E_P.PPEntryPoints[2]},
		{Strict_Dim_Mode,kp->E_P.PPEntryPoints[3]}
	};

  kp->dim = calloc(4,sizeof(kp->dim));
  for(int i = 0; i < 4; i++) {
    kp->dim[i].DIMENSION_NUMBER = DIMENSIONS[i].DIMENSION_NUMBER;
    kp->dim[i].LETTER = DIMENSIONS[i].LETTER;
  }

	/* Booted into Normal Dimension Mode: A - 65 */\
	kp->E_P.booted_dimension = kp->dim[0].LETTER;\

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
    port->dim_ = malloc(sizeof(port->dim_));
    port->dim_->ports = port;
    port->dim_->dim = &port->dim;
    port->dim_->dimension_port = port->dimension;

    default_dimension_setup(port);
    free(port->dim);

    return port->dim_;
}