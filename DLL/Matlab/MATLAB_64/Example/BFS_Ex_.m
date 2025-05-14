%%%%%%%%%%%%%%%%%
%INITIALIZATION
%%%%%%%%%%%%%%%%%
%add path where the lib Elveflow are stored, load library and set all
%required variables (some are pointers to communicate with the DLL)
%and start the instrument
%%%%%%%%%%%%%%%%%

%define here the directory where .m, DLL and this script are 
addpath('C:\Users\Kevin\Desktop\SDK_V3_10_00\DLL\Matlab\MATLAB_64\MATLAB_64\');%path for MATLAB"***.m" file
addpath('C:\Users\Kevin\Desktop\SDK_V3_10_00\DLL\Matlab\MATLAB_64\MATLAB_64\DLL64');%path for the DLL library
addpath('C:\Users\Kevin\Desktop\SDK_V3_10_00\DLL\Matlab\MATLAB_64\Example')%path for your script


%always use Elveflow_Load at the beginning, it loads the DLL
Elveflow_Load;

error =0;%init error to zero, if an error occurs in the DLL, an error is returned
answer='empty_string';%store the user answer in this variable

%create equivalent of char[] to communicate with the DLL
%the instrument com port can be determined in windows device explorer and/or
%NIMAX
%  ! ! ! TO WORK PROPERLY, FTDI DRIVERS ARE REQUIRED !!! (see User Guide)
ComPortPtr = libpointer('cstring','ASRL11::INSTR'); 


%pointer to store the instrument ID (no array)
Inst_ID=libpointer('int32Ptr',zeros(1,1));

%initiate the device (see User
%Guide for help)
%may return an error if the instrument wasn't closed properly last time
error= BFS_Initialization(ComPortPtr,0.001,1,1,Inst_ID);
CheckError(error);
error=0;
disp(strcat('Instrument ID = ', num2str(Inst_ID.Value)));%show the instrument number


%%%%%%%%%%%%%%%%
% MAIN PART
%%%%%%%%%%%%%%%%
%present all the possibility of the BFS
%%%%%%%%%%%%%%%%
%init required variables
temperature = libpointer('doublePtr',zeros(1,1));%pointer to store the temperature
density = libpointer('doublePtr',zeros(1,1));%pointer to store the density
flow_rate = libpointer ('doublePtr',zeros(1,1));%pointer to store the flow rate
SetFilter=-1;
GetValuePtr = libpointer('doublePtr',zeros(1,1));%to store the returned value

%ask the user what to do and loop until user enters exit
while (~strcmp(answer,'exit')) %loop until user enters exit
    %get user answer 
    answer='non valid answer to avoid looping indefinitely';
    while (~(strcmp(answer,'get data')||strcmp(answer,'set filter')||strcmp(answer,'do zero')||strcmp(answer,'exit')))
    prompt = '\nChoose what to do: get data, set filter, do zero or exit\n';
    answer = input(prompt,'s');
    end
    
    %set filter
    if strcmp(answer,'set filter')
        prompt = 'set filter value (1=min filter, 0,00001=max filter)';
        SetFilter=input(prompt);
        error = BFS_Set_Filter(Inst_ID.Value, SetFilter );
        CheckError(error);
    end
    
    %put valves before and after the BFS to stop the flow before performing zeroing
    if strcmp(answer,'do zero')
        disp('Zeroing last approximately 10 sec. Wait for the LED to stop blinking before sending an other command. \nRead corresponding User Guide to perform correctly the zeroing procedure.');
        error=BFS_Zero(Inst_ID.Value);
        CheckError(error);
    end
    
    
    %read a channel the remote loop
    if strcmp(answer,'get data')
        error = BFS_Get_Data(Inst_ID.Value, flow_rate, temperature, density);
        CheckError(error);
        
        disp(strcat('temperature/density/sensor = ' , num2str(temperature.Value),'; ', num2str(density.Value), '; ', num2str(flow_rate.Value)));
    end
end

%%%%%%%%%%%%%%%
%EXIT
%%%%%%%%%%%%%%%
%close communication 
%clear all pointers. If it is not done properly, it will crash at next
%launch
%%%%%%%%%%%%%%%


error=BFS_Destructor(Inst_ID.Value);%close communication with the instrument
CheckError(error);

Elveflow_Unload;

clear Inst_ID;
clear GetValvePtr;
clear temperature;
clear density;
clear flow_rate;