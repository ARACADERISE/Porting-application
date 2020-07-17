#ifndef PORTER_H
#define PORTER_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* PORT ARRAY MAX SIZE */
#define DefaultMemSize 							0xFFFF /* 
    DefaultMemSize: Allocating 65535 indexes so we don't have to consanty re-allocate sizes.
*/

/* 
	IMPORTANT PORT: KeyPort
	This port will be the key to startup as well as access of other ports
*/
#define KeyPort									0xFA0 // Entry Port: 4000
#define AllocPort 							0xEAE
#define MEMPort   							0xAAf
#define PrintPortDefault                0x1ABF // Indicator that application is appending a output
#define PrintPortSTART					0x1ACF
#define PrintPortEND    				0x1CB9
#define PrintPortEntryPoints		PrintPortEND - PrintPortSTART

/* 
	DIMENSION THE PORTS CAN DWELL IN
	Each dimension will have there own functionalities 
*/
#define Normal_Dim_Mode 0xA50 // Dimension Port: 2640:A
#define High_Dim_Mode  	0xAE1 // Dimension Port: 2785:B
#define Low_Dim_Mode		0xC10 // Dimension Port: 3088:C
#define Strict_Dim_Mode	0xCF1 // Dimension Port: 3313:D


/* STRUCT WORKING WITH DIMENSIONS */
struct DIMENSIONS{
	int DIMENSION_NUMBER;
	char LETTER;
} DIMENSIONS_;

/* KEYS FOR THE PORTS */
extern int KEY_PORT;
extern int ALLOC_PORT;
extern int MEM_PORT;
extern int PRINT_PORT_START;
extern int PRINT_PORT_END;

/* 
	Easier to use DIM instead of having to re-define DIMENSIONS using :
	struct DIMENSIONS DIMENSIONS[] = {}
*/
//typedef struct DIMENSIONS DIM[];

/* STRUCT WORKING WITH PORTS */
typedef struct {
    int i; // Index number for Memory
	struct {
		/* 
			The KEY_PORT will be the port that keeps track of everything going on, including memory mangement
		*/
		int KEY_PORT_;
		size_t Memory[DefaultMemSize+1]; /* 
			Index 0 is set to MaxMemory since blocks of memory will be managed at once, as well as re-assigned.
			The Memory array will update everytime the recent port accesses memory.
		*/
		struct {
			/* Struct keeps track of ports and the memory that port used */
			int PrevPortNumbers[0xFFFF];
			int MemoryFromPort[0xFFFF];
		} PortInformation;
	} KeyPORT;
    struct {
        int entry_points;
        char* PPEntryPoints;
        char booted_dimension;
        int default_port;
    } E_P;

    enum {
        KEY_PORT_=KeyPort,
        ALLOC_PORT_=AllocPort,
        MEM_PORT_=MEMPort,
        PRINT_PORT_=PrintPortDefault
    } port;
    enum {
        NORM_DIM=Normal_Dim_Mode,
        HIGH_DIM=High_Dim_Mode,
        LOW_DIM=Low_Dim_Mode,
        STRICT_DIM=Strict_Dim_Mode
    } dimension;

    /* 
        dim - holds the DIMENSION_NUMBER and the letter to the dimension
        dim_ - sets up the actual DIM_ struct that will carry the information throughout the application */
    struct DIMENSIONS* dim;
    struct DIM_STRUCT* dim_;
	// To-Do
	/* Make this struct useful for working with the ports */
} PORTS;

/* Making it easier to assign the PORTS struct */
typedef PORTS p;

/* Assigned after re-defining PrintPortEntryPoints since PRINT_PORT_ENTRY_POINTS is static and keeps its value. */
extern int PRINT_PORT_ENTRY_POINTS;

PORTS* key_port_starter();
struct DIM_STRUCT* key_port_setup_dim(PORTS* port);
PORTS* key_port_adapt(PORTS* port);
PORTS* key_port_update(PORTS* port, size_t mem_used, int port_id);

#endif