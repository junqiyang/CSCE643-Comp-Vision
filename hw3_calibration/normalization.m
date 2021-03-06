function [xyn, xyzn, T, U] = normalization(xy, xyz, N)

%data normalization
%first compute centroid
xy_centroid = mean(xy);
xyz_centroid = mean(xyz);

%then, compute scale
xy_sum = 0;
xyz_sum = 0;
for i = 1:N
    xy_sum = xy_sum + sqrt((xy(i,1) - xy_centroid(1))^2 + (xy(i,2) - xy_centroid(2))^2);
    xyz_sum = xyz_sum + sqrt((xyz(i,1) - xyz_centroid(1))^2 + (xyz(i,2) - xyz_centroid(2))^2 + (xyz(i,3) - xyz_centroid(3))^2);
end


xy_s = sqrt(2.0)/ (xy_sum/N);
xyz_s = sqrt(3.0)/ (xyz_sum/N);
xy_tx = - xy_s * xy_centroid(1);
xy_ty = - xy_s * xy_centroid(2);

xyz_tx = - xyz_s * xyz_centroid(1);
xyz_ty = - xyz_s * xyz_centroid(2);
xyz_tz = - xyz_s * xyz_centroid(3);


%create T and U transformation matrices
T = [xy_s, 0, xy_tx; 
     0, xy_s, xy_ty;
     0, 0, 1];
U = [xyz_s, 0, 0, xyz_tx;
     0, xyz_s, 0, xyz_ty;
     0, 0, xyz_s, xyz_tz;
     0, 0, 0, 1];

%and normalize the points according to the transformations
for i = 1:N
    xy_tmp = [xy(i,1); xy(i,2); 1.0];
    xy_tmp = T * xy_tmp;
    xyn(i,1) = xy_tmp(1)/xy_tmp(3);
    xyn(i,2) = xy_tmp(2)/xy_tmp(3);
    
    xyz_tmp = [xyz(i,1); xyz(i,2); xyz(i,3); 1.0];
    xyz_tmp = U * xyz_tmp;
    xyzn(i,1) = xyz_tmp(1)/xyz_tmp(4);
    xyzn(i,2) = xyz_tmp(2)/xyz_tmp(4);
    xyzn(i,3) = xyz_tmp(3)/xyz_tmp(4);
end

end