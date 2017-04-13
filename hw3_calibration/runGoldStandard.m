function [K, R, t, error] = runGoldStandard(xy, xyz)

xy =  [117,324;  178,161;   256,109;  234,251;  281,224;  336,301; 375,223;  396,164;  419,348;  475,225];
xyz = [190,0,77; 142,0,197; 70,0,245; 94,0,125; 46,0,149; 0,23,77; 0,71,149; 0,95,196; 0,119,53; 0,167,149];
N = 10;
[xy_normalized, XYZ_normalized, T, U] = normalization(xy, xyz, N)
%normalize data points
%compute DLT
[P_normalized] = dlt(xy_normalized, XYZ_normalized, N)
options.Algorithm = 'levenberg-marquardt';
[p,r] = lsqcurvefit(@fminGoldStandard,P_normalized,xyz,xy,[],[],options);
r
p
P_f = [p(1), p(2), p(3), p(4);
       p(5), p(6), p(7), p(8);
       p(9), p(10), p(11), p(12)];

de_P = T^-1*P_f*U


M = [de_P(1,1), de_P(1,2), de_P(1,3);
     de_P(2,1), de_P(2,2), de_P(2,3);
     de_P(3,1), de_P(3,2), de_P(3,3)];
[Q, R] = qr(inv(M));
K = inv(R);

ttp = [70;0;245;1];

tmqqp = de_P*ttp
tmqqp(1)/tmqqp(3)
tmqqp(2)/tmqqp(3)



function f = fminGoldStandard(p,xyz)
    P = [p(1), p(2), p(3), p(4);
         p(5), p(6), p(7), p(8);
         p(9), p(10), p(11), p(12)];
    f =zeros(N,2);
    for i = 1:N
        xyz_tmp = [xyz(i,1);xyz(i,2);xyz(i,3);1];
        tmp = P * xyz_tmp;
        f(i,1) = tmp(1)/tmp(3);
        f(i,2) = tmp(2)/tmp(3);
    end    
end
    
%denormalize camera matrix

%factorize camera matrix in to K, R and t

%compute reprojection error

end