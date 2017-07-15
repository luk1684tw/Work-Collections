//Subject:     Architecture project 2 - ALU Controller
//--------------------------------------------------------------------------------
//Version:     1
//--------------------------------------------------------------------------------
//Writer:
//----------------------------------------------
//Date:
//----------------------------------------------
//Description:
//--------------------------------------------------------------------------------

module ALU_Ctrl(
          funct_i,
          ALUOp_i,
          ALUCtrl_o
          );

//I/O ports
	input      [6-1:0] funct_i;
	input      [3-1:0] ALUOp_i;

	output     [4-1:0] ALUCtrl_o;

	//Internal Signals
	reg        [4-1:0] ALUCtrl_o;

	//Parameter


	//Select exact operation, please finish the following code
	always@(funct_i or ALUOp_i) begin
		case(ALUOp_i)
			3'b000:	begin
				case(funct_i)
					6'h20: ALUCtrl_o = 4'b0010;		//add
					6'h22: ALUCtrl_o = 4'b0110;		//sub
					6'h24: ALUCtrl_o = 4'b0000; 	//and
					6'h25: ALUCtrl_o = 4'b0001;		//or
					6'h2a: ALUCtrl_o = 4'b0111;		//slt
					default: ALUCtrl_o = 4'b1111;
				endcase
			end
			3'b001: begin								//addi
				ALUCtrl_o = 4'b0010;
			end
			3'b010: begin								//lw
				ALUCtrl_o = 4'b0010;
			end
			3'b011: begin								//sw
				ALUCtrl_o = 4'b0010;
			end
			3'b100: begin								//slti
				ALUCtrl_o = 4'b0111;
			end
			3'b101: begin								//beq
				ALUCtrl_o = 4'b0110;
			end
			default:ALUCtrl_o = 4'b1111;
		endcase
	end
endmodule
