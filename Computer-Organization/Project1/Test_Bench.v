`timescale 1ns / 1ps
//Subject:     Architecture Project1 - Test_Bench
//--------------------------------------------------------------------------------
//Version:     1
//--------------------------------------------------------------------------------
//Writer:      
//----------------------------------------------
//Date:        
//----------------------------------------------
//Description: 
//--------------------------------------------------------------------------------

`define CYCLE_TIME 20
`define END_CYCLE 100
module Test_Bench;

	//Internal Signals
	reg         CLK;
	reg         RST;
	integer     count,i;

	//Greate tested module  
	Simulator sim(
        .clk_i(CLK),
		.rst_i(RST)
	);
 
	//Main function

	always #(`CYCLE_TIME/2) CLK = ~CLK;	

	initial begin
		//Read instruction from "testcase.txt"
		$readmemb("testcase_0.txt", sim.Instr_Mem);  
		
		// Generate waveform file
		/*
		$fsdbDumpfile("Top.fsdb"); //waveform file name
		$fsdbDumpvars(0, "+mda");  //"+mda" => also dump 2D register
		*/

		CLK = 1;
		RST = 0;
		count = 0;

		#(`CYCLE_TIME/2)      RST = 1;
		#(`CYCLE_TIME*`END_CYCLE)	$finish;

	end

	always@(posedge CLK) begin
		count = count + 1;
		if( count == `END_CYCLE )begin 
			for(i=0; i<32; i=i+1)begin
				$display("$%0d: %0d", i, sim.Reg_File[i]);
			end
		end
	end
	  
	endmodule