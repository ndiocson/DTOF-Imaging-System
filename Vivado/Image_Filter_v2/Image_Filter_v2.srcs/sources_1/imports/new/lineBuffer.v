`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/30/2020 07:25:49 PM
// Design Name: 
// Module Name: lineBuffer
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

module lineBuffer(
input                  i_clk,
input                  i_rst,
input   [7:0]          i_data,
input                  i_data_valid,
output  [23:0]         o_data,
input                  i_rd_data
);

reg [7:0] line [639:0]; //line buffer
reg [9:0] wrPntr;
reg [9:0] rdPntr;

always @(posedge i_clk)
begin
    if(i_data_valid)
        line[wrPntr] <= i_data;
end

always @(posedge i_clk)
begin
    if(i_rst)
        wrPntr <= 'd0;
    else if(i_data_valid)
    begin
        if (wrPntr < 639)
            wrPntr <= wrPntr + 'd1;
        else
            wrPntr <= 'd0;
    end
end

assign o_data = {line[rdPntr], line[rdPntr + 1], line[rdPntr + 2]};

always @(posedge i_clk)
begin
    if(i_rst)
        rdPntr <= 'd0;
    else if(i_rd_data)
    begin
        if (rdPntr < 639)
            rdPntr <= rdPntr + 'd1;
        else
            rdPntr <= 'd0;
    end
end


endmodule
