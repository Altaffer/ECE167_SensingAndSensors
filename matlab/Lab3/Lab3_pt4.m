% PART 4.1
% Create tumble data claibration
[Anoise,Hnoise,Adist,Bdist] = CreateTumbleData(1000);

% CalibrateElipsoid data 3D calibration
% data = Anoise./1000; for accelerometer
data = Hnoise.*1000;
[Atilde,Btilde] = CalibrateEllipsoidData3D(data(:,1),data(:,2),data(:,3),1000,0);

% Correct Ellipsoid Data 3D
[Xcorr,Ycorr,Zcorr] = CorrectEllipsoidData3D(data(:,1),data(:,2),data(:,3),Atilde,Btilde);

%plot data
%fig1 = figure(1);
%scatter3(data(:,1),data(:,2),data(:,3), 'o');
%title('Lab 3 - Part 4.1: Tumble Test Simulation: Uncalibrated');

%fig2 = figure(2);
%scatter3(Xcorr,Ycorr,Zcorr, 'o');
%title('Lab 3 - Part 4: Tumble Test Simulation: LSM Calibrated');

%fig3 = figure(3);
%accel
%x = 0.053*(data(:,1)-1);
%y = 0.0505*(data(:,2)+5.9);
%z = 0.05*(data(:,3)+7);
%x = 0.00000303*(data(:,1)+5);
%y = 0.000003005*(data(:,2)+9);
%z = 0.0000032*(data(:,3)+10);
%scatter3(x,y,z,'o');
%title('Lab 3 - Part 4: Tumble Test Simulation: Naive Calibrated');

%PART 4.2
file = csvread('Lab3_pt4 - Sheet1.csv',1);
xaccel = file(:,1);
yaccel = file(:,2);
zaccel = file(:,3);
xmag = file(:,4);
ymag = file(:,5);
zmag = file(:,6);

%tumbleweed(xaccel, yaccel, zaccel, xmag, ymag, zmag, 1.003, 1.0005, 1.002, 18, 69, 16, 0.00000303, 0.000003005, 0.0000032, 5, 9, 10);
tumbleweed(Anoise(:,1), Anoise(:,2), Anoise(:,3), Hnoise(:,1), Hnoise(:,2), Hnoise(:,3), 0.053, 0.0505, 0.05, -1, 5.9, 10, 0.00000303, 0.000003005, 0.0000032, 5, 9, 10);

