function[ConvertedLatLongs] = latLong2BeaconCentered(Lat,Long, Altitude, ...
    BeaconLat,BeaconLong,BeaconAlt,CONVERSIONTYPE)
%%latLong2CartFixed references a coordinate in the cartesian frame centered
%%at the beacon for use in the comparison of plane location to beacon
%%direction. Use CONVERSIONTYPE to indicate UTM conversion or ellipsoidal
%%approach.
%%inputs can be vectors of each coordinate

if(CONVERSIONTYPE==0)
    %Ellipsoidal approach to conversion
    dLat = deg2rad(Lat) - deg2rad(BeaconLat);
    dLong = deg2rad(Long)-deg2rad(BeaconLong);
    lat = deg2rad(BeaconLat);
    h=BeaconAlt;
   
    %convention of the function is dx is north,whereas this model has dx as east
    [dy,dx]=dg2lg(dLat,dLong,lat,h); 
end

if (CONVERSIONTYPE == 1)
    %UTM option for conversion
    [yUTM,xUTM,~,~] = ell2utm(deg2rad(BeaconLat),deg2rad(BeaconLong));
    [dyN,dxE,~,~] = ell2utm(deg2rad(Lat),deg2rad(Long));
    dyN = dyN - yUTM;
    dxE = dxE - xUTM;
    dx = dxE;
    dy = dyN;
end

ConvertedLatLongs=[dx,dy,Altitude];

