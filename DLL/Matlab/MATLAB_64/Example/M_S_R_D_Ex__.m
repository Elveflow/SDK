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

error=0;%init error to zero, if an error occurs in the DLL, an error is returned
answer='empty_string';%store the user answer in this variable

%create equivalent of char[] to communicate with the DLL
%the instrument name can be found in NIMAX
Instrument_Name = libpointer('cstring','01EE3A1A');%here instrument name is 01DAA568


%pointer to store the instrument ID (no array)
Inst_ID=libpointer('int32Ptr',zeros(1,1));

%initiate the device and all regulator types (see User
%Guide for help)
%may return an error if the instrument wasn't closed properly last time
error=M_S_R_D_Initialization(Instrument_Name,5,0,0,0,0,0,Inst_ID);%remember that channel 1-2 and 3-4 should be the same kind //sensor type has to be the same in this function as in the "Add_Sens" function (CustomSens_Voltage_Ch12 and Ch34 is used for CustomSensors only, voltage is between 5 and 25V)
CheckError(error);
%M_S_R_D_Add_Sens(M_S_R_D_ID, Channel_1_to_4, SensorType, DigitalAnalog, FSens_Digit_Calib, FSens_Digit_Resolution, Custom_Sensor_VoltageIn525VOptional)
%add sensor
error=M_S_R_D_Add_Sens(Inst_ID.Value,1,5,0,0,7,0); %add digital flow sensor. if sensor is not detected it will throw an error
CheckError(error);

%error=M_S_R_D_Set_Filt(Inst_ID.Value,1,true); %set analog filter for channel 1
%CheckError(error);

disp(strcat('Instrument ID = ', num2str(Inst_ID.Value)));%show the instrument number


%%%%%%%%%%%%%%%%
% MAIN PART
%%%%%%%%%%%%%%%%
%present all the possibility of MSRD
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

    
    %get sensor
    if strcmp(answer,'get sensor')
        prompt = 'which channel (1-4)?';
        channel_n=input(prompt);
        error = M_S_R_D_Get_Data(Inst_ID.Value,channel_n, sensor_value_Ptr );
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


error=M_S_R_D_Destructor(Inst_ID.Value);%close communication with the instrument
CheckError(error);

Elveflow_Unload;

clear Instrument_Name;
clear Inst_ID;
clear sensor_value_Ptr;