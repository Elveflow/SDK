%%%%%%%%%%%%%%%%%
%INITIALIZATION
%%%%%%%%%%%%%%%%%
%add path where the lib Elveflow are stored, load library and set all
%required variables (some are pointers to communicate with the DLL)
%and start the instrument
%%%%%%%%%%%%%%%%%

%define here the directory where .m, DLL and this script are 
addpath('D:\dev\SDK\MATLAB_32\MATLAB_32\');%path for MATLAB"***.m" file
addpath('D:\dev\SDK\MATLAB_32\MATLAB_32\DLL32\');%path for the DLL library
addpath('D:\dev\SDK\MATLAB_32\Example\')%path for your script

%always use Elveflow_Load at the beginning, it loads the DLL
Elveflow_Load;

error =0;%init error to zero, if an error occurs in the DLL, an error is returned
answer='empty_string';%store the user answer in this variable

%create equivalent of char[] to communicate with DLL
%the instrument name can be found in NIMAX
Instrument_Name = libpointer('cstring','MySensorReader'); 


%pointer to store the instrument ID (no array)
Inst_ID=libpointer('int32Ptr',zeros(1,1));

%initiate the device (see User
%Guide for help)
%may return an error if the instrument wasn't closed properly last time
error=F_S_R_Initialization(Instrument_Name,5,0,7,0,Inst_ID);
CheckError(error);

disp(strcat('Instrument ID = ', num2str(Inst_ID.Value)));%show the instrument number


%%%%%%%%%%%%%%%%
% MAIN PART
%%%%%%%%%%%%%%%%
%present all the possibility of Sensor Reader
%%%%%%%%%%%%%%%%
%init required variables
channel_n=-1;
sensor_value_Ptr = libpointer('doublePtr',zeros(1,1));%to store the value of the selected channel 

%ask the user what to do and loop until user enters exit
while (~strcmp(answer,'exit')) %loop until user enters exit
    %get user answer 
    answer='non valid answer to avoid looping indefinitely';
    while (~(strcmp(answer,'get sensor')||strcmp(answer,'exit')))
    prompt = '\nChoose what to do: get sensor or exit\n';
    answer = input(prompt,'s');
    end

    
    % get sensor
    if strcmp(answer,'get sensor')
        prompt = 'which channel (1-4)?';
        channel_n=input(prompt);
        error = F_S_R_Get_Sensor_data(Inst_ID.Value,channel_n, sensor_value_Ptr );
        CheckError(error);
        disp(strcat('sensor',num2str(channel_n),'= ' , num2str(sensor_value_Ptr.Value)));
    end
end

%%%%%%%%%%%%%%%
%EXIT
%%%%%%%%%%%%%%%
%close communication 
%clear all pointers. If it is not done properly, it will crash at next
%launch
%%%%%%%%%%%%%%%


error=F_S_R_Destructor(Inst_ID.Value);%close communication with the instrument
CheckError(error);

Elveflow_Unload;

clear Instrument_Name;
clear Inst_ID;
clear sensor_value_Ptr;