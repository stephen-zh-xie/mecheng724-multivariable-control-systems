% Initialise_ MiniThreeTank_Sim.m    (SYSTEM X)

disp('Initialising simulation parameters');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       Valve positions  G=1 valve open G=0 valve closed
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
G1o = 0;  %Outflow tank 1
G2o = 1;  %Outflow tank 2
G3o = 0;  %Outflow tank 3```````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
G12 = 1;  %Crossflow tank 1 to tank 2
G32 = 1;  %Crossflow tank 3 to tank 2

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       Measured valve parameters (for simulation only)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Outflow valve parameters; outflow [mm/s] = a0*sqrt(height) + b0
a0 = 0.6799;
b0 = 2.7340;
% Crossflow valve parameters; crossflow [mm/s] = ac*sqrt(delta_height) + bc
ac = 0.6312;
bc = 0; 

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%       Common pump flow rate saturation limit and maximum water level
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Qlimit = 20;       % [mm/s]
Hlimit = 350;      % [mm]

disp('Initialisation complete');