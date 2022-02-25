function [ planePosition ] = position( X0,Y0,Z0,VX,VY,VZ, T )
%position - calculates and returns as a 1x3 matrix the plane location
%   Calculates XYZ coordinates of the plane at time T, assuming constant
%   velocity

    xt = X0+VX*T;
    yt = Y0+VY*T;
    zt = Z0+VZ*T;
    
    planePosition = [xt, yt, zt];
end

