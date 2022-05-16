%Solving for x_0, y_0, a, b
Xsquared = -1*[Xmeas.^2];
A = [-2*Xmeas Ymeas.^2 -2*Ymeas ones(size(Xmeas))];
mldivide(A,Xsquared);

%Values
x_0 = 0.3962;
y_0 = -0.33860;
a = 1.0497;
b = 2.03604;

%calibrated x & y
xHat = ((1/a)*(Xmeas-x_0));
yHat = ((1/b)*(Ymeas-y_0));

%Plotting the 2-norm of pre-calibrated
hold on;
axis equal;
plot(Xmeas, Ymeas, 'o');

%Plotting the 2-norm of post-calibrated
plot(xHat, yHat, 'x');

%graph stuff
legend('pre-calibrated', 'post-calibrated');
xlabel('X');
ylabel('Y');
title('Lab 3 - Part 1: Plotting 2-norm pre & post Calibrated Data');
hold off