% Initialise_ MiniThreeTank_H.m    (SYSTEM H)

disp('Initialising parameters');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       System callibration parameters (for RT testing only)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Water level parameters; level [mm] = voltage * H1(1) + H1(2)
H1 = [-1.363636363636364e+02,6.584545454545455e+02];   
H2 = [-1.359434475258292e+02,6.459760739532353e+02];
H3 = [-1.346257404415725e+02,6.457189014539581e+02];   
%  Pump flowrate paramters; voltage = (flow [mm/s] - P1(1))/P1(2)
P1 = [0,4.483707856844433];      
P2 = [0,4.655506526469390];   

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       Common pump flow rate saturation limit and maximum water level
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Qlimit = 20;       % [mm/s]
Hlimit = 350;      % [mm]

disp('Initialisation complete');