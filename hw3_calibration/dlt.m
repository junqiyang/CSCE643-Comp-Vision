function [P] = dlt(xy, xyz, N)
    for i = 1:N
        A(2*i-1, :) = [0, 0, 0, 0, -xyz(i,1), -xyz(i,2), -xyz(i,3), -1, xy(i,2)*xyz(i,1), xy(i,2)*xyz(i,2), xy(i,2)*xyz(i,3), xy(i,2)];
        A(2*i, :) =   [xyz(i,1), xyz(i,2), xyz(i,3), 1, 0, 0, 0, 0, -xy(i,1)*xyz(i,1), -xy(i,1)*xyz(i,2), -xy(i,1)*xyz(i,3), -xy(i,1)];
    end
    [U, D, V] = svd(A);
    P = V(:,end);
end
%computes DLT, xy and XYZ should be normalized before calling this function

