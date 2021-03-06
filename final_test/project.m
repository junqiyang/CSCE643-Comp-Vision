function [F] = project(x)
    global e1 e2 e3 e4 e5 Uc Vc Up Vp Nb_Points;
N=Nb_Points-5;
M1c=x(1:4);
M2c=x(5:8);
M3c=x(9:12);
M1p=x(13:16);
M2p=x(17:20);
M3p=x(21:24);
P(1,:)=x(25:25+N-1);
P(2,:)=x(25+N:25+2*N-1);
P(3,:)=x(25+2*N:25+3*N-1);
P(4,:)=ones(1,N);
m1cp=M1c*P;
m2cp=M2c*P;
m3cp=M3c*P;
m1pp=M1p*P;
m2pp=M2p*P;
m3pp=M3p*P;
B1=[Uc(1)-((M3c*e1)\(M1c*e1)),Vc(1)-((M3c*e1)\(M2c*e1)),Up(1)-((M3p*e1)\(M1p*e1)),Vp(1)-((M3p*e1)\(M2p*e1))];
B2=[Uc(2)-((M3c*e2)\(M1c*e2)),Vc(2)-((M3c*e2)\(M2c*e2)),Up(2)-((M3p*e2)\(M1p*e2)),Vp(2)-((M3p*e2)\(M2p*e2))];
B3=[Uc(3)-((M3c*e3)\(M1c*e3)),Vc(3)-((M3c*e3)\(M2c*e3)),Up(3)-((M3p*e3)\(M1p*e3)),Vp(3)-((M3p*e3)\(M2p*e3))];
B4=[Uc(4)-((M3c*e4)\(M1c*e4)),Vc(4)-((M3c*e4)\(M2c*e4)),Up(4)-((M3p*e4)\(M1p*e4)),Vp(4)-((M3p*e4)\(M2p*e4))];
B5=[Uc(5)-((M3c*e5)\(M1c*e5)),Vc(5)-((M3c*e5)\(M2c*e5)),Up(5)-((M3p*e5)\(M1p*e5)),Vp(5)-((M3p*e5)\(M2p*e5))];

Sc1=Uc(6:Nb_Points)-((m3cp).\(m1cp));
Sc2=Vc(6:Nb_Points)-((m3cp).\(m2cp));
Sp1=Up(6:Nb_Points)-((m3pp).\(m1pp));
Sp2=Vp(6:Nb_Points)-((m3pp).\(m2pp));

F=[B1,B2,B3,B4,B5,Sc1,Sc2,Sp1,Sp2,M1c(2),M3c(3)-1,M3p(4)-230];

end
