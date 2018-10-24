% EUCLIDEAN CONSTRAINTS
function [F]=find_H(x)
    global e1 e2 e3 e4 e5 V;
    h=[x(1:4);x(5:8);x(9:12);x(13:16)];
    error11=(h(1,:)*e1)/(h(4,:)*e1)-V(1,1);
    error12=(h(2,:)*e1)/(h(4,:)*e1)-V(2,1);
    error13=(h(3,:)*e1)/(h(4,:)*e1)-V(3,1);
    error21=(h(1,:)*e2)/(h(4,:)*e2)-V(1,2);
    error22=(h(2,:)*e2)/(h(4,:)*e2)-V(2,2);
    error23=(h(3,:)*e2)/(h(4,:)*e2)-V(3,2);
    error31=(h(1,:)*e3)/(h(4,:)*e3)-V(1,3);
    error32=(h(2,:)*e3)/(h(4,:)*e3)-V(2,3);
    error33=(h(3,:)*e3)/(h(4,:)*e3)-V(3,3);
    error41=(h(1,:)*e4)/(h(4,:)*e4)-V(1,4);
    error42=(h(2,:)*e4)/(h(4,:)*e4)-V(2,4);
    error43=(h(3,:)*e4)/(h(4,:)*e4)-V(3,4);
    error51=(h(1,:)*e5)/(h(4,:)*e5)-V(1,5);
    error52=(h(2,:)*e5)/(h(4,:)*e5)-V(2,5);
    error53=(h(3,:)*e5)/(h(4,:)*e5)-V(3,5);

    F=[error11 error12 error13 error21 error22 error23 error31 error32 error33 error41 error42 error43 error51 error52 error53];
end