function [] = gold_standard_algrithm()
    fid = fopen('point.txt');
    a = fscanf(fid,'%g %g %g %g',[4 inf])
    fclose(fid);
    fid = fopen('h.txt');
    h = fscanf(fid,'%g %g %g',[9 inf]);
    fclose(fid);
    h=h';
    n=20;
    H0=[ h(1,:) ]

    x1= a(1,:)
    y1= a(2,:)
    x2= a(3,:)
    y2= a(4,:)
    
    [homogr,resnorm] = lsqnonlin(@sampson_error,H0)
    se = sampson_error(homogr)

    function S = sampson_error( homogr )
        A = zeros(2*n,9);
        for i = 1:n
            A(2*i-1,:) =  [0 0 0   -x1(i) -y1(i)  -1   (y2(i)* x1(i))   (y1(i)*y2(i))   y2(i)  ]; 
            A(2*i,:) = [ x1(i) y1(i) 1    0 0 0       (-x2(i)* x1(i)) (-x2(i)*y1(i))  -x2(i)  ];
        end;
        e=A * homogr';
        J = jacob(homogr,x1,y1,x2,y2);
        for k=1:n
            J_ = [J(k,1:4)'  J(k,5:8)' ]';
            E_ = [ e(2*k-1,1)  e(2*k,1)];
            S  = sqrt(E_*inv(J_*J_')*E_');
        end;
    end

    function J = jacob(h, x1, x2, y1, y2)
        for i=1:n
            A = (-1)*h(1,4) + h(1,7)*y1(i); 
            B = (-1)*h(1,5) + h(1,8)*y2(i);
            C = 0;
            D = h(1,7)*x1(i) + h(1,8)*y1(i) + h(1,9);
            E = h(1,1) - h(1,7)*x1(i);
            F = h(1,2) - h(1,8)*x2(i);
            G = (-1)*h(1,7)*x1(i) - h(1,8)*y1(i) - h(1,9);
            H = 0;
   
            M = [A B C D];
            N = [E F G H];
            O = [ M N ];
            J(i,:,:) = O';
        end;
    end



















end
