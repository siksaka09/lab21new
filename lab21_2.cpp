#include<iostream>
using namespace std;

struct Rect{
	double x,y,w,h;
};

double overlap(Rect *a,Rect *b){ 
	float s1,s2,sum; 
	s1=min((a->x)+(a->w),(b->x)+(b->w))-max(a->x,b->x); 
	s2=min(a->y,b->y)-max((a->y)-(a->h),(b->y)-(b->h)); 
	sum=s1*s2; 
	if(sum<0){ 
		return 0;
	} 
	else{ 
		return s1*s2;
	}  
}
