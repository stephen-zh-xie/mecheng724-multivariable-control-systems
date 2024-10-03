% Simulating the 3 tank model for assignment 1
% Uses the provided linearized model
% Uses a bunch of provided code and variables
% This stuff here was made by Stephen Xie
% in the early morning of 25/8/2023

% start by clearing the workspace
clear;
clc;

% then load the linear model and initialise the tank
load("LinearModel.mat")
run("Initialise_MiniThreetank_Sim")

% we now have A, B, C and D
% make error space state system for reference tracking
Abar = [[0,0;0,0], C; [0,0;0,0;0,0], A];
Bbar = [[0,0;0,0]; B];

% check if controllable
Mc = ctrb(Abar, Bbar);
rnk = rank(Mc);
disp("Rank of Mc = " + rnk);
    
% calculate gains via pole placement
% placed_poles = (1/25)*[-1, -1, -1.25, -1.5, -1.5];
placed_poles = [-4.0 + 4.2j, -4.0 - 4.2j, -1, -2, -3] * 0.032;
Kbar = place(Abar, Bbar, placed_poles);
Kr = Kbar(1:2, 1:2);
Kx = Kbar(1:2, 3:5);

% run simulations
sim("ThreeTankSIM");
run("calc_settle")