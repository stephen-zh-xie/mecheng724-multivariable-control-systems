% Initialise_ MiniThreeTank_K.m    (SYSTEM K)

disp('Initialising parameters');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       System callibration parameters (for RT testing only)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%  Water level parameters; level [mm] = voltage * H1(1) + H1(2)
H1 = [-1.352082206598161e+02,6.462682531097890e+02];   
H2 = [-1.357220412595006e+02,6.819218241042346e+02];
H3 = [-1.340482573726542e+02,6.796246648793566e+02];   
%  Pump flowrate paramters; voltage = (flow [mm/s] - P1(1))/P1(2)
P1 = [0,4.583974039677245];      
P2 = [0,5.382099661274232];   

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       Common pump flow rate saturation limit and maximum water level
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Qlimit = 20;       % [mm/s]
Hlimit = 350;      % [mm]

disp('Initialisation complete');