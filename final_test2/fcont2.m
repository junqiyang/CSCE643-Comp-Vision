% EUCLIDEAN CONSTRAINTS
function [F]=fcont2(x)
global e1 e2 e3 e4 e5 V PP;
w=[x(1:4);x(5:8);x(9:12);x(13:16)];

equ11=(w(1,:)*e1)/(w(4,:)*e1)-V(1,1);
equ12=(w(2,:)*e1)/(w(4,:)*e1)-V(2,1);
equ13=(w(3,:)*e1)/(w(4,:)*e1)-V(3,1);
equ21=(w(1,:)*e2)/(w(4,:)*e2)-V(1,2);
equ22=(w(2,:)*e2)/(w(4,:)*e2)-V(2,2);
equ23=(w(3,:)*e2)/(w(4,:)*e2)-V(3,2);
equ31=(w(1,:)*e3)/(w(4,:)*e3)-V(1,3);
equ32=(w(2,:)*e3)/(w(4,:)*e3)-V(2,3);
equ33=(w(3,:)*e3)/(w(4,:)*e3)-V(3,3);
equ41=(w(1,:)*e4)/(w(4,:)*e4)-V(1,4);
equ42=(w(2,:)*e4)/(w(4,:)*e4)-V(2,4);
equ43=(w(3,:)*e4)/(w(4,:)*e4)-V(3,4);
equ51=(w(1,:)*e5)/(w(4,:)*e5)-V(1,5);
equ52=(w(2,:)*e5)/(w(4,:)*e5)-V(2,5);
equ53=(w(3,:)*e5)/(w(4,:)*e5)-V(3,5);

F=[equ11 equ12 equ13 equ21 equ22 equ23 equ31 equ32 equ33 equ41 equ42 equ43 equ51 equ52 equ53];