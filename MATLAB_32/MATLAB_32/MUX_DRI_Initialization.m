function [error] = MUX_DRI_Initialization(Visa_COM, MUX_DRI_ID_out)
 % Elveflow Library
 % MUX D-R-I Device
 % 
 % Initiate the MUX Distribution, Distributor, Recirculation or Injection 
 % device using device COM port (ASRLXXX::INSTR where XXX is usually the COM 
 % port that could be found in Windows device manager). It returns the MUX 
 % D-R-I ID (number >=0) to be used with other function.
 
error=calllib('Elveflow32', 'MUX_DRI_Initialization' , Visa_COM, MUX_DRI_ID_out);


end