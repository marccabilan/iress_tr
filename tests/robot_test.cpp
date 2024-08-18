#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../iress_tr_command_handler.h"
#include <map>
//#include "iress_tr_robot.h"

TEST_CASE("Robot Class") {
   iress_tr_robot robot;

   SECTION("Initial State") {
        REQUIRE_FALSE(robot.isPlaced());
    }

    SECTION("Place and Report") {
        robot.place(1, 2, IRESS_TR_DIRECTION_EAST);
        REQUIRE(robot.isPlaced() == true);
        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream
        robot.report();
        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,2,EAST\n");
    }

    SECTION("Move Command") {
        robot.place(1, 2, IRESS_TR_DIRECTION_EAST);
        robot.move();
        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream
        robot.report();
        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "2,2,EAST\n");
    }

    SECTION("Invalid Move") {
        robot.place(4, 2, IRESS_TR_DIRECTION_EAST);
        robot.move(); // Should not move outside table boundary
        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream
        robot.report();
        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "4,2,EAST\n");
    }

    SECTION("Rotate Left") {
        robot.place(1, 1, IRESS_TR_DIRECTION_NORTH);
        robot.left();
        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream
        robot.report();
        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,1,WEST\n");
    }

    SECTION("Rotate Right") {
        robot.place(1, 1, IRESS_TR_DIRECTION_NORTH);
        robot.right();
        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream
        robot.report();
        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,1,EAST\n");
    }
}

TEST_CASE("Table Class Testing") {
    iress_tr_table table;

    SECTION("Place and Report") {
        table.processPlaceCommand(1, 2, IRESS_TR_DIRECTION_EAST);
        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream
        table.processReportCommand();
        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,2,EAST\n");
    }

    SECTION("Move Command") {
        table.processPlaceCommand(1, 2, IRESS_TR_DIRECTION_EAST);
        table.processMoveCommand();
        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream
        table.processReportCommand();
        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "2,2,EAST\n");
    }

    SECTION("Invalid Move") {
        table.processPlaceCommand(4, 2, IRESS_TR_DIRECTION_EAST);
        table.processMoveCommand(); // Should not move outside table boundary
        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream
        table.processReportCommand();
        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "4,2,EAST\n");
    }

    SECTION("Rotate Left") {
        table.processPlaceCommand(1, 1, IRESS_TR_DIRECTION_NORTH);
        table.processLeftCommand();
        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream
        table.processReportCommand();
        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,1,WEST\n");
    }

    SECTION("Rotate Right") {
        table.processPlaceCommand(1, 1, IRESS_TR_DIRECTION_NORTH);
        table.processRightCommand();
        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream
        table.processReportCommand();
        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,1,EAST\n");
    }

}

TEST_CASE("Command Handler Class Testing") {
    iress_tr_command_handler command_handler;

    SECTION("Place and Report") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 1 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 2 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_EAST });
        
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,2,EAST\n");
    }

    SECTION("Move Command - Going East") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 1 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 2 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_EAST });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_MOVE, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "2,2,EAST\n");
    }

    SECTION("Move Command - Going South") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 2 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 2 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_SOUTH });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_MOVE, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "2,1,SOUTH\n");
    }

    SECTION("Move Command - Going North") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 2 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 2 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_NORTH });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_MOVE, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "2,3,NORTH\n");
    }



    SECTION("Move Command - Going West") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 2 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 2 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_WEST });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_MOVE, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,2,WEST\n");
    }

    
    SECTION("Invalid Move - Out of Bounds in X-axis") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 4 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 2 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_EAST });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_MOVE, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "4,2,EAST\n");

    }

    SECTION("Invalid Move - Out of Bounds in Y-axis") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 4 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 4 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_NORTH });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_MOVE, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "4,4,NORTH\n");

    }

    SECTION("Invalid Move - Out of Bounds at Origin") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 0 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 0 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_SOUTH });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_MOVE, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "0,0,SOUTH\n");

    }

    SECTION("Invalid Move - Out of Bounds at Origin") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 0 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 0 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_WEST });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_MOVE, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "0,0,WEST\n");

    }

    SECTION("Initial:North, Action:Left") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 1 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 1 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_NORTH });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_LEFT, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,1,WEST\n");

    }

    SECTION("Initial:North, Action:Right") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 1 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 1 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_NORTH });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_RIGHT, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,1,EAST\n");

    }

    SECTION("Initial:West, Action:Left") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 1 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 1 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_WEST });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_LEFT, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,1,SOUTH\n");

    }

    SECTION("Initial:West, Action:Right") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 1 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 1 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_WEST });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_RIGHT, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,1,NORTH\n");

    }

    SECTION("Initial:South, Action:Left") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 1 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 1 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_SOUTH });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_LEFT, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,1,EAST\n");

    }

    SECTION("Initial:South, Action:Right") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 1 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 1 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_SOUTH });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_RIGHT, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,1,WEST\n");

    }

    SECTION("Initial:East, Action:Left") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 1 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 1 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_EAST });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_LEFT, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,1,NORTH\n");

    }

    SECTION("Initial:East, Action:Right") {

        std::map<IRES_TR_NODE_ID, LONG> request_map;

        request_map.insert({ IRES_TR_NODE_ID_X, 1 });
        request_map.insert({ IRES_TR_NODE_ID_Y, 1 });
        request_map.insert({ IRES_TR_NODE_ID_DIRECTION, IRESS_TR_DIRECTION_EAST });

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_PLACE, request_map); // Command 1
        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_RIGHT, request_map); // Report Command

        std::ostringstream output;
        auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream

        command_handler.iress_tr_command_handler_facade(IRESS_TR_COMMAND_ID_REPORT, request_map); // Report Command

        std::cout.rdbuf(old_buf); // Restore std::cout

        REQUIRE(output.str() == "1,1,SOUTH\n");

    }
    //
    //SECTION("Rotate Left") {
    //    table.processPlaceCommand(1, 1, IRESS_TR_DIRECTION_NORTH);
    //    table.processLeftCommand();
    //    std::ostringstream output;
    //    auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream
    //    table.processReportCommand();
    //    std::cout.rdbuf(old_buf); // Restore std::cout
    //
    //    REQUIRE(output.str() == "1,1,WEST\n");
    //}
    //
    //SECTION("Rotate Right") {
    //    table.processPlaceCommand(1, 1, IRESS_TR_DIRECTION_NORTH);
    //    table.processRightCommand();
    //    std::ostringstream output;
    //    auto old_buf = std::cout.rdbuf(output.rdbuf()); // Redirect std::cout to output stream
    //    table.processReportCommand();
    //    std::cout.rdbuf(old_buf); // Restore std::cout
    //
    //    REQUIRE(output.str() == "1,1,EAST\n");
    //}
    

}