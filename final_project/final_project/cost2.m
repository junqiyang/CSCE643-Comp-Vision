function [F] = cost2(x)
    global e1 e2 e3 e4 e5 U1 V1 U2 V2 n;
    
    N=n-5;
    P1_1=x(1:4);
    P1_2=x(5:8);
    P1_3=x(9:12);
    P2_1=x(13:16);
    P2_2=x(17:20);
    P2_3=x(21:24);
    m(1,:)=x(25:25+N-1);
    m(2,:)=x(25+N:25+2*N-1);
    m(3,:)=x(25+2*N:25+3*N-1);
    m(4,:)=x(25+3*N:25+4*N-1);
    P1_1m=P1_1*m;
    P1_2m=P1_2*m;
    P1_3m=P1_3*m;
    P2_1m=P2_1*m;
    P2_2m=P2_2*m;
    P2_3m=P2_3*m;
    R1=[U1(1)-((P1_3*e1)\(P1_1*e1)), V1(1)-((P1_3*e1)\(P1_2*e1)), U2(1)-((P2_3*e1)\(P2_1*e1)), V2(1)-((P2_3*e1)\(P2_2*e1))]; % reference point
    R2=[U1(2)-((P1_3*e2)\(P1_1*e2)), V1(2)-((P1_3*e2)\(P1_2*e2)), U2(2)-((P2_3*e2)\(P2_1*e2)), V2(2)-((P2_3*e2)\(P2_2*e2))];
    R3=[U1(3)-((P1_3*e3)\(P1_1*e3)), V1(3)-((P1_3*e3)\(P1_2*e3)), U2(3)-((P2_3*e3)\(P2_1*e3)), V2(3)-((P2_3*e3)\(P2_2*e3))];
    R4=[U1(4)-((P1_3*e4)\(P1_1*e4)), V1(4)-((P1_3*e4)\(P1_2*e4)), U2(4)-((P2_3*e4)\(P2_1*e4)), V2(4)-((P2_3*e4)\(P2_2*e4))];
    R5=[U1(5)-((P1_3*e5)\(P1_1*e5)), V1(5)-((P1_3*e5)\(P1_2*e5)), U2(5)-((P2_3*e5)\(P2_1*e5)), V2(5)-((P2_3*e5)\(P2_2*e5))];

    error1=U1(6:n)-((P1_3m).\(P1_1m));
    error2=V1(6:n)-((P1_3m).\(P1_2m));
    error3=U2(6:n)-((P2_3m).\(P2_1m));
    error4=V2(6:n)-((P2_3m).\(P2_2m));

    error5=m(1,:).^2+m(2,:).^2+m(3,:).^2+m(4,:).^2-1;
    
    F=[R1,R2,R3,R4,R5,error1,error2,error3,error4,error5];
end