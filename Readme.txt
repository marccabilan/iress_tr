## Overview

To address the Toy Robot coding challenge, we'll create a C++ console application that simulates a toy robot moving on a 5x5 table. We'll use object-oriented principles to structure our code and ensure it's maintainable and correct. The main components of the project will include:

1. Classes to represent the Robot and Table.
2. Command handling for PLACE, MOVE, LEFT, RIGHT, and REPORT.
3. Error handling to prevent invalid commands or robot movements.
4. Testing to ensure functionality is correct.


## Project Structure

1.) cpp/h files

iress_tr_robot.h		- Declaration of the Robot class.

iress_tr_robot.cpp 		- Implementation of the Robot class.
				- contains function like move, place, left, right, and report.
				- has the information pertaining to the x,y position and face direction of the robot.
				- report command print the position of the robot and its face direction.
				- has helper function to know if the robot is already placed or not.
				- has functions and checks to navigate the robot in the table while making sure it does not fall off from the table.
				

iress_tr_table.h 		- Declaration of the Table class.

iress_tr_table.cpp 		- Implementation of the Table class.
				- Current, the table has one instance of robot.
				- this class act as wrapper class to the robot class.
				- has information to represent the actual size of the table.

iress_tr_command_handler.h 	- Declaration of command handler class.

iress_tr_command_handler.cpp	- Implementation of command handler class.
				- This class act as middle interface between the main application and the lower level module class.
				- receives the command from the main application and calls the appropriate handler functions to be called.

iress_tr.cpp 			- Entry point of the application.
				- processes the input data and perform command validation. 
				- Instantiates the command handler class.
				- Provide the command to the command handler class.

iress_tr_defines.h		- Contains the Global Definition, Enums and Definition of the project.

tests/catch.hpp 		- Contains the single include of catch2 test framework.

tests/robot_test.h 		- Declaration of the cpp unit test files.
				- TEST_CASE("Robot Class") contains the unit test of robot class
				- TEST_CASE("Table Class Testing") contains the unit test of table class
				- TEST_CASE("Command Handler Class Testing") contains the unit test of Command Handler Class

tests/robot_cpp.h 		- Implementation of the cpp unit test files.

2.) test script

test_input.txt			- input file for testing
        			- this is the most basic and quick test, devs are free to edit this conveniently for debugging

3.) Other Files

Iress_toy_robot_test_specification.xlsx		-Contains the functional Test Specification of the Toy Robot Project.
Iress_toy_robot_design.xlsx			-Contains the Basic Design of the toy robot project.
iress_toy_robot_interface_specification.xlsx	-Contains the Command Specification, Define Specification of the Toy Robot Project.



## Building the Application

1. **Clone the repository**:
    ```bash
    git clone <repository-url>
    cd <repository-folder>
    ```

2. **Compile the code**:
    ```bash
    g++ -o toy_robot_application iress_tr.cpp iress_tr_robot.cpp iress_tr_table.cpp iress_tr_command_handler.cpp
    ```

Note: Make sure that GCC MingW is pre-installed on your device. 
for Configuring GCC with MinGW visit site below.
(https://code.visualstudio.com/docs/cpp/config-mingw#_prerequisites)


## Building and Running Tests

1. To build and run the tests, ensure you have Catch2's `catch.hpp` in the `tests` directory. Then use:

```bash
g++ -o toy_robot_tests tests/robot_test.cpp iress_tr_robot.cpp iress_tr_table.cpp iress_tr_command_handler.cpp -I./tests
./toy_robot_tests


Note: these tests, you can verify that your `iress_tr_command_handler`, `iress_tr_command_robot`,  and iress_tr_table classes function correctly
. Adjust the paths and commands according to your project structure as needed.


## Running the Application

1. To run the application and provide commands via standard input, use:
   ```bash
   ./toy_robot_application

2. To run the application and using text file as input stream
   ```bash
   ./toy_robot_application test_input.txt



	