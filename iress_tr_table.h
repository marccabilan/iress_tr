#ifndef TABLE_H
#define TABLE_H

#include "iress_tr_table.h"
#include "iress_tr_robot.h"
#include "iress_tr_defines.h"

class iress_tr_table {
public:
    iress_tr_table();

    //--------------------------------------------------------------
    //! processPlaceCommand function.
    //!		@param[in]		pos_x					x-coordinate. 
    //!		@param[in]		pos_y					y-coordinate. 
    //!		@param[in]		direction				robot's face direction.
    //--------------------------------------------------------------
    //! @details
    //!     wrapper function to robot's place function
    //--------------------------------------------------------------
    void processPlaceCommand(int pos_x, int pos_y, IRESS_TR_DIRECTION direction);

    //--------------------------------------------------------------
    //! processMoveCommand.
    //!     no param
    //--------------------------------------------------------------
    //! @details
    //!     wrapper function to robot's move function
    //--------------------------------------------------------------
    void processMoveCommand();

    //--------------------------------------------------------------
    //! processMoveCommand.
    //!     no param
    //--------------------------------------------------------------
    //! @details
    //!     wrapper function to robot's left rotate function
    //--------------------------------------------------------------
    void processLeftCommand();

    //--------------------------------------------------------------
    //! processMoveCommand.
    //!     no param
    //--------------------------------------------------------------
    //! @details
    //!     wrapper function to  robot's right rotate function
    //--------------------------------------------------------------
    void processRightCommand();

    //--------------------------------------------------------------
    //! processReportCommand.
    //!     no param
    //--------------------------------------------------------------
    //! @details
    //!     wrapper function to robot's report function
    //--------------------------------------------------------------
    void processReportCommand();


private:
    // the table can only have one instance of robot
    // in the future, implement as vector and assigned ids to each robot
    iress_tr_robot robot;

    // For Improvement: Implement table size to be a variable
    //                  in the comment requirement, the table is fixed
    int table_size_x; 
    int table_size_y; 

};

#endif // TABLE_H