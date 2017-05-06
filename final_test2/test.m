% 3-D RECONSTRUCTION FROM AN UNCALIBRATED SENSOR
% SIMULATION : PROJECTIVE RECONSTRUCTION + EUCLIDEAN CONSTRAINTS
% simproj.m
clear all;close all;
VAR=0;
global e1 e2 e3 e4 e5 Uc Vc Up Vp Nb_Points V PP;
format long;
% CAMERA MODEL 1 (translation T1, rotation R1 with respect to O)
au1=85;av1=90;uo1=130;vo1=135;
A1=[au1 0 uo1 0;0 av1 vo1 0;0 0 1 0];
a=0;b=0;c=0;
tx=0;ty=0;tz=0;
Rx=[1 0 0;0 cos(a) -sin(a);0 sin(a) cos(a)];
Ry=[cos(b) 0 sin(b);0 1 0;-sin(b) 0 cos(b)];
Rz=[cos(c) -sin(c) 0;sin(c) cos(c) 0;0 0 1];
R1=Rz*Ry*Rx;
T1=[tx;ty;tz];
RT1=[R1 T1;0 0 0 1];
ART1=A1*RT1;
% CAMERA MODEL 2 (translation T2, rotation R2 with respect to O)
au2=85;av2=90;uo2=130;vo2=135;
a=0.1;b=0.7;c=0.2;
tx=1000;ty=-400;tz=230;
Rx=[1 0 0;0 cos(a) -sin(a);0 sin(a) cos(a)];
Ry=[cos(b) 0 sin(b);0 1 0;-sin(b) 0 cos(b)];
Rz=[cos(c) -sin(c) 0;sin(c) cos(c) 0;0 0 1];
R2=Rz*Ry*Rx;
T2=[tx;ty;tz];
RT2=[R2 T2;0 0 0 1];
A2=[au2 0 uo2 0;0 av2 vo2 0;0 0 1 0];
ART2=A2*RT2;
VAR=input('Variance du bruit sur la base : ');
% 3-D POINTS
V(:,1) = [115;-400;2000;1];
V(:,20) = [300;-431;3000;1];
V(:,11) = [500;-400;4020;1];
V(:,4) = [733;-400;2000;1];

V(:,5) = [900;-395;3000;1];
V(:,6) = [100;-50;4000;1];
V(:,7) = [300;-50;2000;1];
V(:,8) = [500;-50;3000;1];
V(:,9) = [700;-50;4000;1];
V(:,10) = [900;-50;2000;1];
V(:,3) = [100;50;3000;1];
V(:,12) = [300;50;4000;1];
V(:,13) = [500;50;2000;1];
V(:,14) = [700;50;3000;1];
V(:,15) = [900;50;4000;1];
V(:,16) = [100;400;2000;1];
V(:,17) = [300;400;3000;1];
V(:,18) = [500;400;4000;1];
V(:,19) = [700;400;2000;1];
V(:,2) = [900;400;3000;1];
V(:,21) = [450;75;2500;1];
V(:,22) = [375;25;2100;1];
V(:,23) = [450;30;1400;1];
V(:,24) = [300;-40;3200;1];
V(:,25) = [350;75;2000;1];
V(:,26) = [550;75;2300;1];
V(:,27) = [395;250;2100;1];
V(:,28) = [150;300;1000;1];
V(:,29) = [100;-80;2200;1];
V(:,30) = [450;175;1000;1];
V(:,31) = [345;-75;1500;1];
V(:,32) = [275;125;2350;1];
V(:,33) = [150;-30;1700;1];
V(:,34) = [600;-100;2000;1];
V(:,35) = [280;-50;1830;1];
V(:,36) = [145;-175;1700;1];
V(:,37) = [420;185;2400;1];
V(:,38) = [550;-70;1600;1];
V(:,39) = [705;-120;1000;1];
V(:,40) = [380;-70;700;1];
Nb_Points=40;
% PROJECTION ONTO THE IMAGE PLANES
for i=1:Nb_Points,
P1(:,i) = ART1*V(:,i);
Uc(i) = P1(1,i)/P1(3,i);
Vc(i) = P1(2,i)/P1(3,i);
P2(:,i) = ART2*V(:,i);
Up(i) = P2(1,i)/P2(3,i);
Vp(i) = P2(2,i)/P2(3,i);
end

VAR=input('Variance du bruit sur les mesures : ');
Uc=Uc+VAR*(rand(Nb_Points,1))'-VAR/2;
Vc=Vc+VAR*(rand(Nb_Points,1))'-VAR/2;
Up=Up+VAR*(rand(Nb_Points,1))'-VAR/2;
Vp=Vp+VAR*(rand(Nb_Points,1))'-VAR/2;

for i=1:Nb_Points-5,
 cx(i)=0.5;
 cy(i)=0.5;
 cz(i)=0.5;
 ct(i)=1;
end
% INITIALISATION OF REFERENCE POINTS
e1=[1;0;0;1];
e2=[0;1;0;1];
e3=[0;0;1;1];
e4=[0;0;0;1];
e5=[1;1;1;1];
% INITIALISATION OF PROJECTION MATRICES
M1c=[0.1 0.1 0.1 20];
M2c=[0.1 0.1 0.1 20];
M3c=[0.1 0.1 0.1 1];
M1p=[0.1 0.1 0.1 20];
M2p=[0.1 0.1 0.1 20];
M3p=[0.1 0.1 0.1 1];
% OPTIONS FOR OPTIMISATION

X0=[M1c,M2c,M3c,M1p,M2p,M3p,cx,cy,cz,ct];

options = optimoptions('lsqnonlin','Algorithm','levenberg-marquardt','TolX',0.0000001,'TolFun',0.0000001);
[X,W] = lsqnonlin(@proj3D, X0,[],[],options)


%disp(sprintf('Valeur finale : %g',OPTIONS(8)));
% ERROR ON IMAGE POINTS
N=Nb_Points-5;
PP=[X(25:25+N-1);X(25+N:25+2*N-1);X(25+2*N:25+3*N-1);X(25+3*N:25+4*N-1)];
Mc=[X(1:4);X(5:8);X(9:12)];
Mp=[X(13:16);X(17:20);X(21:24)];
Ac=Mc*PP;
Ac(1,:)=Ac(1,:)./Ac(3,:);
Ac(2,:)=Ac(2,:)./Ac(3,:);
Ac(3,:)=Ac(3,:)./Ac(3,:);
Ap=Mp*PP;
Ap(1,:)=Ap(1,:)./Ap(3,:);
Ap(2,:)=Ap(2,:)./Ap(3,:);
Ap(3,:)=Ap(3,:)./Ap(3,:);
Erreur_cam=[Uc(6:Nb_Points);Vc(6:Nb_Points);ones(1,Nb_Points-5)]-Ac;
Erreur_proj=[Up(6:Nb_Points);Vp(6:Nb_Points);ones(1,Nb_Points-5)]-Ap;
Erreur_moy=mean(mean(Erreur_proj+Erreur_cam))
figure(1)
plot(Uc(6:Nb_Points),Vc(6:Nb_Points),'ro',Ac(1,:),Ac(2,:),'g+')
figure(2)
plot(Up(6:Nb_Points),Vp(6:Nb_Points),'ro',Ap(1,:),Ap(2,:),'g+')
PP(1,:)=PP(1,:)./PP(4,:);
PP(2,:)=PP(2,:)./PP(4,:);
PP(3,:)=PP(3,:)./PP(4,:);
PP(4,:)=PP(4,:)./PP(4,:);

w0=[1 0 0 0 0 1 0 0 0 0 1 0 0 0 0 1];

options = optimoptions('lsqnonlin','Algorithm','levenberg-marquardt' ,'TolX',0.00001,'TolFun',0.00001);
[w] = lsqnonlin(@fcont2, w0,[],[],options)
%disp(sprintf('Valeur finale : %g',OPTIONS(8)));
W=[w(1:4);w(5:8);w(9:12);w(13:16)];
P3D=W*PP;
P3D(1,:)=P3D(1,:)./P3D(4,:);
P3D(2,:)=P3D(2,:)./P3D(4,:);
P3D(3,:)=P3D(3,:)./P3D(4,:);
P3D(4,:)=P3D(4,:)./P3D(4,:);
figure(3)
plot3(P3D(1,:),P3D(2,:),P3D(3,:),'b+',V(1,6:Nb_Points),V(2,6:Nb_Points),V(3,6:Nb_Points),'ro');
Erreur_Points=P3D-V(:,6:Nb_Points)
