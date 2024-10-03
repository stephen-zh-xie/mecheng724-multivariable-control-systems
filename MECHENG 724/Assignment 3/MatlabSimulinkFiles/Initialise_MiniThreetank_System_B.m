% Initialise_ MiniThreeTank_B.m    (SYSTEM B)

disp('Initialising parameters');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       System callibration parameters (for P2(2) = P2(1)/10RT testing only)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%P2(2) = P2(1)/10%%%%%%%%%%%%%%
%  Water level parameters; level [mm] = voltage * H1(1) + H1(2)
H1 = [-1.331203407880724e+02,6.479765708200213e+02];
H2 = [-1.336183858898984e+02,6.723944414751468e+02];
H3 = [-1.330153683094860e+02,6.496332803391626e+02];   
%  Pump flowrate paramters; voltage = (flow [mm/s] - P1(1))/P1(2)
P1 = [0,4.778539903643306];      
P2 = [0,5.119197719447961];   

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       Common pump flow rate saturation limit and maximum water level
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Qlimit = 20;       % [mm/s]
Hlimit = 350;      % [mm]

disp('Initialisation complete');