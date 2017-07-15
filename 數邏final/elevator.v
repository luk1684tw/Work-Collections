`timescale 1ns/100ps
module elevator(U1,     U2,     U3,
				U1_led, U2_led, U3_led,
				D2,     D3,     D4,
				D2_led, D3_led, D4_led,
				F1,     F2,     F3,     F4,
				F1_led, F2_led, F3_led, F4_led,
				Opened, Direction, Floor,
				clk, rst
);

	input  U1,     U2,     U3,     D2,     D3,     D4;
	output U1_led, U2_led, U3_led, D2_led, D3_led, D4_led;
	input  F1,     F2,     F3,     F4;
	output F1_led, F2_led, F3_led, F4_led;
	output Opened;
	output [1:0] Direction;
	output [1:0] Floor;
	input clk, rst;

	parameter STOP = 2'b00,
			  UP = 2'b01,
			  OPEN = 2'b10,
			  DOWN = 2'b11;

	reg [1:0] state, next_state,next_floor;
	reg [1:0] reach;
	reg [3:0] floorStopOrNot;
	reg 	  U1_led,U2_led,U3_led,D2_led,D3_led,D4_led,F1_led,F2_led,F3_led,F4_led;
	reg [1:0] Floor;
	wire [1:0] action;
	
	
	assign action = (state == STOP)	? 2'b00:
					(state == UP)   ? 2'b10:
					(state == DOWN) ? 2'b01: action;
	assign Opened = (state == OPEN)?1:0;
	assign Direction = (state == STOP || state == OPEN)?2'b00:
					   (state == UP)?2'b10:
					   (state == DOWN)?2'b01: 2'b00;
	//where to stop
	
	always@(*)begin
		if(U1_led||F1_led) begin
			floorStopOrNot[0] = 1'b1;
			
		end else begin
			floorStopOrNot[0] = 1'b0;
		end
	end
	
	always@(*)begin
		if(U2_led||F2_led||D2_led) begin
			floorStopOrNot[1] = 1'b1;		
		end else begin
			floorStopOrNot[1] = 1'b0;
		end
	end
	
	always@(*)begin
		if(U3_led||F3_led||D3_led) begin
			floorStopOrNot[2] = 1'b1;
		end else begin
			floorStopOrNot[2] = 1'b0;
		end
	end
	
	always@(*)begin
		if(F4_led||D4_led) begin
			floorStopOrNot[3] = 1'b1;
		end else begin
			floorStopOrNot[3] = 1'b0;
		end
	end
	
	
	
	
	//LED inside control
	always@(*)begin
		if(Floor==0 && F1)
			F1_led = 0;
		else if(Floor!=0 && F1)
			F1_led = 1;
		else if (Floor!=0)
			F1_led = F1_led;
		else
			F1_led = 0;
		/*if(F1)
			F1_led = 1;
		else if(Floor!=0)
			F1_led=F1_led;
		else
			F1_led = 0;*/
	end
	
	always@(*)begin
		if(Floor==1 && F2)
			F2_led = 0;
		else if(Floor!=1 && F2)
			F2_led = 1;
		else if (Floor!=1)
			F2_led = F2_led;
		else
			F2_led = 0;
	end
	
	always@(*)begin
		if(Floor==2 && F3)
			F3_led = 0;
		else if(Floor!=2 && F3)
			F3_led = 1;
		else if (Floor!=2)
			F3_led = F3_led;
		else
			F3_led = 0;
	end
	
	always@(*)begin
		if(Floor==3 && F4)
			F4_led = 0;
		else if(Floor!=3 && F4)
			F4_led = 1;
		else if (Floor!=3)
			F4_led = F4_led;
		else
			F4_led = 0;
	end
	
	//LED outside control  : U
	
	always@(*)begin
		if(Floor==0 && U1)
			U1_led = 0;
		else if(Floor!=1 && U1)
			U1_led = 1;
		else if (Floor!=1)
			U1_led = U1_led;
		else
			U1_led = 0;
	end
	
	always@(*)begin
		if(Floor==1 && U2)
			U2_led = 0;
		else if(Floor!=1 && U2)
			U2_led = 1;
		else if (Floor!=1)
			U2_led = U2_led;
		else
			U2_led = 0;
	end
	
	always@(*)begin
		if(Floor==2 && U3)
			U3_led = 0;
		else if(Floor!=2 && U3)
			U3_led = 1;
		else if (Floor!=2)
			U3_led = U3_led;
		else
			U3_led = 0;
	end
	
	
	//LED outside control  :  D
	
	always@(*)begin
		if(Floor==1 && D2)
			D2_led = 0;
		else if(Floor!=1 && D2)
			D2_led = 1;
		else if (Floor!=1)
			D2_led = D2_led;
		else
			D2_led = 0;
	end
	
	always@(*)begin
		if(Floor==2 && D3)
			D3_led = 0;
		else if(Floor!=2 && D3)
			D3_led = 1;
		else if (Floor!=2)
			D3_led = D3_led;
		else
			D3_led = 0;
	end
	
	always@(*)begin
		if(Floor==3 && D4)
			D4_led = 0;
		else if(Floor!=3 && D4)
			D4_led = 1;
		else if (Floor!=3)
			D4_led = D4_led;
		else
			D4_led = 0;
	end
	
	wire [2:0]num;
	assign num = floorStopOrNot[0]+floorStopOrNot[1]+floorStopOrNot[2]+floorStopOrNot[3];
	
	always@(*)begin
		case(action)
			2'b00  :begin//stop
				if (num==0) begin
					reach = 4;
				end
				else        begin
					if      (Floor == 0)begin
						if	    (floorStopOrNot[0] == 1) begin
							reach = 0;
						end
						else if (floorStopOrNot[1] == 1) begin
							reach = 1;
						end
						else if (floorStopOrNot[2] == 1) begin
							reach = 2;
						end
						else if (floorStopOrNot[3] == 1) begin
							reach = 3;
						end
						else					 begin
							reach = 4;
						end
					end
					else if (Floor == 1)begin
						if      (floorStopOrNot[1] == 1) begin
							reach = 1;
						end
						else if (floorStopOrNot[2] == 1) begin
							reach = 2;
						end
						else if (floorStopOrNot[0] == 1) begin
							reach = 0;
						end
						else if (floorStopOrNot[3] == 1) begin
							reach = 3;
						end
						else					 begin
							reach = 4;
						end
					end
					else if (Floor == 2)begin
						if 		(floorStopOrNot[2] == 1) begin
							reach = 2;
						end
						else if (floorStopOrNot[3] == 1) begin
							reach = 3;
						end
						else if (floorStopOrNot[1] == 1) begin
							reach = 1;
						end
						else if (floorStopOrNot[0] == 1) begin
							reach = 0;
						end
						else 					 begin
							reach = 4;
						end
					end
					else if (Floor == 3)begin
						if 		(floorStopOrNot[3] == 1) begin
							reach = 3;
						end
						else if (floorStopOrNot[2] == 1) begin
							reach = 2;
						end
						else if (floorStopOrNot[1] == 1) begin
							reach = 4;
						end
						else if (floorStopOrNot[0] == 1) begin
							reach = 0;
						end
						else 					 begin
							reach = 4;
						end
					end
				end
			end
			2'b01  :begin//down
				if     (Floor == 0)begin
					if(floorStopOrNot[0]==1)
						reach=0;
					if      (floorStopOrNot[1] == 0 && floorStopOrNot[2] == 0 && floorStopOrNot[3] == 0)begin
						reach = 4;
					end
					else if (floorStopOrNot[1] == 1) begin
						reach = 1;
					end
					else if (floorStopOrNot[2] == 1) begin
						reach = 2;
					end
					else if (floorStopOrNot[3] == 1) begin
						reach = 3;
					end
					else begin
						reach = 4;
					end
				end
				else if(Floor == 1)begin
					if(floorStopOrNot[0] == 0 && floorStopOrNot[2] == 0 && floorStopOrNot[3] == 0)begin
						reach = 4;
					end
					else if (floorStopOrNot[0] == 1) begin
						reach = 0;
					end
					else if (floorStopOrNot[2] == 1) begin
						reach = 2;
					end
					else if (floorStopOrNot[3] == 1) begin
						reach = 3;
					end
					else begin
						reach = 4;
					end
				end
				else if(Floor == 2)begin
					if(floorStopOrNot[0] == 0 && floorStopOrNot[1] == 0 && floorStopOrNot[3] == 0)begin
						reach = 4;
					end
					else if (floorStopOrNot[1] == 1) begin
						reach = 1;
					end
					else if (floorStopOrNot[0] == 1) begin
						reach = 0;
					end
					else if (floorStopOrNot[3] == 1) begin
						reach = 3;
					end
					else begin
						reach = 4;
					end
				end
				else if(Floor == 3)begin
					if(floorStopOrNot[0] == 0 && floorStopOrNot[1] == 0 && floorStopOrNot[2] == 0)begin
						reach = 4;
					end
					else if (floorStopOrNot[2] == 1) begin
						reach = 2;
					end
					else if (floorStopOrNot[1] == 1) begin
						reach = 1;
					end
					else if (floorStopOrNot[0] == 1) begin
						reach = 0;
					end
					else begin
						reach = 4;
					end
				end
				else                   begin
					reach = 4;
				end
			end		
			2'b10  :begin//up
				if     (Floor == 0)begin
					if      (floorStopOrNot[1] == 0 && floorStopOrNot[2] == 0 && floorStopOrNot[3] == 0)begin
						reach = 4;
					end
					else if (floorStopOrNot[1] == 1) begin
						reach = 1;
					end
					else if (floorStopOrNot[2] == 1) begin
						reach = 2;
					end
					else if (floorStopOrNot[3] == 1) begin
						reach = 3;
					end
					else begin
						reach = 4;
					end
				end
				else if(Floor == 1)begin
					if(floorStopOrNot[0] == 0 && floorStopOrNot[2] == 0 && floorStopOrNot[3] == 0)begin
						reach = 4;
					end
					else if (floorStopOrNot[2] == 1) begin
						reach = 2;
					end
					else if (floorStopOrNot[3] == 1) begin
						reach = 3;
					end
					else if (floorStopOrNot[0] == 1) begin
						reach = 0;
					end
					else begin
						reach = 4;
					end
				end
				else if(Floor == 2)begin
					if(floorStopOrNot[0] == 0 && floorStopOrNot[1] == 0 && floorStopOrNot[3] == 0)begin
						reach = 4;
					end
					else if (floorStopOrNot[3] == 1) begin
						reach = 3;
					end
					else if (floorStopOrNot[1] == 1) begin
						reach = 1;
					end
					else if (floorStopOrNot[0] == 1) begin
						reach = 0;
					end
					else begin
						reach = 4;
					end
				end
				else if(Floor == 3)begin
					if(floorStopOrNot[0] == 0 && floorStopOrNot[1] == 0 && floorStopOrNot[2] == 0)begin
						reach = 4;
					end
					else if (floorStopOrNot[2] == 1) begin
						reach = 2;
					end
					else if (floorStopOrNot[1] == 1) begin
						reach = 1;
					end
					else if (floorStopOrNot[0] == 1) begin
						reach = 0;
					end
					else begin
						reach = 4;
					end
				end
				else                   begin
					reach = 4;
				end
			end
			default:begin
				reach = 4;
			end
		endcase
	end
	
	
	
	always@(posedge clk or posedge rst)begin
		if (rst) begin
			state <= STOP;
			Floor <= 0;
		end else begin
			state <= next_state;
			Floor <= next_floor;
		end
	end
	
	reg [3:0] count, next_count;
	
	always@(*)begin
		case(state)
			STOP:begin
				next_count = 0;
				next_floor = Floor;
				if(reach == 4)begin
					next_state = STOP;
				end
				else if (reach == Floor) begin
					next_state = OPEN;
				end
				else if (reach > Floor) begin
					next_state = UP;
				end
				else begin
					next_state = DOWN;
				end
			end
			UP:begin
				if(count < 12)begin
					next_count = count+1;
					next_state = UP;
					next_floor = Floor;
				end
				else if(count == 12 && reach == Floor) begin
					next_count = 0;
					next_state = OPEN;
					next_floor = Floor+1;
				end
				else begin
					next_count = 0;
					next_state = UP;
					next_floor = Floor+1;
				end
			end
			DOWN:begin
				if(count < 12) begin
					next_count = count + 1 ;
					next_state = DOWN;
					next_floor = Floor;
				end
				else if (count == 12 && reach == Floor) begin
					next_count = 0;
					next_state = OPEN;
					next_floor = Floor-1;
				end
				else begin
					next_count = 0;
					next_state = DOWN;
					next_floor = Floor-1;
				end
			end
			OPEN:begin
				next_floor = Floor;
				if(count < 5)begin
					next_count = count+1;
					next_state = OPEN;
				end
				else if (count == 5 && reach > Floor)begin
					next_count = 0;
					next_state = UP;
				end
				else if (count == 5 && reach < Floor) begin
					next_count = 0;
					next_state = DOWN;
				end
				else begin
					next_count = 0;
					next_state = STOP;
				end
			end
			default:begin
				next_count = 0;
				next_state = STOP;
				next_floor = Floor;
			end
		endcase
	end
	
	always@(posedge clk or posedge rst)begin
		if(rst)
			count <= 0;
		else
			count <= next_count;
	end
	
	
	
	
	
	
	
	
endmodule