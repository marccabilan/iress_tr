#include "iress_tr_command_handler.h"
#include "iress_tr_table.h"
#include <iostream>



//--------------------------------------------------------------
//! @details
//!     The interface commands and its corresponding handler is listed in the table below.
//--------------------------------------------------------------
const iress_tr_command_handler::IRESS_TR_COMMAND_HANDLER_TABLE
iress_tr_command_handler::s_iress_tr_command_handler_table_[] = {
	{	IRESS_TR_COMMAND_ID_PLACE,		&iress_tr_command_handler::handler_place	},
	{	IRESS_TR_COMMAND_ID_MOVE,		&iress_tr_command_handler::handler_move		},
	{	IRESS_TR_COMMAND_ID_LEFT,		&iress_tr_command_handler::handler_left		},
	{	IRESS_TR_COMMAND_ID_RIGHT,		&iress_tr_command_handler::handler_right	},
	{	IRESS_TR_COMMAND_ID_REPORT,		&iress_tr_command_handler::handler_report	},
};

const UINT iress_tr_command_handler::s_iress_tr_command_handler_table_size_= sizeof(iress_tr_command_handler::s_iress_tr_command_handler_table_) / sizeof(iress_tr_command_handler::s_iress_tr_command_handler_table_[0]);

iress_tr_command_handler::iress_tr_command_handler() {
    // since the current requirements is a fixed-size table, it ok to set the size here using the Globally defined
    // table size, change this in case the table size is variable
    // m_table.SetSize(IRESS_TR_TABLE_MAX_SIZE_X, IRESS_TR_TABLE_MAX_SIZE_Y);
}

iress_tr_command_handler::~iress_tr_command_handler() {

}

//--------------------------------------------------------------
//! @details
//!     the main interface to the lower modules.
//!     perform processing of the command ids from the application and dispatch
//!     to the appropriate handler function of the received command.
//--------------------------------------------------------------
void iress_tr_command_handler::iress_tr_command_handler_facade (IRES_TR_COMMAND_ID command_id ,const std::map<IRES_TR_NODE_ID, LONG>& request) {

	//std::cout << "CALL LOGS:: toy_robot_handler.iress_tr_command_handler_facade:" << command_id << std::endl;
	
	// dispatach the command to its handler functions
	for (int index = 0; index < s_iress_tr_command_handler_table_size_; index++) {
		if (command_id == s_iress_tr_command_handler_table_[index].command_id) {
			if (NULL != s_iress_tr_command_handler_table_[index].func_p) {
				(this->* (s_iress_tr_command_handler_table_[index].func_p))(request);
				break;
			}else { /* nothing to do. */ }
		} else { /* nothing to do. */ }
	}

}

//--------------------------------------------------------------
//! place command handler.
//--------------------------------------------------------------
void iress_tr_command_handler::handler_place(const std::map<IRES_TR_NODE_ID, LONG> &request) {


	//std::cout << "ENTRY LOGS:: iress_tr_command_handler::handler_place:" << std::endl;

	int pos_x = 0;
	int pos_y = 0;
	IRESS_TR_DIRECTION direction = IRESS_TR_DIRECTION_NORTH;

	// Gets the x coordinates from the request parameters of the command
	auto map_it = request.find(IRES_TR_NODE_ID_X);;
	
	if (map_it != request.end()) {
		pos_x = map_it->second;
	} else {
		std::cout << "pox x not found" << std::endl;
	}

	// Gets the y coordinates from the request parameters of the command
	map_it = request.find(IRES_TR_NODE_ID_Y);
	if (map_it != request.end()) {
		pos_y = map_it->second;
	} else {
		std::cout << "pox y not found" << std::endl;
	}

	// Gets the direction from the request parameters of the command
	map_it = request.find(IRES_TR_NODE_ID_DIRECTION);
	if (map_it != request.end()) {
		direction = static_cast<IRESS_TR_DIRECTION>(map_it->second);
	} else {
		std::cout << "direction not found" << std::endl;
	}

	m_table.processPlaceCommand( pos_x, pos_y, direction);

}

//--------------------------------------------------------------
//! place command handler.
//--------------------------------------------------------------
void iress_tr_command_handler::handler_move(const std::map<IRES_TR_NODE_ID, LONG>& request)
{
	m_table.processMoveCommand();
}

//--------------------------------------------------------------
//! place command handler.
//--------------------------------------------------------------
void iress_tr_command_handler::handler_left(const std::map<IRES_TR_NODE_ID, LONG>& request)
{
	m_table.processLeftCommand();
}

//--------------------------------------------------------------
//! place command handler.
//--------------------------------------------------------------
void iress_tr_command_handler::handler_right(const std::map<IRES_TR_NODE_ID, LONG>& request)
{
	m_table.processRightCommand();
}

//--------------------------------------------------------------
//! place command handler.
//--------------------------------------------------------------
void iress_tr_command_handler::handler_report(const std::map<IRES_TR_NODE_ID, LONG>& request)
{	
	m_table.processReportCommand();
}

