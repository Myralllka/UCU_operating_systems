# Lab 0: 4-bit ALU based on FPGA


## Team
- Mykola Morhunenko
- Solomiia Leno


## Prerequisities
- FPGA board **terasic DE10-Nano**
- **Quartus Lite** IDE along with Verilog compiler
- **ModelSim** simulator within Quartus IDE
- We used 16.1 version of both applications


## About
**Important!** project name is `blink`.

This project implements a simple **4-bit ALU** that supports **4 operations**: addition, subtraction, logical AND and OR - based on FPGA board DE10-Nano.

Hardware description language used for writing the code is **Verilog HDL**.

The project also includes module for full automated testing.


## Usage
If you want to use it as ALU you need to follow all the steps below:

1. Open the project and plug in your FPGA borad. Connect it to your computer.
2. Connect switches to user pins of the FPGA.
3. Assign needed pins.
4. Compile the code and program FPGA board.

Both input and output are 4-bit binary numbers.

The operation to be performed by the ALU (addition, subtraction, AND, OR) is encoded using 2-bit binary number (operations encoding is explained at the end of this README). 

In out implementation, we used the switch buttons for input and user LEDs for output.

You can find photo of our hardware implementation in the project folder under **implmentation.jpg** name.


## Testing
In order to automatically test the ALU code run the ALU_test.v module within the ModelSim simulator. 


### Operations encoding
- **00** addition
- **01** subtraction
- **10** logical AND
- **11** logical OR

