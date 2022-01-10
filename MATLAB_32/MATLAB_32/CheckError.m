function [] = CheckError(ElveflowError)
% Get a warning if error is not empty
    if ElveflowError~=0
        temp=strcat('An ERRORS occurs, check SDK User guide and LabView standar error. Error n°:',num2str(ElveflowError));
        disp(temp);
    end
end