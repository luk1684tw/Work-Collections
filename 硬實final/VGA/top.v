module top(
	input clk,
	input rst,
	output  [3:0] vgaRed,
	output  [3:0] vgaGreen,
	output  [3:0] vgaBlue,
	output hsync,
	output vsync,
	inout wire PS2_DATA,
	inout wire PS2_CLK
	);

    wire [11:0] data;
    wire clk_25MHz;
    wire clk_22;
    wire [16:0] pixel_addr_board,pixel_addr_ball;
    wire [11:0] pixel_board,pixel_ball;
    wire valid;
    wire [9:0] h_cnt;  //640
    wire [9:0] v_cnt;  //480
	wire [1:0] key_num;
	reg [9:0] position;
	
	keyboardinput kb(
	.key_num(key_num),
	.PS2_DATA(PS2_DATA),
	.PS2_CLK(PS2_CLK),
	.rst(rst),
	.clk(clk_22)
	);
	
    clock_divisor clk_wiz_0_inst(
		.clk(clk),
		.clk1(clk_25MHz),
		.clk22(clk_22)
    );
	
    mem_addr_gen_board board(
		.clk(clk_22),
		.rst(rst),
		.position(position),
		.h_cnt(h_cnt),
		.v_cnt(v_cnt),
		.pixel_addr(pixel_addr_board)
    );
	mem_addr_gen_ball ball_mem(
		.clk(clk22),
		.rst(rst),
		.h_cnt(h_cnt),
		.v_cnt(v_cnt),
		.pixel_addr(pixel_addr_ball)
	);
	
    blk_mem_gen_0 board_blk(
		.clka(clk_25MHz),
		.wea(0),
		.addra(pixel_addr_board),
		.dina(data[11:0]),
		.douta(pixel_board)
    );
	
	blk_mem_gen_1 ball_blk(
		.clka(clk_25MHz),
		.wea(0),
		.addra(pixel_addr_ball),
		.dina(data[11:0]),
		.douta(pixel_ball)
    );
	
    vga_controller   vga_inst(
		.pclk(clk_25MHz),
		.reset(rst),
		.hsync(hsync),
		.vsync(vsync),
		.valid(valid),
		.h_cnt(h_cnt),
		.v_cnt(v_cnt)
    );
					   
	assign {vgaRed,vgaGreen,vgaBlue} =  ((h_cnt>>1) >= (145 + position) && (h_cnt>>1) <= (175 + position) 
										  && (v_cnt>>1) >= 190 )? pixel_board : 
										((h_cnt>>1) >= (145 + position) && (h_cnt>>1) <= (160 + position) 
										  && (v_cnt>>1) >= 120 && (v_cnt>>1) <= 135 )? pixel_ball : 12'h0;
										/*(key_num == 2'b01)?
										((h_cnt>>1) >= (145 - position) && (h_cnt>>1) <= (175 - position) && (v_cnt>>1) >= 190 )?
										pixel : 12'h0 : 12'h0;*/
	always @(*) begin
		if (rst) begin
			position = 0;
		end else if (key_num == 2'b10) begin
			if ((position + 175 + 8) < 320) begin
				position = position + 8;
			end
		end
	end
endmodule