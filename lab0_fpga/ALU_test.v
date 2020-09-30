`timescale 1 ns/1 ps;

module alu_tb;
	reg [3:0] A, B;
	reg [1:0] op;
	wire [3:0] out;
	wire carry;
	
	localparam period = 20;
	
	ALU dut (.A(A), .B(B), .op(op), .out(out), .carry(carry));
	
reg clk;
reg i, j, k;

always
begin
	clk = 1'b1;
	#20;  // 20 * timescale
	
	clk = 1'b0;
	#20;
end

always @(posedge clk)
begin
	for (i = 0; i < 16; i=i+1)
	begin
		for (j = 0; j < 16; j=j+1)
		begin
			for (k = 0; k < 4; k=k+1)
			begin
				A = i;
				B = j;
				op = k;
				#period;
			end
		end
	end
end

