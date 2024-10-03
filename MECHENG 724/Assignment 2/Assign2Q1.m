%% 2023 S2 MECHENG 724
% MATLAB script for Assignment 2 - modified/finished by Stephen Xie


close all
clear all
clc

% sim('DbInvPenQ1');   % You can run simulink models from m-file using sim
%Make copies of this simulink file to make Reference Tracking and
%Realisable Controllers. 

load sys_cart_dpen
A=sys_cart_dpen.A;
B=sys_cart_dpen.B;
C=sys_cart_dpen.C;

Cinv = inv(C);

%THE FOLLOWING FIGURE IS FOR ILLUSTRATING 
%HOW TO PLOT RESULTS FROM SIMULINK IN MATLAB
%YOU CAN REMOVE THIS FIGURE FROM YOUR SUBMISSION
%{
figure (1)
subplot(3,1,1)
plot(tout, yout(:,1))
xlabel('Time (sec)')
ylabel('Cart Position (cm)')
subplot(3,1,2)
plot(tout, yout(:,3))
xlabel('Time (sec)')
ylabel('\theta_1 (deg)')
subplot(3,1,3)
plot(tout, yout(:,5))
xlabel('Time (sec)')
ylabel('\theta_2 (deg)')
%}


% Since we're making a reference tracking controller we need to operate in
% the error domain, so I'll start by constructing the error space model
% note: 6 states, 2 inputs, 6 outputs
Aspace = zeros(6);
Bspace = zeros(6, 2);
Abar = [Aspace, C; Aspace, A];
Bbar = [Bspace; B];

%% (1) Check controlability here
Mc = ctrb(Abar, Bbar);
rankMc = rank(Mc);
disp('Rank of Mc = ')
disp(rankMc)
disp(' which is not full rank (n=12) so we cannot place poles arbitrarily')

%% (2) Design reference tracking controller here

% You may run the simulink model for reference tracking controller from your m
% file here or directly from simulink.
%Present the controller performance by plotting states x, theta1_dot,
%theta2_dot.

% Design controller via pole placement
placed_poles = [-6 + 2j, -6 - 2j, -6.5, -7, -7 + 2j, -7 - 2j];
K = place(A, B, placed_poles);

%sim('DbInvPenQ1');
% It stalls and runs too slowly to be feasible and I'm not sure why
%% (3) Check observability here



%% (4) Design state estimator here

% You can also run a realisable controller simulink model from your m
% file here or directly from simulink.
%Present the controller performance by plotting states x, theta1,
%theta2.
% Presents plots to compare state estimates with actual states.



%% (5) Closed loop eigenvalues




