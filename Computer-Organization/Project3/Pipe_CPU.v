`timescale 1ns / 1ps
/*******************************************************************
 * Create Date: 	2016/05/03
 * Design Name: 	Pipeline CPU
 * Module Name:		Pipe_CPU 
 * Project Name: 	Architecture Project_3 Pipeline CPU
 
 * Please DO NOT change the module name, or your'll get ZERO point.
 * You should add your code here to complete the project 3.
 ******************************************************************/
module Pipe_CPU(
        clk_i,
		rst_i
		);
    
/****************************************
*            I/O ports                  *
****************************************/
input clk_i;
input rst_i;

/****************************************
*          Internal signal              *
****************************************/

	wire [32-1:0] instr_w;
	wire [5 -1:0] mux_write_w;
	wire [32-1:0] pc_addr_w;
	wire [32-1:0] sign_extend_w;
	wire [32-1:0] shift_left_w;
	wire [32-1:0] mux_alusrc_w;
	wire [32-1:0] mux_pc_result_w;
	wire [32-1:0] add2_sum_w;
	wire [4-1:0]  alu_control_w;
	wire [32-1:0] alu_result_w;
	wire [32-1:0] dataMem_read_w;
	wire [32-1:0] mux_dataMem_result_w;
	wire [32-1:0] rf_rs_data_w;
	wire [32-1:0] rf_rt_data_w;
	wire [32-1:0] add1_result_w;
	wire [32-1:0] add1_source_w;
	assign add1_source_w = 32'd4;
	wire [3-1:0]  ctrl_alu_op_w;
	wire ctrl_write_mux_w;
	wire ctrl_register_write_w;
	wire ctrl_branch_w;
	wire ctrl_alu_mux_w;
	wire and_result_w;
	wire alu_zero_w;
	wire ctrl_mem_write_w;
	wire ctrl_mem_read_w;
	wire ctrl_mem_mux_w;
	
	
	wire [31:0] IF_ID_pc;
	wire [31:0] IF_ID_instr_w;

	
	
	
	wire [31:0] ID_EX_pc;
	wire [31:0] ID_EX_data_1;
	wire [31:0] ID_EX_data_2;
	wire [31:0] ID_EX_signed;
	wire [4:0]	ID_EX_reg_rs;
	wire [4:0]  ID_EX_reg_rt;
	wire [4:0]  ID_EX_reg_rd;
	wire 		ID_EX_ctrl_register_write_w;
	wire [2:0]  ID_EX_ctrl_alu_op_w;
	wire 		ID_EX_ctrl_alu_mux_w;
	wire 		ID_EX_ctrl_write_mux_w;
	wire 		ID_EX_ctrl_branch_w;
	wire 		ID_EX_ctrl_mem_write_w;
	wire 		ID_EX_ctrl_mem_read_w;
	wire 		ID_EX_ctrl_mem_mux_w;
	
	
	
	wire [31:0]	EX_MEM_pc;
	wire [31:0] EX_pc;
	wire 		EX_MEM_zero;
	wire [31:0]	EX_MEM_alu_result;
	wire [31:0]	EX_MEM_data_2;
	wire [4:0]	EX_MEM_reg_rt;
	wire 		EX_MEM_ctrl_register_write_w;
	wire 		EX_MEM_ctrl_branch_w;
	wire 		EX_MEM_ctrl_mem_write_w;
	wire 		EX_MEM_ctrl_mem_read_w;
	wire 		EX_MEM_ctrl_mem_mux_w;
	wire [1:0]  forward_A;
	wire [1:0] 	forward_B;
	wire [31:0] EX_data_a;
	wire [31:0] EX_data_2;
	
	
	
	wire 		MEM_WB_ctrl_register_write_w;
	wire 		MEM_WB_ctrl_mem_mux_w;
	wire [31:0]	MEM_WB_data;
	wire [31:0]	MEM_WB_alu_result;
	wire [4:0]	MEM_WB_reg_rt;
	
	
/****************************************
*       Instantiate modules             *
****************************************/

/******************IF stage*********************/

	MUX_2to1 #(.size(32)) Mux_PC_Source(
        .data0_i(add1_result_w),
        .data1_i(EX_MEM_pc),
        .select_i(EX_MEM_ctrl_branch_w & alu_zero_w),
        .data_o(mux_pc_result_w)
    );
	
	ProgramCounter PC(
        .clk_i(clk_i),      
	    .rst_i (rst_i),     
	    .pc_in_i(mux_pc_result_w) ,   
	    .pc_out_o(pc_addr_w) 
	);
	
	Adder Adder1(
        .src1_i(pc_addr_w),     
	    .src2_i(add1_source_w),     
	    .sum_o(add1_result_w)    
	);
	
	Instr_Memory IM(
        .pc_addr_i(pc_addr_w),  
	    .instr_o(instr_w)    
	);
		
	Pipe_Reg #(.size(32)) IF_PC(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(add1_result_w),
		.data_o(IF_ID_pc)
	);
	
	Pipe_Reg #(.size(32)) IF_INSTR(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(instr_w),
		.data_o(IF_ID_instr_w)
	);
		
/******************ID stage*********************/
	
	
	Reg_File RF(
        .clk_i(clk_i),
		.rst_i(rst_i),
		.RSaddr_i(IF_ID_instr_w[25:21]) ,
		.RTaddr_i(IF_ID_instr_w[20:16]) ,
		.RDaddr_i(MEM_WB_reg_rt) ,
		.RDdata_i(mux_dataMem_result_w),
		.RegWrite_i(MEM_WB_ctrl_register_write_w),
		.RSdata_o(rf_rs_data_w) ,
		.RTdata_o(rf_rt_data_w)
    );
	

		
	Decoder Decoder(
        .instr_op_i(IF_ID_instr_w[31:26]), 
	    .RegWrite_o(ctrl_register_write_w), 
	    .ALU_op_o(ctrl_alu_op_w),   
	    .ALUSrc_o(ctrl_alu_mux_w),   
	    .RegDst_o(ctrl_write_mux_w),   
		.Branch_o(ctrl_branch_w), 
		.MemWrite_o(ctrl_mem_write_w),
		.MemRead_o(ctrl_mem_read_w),
		.MemtoReg_o(ctrl_mem_mux_w)
	);
	
	Sign_Extend SE(
        .data_i(IF_ID_instr_w[15:0]),
        .data_o(sign_extend_w)
    );

	Pipe_Reg #(.size(1)) ID_reg_write(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(ctrl_register_write_w),
		.data_o(ID_EX_ctrl_register_write_w)
	);
			
	Pipe_Reg #(.size(3)) ID_ALU_op(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(ctrl_alu_op_w),
		.data_o(ID_EX_ctrl_alu_op_w)
	);
	
	Pipe_Reg #(.size(1)) ID_ALU_src(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(ctrl_alu_mux_w),
		.data_o(ID_EX_ctrl_alu_mux_w)
	);
	
	Pipe_Reg #(.size(1)) ID_RegDst_o(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(ctrl_write_mux_w),
		.data_o(ID_EX_ctrl_write_mux_w)
	);
	
	Pipe_Reg #(.size(1)) ID_Branch_o(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(ctrl_branch_w),
		.data_o(ID_EX_ctrl_branch_w)
	);
	
	Pipe_Reg #(.size(1)) ID_MemWrite_o(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(ctrl_mem_write_w),
		.data_o(ID_EX_ctrl_mem_write_w)
	);
	
	Pipe_Reg #(.size(1)) ID_MemRead_o(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(ctrl_mem_read_w),
		.data_o(ID_EX_ctrl_mem_read_w)
	);
	
	Pipe_Reg #(.size(1)) ID_MemtoReg_o(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(ctrl_mem_mux_w),
		.data_o(ID_EX_ctrl_mem_mux_w)
	);
	
	Pipe_Reg #(.size(32)) ID_Data_1(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(rf_rs_data_w),
		.data_o(ID_EX_data_1)
	);
	
	Pipe_Reg #(.size(32)) ID_Data_2(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(rf_rt_data_w),
		.data_o(ID_EX_data_2)
	);
	
	Pipe_Reg #(.size(32)) ID_PC(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(IF_ID_pc),
		.data_o(ID_EX_pc)
	);
	
	Pipe_Reg #(.size(32)) ID_Sign_Extend(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(sign_extend_w),
		.data_o(ID_EX_signed)
	);
	
	Pipe_Reg #(.size(5)) ID_instr_Rt(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(IF_ID_instr_w[20:16]),
		.data_o(ID_EX_reg_rt)
	);
	
	Pipe_Reg #(.size(5)) ID_instr_Rd(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(IF_ID_instr_w[15:11]),
		.data_o(ID_EX_reg_rd)
	);
	
	Pipe_Reg #(.size(5)) ID_instr_Rs(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(IF_ID_instr_w[25:21]),
		.data_o(ID_EX_reg_rs)
	);
	
	
/******************EXE stage*********************/

	ALU_Ctrl AC(
		.funct_i(ID_EX_signed[5:0]),   
		.ALUOp_i(ID_EX_ctrl_alu_op_w),   
		.ALUCtrl_o(alu_control_w) 
	);
					
			
	Adder Adder2(
		.src1_i(ID_EX_pc),     
		.src2_i(shift_left_w),     
		.sum_o(EX_pc)      
	);
			
	Shift_Left_Two_32 Shifter(
		.data_i(ID_EX_signed),
		.data_o(shift_left_w)
	); 		

	
	MUX_3to1 #(.size(32)) Mux_Forward_A(
		.data0_i(ID_EX_data_1),
		.data1_i(mux_dataMem_result_w),
		.data2_i(EX_MEM_alu_result),
		.select_i(forward_A),
		.data_o(EX_data_a)
	);
			
	MUX_3to1 #(.size(32)) Mux_Forward_B(
		.data0_i(ID_EX_data_2),
		.data1_i(mux_dataMem_result_w),
		.data2_i(EX_MEM_alu_result),
		.select_i(forward_B),
		.data_o(EX_data_2)
	);
			
	MUX_2to1 #(.size(32)) Mux_ALUSrc(
		.data0_i(EX_data_2),
		.data1_i(ID_EX_signed),
		.select_i(ID_EX_ctrl_alu_mux_w),
		.data_o(mux_alusrc_w)
	);	
		
	ALU ALU(
		.src1_i(EX_data_a),
		.src2_i(mux_alusrc_w),
		.ctrl_i(alu_control_w),
		.result_o(alu_result_w),
		.zero_o(alu_zero_w)
	);
			
	MUX_2to1 #(.size(5)) Mux_Write_Reg(
		.data0_i(ID_EX_reg_rt),
		.data1_i(ID_EX_reg_rd),
		.select_i(ID_EX_ctrl_write_mux_w),
		.data_o(mux_write_w)
	);
	
	Pipe_Reg #(.size(1)) EX_RegWrite(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(ID_EX_ctrl_register_write_w),
		.data_o(EX_MEM_ctrl_register_write_w)
	);
	
	Pipe_Reg #(.size(1)) EX_Branch(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(ID_EX_ctrl_branch_w),
		.data_o(EX_MEM_ctrl_branch_w)
	);
	
	Pipe_Reg #(.size(1)) EX_MemWrite(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(ID_EX_ctrl_mem_write_w),
		.data_o(EX_MEM_ctrl_mem_write_w)
	);
	
	Pipe_Reg #(.size(1)) EX_MemRead(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(ID_EX_ctrl_mem_read_w),
		.data_o(EX_MEM_ctrl_mem_read_w)
	);
	
	Pipe_Reg #(.size(1)) EX_MemtoReg(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(ID_EX_ctrl_mem_mux_w),
		.data_o(EX_MEM_ctrl_mem_mux_w)
	);
	
	Pipe_Reg #(.size(32)) EX_PC(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(EX_pc),
		.data_o(EX_MEM_pc)
	);
	
	Pipe_Reg #(.size(1)) EX_Zero(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(alu_zero_w),
		.data_o(EX_MEM_zero)
	);
	
	Pipe_Reg #(.size(32)) EX_Alu_result(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(alu_result_w),
		.data_o(EX_MEM_alu_result)
	);
	
	Pipe_Reg #(.size(32)) EX_Data_2(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(EX_data_2),
		.data_o(EX_MEM_data_2)
	);
	
	Pipe_Reg #(.size(5)) EX_Reg_Rt(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(mux_write_w),
		.data_o(EX_MEM_reg_rt)
	);
	/*always @(*) begin
		$display("a-0: %d",ID_EX_data_1);
		$display("a-1: %d",mux_dataMem_result_w);
		$display("a-2: %d",EX_MEM_alu_result);
		$display("forward: %d",forward_A);
		$display("a-: %d",EX_data_a);
		$stop;
	end*/
		
/******************MEM stage*********************/	
		
	Data_Memory DataMemory(
		.clk_i(clk_i),
		.rst_i(rst_i),
		.addr_i(EX_MEM_alu_result),
		.data_i(EX_MEM_data_2),
		.MemRead_i(EX_MEM_ctrl_mem_read_w),
		.MemWrite_i(EX_MEM_ctrl_mem_write_w),
		.data_o(dataMem_read_w)
	);
	
	Pipe_Reg #(.size(1)) MEM_Reg_Write(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(EX_MEM_ctrl_register_write_w),
		.data_o(MEM_WB_ctrl_register_write_w)
	);
	
	Pipe_Reg #(.size(1)) MEM_Mem_to_Reg(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(EX_MEM_ctrl_mem_mux_w),
		.data_o(MEM_WB_ctrl_mem_mux_w)
	);
	
	Pipe_Reg #(.size(32)) MEM_Data(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(dataMem_read_w),
		.data_o(MEM_WB_data)
	);
	
	Pipe_Reg #(.size(32)) MEM_Alu_Result(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(EX_MEM_alu_result),
		.data_o(MEM_WB_alu_result)
	);
	
	Pipe_Reg #(.size(5)) MEM_Reg_Rt(
		.rst_i(rst_i),
		.clk_i(clk_i),   
		.data_i(EX_MEM_reg_rt),
		.data_o(MEM_WB_reg_rt)
	);
	
/******************WB stage*********************/	
	MUX_2to1 #(.size(32)) Mux_DataMem_Read(
        .data0_i(MEM_WB_alu_result),
        .data1_i(MEM_WB_data),
        .select_i(MEM_WB_ctrl_mem_mux_w),
        .data_o(mux_dataMem_result_w)
	);

/****************************************
*         Signal assignment             *
****************************************/
	ForwardinUnit forward(
		.EX_MEMRegWrite(EX_MEM_ctrl_register_write_w) ,
		.MEM_WBRegWrite(MEM_WB_ctrl_register_write_w) ,
		.EX_MEMRegisterRd(EX_MEM_reg_rt) ,
		.MEM_WBRegisterRd(MEM_WB_reg_rt) ,
		.ID_EXRegisterRs(ID_EX_reg_rs) ,
		.ID_EXRegisterRt(ID_EX_reg_rt) ,
		.ForwardA(forward_A) ,
		.ForwardB(forward_B)
	);
	
endmodule