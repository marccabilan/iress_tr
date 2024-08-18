#include "iress_tr_robot.h"
#include <iostream>

iress_tr_robot::iress_tr_robot() : pos_x_(0), pos_y_(0), direction_ (IRESS_TR_DIRECTION_NORTH), placed_(false) {

}


//--------------------------------------------------------------
//! @details
//!     places the robot in the table
//--------------------------------------------------------------
void iress_tr_robot::place(int x, int y, IRESS_TR_DIRECTION direction) {
    
    // Perform check to determine whether robot has fallen of from the table (Out of Bounds)
    if (x >= IRESS_TR_TABLE_ORIGIN_X && x < IRESS_TR_TABLE_MAX_SIZE_X && y >= IRESS_TR_TABLE_ORIGIN_Y && y < IRESS_TR_TABLE_MAX_SIZE_Y) {
        this->pos_x_ = x;
        this->pos_y_ = y;
        this->direction_ = direction;
        this->placed_ = true;
    }
    else {
        std::cerr << "Invalid PLACE command: out of bounds." << std::endl;
    }
}

//--------------------------------------------------------------
 //! @details
 //!     moves the robot by 1 step
 //--------------------------------------------------------------
bool iress_tr_robot::move() {

    bool b_ret = false;

    if (!placed_) {
        std::cout << "robot is not yet placed, perform PLACE command." << std::endl;
        return b_ret;
    }

    switch (direction_) {
        case IRESS_TR_DIRECTION_NORTH: 
            if (pos_y_ < (IRESS_TR_TABLE_MAX_SIZE_Y-1)) {
                ++pos_y_;
                b_ret = true;
            } else {/*nop*/}
            break;
        case IRESS_TR_DIRECTION_SOUTH:
            if (pos_y_ > IRESS_TR_TABLE_ORIGIN_Y) {
                --pos_y_;
                b_ret = true;
            } else {/*nop*/ }
            break;
        case IRESS_TR_DIRECTION_EAST:  
            if (pos_x_ < (IRESS_TR_TABLE_MAX_SIZE_X-1)) {
                ++pos_x_;
                b_ret = true;
            } else {/*nop*/ }
            break;
        case IRESS_TR_DIRECTION_WEST: 
            if (pos_x_ > IRESS_TR_TABLE_ORIGIN_X) {
                --pos_x_;
                b_ret = true;
            } else {/*nop*/ }
            break;
        default:
            std::cerr << "error: Unhandled direction:" << std::endl;
            break;
    }

    return b_ret;
}

//--------------------------------------------------------------
//! @details
//!    rotates the robot 90 degrees counter clockwise 
//--------------------------------------------------------------
void iress_tr_robot::left() {

    bool b_ret = false;
    IRESS_TR_DIRECTION res_direction = IRESS_TR_DIRECTION_WEST;

    if (!placed_) {
        std::cout << "robot is not yet placed, perform PLACE command." << std::endl;
        return;
    }

    switch (direction_) {
        case IRESS_TR_DIRECTION_NORTH:
            res_direction = IRESS_TR_DIRECTION_WEST;
            break;
        case IRESS_TR_DIRECTION_SOUTH:
            res_direction = IRESS_TR_DIRECTION_EAST;
            break;
        case IRESS_TR_DIRECTION_EAST:
            res_direction = IRESS_TR_DIRECTION_NORTH;
            break;
        case IRESS_TR_DIRECTION_WEST:
            res_direction = IRESS_TR_DIRECTION_SOUTH;
            break;
        default:
            std::cerr << "error: Unhandled direction:" << std::endl;
            break;
    }

    updateDirection(res_direction);

}

//--------------------------------------------------------------
//! @details
//!    rotates the robot 90 degrees clockwise 
//--------------------------------------------------------------
void iress_tr_robot::right() {

    bool b_ret = false;
    IRESS_TR_DIRECTION res_direction = IRESS_TR_DIRECTION_WEST;

    if (!placed_) {
        std::cout << "robot is not yet placed, perform PLACE command." << std::endl;
        return;
    }

    switch (direction_) {
        case IRESS_TR_DIRECTION_NORTH:
            res_direction = IRESS_TR_DIRECTION_EAST;
            break;
        case IRESS_TR_DIRECTION_SOUTH:
            res_direction = IRESS_TR_DIRECTION_WEST;
            break;
        case IRESS_TR_DIRECTION_EAST:
            res_direction = IRESS_TR_DIRECTION_SOUTH;
            break;
        case IRESS_TR_DIRECTION_WEST:
            res_direction = IRESS_TR_DIRECTION_NORTH;
            break;
        default:
            std::cerr << "error: Unhandled direction:" << std::endl;
            break;
    }

    updateDirection(res_direction);
}

void iress_tr_robot::report() const {
    if (placed_) {
        std::cout << pos_x_ << "," << pos_y_ << ",";
        switch (direction_) {
            case IRESS_TR_DIRECTION_NORTH: 
                std::cout << "NORTH"; 
                break;
            case IRESS_TR_DIRECTION_EAST:  
                std::cout << "EAST"; 
                break;
            case IRESS_TR_DIRECTION_SOUTH: 
                std::cout << "SOUTH"; 
                break;
            case IRESS_TR_DIRECTION_WEST:  
                std::cout << "WEST"; 
                break;
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "robot is not yet placed, perform PLACE command." << std::endl;
        
    }
}

//--------------------------------------------------------------
//! @details
//!    flags to indicate the robot has been placed already or not.
//--------------------------------------------------------------
bool iress_tr_robot::isPlaced() const {
    return placed_;
}

//--------------------------------------------------------------
//! @details
//!    sets the updated direction of the robot.
//--------------------------------------------------------------
void iress_tr_robot::updateDirection( IRESS_TR_DIRECTION newDirection) {
    direction_ = newDirection;
}