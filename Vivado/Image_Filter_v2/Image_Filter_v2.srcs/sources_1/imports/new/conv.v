`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/31/2020 10:09:05 PM
// Design Name: 
// Module Name: conv
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module conv(
input        i_clk,
input [71:0] i_pixel_data,
input        i_pixel_data_valid,
output reg [7:0] o_convolved_data,
output reg   o_convolved_data_valid
    );
    
integer i; 
reg [7:0] kernel [8:0];
reg [15:0] multData[8:0];
reg [15:0] sumDataInt;
reg [15:0] sumData;
reg multDataValid;
reg sumDataValid;
reg convolved_data_valid;

//initial
//begin
//    for(i=0;i<9;i=i+1)
//    begin
//        kernel[i] = 1;
//    end
//end    
initial
begin
    for (i = 0; i < 9; i = i + 1)
    begin
        if (i == 4)
            kernel[i] = 8;
        else
            kernel[i] = -1;
    end
end    

    
always @(posedge i_clk)
begin
    for(i=0;i<9;i=i+1)
    begin
        multData[i] <= kernel[i]*i_pixel_data[i*8+:8];
    end
    multDataValid <= i_pixel_data_valid;
end


always @(*)
begin
    sumDataInt = 0;
    for(i=0;i<9;i=i+1)
    begin
        sumDataInt = sumDataInt + multData[i];
    end
end

always @(posedge i_clk)
begin
    sumData <= sumDataInt;
    sumDataValid <= multDataValid;
end
    
always @(posedge i_clk)
begin
//    o_convolved_data <= sumData/9;
    o_convolved_data <= sumData;
    o_convolved_data_valid <= sumDataValid;
end
    
endmodule

//`timescale 1ns / 1ps
////////////////////////////////////////////////////////////////////////////////////
//// Company: 
//// Engineer: 
//// 
//// Create Date: 03/31/2020 10:09:05 PM
//// Design Name: 
//// Module Name: conv
//// Project Name: 
//// Target Devices: 
//// Tool Versions: 
//// Description: 
//// 
//// Dependencies: 
//// 
//// Revision:
//// Revision 0.01 - File Created
//// Additional Comments:
//// 
////////////////////////////////////////////////////////////////////////////////////


//module conv(
//input        i_clk,
//input [71:0] i_pixel_data,
//input        i_pixel_data_valid,
//output reg [7:0] o_convolved_data,
//output reg   o_convolved_data_valid
//    );
    
//integer i; 
//reg [7:0] kernel [8:0];
//reg [15:0] multData[8:0];
//reg [15:0] sumDataInt;
//reg [15:0] sumData;
//reg multDataValid;
//reg sumDataValid;
//reg convolved_data_valid;

//initial
//begin
//    kernel[0] = -1;
//    kernel[1] = -1;
//    kernel[2] = -1;
//    kernel[3] = -1;
//    kernel[4] = 8;
//    kernel[5] = -1;
//    kernel[6] = -1;
//    kernel[7] = -1;
//    kernel[8] = -1;
//end    
    
//always @(posedge i_clk)
//begin
//    for(i=0;i<9;i=i+1)
//    begin
//        multData[i] <= $signed(kernel[i])*$signed({1'b0, i_pixel_data[i*8+:8]});
//    end
//    multDataValid <= i_pixel_data_valid;
//end


//always @(*)
//begin
//    sumDataInt = 0;
//    for(i=0;i<9;i=i+1)
//    begin
//        sumDataInt = $signed(sumDataInt) + $signed(multData[i]);
//    end
//end

//always @(posedge i_clk)
//begin
//    sumData <= sumDataInt;
//    sumDataValid <= multDataValid;
//end
    
//always @(posedge i_clk)
//begin
//    o_convolved_data <= sumData;
//    o_convolved_data_valid <= sumDataValid;
//end
    
//endmodule
