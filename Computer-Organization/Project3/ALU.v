//Subject:     Architecture project 2 - ALU
//--------------------------------------------------------------------------------
//Version:     1
//--------------------------------------------------------------------------------
//Writer:      
//----------------------------------------------
//Date:        
//----------------------------------------------
//Description: 
//--------------------------------------------------------------------------------

module ALU(
    src1_i,
	src2_i,
	ctrl_i,
	result_o,
	zero_o
	);
     
//I/O ports
	input  signed [32-1:0]  src1_i;
	input  signed [32-1:0]	src2_i;
	input  [4-1:0]   ctrl_i;

	output signed [32-1:0]	 result_o;
	output           zero_o;

	//Internal signals
	reg    [32-1:0]  result_o;
	wire             zero_o;

//Parameter

//Main function
	assign zero_o = (src1_i == src2_i)? 1 : 0;
	
	always @(*) begin
		case (ctrl_i)
			4'b0010: begin
				result_o = src1_i + src2_i;
			end
			4'b0110 : begin
				result_o = src1_i - src2_i;
			end
			4'b0000 : begin
				result_o = src1_i & src2_i;
			end
			4'b0001 : begin
				result_o = src1_i | src2_i;
			end
			4'b0111 : begin
				result_o = (src1_i < src2_i) ? 32'b1 : 32'b0;
			end
			default : result_o = 32'hffffffff;
		endcase
	end
endmodule