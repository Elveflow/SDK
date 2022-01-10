%Unload the Elveflow DLL and release the memory. This script has to be
%executed only once at the end of the working session or when no more
%communication with Elveflow instrument is required

unloadlibrary('Elveflow64');