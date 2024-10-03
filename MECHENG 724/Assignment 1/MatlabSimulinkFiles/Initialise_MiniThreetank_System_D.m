% Initialise_ MiniThreeTank_D.m    (SYSTEM D)

disp('Initialising parameters');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       System callibration parameters (for RT testing only)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Water level parameters; level [mm] = voltage * H1(1) + H1(2)
H1 = [-1.334757074212494e+02,6.618526428190070e+02];   
H2 = [-1.341201716738198e+02,6.680257510729615e+02];
H3 = [-1.346566523605150e+02,6.562242489270387e+02];   
%  Pump flowrate paramters; voltage = (flow [mm/s] - P1(1))/P1(2)
P1 = [0,4.758272391648974];      
P2 = [0,4.950856816941413];   

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       Common pump flow rate saturation limit and maximum water level
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Qlimit = 20;       % [mm/s]
Hlimit = 350;      % [mm]

disp('Initialisation complete');