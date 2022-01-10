%%%%%%%%%%%%%%%%%
%INITIALIZATION
%%%%%%%%%%%%%%%%%
%add path where the lib Elveflow are stored, load library and set all
%required variable (some are pointers to communicate with the DLL)
%and start the instrument
%%%%%%%%%%%%%%%%%

%define here the directory where .m, DLL and this script are 
addpath('D:\dev\SDK\MATLAB_64\MATLAB_64\');%path for MATLAB"***.m" file
addpath('D:\dev\SDK\MATLAB_64\MATLAB_64\DLL64\');%path for the DLL library
addpath('D:\dev\SDK\MATLAB_64\Example\')%path for your script

%always use Elveflow_Load at the beginning, it loads the DLL
Elveflow_Load;

error =0;%init error to zero, if an error occurs in the DLL, an error is returned
answer='empty_string';%store the user answer in this variable

%create equivalent of char[] to communicate with the DLL
%the instrument name can be found in NIMAX (installed with ESI)
Instrument_Name = libpointer('cstring','MyAF1'); 

%create a pointer for calibration
CalibSize = 1000;
Calibration = libpointer('doublePtr',zeros(CalibSize,1));

%pointer to store the instrument ID (no array)
Inst_ID=libpointer('int32Ptr',zeros(1,1));

%initiate the device and all regulators and sensors types (see user
%guide for help)
%may return an error if the instrument wasn't closed properly last time
error=AF1_Initialization(Instrument_Name,4,1,Inst_ID);
CheckError(error);

disp(strcat('Instrument ID = ', num2str(Inst_ID.Value)));%show the instrument number


%%%%%%%%%%%%%%%%
% CALIBRATION
%%%%%%%%%%%%%%%%
%choose between new calibration (take about 2 minutes) load calibration or
%default calibration
%%%%%%%%%%%%%%%%

%set the calibration path (if not found it will ask the user to choose the
%file). For instance define: 
%Calib_Save = libpointer('cstring','C:\Users\Public\Documents\Elvesys\MyCalib');
Calib_Save = libpointer('cstring',' ');
Calib_Load = libpointer('cstring',' ');


%ask the user what kind of calibration to use
while (~(strcmp(answer,'new')||strcmp(answer,'load')||strcmp(answer,'default')))
    prompt = 'What kind of calibration do you want to use?(new, load, default)\n';
    answer = input(prompt,'s');
end

if strcmp(answer,'new')%new calibration takes about 2 minutes
    if error==0
        error=AF1_Calib(Inst_ID.Value,Calibration, CalibSize);
        CheckError(error);
    end
    %save the calibration for further use
    if error==0
        error=Elveflow_Calibration_Save( Calib_Save , Calibration, CalibSize);
        CheckError(error);
    end
end

if strcmp(answer,'load')%load previous calibration
    if error==0
         error = Elveflow_Calibration_Load( Calib_Load , Calibration, CalibSize);
    end
end

if strcmp(answer,'default')%use default calibration
    if error==0
         error = Elveflow_Calibration_Default(Calibration, CalibSize);
    end
end

%%%%%%%%%%%%%%%%
% MAIN PART
%%%%%%%%%%%%%%%%
%Present all the possibility of AF1
%%%%%%%%%%%%%%%%
%init required variables
Pressure = libpointer('doublePtr',zeros(1,1));%pointer to store the pressure
flow_rate = libpointer ('doublePtr',zeros(1,1));%pointer to store the flow rate
trigger = libpointer ('int32Ptr',zeros(1,1));%pointer to store the trigger
channel_n = -1;
trigger_value=0;
%ask the user what to do and loop until the user enters exit
while (~strcmp(answer,'exit'))%loop until user enters exit
    %get user answers 
    answer='non valid answer to avoid looping indefinitely';
    while (~(strcmp(answer,'get pressure')||strcmp(answer,'set pressure')||strcmp(answer,'get sensor')||strcmp(answer,'get trigger')||strcmp(answer,'set trigger')||strcmp(answer,'start')||strcmp(answer,'stop')||strcmp(answer,'add PID')||strcmp(answer,'set target')||strcmp(answer,'read channel')||strcmp(answer,'exit')))
        prompt = '\nChoose what to do: get pressure, set pressure, get sensor, set trigger, get trigger or exit\n';
        answer = input(prompt,'s');
    end
    
    channel_n=-1;%reset channel_n to -1
    set_pressure=0;
    
    %get pressure
    if strcmp(answer,'get pressure')
        %integrate pressure over 100 ms
        error = AF1_Get_Press(Inst_ID.Value,100,Calibration, Pressure, CalibSize);
        CheckError(error);
        disp(strcat('pressure ch = ' , num2str(Pressure.Value),' mbar'));
    end
    
    %set pressure
    if strcmp(answer,'set pressure')
        prompt = 'select pressure (mbar)';
        set_pressure=input(prompt);
        error = AF1_Set_Press(Inst_ID.Value,set_pressure,Calibration,CalibSize);
        CheckError(error);
    end
    
    %get flow
    if strcmp(answer,'get sensor')
        error = AF1_Get_Flow_rate(Inst_ID.Value,flow_rate);
        CheckError(error);
        disp(strcat( 'flow rate = ',num2str(flow_rate.Value)));
              
    end
    
    %get the trigger value
    if strcmp(answer,'get trigger')
        error = AF1_Get_Trig(Inst_ID.Value,trigger);
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
            error = AF1_Set_Trig(Inst_ID.Value,1);
            CheckError(error);
        else
            error = AF1_Set_Trig(Inst_ID.Value,0);
            CheckError(error);
        end
    end
    
    
    %start the remote loop
    if strcmp(answer,'start')
        error = AF1_Start_Remote_Measurement(Inst_ID.Value,Calibration,CalibSize);
        CheckError(error);
    end
    
    %stop the remote loop
    if strcmp(answer,'stop')
        error = AF1_Stop_Remote_Measurement(Inst_ID.Value);
        CheckError(error);
    end
    
    %set a target in the remote loop
    if strcmp(answer,'set target')
        prompt = 'select target (mbar or uL/min)';
        set_pressure=input(prompt);
        error = AF1_Set_Remote_Target(Inst_ID.Value,set_pressure);
        CheckError(error);
    end
    
    %read the channel in the remote loop
    if strcmp(answer,'read channel')
        error = AF1_Get_Remote_Data(Inst_ID.Value, Press_value, flow_rate);
        CheckError(error);
        
        disp(strcat('regulator/sensor = ' , num2str(Press_value.Value),'; ', num2str(flow_rate.Value)));
    end
    
    %add a PID in the remote loop
    if strcmp(answer,'add PID')
        error = PID_Add_Remote(Inst_ID.Value,1,Inst_ID.Value,1,10,0.1,1);
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


error=AF1_Destructor(Inst_ID.Value);%close communication with the instrument
CheckError(error);

Elveflow_Unload;

clear Instrument_Name;
clear Inst_ID;
clear MyCalibPath;
clear Calibration;
clear Press_Array;
clear flow_rate;
clear trigger;

