#include "iress_tr_table.h"
#include <sstream>
#include <iostream>

iress_tr_table::iress_tr_table() {}


//--------------------------------------------------------------
//! @details
//!     wrapper function to robot's place function
//--------------------------------------------------------------
void iress_tr_table::processPlaceCommand(int pos_x, int pos_y, IRESS_TR_DIRECTION direction) {
    robot.place(pos_x, pos_y, direction);
}

//--------------------------------------------------------------
//! @details
//!     wrapper function to robot's move function
//--------------------------------------------------------------
void iress_tr_table::processMoveCommand() {
    robot.move();
}

//--------------------------------------------------------------
//! @details
//!     wrapper function to robot's left rotate function
//--------------------------------------------------------------
void iress_tr_table::processLeftCommand() {
    robot.left();
}

//--------------------------------------------------------------
//! @details
//!     wrapper function to  robot's right rotate function
//--------------------------------------------------------------
void iress_tr_table::processRightCommand() {
    robot.right();
}

//--------------------------------------------------------------
//! @details
//!     wrapper function to robot's report function
//--------------------------------------------------------------
void iress_tr_table::processReportCommand() {
    robot.report();
}