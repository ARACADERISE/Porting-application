#ifndef PORTER_H
#define PORTER_H
#include <string.h>
#include <stdlib.h>

/* PORT ARRAY MAX SIze */
#define MaxMemorySize 							0xAFF /* 2815 to begin with. Number will increase within each dimension */

/* 
	IMPORTANT PORT: KeyPort
	This port will be the key to startup as well as access of other ports
*/
#define KeyPort									0xFA0 // Entry Port: 4000
#define AllocPort 							0xEAE
#define MEMPort   							0xAAf
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
static int KEY_PORT = KeyPort;
static int ALLOC_PORT = AllocPort;
static int MEM_PORT = MEMPort;
static int PRINT_PORT_START = PrintPortSTART;
static int PRINT_PORT_END = PrintPortEND;

/* 
	ARRAY DATA FOR THE PORTS. 
	PP: PrintPort 
*/
//static char PPEntryPoints[PrintPortEntryPoints+1/*+1: For the dimension.*/];

/* 
	Easier to use DIM instead of having to re-define DIMENSIONS using :
	struct DIMENSIONS DIMENSIONS[] = {}
*/
typedef struct DIMENSIONS DIM[];

/* STRUCT WORKING WITH PORTS */
typedef struct {
    int i;
	struct {
		/* 
			The KEY_PORT will be the port that keeps track of everything going on, including memory mangement
		*/
		int KEY_PORT_;
		size_t Memory[MaxMemorySize+1]; /* 
			Set to MaxMemory since blocks of memory will be managed at once, as well as re-assigned.
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
    } E_P;

    struct DIMENSIONS* dim;
	// To-Do
	/* Make this struct useful for working with the ports */
} PORTS;

/* Making it easier to assign the PORTS struct */
typedef PORTS p;

/* Assigned after re-defining PrintPortEntryPoints since PRINT_PORT_ENTRY_POINTS is static and keeps its value. */
extern int PRINT_PORT_ENTRY_POINTS;

PORTS* key_port_starter();
PORTS* key_port_update(PORTS* port, size_t mem_used, int port_id);

#endif