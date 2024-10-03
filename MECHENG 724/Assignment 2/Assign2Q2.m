%%2023 S2 MECHENG 724
% MATLAB script for Controlling Double Inverted Pendulum using MPC

close all
clear all
clc


load sys_cart_dpen
A=sys_cart_dpen.A;
B=sys_cart_dpen.B;
C=sys_cart_dpen.C;
D=sys_cart_dpen.D;

%% Convert to discrete time system

sysc=ss(A,B,C,D);
Ts=0.05;
sysd=   ;                         %Convert the state-space model to discrete time


%% System matrices

n = size(sysd.A,1);

m = size(sysd.B,2)

p = size(sysd.C,1);

Ap = [sysd.A zeros(n,p); C*sysd.A eye(p)]
Bp = [sysd.B; C*sysd.B]
Cp = [zeros(p,n) eye(p)]


%% Horizon    (Do not change for final solution submission)
Np = 10; % Predicition Horizon
Nc = 4; % Control horizon


%% Building F and phi








%Print F and phi matrix
F
phi

%% Reference cart position
ref_cart_x = Cp*[0; 0; 0; 0; 0; 0; 25; 0; 0; 0; 0; 0]               %You can change the reference here 
Yr=repmat(ref_cart_x,[Np,1])    %Build the reference matrix cover Prediction horizon


%% Matrices for optimal control
phiTphi= 
phiTF = 
phiTYr = 

%% Weight

rw= 100;
R = rw*eye(m*Nc);


%% Running Simulink model and displaying results

disp('Simulink Model for Control of Double Inverted Pendulum with MPC');
open_system('DbInvPenQ2.slx')   % This will print the model on published file if simulink model is closed initially. 
DPmpc = sim('DbInvPenQ2','SaveTime','on','TimeSaveName','tout','SaveOutput','on','OutputSaveName','yout');   

% The following commands plotting commands  work if 
% Model Settings > Data Import/ Export  > Format = 'Array'

figure (1)
subplot(3,1,1)
plot(DPmpc.tout, DPmpc.yout(:,1),'-k',DPmpc.tout, 25*ones(length(DPmpc.tout)),'-.r')
xlabel('Time (sec)')
ylabel('Cart Position (cm)')
legend('Actual position', 'Reference Position')  
subplot(3,1,2)
plot(DPmpc.tout, DPmpc.yout(:,3),'-k')
xlabel('Time (sec)')
ylabel('$\theta_1$ (deg)', 'Interpreter','latex')
legend('Lower link position')  
subplot(3,1,3)
plot(DPmpc.tout, DPmpc.yout(:,5),'-k')
xlabel('Time (sec)')
ylabel('$\theta_2$ (deg)', 'Interpreter','latex')
legend('Upper link position')  