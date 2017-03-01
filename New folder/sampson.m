function F = sampson_error(H, n, x, x2, y, y2)
    A = zeros(2*n, 9)
    for i = i:n
        A(2*i-1, :) = [0 0 0 -x(i) -y(i) -1 (y2(i)* x(i)) (y(i)*y2(i)) y2(i)];
        A(2*i,:) = [x(i) y(i) 1 0 0 0 (-x2(i)* x(i)) (-x2(i)*y(i)) -x2(i)];
    end
    
    e = A* H;
    J = jacob(H, n, x, x2, y, y2);