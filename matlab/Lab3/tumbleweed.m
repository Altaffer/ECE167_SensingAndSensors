function a = PlotMeDaddy(x_acc, y_acc, z_acc, x_mag, y_mag, z_mag, a_acc_x, a_acc_y, a_acc_z, b_acc_x, b_acc_y, b_acc_z, a_mag_x, a_mag_y, a_mag_z, b_mag_x, b_mag_y, b_mag_z)
%% scale data
x_acc_scale = x_acc ./ 1000;
y_acc_scale = y_acc ./ 1000;
z_acc_scale = z_acc ./ 1000;
x_mag_scale = x_mag .* 1000;
y_mag_scale = y_mag .* 1000;
z_mag_scale = z_mag .* 1000;

%% plot accelerometer data
% plot uncalibrated accelerometer data
acc_uncalibrated = figure(1);
scatter3(x_acc_scale, y_acc_scale, z_acc_scale, "o");
title("uncalibrated accelerometer data");

% plot naive calibrated accelerometer data
acc_naivecalbrated = figure(2);
x_acc_naive = a_acc_x.*(x_acc_scale + b_acc_x);
y_acc_naive = a_acc_y.*(y_acc_scale + b_acc_y);
z_acc_naive = a_acc_z.*(z_acc_scale + b_acc_z);
scatter3(x_acc_naive, y_acc_naive, z_acc_naive, "o");
title("naive calibrated accelerometer data");

% plot LSM calibrated accelerometer data
[Atilde,Btilde] = CalibrateEllipsoidData3D(x_acc_scale,y_acc_scale,z_acc_scale,1000,0);
[Xcorr,Ycorr,Zcorr] = CorrectEllipsoidData3D(x_acc_scale,y_acc_scale,z_acc_scale,Atilde,Btilde);
acc_LSMcalibrated = figure(3);
scatter3(Xcorr, Ycorr, Zcorr, "o");
title("LSM calibrated accelerometer data");

% take the norms of each accelerometer dataset
uncalibrated_norm = zeros(size(x_acc_scale));
naive_calibrated_norm = zeros(size(x_acc_scale));
LSM_calibrated_norm = zeros(size(x_acc_scale));

for i = 1:1:size(x_acc_scale)
    uncalibrated_norm(i) = sqrt(x_acc_scale(i).^2 + y_acc_scale(i).^2 + z_acc_scale(i).^2);
    naive_calibrated_norm(i) = sqrt(x_acc_naive(i).^2 + y_acc_naive(i).^2 + z_acc_naive(i).^2);
    LSM_calibrated_norm(i) = sqrt(Xcorr(i).^2 + Ycorr(i).^2 + Zcorr(i).^2);
end

% plot the norms of each acclerometer dataset
acc_uncalibrated_norm = figure(4);
plot(uncalibrated_norm, "x");
title("uncalibrated accelerometer norm");

acc_naivecalibrated_norm = figure(5);
plot(naive_calibrated_norm, "x");
title("naive calibrated accelerometer norm");

acc_LSMcalibrated_norm = figure(6);
plot(LSM_calibrated_norm, "x");
title("LSM calibrated accelerometer norm");

% get the mean and standard deviation for each norm
txt=sprintf("acc uncalibrated - mean: %f, stdev: %f\n", mean(uncalibrated_norm), std(uncalibrated_norm));
disp(txt);
txt=sprintf("acc naive calibrated - mean: %f, stdev: %f\n", mean(naive_calibrated_norm), std(naive_calibrated_norm));
disp(txt);
txt=sprintf("acc LSM calibrated - mean: %f, stdev: %f\n", mean(LSM_calibrated_norm), std(LSM_calibrated_norm));
disp(txt);
%% plot magnetometer data
% plot uncalibrated magnetometer data
mag_uncalibrated = figure(7);
scatter3(x_mag_scale, y_mag_scale, z_mag_scale, "o");
title("uncalibrated magnetometer data");

% plot naive calibrated magnetometer data
mag_naivecalbrated = figure(8);
x_mag_naive = a_mag_x.*(x_mag_scale + b_mag_x);
y_mag_naive = a_mag_y.*(y_mag_scale + b_mag_y);
z_mag_naive = a_mag_z.*(z_mag_scale + b_mag_z);
scatter3(x_mag_naive, y_mag_naive, z_mag_naive, "o");
title("naive calibrated magnetometer data");

% plot LSM calibrated magnetometer data
[Atilde,Btilde] = CalibrateEllipsoidData3D(x_mag_scale,y_mag_scale,z_mag_scale,1000,0);
[Xcorr,Ycorr,Zcorr] = CorrectEllipsoidData3D(x_mag_scale,y_mag_scale,z_mag_scale,Atilde,Btilde);
mag_LSMcalibrated = figure(9);
scatter3(Xcorr, Ycorr, Zcorr, "o");
title("LSM calibrated magnetometer data");

% take the norms of each magnetometer dataset
uncalibrated_norm = zeros(size(x_mag_scale));
naive_calibrated_norm = zeros(size(x_mag_scale));
LSM_calibrated_norm = zeros(size(x_mag_scale));

for i = 1:1:size(x_mag_scale)
    uncalibrated_norm(i) = sqrt(x_mag_scale(i).^2 + y_mag_scale(i).^2 + z_mag_scale(i).^2);
    naive_calibrated_norm(i) = sqrt(x_mag_naive(i).^2 + y_mag_naive(i).^2 + z_mag_naive(i).^2);
    LSM_calibrated_norm(i) = sqrt(Xcorr(i).^2 + Ycorr(i).^2 + Zcorr(i).^2);
end

% plot the norms of each magnetometer dataset
mag_uncalibrated_norm = figure(10);
plot(uncalibrated_norm, "x");
title("uncalibrated magnetometer norm");

mag_naivecalibrated_norm = figure(11);
plot(naive_calibrated_norm, "x");
title("naive calibrated magnetometer norm");

mag_LSMcalibrated_norm = figure(12);
plot(LSM_calibrated_norm, "x");
title("LSM calibrated magnetometer norm");

% get the mean and standard deviation for each norm
txt=sprintf("mag uncalibrated - mean: %f, stdev: %f\n", mean(uncalibrated_norm), std(uncalibrated_norm));
disp(txt);
txt=sprintf("mag naive calibrated - mean: %f, stdev: %f\n", mean(naive_calibrated_norm), std(naive_calibrated_norm));
disp(txt);
txt=sprintf("mag LSM calibrated - mean: %f, stdev: %f\n", mean(LSM_calibrated_norm), std(LSM_calibrated_norm));
disp(txt);
end