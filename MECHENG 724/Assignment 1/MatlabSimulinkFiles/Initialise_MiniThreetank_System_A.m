% Initialise_ MiniThreeTank_A.m    (SYSTEM A)

disp('Initialising parameters');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       System callibration parameters (for P2(2) = P2(1)/10RT testing only)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%P2(2) = P2(1)/10%%%%%%%%%%%%%%
%  Water level parameters; level [mm] = voltage * H1(1) + H1(2)
H1 = [-1.351351351351351e+02,6.689189189189188e+02];
H2 = [-1.344086021505376e+02,6.588709677419354e+02];
H3 = [-1.351351351351351e+02,6.513513513513514e+02];   
%  Pump flowrate paramters; voltage = (flow [mm/s] - P1(1))/P1(2)
P1 = [0,5.435299228977511];      
P2 = [0,4.997863989252405];   

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       Common pump flow rate saturation limit and maximum water level
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Qlimit = 20;       % [mm/s]
Hlimit = 350;      % [mm]

disp('Initialisation complete');