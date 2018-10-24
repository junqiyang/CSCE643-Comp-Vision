clear all; close all;

global e1 e2 e3 e4 e5 U1 V1 U2 V2 n V;

[P1, P2, V] = simulator();
%U1 = [326 324 580 195 422 428 514 433 526 440 538 264 270 225 219 369 461 398 315 623]
%V1 = [528 185 428 374 87 397 369 289 267 170 154 274 375 332 237 141 128 109 119 141]
%U2 = [373 368 559 268 445 445 509 448 517 451 528 325 331 292 286 401 476 425 357 596]
%V2 = [543 380 442 390 154 461 428 406 373 342 309 383 441 387 334 287 258 214 240 278]
%n = 20

V(:,1) = [1100;500;500;1];
V(:,2) = [500;1100;500;1];
V(:,3) = [500;500;1100;1];
V(:,4) = [500;500;500;1];
V(:,5) = [1100;1100;1100;1];


for i=1:n-5,
 cx(i)=0.5;
 cy(i)=0.5;
 cz(i)=0.5;
 ct(i)=1;
end


e1=[1;0;0;1];
e2=[0;1;0;1];
e3=[0;0;1;1];
e4=[0;0;0;1];
e5=[1;1;1;1];

P1_1=[0.1 0.1 0.1 20];
P1_2=[0.1 0.1 0.1 20];
P1_3=[0.1 0.1 0.1 1];
P2_1=[0.1 0.1 0.1 20];
P2_2=[0.1 0.1 0.1 20];
P2_3=[0.1 0.1 0.1 1];

X0=[P1_1,P1_2,P1_3,P2_1,P2_2,P2_3,cx,cy,cz,ct];
options = optimoptions('lsqnonlin','Algorithm','levenberg-marquardt' ,'TolX',0.00000000001,'TolFun',0.00000000001);
[X,W] = lsqnonlin(@cost2, X0,[],[],options);

P1_estimate = [X(1:4);X(5:8);X(9:12)];
P2_estimate = [X(13:16);X(17:20);X(21:24)];
N = n - 5;
c_3d_p = [X(25:25+N-1);X(25+N:25+2*N-1);X(25+2*N:25+3*N-1);X(25+3*N:25+4*N-1)];


h=[0.5 0.1 0.1 0.1 0.1 0.5 0.1 0.1 0.1 0.1 0.5 0.1 0.1 0.1 0.1 0.5];

options = optimoptions('lsqnonlin','Algorithm','levenberg-marquardt' ,'TolX',0.00000000001,'TolFun',0.00000000001);
h = lsqnonlin(@find_H, h,[],[],options);

H=[h(1:4);h(5:8);h(9:12);h(13:16)]

P_error1 = P1_estimate - P1;
P_error2 = P2_estimate - P2;

c_3d=H * c_3d_p;
c_3d(1,:)=c_3d(1,:)./c_3d(4,:);
c_3d(2,:)=c_3d(2,:)./c_3d(4,:);
c_3d(3,:)=c_3d(3,:)./c_3d(4,:);
c_3d(4,:)=c_3d(4,:)./c_3d(4,:);


figure(1)
plot3(c_3d(1,:),c_3d(2,:),c_3d(3,:),'b*',V(1,1:5),V(2,1:5),V(3,1:5),'g+')
axis off