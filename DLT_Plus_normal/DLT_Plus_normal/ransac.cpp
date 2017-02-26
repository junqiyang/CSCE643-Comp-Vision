#include "ransac.h"

void ransac_h(int num, int N, CvPoint2D64f *point_1, CvPoint2D64f *point_2, CvMat *H, CvMat *inlier_mask) {
	int i, j;
	int N = 1000, s = 4, sample_cnt = 0;
	double e, p = 0.99;
	int numinlier, MAX_num;
	double curr_dist_std, dist_std;
	bool iscolinear;
	CvPoint2D64f *curr_m1 = new CvPoint2D64f[s];
	CvPoint2D64f *curr_m2 = new CvPoint2D64f[s];
	int *curr_idx = new int[s];

	CvMat *curr_inlier_mask = cvCreateMat(num, 1, CV_64FC1);
	CvMat *curr_H = cvCreateMat(3, 3, CV_64FC1); 
	CvMat *T1 = cvCreateMat(3, 3, CV_64FC1);
	CvMat *T2 = cvCreateMat(3, 3, CV_64FC1);
	CvMat *invT2 = cvCreateMat(3, 3, CV_64FC1);
	CvMat *tmp_pt = cvCreateMat(3, 1, CV_64FC1);

	// RANSAC algorithm (reject outliers and obtain the best H)       
	srand(134);  
	MAX_num  = -1;  
	while(N > sample_cnt){   
		// for a randomly chosen non-colinear correspondances   
		iscolinear = true;   
		while(iscolinear == true){ 
			iscolinear = false;    
			for(i=0; i<s; i++){ 
				// randomly select an index 
				curr_idx[i] = rand()%num;  
				for(j=0; j<i; j++){   
					if(curr_idx[i] == curr_idx[j]){ 
						iscolinear = true;
	break;
}     }     if (iscolinear == true) break;     curr_m1[i].x = m1[curr_idx[i]].x;     curr_m1[i].y = m1[curr_idx[i]].y;     curr_m2[i].x = m2[curr_idx[i]].x;     curr_m2[i].y = m2[curr_idx[i]].y;    }    // Check whether these points are colinear    if(iscolinear == false)     iscolinear = isColinear(s, curr_m1);   }   // Nomalized DLT   Normalization(s, curr_m1, T1); //curr_m1 <- T1 * curr_m1   Normalization(s, curr_m2, T2); //curr_m2 <- T2 * curr_m2 

																																																		   // Compute the homography matrix H = invT2 * curr_H * T1   ComputeH(s, curr_m1, curr_m2, curr_H);   cvInvert(T2, invT2);   cvMatMul(invT2, curr_H, curr_H); // curr_H <- invT2 * curr_H   cvMatMul(curr_H, T1, curr_H);     // curr_H <- curr_H * T1 

																																																		   // Calculate the distance for each putative correspondence   // and compute the number of inliers     numinlier = ComputeNumberOfInliers(num,m1,m2,curr_H,curr_inlier_mask,&curr_dist_std);   

																																																		   // Update a better H   if(numinlier > MAX_num || (numinlier == MAX_num && curr_dist_std < dist_std)){    MAX_num = numinlier;    cvCopy(curr_H, H);    cvCopy(curr_inlier_mask, inlier_mask);    dist_std = curr_dist_std;   } 

																																																		   // update number N by Algorithm 4.5   e = 1 - (double)numinlier / (double)num;   N = (int)(log(1-p)/log(1-pow(1-e,s)));   sample_cnt++;  } 

																																																		   // Optimal estimation using all the inliers  delete curr_m1, curr_m2, curr_idx;  cvReleaseMat(&curr_H);  cvReleaseMat(&T1);  cvReleaseMat(&T2);  cvReleaseMat(&invT2);  cvReleaseMat(&tmp_pt);  cvReleaseMat(&curr_inlier_mask); } 
