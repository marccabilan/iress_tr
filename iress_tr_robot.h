#include "iress_tr_defines.h"
#include <string>


class iress_tr_robot {
public:
    iress_tr_robot();

    //--------------------------------------------------------------
    //! place function.
    //!		@param[in]		x						x-coordinate. 
    //!		@param[in]		y						y-coordinate. 
    //!		@param[out]		direction				robot's face direction.
    //--------------------------------------------------------------
    //! @details
    //!     places the robot in the table
    //--------------------------------------------------------------
    void place(int x, int y, IRESS_TR_DIRECTION direction);

    //--------------------------------------------------------------
    //! move function.
    //!		@retval[out]	true				    robot is movement is successfully.
    //!		@retval[out]	false				    robot is movement has failed.
    //--------------------------------------------------------------
    //! @details
    //!     moves the robot by 1 step
    //--------------------------------------------------------------
    bool move();

    //--------------------------------------------------------------
    //! left function.
    //!    no param    	 		
    //--------------------------------------------------------------
    //! @details
    //!    rotates the robot 90 degrees counter clockwise 
    //--------------------------------------------------------------
    void left();

    //--------------------------------------------------------------
    //! right function.
    //!    no param    	 		
    //--------------------------------------------------------------
    //! @details
    //!    rotates the robot 90 degrees clockwise 
    //--------------------------------------------------------------
    void right();

    //--------------------------------------------------------------
    //! report function.
    //!    no param    	 		
    //--------------------------------------------------------------
    //! @details
    //!    reports the x, y coordinates and face direction of the robot via
    //!    standard output. 
    //--------------------------------------------------------------
    void report() const;

    //--------------------------------------------------------------
    //! is placed function.
    //!    @retval[out]        false   the robot is not placed in the table
    //!    @retval[out]        true    the robot is already placed in the table       	 		
    //--------------------------------------------------------------
    //! @details
    //!    flags to indicate the robot has been placed already or not.
    //--------------------------------------------------------------
    bool isPlaced() const;

private:
    //--------------------------------------------------------------
    //! is placed function.
    //!    @param[in]        newDirection   the updated direction of the Robot       	 		
    //--------------------------------------------------------------
    //! @details
    //!    sets the updated direction of the robot.
    //--------------------------------------------------------------
    void updateDirection(IRESS_TR_DIRECTION newDirection);

private:
    int pos_x_, pos_y_;             //position of robot
    IRESS_TR_DIRECTION direction_;  //face direction of robot
    bool placed_;                   //flag to know if the robot has been placed
    
};

