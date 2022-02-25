%BeaconGen     the Fieldworker-Aerial Awareness Beacon model The purpose of
%this script is to show model the ability of an Aerial Applicator to see an
%alert beacon showing the location of a fieldworker or crew. Maximizing
%awareness of ground-based workers can help to mitigate unwanted human
%exposure to agrochemical products.

%Assumptions:
    %No ability to see behind(for now), only the approach matters(can't see
        %behind themselves anyway...
    %continuous light emitted from beacon (will add flash soon)
    
clear
%%
%read the flight log information (note different file paths for computer)
filename = 'C:\Users\way\Google Drive\ME Project - Beaconator\Modelling\
logs&video Recording\October 1st Trials\zipline\ziplineBook.xlsx';
foreflight = xlsread(filename);

%%run notes for 8/23(constant elevation angle):
%BROT = 10 seconds; BTILT=.8seconds; BDEGOFF=25; BDEGTILT=0 BEACONLAT =
%38.538894;    BEACONLONG =  -121.773381;    BEACONALT = 20;

%Global parameters
    %inputs/variable parameters
    BROT = 10;          %Time(s) for 1 rotation of the beacon
    BTILT = .8;        %time(s) for 1 tilt cycle(up and down)
    BTILTOFF = 25;      %minimum tilt(degrees) of the beacon 
    BDEGPHI = 0;   %max additional upward tilt
    BX0 = 0; BY0 = 0; BZ0 = 0;    %Beacon coordinate 0,0,0
    BVIEW = 50;     %viewing angle of the Beacon
   
    BTHETA = 0;     %Initial Beacon swivel(degrees) Horizontal 0 is due EAST
    BPHI = 0;     %initial Beacon tilt(degrees) 0 is FLAT
    
    SIMSTEP = .001;      %subdivision of whole seconds .001=1millisecond
    SIMTIME = SIMSTEP*foreflight(size(foreflight,1),1);       %period of time simulated(seconds)
    
    BEACONLAT =  38.955480;  %beacon latitude
    BEACONLONG =  -122.070194;  %beacon longitude
    BEACONALT = 20; %beacon altitude (meters)
    
    Plane = zeros(size(foreflight,1),3); %matrix with plane positions
    Beacon = zeros(size(foreflight,1),2);  
    t = zeros(size(foreflight,1),1);
%%end globals
%%
%Time series calculation for plane position, beacon sweep (horizontal and
%vertical

for n = 1:(size(foreflight,1))
    time = SIMSTEP*foreflight(n,1);   %the time(s) of the snapshot, increments of SIMSTEP

    Plane(n,:)= latLong2BeaconCentered(foreflight(n,2),foreflight(n,3),foreflight(n,4),...
                BEACONLAT,BEACONLONG,BEACONALT,1);

    Beacon(n,:) = sweep(BTHETA,BPHI,BROT,BTILT,BTILTOFF,BDEGPHI,time);   %beacon illum.f(t) 

    t(n,:) = time;    %each time step

end

% Optional plotting animation
%plot3(Plane(:,1), Plane(:,2), Plane(:,3),'d');
% plot(Beacon(:,1),Beacon(:,2),Beacon(:,1),Beacon(:,3));
	
% Resulting Data output for matches 
Resulting(:,2) = comparator(BVIEW,BROT,Beacon,Plane,foreflight(:,5),foreflight(:,1),1);
Resulting(:,1) = t;
