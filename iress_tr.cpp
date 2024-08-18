// iress_tr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "iress_tr_command_handler.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>


iress_tr_command_handler toy_robot_handler;

void process_line(std::string line) {
 

    if (line.empty()) {
        return;
    }


    IRES_TR_COMMAND_ID command_id = IRESS_TR_COMMAND_ID_UNKNOWN;
    std::map<IRES_TR_NODE_ID, LONG> request_map;
    bool call_flag = true;

    // variables to hold the tokens after parsing based on ' ' (space) delimiter
    std::vector<std::string> tokens;
    std::string token;

    std::stringstream ss(line);
    
    // read each token and put in vector
    while (std::getline(ss, token, ' ')) {
        tokens.push_back(token);
    }

    if (tokens[0] == "PLACE" && tokens.size() == 2) {
        std::vector<std::string> place_tokens;
        std::string place_token;

        // Parse tokens[1] using comma as delimiter
        std::stringstream place_ss(tokens[1]);
        while (getline(place_ss, place_token, ',')) {
            place_tokens.push_back(place_token);
        }

        // Check if we have exactly 3 parameters
        if (place_tokens.size() == 3) {
            // Helper lambda to convert string to long and check for errors
            auto to_long = [](const std::string& str, long& value) -> bool {
                char* end = nullptr;
                errno = 0;
                value = strtol(str.c_str(), &end, 10);
                return (errno == 0 && *end == '\0');
             };

            IRESS_TR_DIRECTION direction = IRESS_TR_DIRECTION_UNKNOWN;

            long pos_x_l = 0;
            long pos_y_l = 0;
            if (to_long(place_tokens[0], pos_x_l) && to_long(place_tokens[1], pos_y_l)) {
                // Map face strings to enum or constants
                if (place_tokens[2] == "NORTH") {
                    direction = IRESS_TR_DIRECTION_NORTH;
                }
                else if (place_tokens[2] == "SOUTH") {
                    direction = IRESS_TR_DIRECTION_SOUTH;
                }
                else if (place_tokens[2] == "EAST") {
                    direction = IRESS_TR_DIRECTION_EAST;
                }
                else if (place_tokens[2] == "WEST") {
                    direction = IRESS_TR_DIRECTION_WEST;
                }
                else {
                    // Invalid face direction
                     std::cout << "Invalid face or direction. Supported: NORTH, SOUTH, EAST, WEST. Case sensitive." << std::endl;
                     call_flag = false;
                }

                request_map.insert({ IRES_TR_NODE_ID_X, pos_x_l });
                request_map.insert({ IRES_TR_NODE_ID_Y, pos_y_l });
                request_map.insert({ IRES_TR_NODE_ID_DIRECTION, direction });
            }
            else {
                // Conversion failed for x or y
                std::cout << "Failed to convert x or y to long" << std::endl;
                call_flag = false;
            }
        }
        else {
            // Incorrect number of PLACE parameters
            std::cout << "Invalid PLACE Command parameters" << std::endl;
            call_flag = false;
        }

        command_id = IRESS_TR_COMMAND_ID_PLACE;
    }
    else if (token == "MOVE" && tokens.size() == 1) {
        command_id = IRESS_TR_COMMAND_ID_MOVE;
    }
    else if (token == "LEFT" && tokens.size() == 1) {
        command_id = IRESS_TR_COMMAND_ID_LEFT;
    }
    else if (token == "RIGHT" && tokens.size() == 1) {
        command_id = IRESS_TR_COMMAND_ID_RIGHT;
    }
    else if (token == "REPORT" && tokens.size() == 1) {
        command_id = IRESS_TR_COMMAND_ID_REPORT;
    }
    else {
        std::cout << "Invalid command. Ignore and move to next line." << std::endl;
        call_flag = false;
    }
    
    if (call_flag) {
        std::cout << "CALL LOGS:: toy_robot_handler.iress_tr_command_handler_facade :: command id:" << command_id << " call flag:" << call_flag << std::endl;
        toy_robot_handler.iress_tr_command_handler_facade(command_id, request_map);
    } else {/*nothing to do*/ }
  
}


int main(int argc, char* argv[]) {

    std::string line;

    if (argc > 1) {
        std::ifstream inputFile(argv[1]);

        if (inputFile.is_open()) {
            while (std::getline(inputFile, line)) {
                process_line(line);
            }
        }
        else {
            std::cout << "unable to open " << argv[1] << std::endl;
        }
    }
    else {
        while (std::getline(std::cin, line)) {
            process_line(line);
        }
    }

    return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
