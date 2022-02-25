%calculate the sweep of the beacon illumination


function [ s ] = sweep(BTHETA, BPHI, BROT,BTILT,BTILTOFF,BDEGPHI, t )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

    degTheta = 360; %full rotation amount(degrees)
    degPhi = deg2rad(BDEGPHI); %maximum additional upward tilt of beacon
    
    startTheta = deg2rad(BTHETA);
    startPhi = deg2rad(BPHI);

    
    %% use timer and mod to create functions that move linearly from start to 
    %finish once every period, rotation or elevation, respectively

    theta = 2*2*pi()/BROT * (abs(mod(t-BROT/2,BROT)-BROT/2)-BROT/4) + pi();
    phi = 2 * degPhi/BTILT * (abs(mod(t-BTILT/2,BTILT)-BTILT/2)-BTILT/4) + degPhi/2+deg2rad(BTILTOFF);
    %     rTimer = mod(t,BROT);
%     rotAngleRate = 2*pi()/(0.5*BROT);
%     if (rTimer <= BROT/2)
%         theta = rotAngleRate*rTimer;
%     else
%         theta = 2*pi() - (rTimer-BROT/2)*rotAngleRate;
%     end
%         
%     eTimer = mod(t,BTILT);
%     elevAngleRate = deg2rad(BTILTOFF+BDEGPHI)/(0.5*BTILT);
%     if (eTimer <= BTILT/2)
%         phi = elevAngleRate*eTimer;
%     else
%         phi = deg2rad(BTILTOFF) - (eTimer-BTILT/2)*elevAngleRate;
%     end
%     theta = startTheta + deg2rad(degTheta) * abs(sin(3.14159/BROT*t));    %center illumination angle
%     phi = startPhi + deg2rad(degPhi) * abs(sin(3.14159/BTILT*t))+deg2rad(BTILTOFF); %returns in radians
    
    
%     might be unneeded due to switch to polar
%     phi1 = phi-BVIEW;   %lagging illumination edge
%     phi2 = phi+BVIEW;   %leading illumination edge
%     theta1 = theta-BVIEW;          %currently not built to tilt
%     theta2 = theta+BVIEW;
%     %%%%/
    s = [theta phi];    %lag, lead, tilt "top", tilt "bottom"
end

