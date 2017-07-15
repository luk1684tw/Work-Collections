module mem_addr_gen_board(
	input clk,
	input rst,
	input [9:0] position,
	input [9:0] h_cnt,
	input [9:0] v_cnt,
	output [16:0] pixel_addr
	);
	
	assign pixel_addr = ((h_cnt>>1) - (position + 145) + 30*((v_cnt>>1)-190)) % 900;
endmodule


module mem_addr_gen_ball(
	input clk,
	input rst,
	input [9:0] h_cnt,
	input [9:0] v_cnt,
	output [16:0] pixel_addr
	);
	
	assign pixel_addr = ((h_cnt>>1)-145 + 15*((v_cnt>>1)-120)) % 225;
endmodule


	