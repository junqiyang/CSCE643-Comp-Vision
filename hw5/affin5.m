close all; clear all; clc;

x1 = [	172,500;
     210,513; 263,530; 264,422; 264,412; 190,369; 191,345; 265,298; 265,288; 267,170;
	 333,143; 365,140; 447,151; 443,295; 442,309; 436,446; 436,459; 429,588; 524,386; 521,421;
	 527,621; 289,583; 317,619; 352,661; 319,714; 282,659; 245,625; 156,626; 54 ,636; 130,688;
	 233,755; 363,783; 441,735; 504,696; 122,579; 115,550; 8  ,702; 95 ,776; 449,646; 544,785;
     ];
x2 = [  29 ,531; 123,502; 230,470; 223,338; 222,327; 74 ,310; 72 ,273; 217,187; 216,175; 211,29 ;
	 299,17 ; 335,22 ; 405,50 ; 406,169; 406,180; 407,295; 408,305; 408,414; 461,229; 461,254;
	 464,397; 345,478; 430,467; 513,456; 598,464; 516,477; 551,487; 466,528; 510,578; 600,527;
	 670,485; 673,452; 608,436; 549,421; 324,561; 208,579; 662,575; 733,523; 408,414; 645,419; 
    ]   

F= [-1.769966826655486e-06, 5.831095730050382e-06, -0.001629505922811061;
 3.974267066678428e-06, 8.322182576621457e-07, 0.002892524449030241;
 0.0008638037204245528, -0.006566185689964552, 1]

P1 = [1,0,0,0;0,1,0,0;0,0,1,0];
e_2=null(F');
skew_e_2=[0,-e_2(3),e_2(2);e_2(3),0,-e_2(1);-e_2(2),e_2(1),0];
P2=[skew_e_2*F,e_2]

for i=1:40
A_X(1,:)=x1(i,1)*P1(3,:)-P1(1,:);
A_X(2,:)=x1(i,2)*P1(3,:)-P1(2,:);
A_X(3,:)=x2(i,1)*P2(3,:)-P2(1,:);
A_X(4,:)=x2(i,2)*P2(3,:)-P2(2,:);
[u2,s2,v2]=svd(A_X);
X(:,i)=v2(:,4)';
end

line1_1=cross([x1(3,:),1],[x1(18,:),1]);
line1_2=cross([x1(10,:),1],[x1(13,:),1]);
vanish1_1=cross(line1_1,line1_2);
vanish2_1=F*vanish1_1';
line2_1=cross([x2(3,:),1],[x2(18,:),1]);
vanish3_1=cross(vanish2_1,line2_1);

A(1,:)=vanish1_1(1)/vanish1_1(3)*P1(3,:)-P1(1,:);
A(2,:)=vanish1_1(2)/vanish1_1(3)*P1(3,:)-P1(2,:);
A(3,:)=vanish3_1(1)/vanish3_1(3)*P2(3,:)-P2(1,:);
A(4,:)=vanish3_1(2)/vanish3_1(3)*P2(3,:)-P2(2,:)

Space_vanish_point1=null(A) % 3D vanishing pt

line1_3=cross([x1(3,:),1],[x1(10,:),1]);
line1_4=cross([x1(18,:),1],[x1(13,:),1]);
vanish1_2=cross(line1_3,line1_4);
vanish2_2=F*vanish1_2';
line2_2=cross([x2(3,:),1],[x2(10,:),1]);
vanish3_2=cross(vanish2_2,line2_2);

A(1,:)=vanish1_2(1)/vanish1_2(3)*P1(3,:)-P1(1,:);
A(2,:)=vanish1_2(2)/vanish1_2(3)*P1(3,:)-P1(2,:);
A(3,:)=vanish3_2(1)/vanish3_2(3)*P2(3,:)-P2(1,:);
A(4,:)=vanish3_2(2)/vanish3_2(3)*P2(3,:)-P2(2,:);

Space_vanish_point2=null(A);

line1_5=cross([x1(9,:),1],[x1(13,:),1]);
line1_6=cross([x1(5,:),1],[x1(15,:),1]);
vanish1_3=cross(line1_5,line1_6);
vanish2_3=F*vanish1_3';
line2_3=cross([x2(9,:),1],[x2(13,:),1]);
vanish3_3=cross(vanish2_3,line2_3);

A(1,:)=vanish1_3(1)/vanish1_3(3)*P1(3,:)-P1(1,:);
A(2,:)=vanish1_3(2)/vanish1_3(3)*P1(3,:)-P1(2,:);
A(3,:)=vanish3_3(1)/vanish3_3(3)*P2(3,:)-P2(1,:);
A(4,:)=vanish3_3(2)/vanish3_3(3)*P2(3,:)-P2(2,:);

Space_vanish_point3=null(A);

infinity_plane=null([Space_vanish_point1';Space_vanish_point2';Space_vanish_point3']) 

H1=[1,0,0,0;0,1,0,0;0,0,1,0;infinity_plane']

X(:,1:21)=H1*X(:,1:21);

line1_1=cross([x1(22,:),1],[x1(28,:),1]);
line1_2=cross([x1(39,:),1],[x1(25,:),1]);
vanish1_1=cross(line1_1,line1_2);
vanish2_1=F*vanish1_1';
line2_1=cross([x2(22,:),1],[x2(28,:),1]);
vanish3_1=cross(vanish2_1,line2_1);

A(1,:)=vanish1_1(1)/vanish1_1(3)*P1(3,:)-P1(1,:);
A(2,:)=vanish1_1(2)/vanish1_1(3)*P1(3,:)-P1(2,:);
A(3,:)=vanish3_1(1)/vanish3_1(3)*P2(3,:)-P2(1,:);
A(4,:)=vanish3_1(2)/vanish3_1(3)*P2(3,:)-P2(2,:);

Space_vanish_point1=null(A); 

line1_3=cross([x1(22,:),1],[x1(39,:),1]);
line1_4=cross([x1(28,:),1],[x1(25,:),1]);
vanish1_2=cross(line1_3,line1_4);
vanish2_2=F*vanish1_2';
line2_2=cross([x2(22,:),1],[x2(39,:),1]);
vanish3_2=cross(vanish2_2,line2_2);

A(1,:)=vanish1_2(1)/vanish1_2(3)*P1(3,:)-P1(1,:);
A(2,:)=vanish1_2(2)/vanish1_2(3)*P1(3,:)-P1(2,:);
A(3,:)=vanish3_2(1)/vanish3_2(3)*P2(3,:)-P2(1,:);
A(4,:)=vanish3_2(2)/vanish3_2(3)*P2(3,:)-P2(2,:);

Space_vanish_point2=null(A);
line1_5=cross([x1(23,:),1],[x1(24,:),1]);
line1_6=cross([x1(26,:),1],[x1(25,:),1]);
vanish1_3=cross(line1_5,line1_6);
vanish2_3=F*vanish1_3';
line2_3=cross([x2(23,:),1],[x2(24,:),1]);
vanish3_3=cross(vanish2_3,line2_3);
A(1,:)=vanish1_3(1)/vanish1_3(3)*P1(3,:)-P1(1,:);
A(2,:)=vanish1_3(2)/vanish1_3(3)*P1(3,:)-P1(2,:);
A(3,:)=vanish3_3(1)/vanish3_3(3)*P2(3,:)-P2(1,:);
A(4,:)=vanish3_3(2)/vanish3_3(3)*P2(3,:)-P2(2,:);
Space_vanish_point3=null(A);
infinity_plane=null([Space_vanish_point1';Space_vanish_point2';Space_vanish_point3'])
H2=[1,0,0,0;0,1,0,0;0,0,1,0;infinity_plane'] 
X(:,22:40)=H2*X(:,22:40);
for i=1:4
X(i,:)=X(i,:)./X(4,:);
end
X

scatter3(X(1,1:21),X(2,1:21),X(3,1:21), 'r');
hold on;
scatter3(X(1,22:40),X(2,22:40),X(3,22:40), 'g');


