function [error] = Elveflow_EXAMPLE_PID(PID_ID_in, actualValue, Reset, P, I, targetValue, PID_ID_out, value)
 % Elveflow Library - ONLY FOR ILLUSTRATION - 
 % OB1 and AF1 Devices
 % 
 % This function is only provided for illustration purpose, to explain how to 
 % do your own feedback loop. Elveflow does not guarante neither efficient nor 
 % optimum regulation with this illustration of PI regulator . With this 
 % function the PI parameters have to be tuned for every regulator and every 
 % microfluidic circuit.   
 % 
 % In this function need to be initiate with a first call where PID_ID =-1. 
 % The PID_out will provide the new created PID_ID. This ID should be use in 
 % further call. 
 % 
 % General remarks of this PI regulator :
 % 
 % The error "e" is calculate for every step as e=target value-actual value
 % There are 2 contributions to a PI regulator: proportional contribution 
 % which only depend on this step and  Prop=e%P and integral part which is the 
 % "memory" of the regulator. This value is calculated as 
 % Integ=integral(I%e%dt) and can be reset. 
 %   
 
error=calllib('Elveflow32', 'Elveflow_EXAMPLE_PID' , PID_ID_in, actualValue, Reset, P, I, targetValue, PID_ID_out, value);


end