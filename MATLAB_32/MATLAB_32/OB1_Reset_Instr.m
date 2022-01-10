function [error] = OB1_Reset_Instr(OB1_ID)
 % Warning: advanced feature. Reset OB1 communication for pressure and flow.
 
error=calllib('Elveflow32', 'OB1_Reset_Instr' , OB1_ID);


end