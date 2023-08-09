%%%%%%%%%%%%%%%%%
%INITIALIZATION
%%%%%%%%%%%%%%%%%
%add path where the lib Elveflow are stored, load library and set all
%required variables (some are pointers to communicate with the DLL)
%and start the instrument
%%%%%%%%%%%%%%%%%

%define here the directory where .m, DLL and this script are 
addpath('D:\dev\SDK\SDK_V3_06_03\MATLAB_64\MATLAB_64\');%path for MATLAB"***.m" file
addpath('D:\dev\SDK\SDK_V3_06_03\MATLAB_64\MATLAB_64\DLL64\');%path for the DLL library
addpath('D:\dev\SDK\SDK_V3_06_03\MATLAB_64\Example\')%path for your script

%always use Elveflow_Load at the beginning, it loads the DLL
Elveflow_Load;

error =0;%init error to zero, if an error occurs in the DLL, an error is returned
answer='empty_string';%store the user answer in this variable


%create equivalent of char[] to communicate with the DLL
%the instrument name can be found in NIMAX
Instrument_Name = libpointer('cstring','COM5');%COM5 is the COM port of the instrument
%COM port is applicable only for OB1 MK4 devices
%For OB1 MK3+, use NI 485 serial number found in NI MAX

%create a pointer for calibration
CalibSize = 1000;
Calibration = libpointer('doublePtr',zeros(CalibSize,1));

%pointer to store the instrument ID (no array)
Inst_ID=libpointer('int32Ptr',zeros(1,1));

%initiate the device and all regulator and sensor types (see User
%Guide for help)
error=OB1_Initialization(Instrument_Name,0,0,0,0,Inst_ID);
CheckError(error);

%add digital flow sensor. Valid for OB1 MK3+ only, if sensor is not detected it will throw an error
%error=OB1_Add_Sens(Inst_ID.Value,3,1,1,0,7,0);%(CustomSens_Voltage_5_to_25 only works with CustomSensors and OB1 from 2020 and after)
%CheckError(error);

disp(strcat('Instrument ID = ', num2str(Inst_ID.Value)));%show the instrument number


%%%%%%%%%%%%%%%%
% CALIBRATION
%%%%%%%%%%%%%%%%
%choose between new calibration (take about 2 minutes) load calibration or
%default calibration
%%%%%%%%%%%%%%%%

%set the calibrations path (if not found it will ask the user to choose the
%file). For instance define: 
%Calib_Save = libpointer('cstring','C:\Users\Public\Documents\Elvesys\MyCalib');
Calib_Save = libpointer('cstring',' ');
Calib_Load = libpointer('cstring',' ');


%ask user what kind of calibration to use
while (~(strcmp(answer,'new')||strcmp(answer,'load')||strcmp(answer,'default')))
    prompt = 'What kind of calibration do you want to use ?(new, load, default)\n';
    answer = input(prompt,'s');
end

if strcmp(answer,'new')%new calibration takes about 2 minutes
    if error==0%avoid new calibration if something happened during the initialization
        error = OB1_Calib(Inst_ID.Value,Calibration, CalibSize);
        %save the calibration for further use
        error=Elveflow_Calibration_Save( Calib_Save , Calibration, CalibSize);
        CheckError(error);
    end
end

if strcmp(answer,'load')%load previous calibration
    error = Elveflow_Calibration_Load( Calib_Load , Calibration, CalibSize);
    CheckError(error);
end

if strcmp(answer,'default')%use default calibration
    error = Elveflow_Calibration_Default(Calibration, CalibSize);
    CheckError(error);
end


%%%%%%%%%%%%%%%%
% MAIN PART
%%%%%%%%%%%%%%%%
%present all the possibility of OB1
%%%%%%%%%%%%%%%%
%init required variables
Press_Array = libpointer('doublePtr',zeros(4,1)); %pointer to store the 4 pressure channels
Press_value= libpointer('doublePtr',zeros(1,1));%pointer to store the pressure of 1 channel
flow_rate = libpointer ('doublePtr',zeros(1,1)); %pointer to store the flow rate
trigger = libpointer ('int32Ptr',zeros(1,1)); %pointer to store the trigger
channel_n = -1;
channel_n_2 = -1;
trigger_value=0;
%ask the user what to do and loop until user enters exit
while (~strcmp(answer,'exit')) %loop until user enters exit
    %get user answer 
    answer='non valid answer to avoid looping indefinitely';
    while (~(strcmp(answer,'get pressure')||strcmp(answer,'set pressure')||strcmp(answer,'get everything')||strcmp(answer,'get sensor')||strcmp(answer,'get trigger')||strcmp(answer,'set trigger')||strcmp(answer,'start')||strcmp(answer,'stop')||strcmp(answer,'add PID')||strcmp(answer,'set target')||strcmp(answer,'read channel')||strcmp(answer,'exit')))
    prompt = '\nChoose what to do: get pressure, get sensor, get everything, set pressure, set trigger, get trigger or exit\n';
    answer = input(prompt,'s');
    end
    
    channel_n=-1; %reset channel_n to -1
    set_pressure=0;
    
    %get pressure
    if strcmp(answer,'get pressure')
        %select the channel
         while (~(channel_n>0&&channel_n<5))
            prompt = 'select channel (1-4)';
            channel_n=input(prompt);
        end
        
        error = OB1_Get_Press(Inst_ID.Value ,channel_n, 1, Calibration, Press_value, CalibSize);
        CheckError(error);
        
        disp(strcat('pressure ch',num2str(channel_n), ' = ' , num2str(Press_value.Value),' mbar'));
    end
    
    %get flow
    if strcmp(answer,'get sensor')
        while (~(channel_n>0&&channel_n<5))
            prompt = 'select channel (1-4)';
            channel_n=input(prompt);
        end
        error = OB1_Get_Sens_Data(Inst_ID.Value,channel_n, 1,flow_rate); %Acquire data=1 -> acquire the fresh data, if zero, used data in buffer 
        CheckError(error);
        disp(strcat( 'sensor data = ',num2str(flow_rate.Value)));
    end
    
    %get all pressure and sensor values
    if strcmp(answer,'get everything')
        
        error = OB1_Get_Press(Inst_ID.Value ,1, 1, Calibration, Press_value, CalibSize);%Acquire data=1 -> refresh the buffer (takes about 2 ms)
        CheckError(error);
        disp(strcat('pressure ch',num2str(i), ' = ' , num2str(Press_value.Value),' mbar'));
        for i = 2:4 %read all the other channels using the value written in buffer by the previous OB1_Get_Press function
             error = OB1_Get_Press(Inst_ID.Value , i, 0, Calibration, Press_value, CalibSize);%Acquire data=0 -> use data acquired in the buffer (takes about 2 ms)
             disp(strcat('pressure ch',num2str(i), ' = ' , num2str(Press_value.Value),' mbar'));
        end
        
        for i = 1:4 %read all sensors using the value written in buffer by the previous OB1_Get_Press function. For digital sensor, the value is read by this function
             error = OB1_Get_Sens_Data(Inst_ID.Value ,i, 0, flow_rate);%Acquire data=0 -> use data acquired in the buffer (takes about 2 ms)
             disp(strcat('sens ch',num2str(i), ' = ' , num2str(flow_rate.Value),'µL/min or mbar'));
        end
    end
    
    %set pressure
    if strcmp(answer,'set pressure')
        while (~(channel_n>0&&channel_n<5))
            prompt = 'select channel (1-4)';
            channel_n=input(prompt);
        end
        prompt = 'select pressure (mbar)';
        set_pressure=input(prompt);
        error = OB1_Set_Press(Inst_ID.Value,channel_n,set_pressure,Calibration,CalibSize);
        CheckError(error);
    end
    
    
    %get the trigger value
    if strcmp(answer,'get trigger')
        error = OB1_Get_Trig(Inst_ID.Value,trigger);
        CheckError(error);
        if trigger.Value==0
            disp(strcat( 'Trigger is Low '));
        end
        if trigger.Value==1
            disp(strcat( 'Trigger is High '));
        end   
    end
    
    %set trigger
    if strcmp(answer,'set trigger')
        
        while (~(strcmp(answer,'high')||strcmp(answer,'low')))
            prompt = 'set trigger state (high or low)';
            answer=input(prompt,'s');
        end
        if strcmp(answer,'high')
            error = OB1_Set_Trig(Inst_ID.Value,1);
            CheckError(error);
        else
            error = OB1_Set_Trig(Inst_ID.Value,0);
            CheckError(error);
        end
       
    end
    
    %start the remote loop
    if strcmp(answer,'start')
        error = OB1_Start_Remote_Measurement(Inst_ID.Value,Calibration,CalibSize);
        CheckError(error);
    end
    
    %stop the remote loop
    if strcmp(answer,'stop')
        error = OB1_Stop_Remote_Measurement(Inst_ID.Value);
        CheckError(error);
    end
    
    %set a target in the remote loop
    if strcmp(answer,'set target')
        %select the channel
        while (~(channel_n>0&&channel_n<5))
            prompt = 'select channel (1-4)';
            channel_n=input(prompt);
        end
        prompt = 'select target (mbar or uL/min)';
        set_pressure=input(prompt);
        error = OB1_Set_Remote_Target(Inst_ID.Value,channel_n,set_pressure);
        CheckError(error);
    end
    
    %read a channel in the remote loop
    if strcmp(answer,'read channel')
        %select the channel
        while (~(channel_n>0&&channel_n<5))
            prompt = 'select channel (1-4)';
            channel_n=input(prompt);
        end
        
        error = OB1_Get_Remote_Data(Inst_ID.Value ,channel_n, Press_value, flow_rate);
        CheckError(error);
        
        disp(strcat('regulator/sensor ch',num2str(channel_n), ' = ' , num2str(Press_value.Value),'; ', num2str(flow_rate.Value)));
    end
    
    %add a PID in the remote loop
    if strcmp(answer,'add PID')
        while (~(channel_n>0&&channel_n<5))
            prompt = 'select channel regulator (1-4)';
            channel_n=input(prompt);
        end
        while (~(channel_n_2>0&&channel_n_2<5))
            prompt = 'select channel sensor (1-4)';
            channel_n_2=input(prompt);
        end
        error = PID_Add_Remote(Inst_ID.Value,channel_n,Inst_ID.Value,channel_n_2,10,0.1,1);
        CheckError(error);
    end
    
end

%%%%%%%%%%%%%%%
%EXIT
%%%%%%%%%%%%%%%
%close communication 
%clear all pointers. If it is not done properly, it will crash at next
%launch
%%%%%%%%%%%%%%%

error=OB1_Destructor(Inst_ID.Value);%close communication with the instrument
CheckError(error);
    

Elveflow_Unload;%unload DLL


clear Instrument_Name;
clear Inst_ID;
clear MyCalibPath;
clear Calibration;
clear Press_Array;
clear flow_rate;
clear trigger;