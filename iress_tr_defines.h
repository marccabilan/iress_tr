#pragma once

#define UINT	unsigned int
#define	ULONG	unsigned long
#define LONG	long
//-----------------------------------------
//! Enums declaration
//-----------------------------------------

enum  IRESS_TR_DIRECTION
{
	IRESS_TR_DIRECTION_UNKNOWN	=	0,
	IRESS_TR_DIRECTION_NORTH	=	1,
	IRESS_TR_DIRECTION_EAST		=	2,
	IRESS_TR_DIRECTION_SOUTH	=	3,
	IRESS_TR_DIRECTION_WEST		=	4,
};


//-----------------------------------------
//! Defines declaration
//-----------------------------------------

const UINT IRESS_TR_TABLE_MAX_SIZE_X = 5;
const UINT IRESS_TR_TABLE_MAX_SIZE_Y = 5;

const UINT IRESS_TR_TABLE_ORIGIN_X = 0;
const UINT IRESS_TR_TABLE_ORIGIN_Y = 0;

const UINT IRESS_TR_INVALID_POS_X = -1;
const UINT IRESS_TR_INVALID_POS_Y = -1;


//-----------------------------------------
//! Command ID and Node IDs
//-----------------------------------------

typedef ULONG IRES_TR_COMMAND_ID;

const IRES_TR_COMMAND_ID	IRESS_TR_COMMAND_ID_UNKNOWN		= 0;
const IRES_TR_COMMAND_ID	IRESS_TR_COMMAND_ID_PLACE		= 1;
const IRES_TR_COMMAND_ID	IRESS_TR_COMMAND_ID_MOVE		= 2;
const IRES_TR_COMMAND_ID	IRESS_TR_COMMAND_ID_LEFT		= 3;
const IRES_TR_COMMAND_ID	IRESS_TR_COMMAND_ID_RIGHT		= 4;
const IRES_TR_COMMAND_ID	IRESS_TR_COMMAND_ID_REPORT		= 5;

typedef ULONG IRES_TR_NODE_ID;

const IRES_TR_NODE_ID 	IRES_TR_NODE_ID_UNKNOWN				= 0;
const IRES_TR_NODE_ID 	IRES_TR_NODE_ID_X					= 1;
const IRES_TR_NODE_ID 	IRES_TR_NODE_ID_Y					= 2;
const IRES_TR_NODE_ID 	IRES_TR_NODE_ID_DIRECTION			= 3;





