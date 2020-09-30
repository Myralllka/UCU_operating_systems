module ALU(input[3:0] A, B, input[1:0] op, output[3:0] out, output carry);
reg[3:0] result;
wire[4:0] tmp;
assign out=result;
assign carry=A[3] & B[3];
always@(*)
begin
	case(op)
	2'b00:
		result = A+B;
	2'b01:
		result = A-B;
	2'b10:
		result = A&B;
	2'b11:
		result = A|B;
	default: result = A+B;
	endcase
end
endmodule