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

ElveflowError = 0;%init error to zero, if an error occurs in the DLL, an error is returned
answer='empty_string';%store the user answer in this variable

%create equivalent of char[] to communicate with the DLL
%the instrument name can be found in NIMAX
Instrument_Name = libpointer('cstring','Dev4'); 


%pointer to store the instrument ID (no array)
Inst_ID=libpointer('int32Ptr',zeros(1,1));

%initiate the device 
ElveflowError=MUX_Initialization(Instrument_Name,Inst_ID);
CheckError(ElveflowError);

disp(strcat('Instrument ID = ', num2str(Inst_ID.Value)));%show the instrument number


%%%%%%%%%%%%%%%%
% MAIN PART
%%%%%%%%%%%%%%%%
%present all the possibility of MUX
%%%%%%%%%%%%%%%%
%init required variables
input_valve = -1;
output_valve = -1;
valve_state = -1;

Array_user=[1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0];%change here valves state (see MUX_Set_all_valves.m for description)
Array_user_Ptr = libpointer('int32Ptr',Array_user);%init all valves here !!! should be exactly 16 elements, otherwise nothing will happen 

Array_all_open= [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1];
Array_all_open_Ptr = libpointer('int32Ptr',Array_all_open);%all valves opened

Array_all_closed=[0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
Array_all_closed_Ptr = libpointer('int32Ptr',Array_all_closed);%all valves closed


trigger = libpointer ('int32Ptr',zeros(1,1)); %pointer to trigger
trigger_value=0;
%ask the user what to do and loop until user enters exit
while (~strcmp(answer,'exit'))%loop until user enters exit
    %get user answer 
    answer='non valid answer to avoid looping indefinitely';
    while (~(strcmp(answer,'set individual valve')||strcmp(answer,'set all valves')||strcmp(answer,'set all valves (MUX Wire)')||strcmp(answer,'close all')||strcmp(answer,'open all')||strcmp(answer,'get trigger')||strcmp(answer,'set trigger')||strcmp(answer,'exit')))
    prompt = '\nChoose what to do: set individual valve, set all valves, set all valves (MUX Wire),close all, open all, get trigger, set trigger op exit\n';
    answer = input(prompt,'s');
    end

    
    %set individual valve (for MUX quake)
    if strcmp(answer,'set individual valve')
        prompt = 'input valve';
        input_valve=input(prompt);
        prompt = 'output valve';
        output_valve=input(prompt);
        prompt = 'valve_state';
        valve_state=input(prompt);
        ElveflowError = MUX_Set_indiv_valve(Inst_ID.Value,input_valve, output_valve, valve_state);
        CheckError(ElveflowError);
    end
    
    %set all valves (uses Array_user defined above)
    if strcmp(answer,'set all valves')
        
        ElveflowError = MUX_Set_all_valves(Inst_ID.Value, Array_user_Ptr,16);
        CheckError(ElveflowError);
    end
    
    %set all valves for the MUX WIRE(uses Array_user defined above) VALVE
    %ORDER IS DIFFERENT THAN OTHER MUX
    if strcmp(answer,'set all valves (MUX Wire)')
        
        ElveflowError = MUX_Wire_Set_all_valves(Inst_ID.Value, Array_user_Ptr,16);
        CheckError(ElveflowError);
    end
    
    %close all valves 
    if strcmp(answer,'close all')
        
        ElveflowError = MUX_Set_all_valves(Inst_ID.Value, Array_all_closed_Ptr,16);
        CheckError(ElveflowError);
    end
    
    %open all valves 
    if strcmp(answer,'open all')
        
        ElveflowError = MUX_Set_all_valves(Inst_ID.Value, Array_all_open_Ptr,16);
        CheckError(ElveflowError);
    end
    
   
    
    %get the trigger value
    if strcmp(answer,'get trigger')
        ElveflowError = MUX_Get_Trig(Inst_ID.Value,trigger);
        CheckError(ElveflowError);
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
            ElveflowError = MUX_Set_Trig(Inst_ID.Value,1);
        else
            ElveflowError = MUX_Set_Trig(Inst_ID.Value,0);
        end
        CheckError(ElveflowError);
    end
end

%%%%%%%%%%%%%%%
%EXIT
%%%%%%%%%%%%%%%
%close communication 
%clear all pointers. If it is not done properly, it will crash at next
%launch
%%%%%%%%%%%%%%%


MUX_Destructor(Inst_ID.Value);%close communication with the instrument

Elveflow_Unload;

clear Instrument_Name;
clear Inst_ID;
clear Array_all_open_Ptr;
clear Array_user_Ptr;
clear Array_all_closed_Ptr;
clear trigger;