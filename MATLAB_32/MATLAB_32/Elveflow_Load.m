%Load the Elveflow DLL that contains every functions used for the control
%of elveflow instruments. This script has to be executed only once at the beginning of the working session before
%using elveflow instruments.

DLL_name='Elveflow32';
if libisloaded(DLL_name)==false;
    [notfound,warnings]=loadlibrary(DLL_name,strcat(DLL_name,'.h')); %load the library. The header file and the dll file must be in your path
end
%libfunctions(DLL_name);%list all function in DLL.Should return many function