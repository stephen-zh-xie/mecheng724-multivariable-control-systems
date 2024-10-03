% calculate 3% settling times for tanks 1 & 2

% h1_ref = input('Enter reference height for tank 1 (mm): ');
% h2_ref = input('Enter reference height for tank 2 (mm): ');
h1_ref = 175; disp(['h1_ref = ',num2str(h1_ref)]);
h2_ref = 100; disp(['h2_ref = ',num2str(h2_ref)]);

[b,a]=butter(5, 0.1);                   % create 5th-order low-pass Butterworth filter with normalised cut-off freq of 0.1
heights_filt = filtfilt(b,a,heights.signals.values);   % filter the height signals both ways (zero delay)

dh1 = abs(heights_filt(:,1) - h1_ref);  % absolute errors
dh2 = abs(heights_filt(:,2) - h2_ref);

i = length(dh1);
while dh1(i) < 0.03*h1_ref
    i = i - 1;
end
Ts_1 = round(heights.time(i+1));
disp(['Settling time for tank 1 = ',num2str(Ts_1),' sec']);

i = length(dh2);
while dh2(i) < 0.03*h2_ref
    i = i - 1;
end
Ts_2 = round(heights.time(i+1));
disp(['Settling time for tank 2 = ',num2str(Ts_2),' sec']);

% calculate the standard deviation of steady-state pump flow rates

if max([Ts_1, Ts_2]) < heights.time(end)-50      % only perform calc if system has settled for at least 50 seconds before end of sim
    tstart = find(heights.time == heights.time(end)-20); % sample number 20 seconds from end
    pumps_std = std(pumps.signals.values(tstart:end,:));
    disp(['Standard deviation of pump 1 = ',num2str(pumps_std(1)),' mm/s']);
    disp(['Standard deviation of pump 2 = ',num2str(pumps_std(2)),' mm/s']);
end
disp(' ');    
