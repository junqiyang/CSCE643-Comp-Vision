clear all; close all;

global e1 e2 e3 e4 e5 U1 V1 U2 V2 n;
%e1 to e5 is the ground truth for reference point


[P1, P2, V] = simulator();

for i=1:n-5,
 cx(i)=mean(V(1,1:5));
 cy(i)=mean(V(2,1:5));
 cz(i)=mean(V(3,1:5));
end

e1=V(1:4,1);%add ground truth to the reference points
e2=V(1:4,2);
e3=V(1:4,3);
e4=V(1:4,4);
e5=V(1:4,5);

P1_1=[0.1 0.1 0.1 20];
P1_2=[0.1 0.1 0.1 20];
P1_3=[0.1 0.1 0.1 1];
P2_1=[0.1 0.1 0.1 20];
P2_2=[0.1 0.1 0.1 20];
P2_3=[0.1 0.1 0.1 1];

X0=[P1_1,P1_2,P1_3,P2_1,P2_2,P2_3,cx,cy,cz];
options = optimoptions('lsqnonlin','Algorithm','levenberg-marquardt' ,'TolX',0.00000000001,'TolFun',0.00000000001);
[X,W] = lsqnonlin(@cost1, X0,[],[],options);

P1_estimate = [X(1:4);X(5:8);X(9:12)];
P2_estimate = [X(13:16);X(17:20);X(21:24)];
c_3d = [X(24+1:24+n-5);X(24+n-5+1:24+2*(n-5));X(24+2*(n-5)+1:24+3*(n-5))]

Point_error = c_3d-V(1:3,6:n)
P_error1 = P1_estimate - P1
P_error2 = P2_estimate - P2

figure(1)
plot3(V(1,6:n),V(2,6:n),V(3,6:n),'ro',c_3d(1,:),c_3d(2,:),c_3d(3,:),'b*',V(1,1:5),V(2,1:5),V(3,1:5),'g+')
axis off
