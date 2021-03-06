
clear all; close all;
global e1 e2 e3 e4 e5 Uc Vc Up Vp Nb_Points;
format long;
VAR=0;
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
% VECTORS OF 3-D POINTS
V(:,1) = [1000;500;500;1];
V(:,2) = [500;1000;500;1];
V(:,3) = [500;500;1000;1];
V(:,4) = [500;500;500;1];
V(:,5) = [1000;1000;1000;1];
scatter3(V(1,:), V(2,:), V(3,:),'r')

V(:,20) = [300;-431;3000;1];
V(:,11) = [500;-400;4020;1];
V(:,6) = [100;-50;4000;1];
V(:,7) = [300;-50;2000;1];
V(:,8) = [500;-50;3000;1];
V(:,9) = [700;-50;4000;1];
V(:,10) = [900;-50;2000;1];
V(:,12) = [300;50;4000;1];
V(:,13) = [500;50;2000;1];
V(:,14) = [700;50;3000;1];
V(:,15) = [900;50;4000;1];
V(:,16) = [100;400;2000;1];
V(:,17) = [500;400;3000;1];
V(:,18) = [500;400;4000;1];
V(:,19) = [700;400;2000;1];
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

for i=1:Nb_Points,
P1(:,i) = ART1*V(:,i);
Uc(i) = P1(1,i)/P1(3,i);
Vc(i) = P1(2,i)/P1(3,i);
P2(:,i) = ART2*V(:,i);
Up(i) = P2(1,i)/P2(3,i);
Vp(i) = P2(2,i)/P2(3,i);
end

for i=1:Nb_Points-5,
 cx(i)=mean(V(1,:));
 cy(i)=mean(V(2,:));
 cz(i)=mean(V(3,:));
end

e1=V(1:4,1);
e2=V(1:4,2);
e3=V(1:4,3);
e4=V(1:4,4);
e5=V(1:4,5);

M1c=[85 0 130 0];%+[5 0 -4 0];
M2c=[0 90 135 0];%+[0 -3 5 0];
M3c=[0 0 1 0];
M1p=[85 0 130 0];%+[4 -3 1 5];
M2p=[0 90 135 0];%+[-6 1 4 -2];
M3p=[0 0 1 0];%+[1 2 -1 0];

X0=[M1c,M2c,M3c,M1p,M2p,M3p,cx,cy,cz];

options = optimoptions('lsqnonlin','Algorithm','levenberg-marquardt' ,'TolX',0.00000000001,'TolFun',0.00000000001);
[X,W] = lsqnonlin(@project, X0,[],[],options)
X
P3D=[X(24+1:24+Nb_Points-5);X(24+Nb_Points-5+1:24+2*(Nb_Points-5));X(24+2*(Nb_Points-5)+1:24+3*(Nb_Points-5))];
Erreur_Points=P3D-V(1:3,6:Nb_Points)
Erreur_max=max(max(abs(Erreur_Points)))
Erreur_moy=mean(mean(abs(Erreur_Points)))

M1c=X(1:4);
M2c=X(5:8);
M3c=X(9:12);
Mc=[M1c;M2c;M3c];
Erreur_cam=Mc-ART1

M1p=X(13:16);
M2p=X(17:20);
M3p=X(21:24);
Mp=[M1p;M2p;M3p];
Erreur_proj=Mp-ART2

for i=1:5,
P=[Mc(1,1)-Mc(3,1)*Uc(i),Mc(1,2)-Mc(3,2)*Uc(i),Mc(1,3)-Mc(3,3)*Uc(i);
 Mc(2,1)-Mc(3,1)*Vc(i),Mc(2,2)-Mc(3,2)*Vc(i),Mc(2,3)-Mc(3,3)*Vc(i);
 Mp(1,1)-Mp(3,1)*Up(i),Mp(1,2)-Mp(3,2)*Up(i),Mp(1,3)-Mp(3,3)*Up(i);
 Mp(2,1)-Mp(3,1)*Vp(i),Mp(2,2)-Mp(3,2)*Vp(i),Mp(2,3)-Mp(3,3)*Vp(i)];
F=[Mc(3,4)*Uc(i)-Mc(1,4);
 Mc(3,4)*Vc(i)-Mc(2,4);
 Mp(3,4)*Up(i)-Mp(1,4);
 Mp(3,4)*Vp(i)-Mp(2,4)];
N=inv(P'*P)*P'*F;
Erreur_Ref=N-V(1:3,i)
end
plot3(V(1,6:Nb_Points),V(2,6:Nb_Points),V(3,6:Nb_Points),'ro',P3D(1,:),P3D(2,:),P3D(3,:),'y*',V(1,1:5),V(2,1:5),V(3,1:5),'g+')
