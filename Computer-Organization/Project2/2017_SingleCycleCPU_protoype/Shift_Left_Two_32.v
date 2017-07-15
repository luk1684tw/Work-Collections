//Subject:      Architecture project 2 - Shift_Left_Two_32
//--------------------------------------------------------------------------------
//Version:     1
//--------------------------------------------------------------------------------
//Description: 
//--------------------------------------------------------------------------------

module Shift_Left_Two_32(
    data_i,
    data_o
    );

//I/O ports                    
	input wire [32-1:0] data_i;
	output wire [32-1:0] data_o;

//shift left 2
    assign data_o = data_i << 2;
endmodule