`timescale 1ns/100ps
module final_test;
	parameter cyc=10;
	parameter delay=cyc/2;
	parameter delta=cyc/5;
	reg clk,rst,U1,U2,D2,U3,D3,D4,F1,F2,F3,F4;
	wire U1_led,U2_led,D2_led,U3_led,D3_led,D4_led,F1_led,F2_led,F3_led,F4_led,Opened;
	wire[1:0] Direction;
	wire[1:0] Floor;
	elevator A (U1,     U2,     U3,
				U1_led, U2_led, U3_led,
				D2,     D3,     D4,
				D2_led, D3_led, D4_led,
				F1,     F2,     F3,     F4,
				F1_led, F2_led, F3_led, F4_led,
				Opened, Direction, Floor,
				clk, rst
);
   always #(cyc/2) clk = ~clk;
   
   initial begin
      $fsdbDumpfile("elevator.fsdb");
      $fsdbDumpvars;
      $monitor(" ///////////////\nclk=%b rst=%b U1_led=%b U2_led=%b D2_led=%b U3_led=%b D3_led=%b D4_led=%b  F1_led=%b F2_led=%b F3_led=%b F4_led=%b \n door_open=%b Direction=%b floor=%b\n",clk,rst,U1_led,U2_led,D2_led,U3_led,D3_led,D4_led,F1_led,F2_led,F3_led,F4_led,Opened,Direction,Floor);
   end

	initial begin
		rst = 1'b0;
		clk = 1'b1;
		#(cyc);
		#(delay) rst = 1;
		#(cyc*4) rst = 0;
		#(delay);
		
        U1=0;
        U2=0;
        D2=1;
        U3=0;
        D3=0;
        D4=1;
        F1=0;
        F2=0;
        F3=0;
        F4=1;
		#(cyc);
		// U3=0;
		D4=0;        
		#200
		F2=1;
		#(cyc);
		F2=0;
		#200
		//#(delay);
		// $display(" clk=%b rst=%b U2_led=%b U1=%b U2=%b D2=%b U3=%b D3=%b D4=%b F1=%b F2=%b F3=%b F4=%b door_open=%b Direction=%b floor=%b",clk,rst,U2_led, U1, U2, D2, U3, D3, D4,F1,F2,F3,F4,door_open,Direction,Floor);
      
		$finish;
	end
endmodule
   
