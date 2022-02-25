%FAABsim.m      the Fieldworker-Aerial Awareness Beacon model
%The purpose of this script is to show model the ability of an Aerial
%Applicator to see an alert beacon showing the location of a fieldworker or
%crew. Maximizing awareness of ground-based workers can help to mitigate
%unwanted human exposure to agrochemical products.

%Assumptions:
    %straight level flight VZ = 0
    %ability to see behind(for now) OR only the approach matters(can't see 
        %behind themselves anyway...
    %continuous light emitted from beacon (will add flash soon)
    
clear
%%
%Global parameters
    %inputs/variable parameters
    V = 120 * 1.68781;    %speed(knots*1.68->ft/s)
    H = 90;     %Heading(degees, 0 is due NORTH)
    X0 = -6000;  %initial position(ft) on the x axis(positive is East) 
    Y0 = 0;  %initial position(ft) on the y axis(positive is North)
    Z0 = 200;   %initial position(ft) on the z axis(positive is Up)
    VZ = 0;     %climb/descent rate(ft/s)

    BROT = 3;          %Time(s) for 1 rotation of the beacon
    BTILT = .4;        %time(s) for 1 tilt cycle(up and down)
    BTILTOFF = 10;      %minimum tilt(degrees) of the beacon 
    BDEGPHI = 15;   %max additional upward tilt
    BX0 = 0; BY0 = 0; BZ0 = 0;    %Beacon coordinate 0,0,0
    BVIEW = 20;     %viewing angle of the Beacon
   
    BTHETA = 0;     %Initial Beacon swivel(degrees) Horizontal 0 is due EAST
    BPHI = 0;     %initial Beacon tilt(degrees) 0 is FLAT
    SIMTIME = 30;       %period of time simulated(seconds)
    SIMSTEP = 0.1;      %subdivision of whole seconds

    %Calculated Globals/innvariant parameters
    PI = 3.14159;       %pi used forcalculation
    vx = V*sin(2*PI/360*H);     %Velocity in X of the Plane (ft/s)
    vy = V*cos(2*pi/360*H);     %Velocity in Y of the Plane (ft/s)
    
    Plane = zeros(SIMTIME/SIMSTEP,3); %matrix with plane positions
    %Plane(1,:) = [X0, Y0, Z0];
    Beacon = zeros(SIMTIME/SIMSTEP,2);
    %Beacon = [BTHETA, BPHI];  
    t = zeros(SIMTIME/SIMSTEP,1);
%%end globals
%%
%Time series calculation for plane position, beacon sweep (horizontal and
%vertical

for n = 1:(SIMTIME/SIMSTEP)
time = (n-1)*SIMSTEP;   %the time(s) of the snapshot, increments of SIMSTEP

Plane(n,:)= position(X0,Y0,Z0,vx,vy,VZ,time);   %plane positions f(t)

Beacon(n,:) = sweep(BTHETA,BPHI,BROT,BTILT,BTILTOFF,BDEGPHI,time);   %beacon illum.f(t) 

t(n,:) = time;    %each time step



end

plot(Beacon);

Resulting = comparator(BVIEW,BROT,Beacon,Plane,H,t,0)

