module keyboardinput(
	output wire key_num,
	inout wire PS2_DATA,
	inout wire PS2_CLK,
	input wire rst,
	input wire clk
	);
	parameter [8:0] KEY_CODES [0:2] = {
		9'b0_0010_1001,	// space => start
		9'b0_0001_1100, // a => left
		9'b0_0010_0011  // d => right
	};
	wire [511:0] key_down;
	wire [8:0] last_change;
	reg [1:0] key_num;
	wire been_ready;
	
	KeyboardDecoder key_de (
		.key_down(key_down),
		.last_change(last_change),
		.key_valid(been_ready),
		.PS2_DATA(PS2_DATA),
		.PS2_CLK(PS2_CLK),
		.rst(rst),
		.clk(clk)
	);
	
	always @ (*) begin
		case (last_change)
			KEY_CODES[0] : key_num = 2'b00;  //start
			KEY_CODES[1] : key_num = 2'b01;  //left
			KEY_CODES[2] : key_num = 2'b10;  //right
			default		 : key_num = 2'b11;  
		endcase
	end
endmodule
