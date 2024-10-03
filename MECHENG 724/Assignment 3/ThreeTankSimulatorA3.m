% Simulating the 3 tank model for assignment 3
% Uses the provided non-linear model
% Uses a bunch of provided code and variables
% This stuff here was made by Stephen Xie
% in the early morning of 17/10/2023

% start by clearing the workspace
clear;
clc;

% then load the model and initialise the tank
run("Initialise_MiniThreetank_Sim")

% setup gains (k0, k1, ac and ao) using arbitrary gains
k0 = 0.05;
k1 = 0.01;
k2 = 0.2;
k3 = 0;

% run simulations
sim("ThreeTankSIM");
run("calc_settle")