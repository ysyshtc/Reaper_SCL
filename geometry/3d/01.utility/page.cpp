//vlen(point3 P):length of vector; zero(double x):if fabs(x)<eps) return true;
//平面法向量
point3 pvec(point3 s1,point3 s2,point3 s3){return det((s1-s2),(s2-s3));}
//check共线
int dots_inline(point3 p1,point3 p2,point3 p3){
	return vlen(det(p1-p2,p2-p3))<eps;}
//check共平面
int dots_onplane(point3 a,point3 b,point3 c,point3 d){
	return zero(dot(pvec(a,b,c),d-a));}
//check在线段上(end point inclusive)
int dot_online_in(point3 p,line3 l);
int dot_online_in(point3 p,point3 l1,point3 l2){
	return zero(vlen(det(p-l1,p-l2)))&&(l1.x-p.x)*(l2.x-p.x)<eps&&(l1.y-p.y)*(l2.y-p.y)<eps&&(l1.z-p.z)*(l2.z-p.z)<eps;}
//check在线段上(end point exclusive)
int dot_online_ex(point3 p,line3 l);
int dot_online_ex(point3 p,point3 l1,point3 l2){
	return dot_online_in(p,l1,l2)&&(!zero(p.x-l1.x)||!zero(p.y-l1.y)||!zero(p.z-l1.z))&&(!zero(p.x-l2.x)||!zero(p.y-l2.y)||!zero(p.z-l2.z));}
//check一个点是否在三角形里(inclusive)
int dot_inplane_in(point3 p,plane3 s);
int dot_inplane_in(point3 p,point3 s1,point3 s2,point3 s3){
	return zero(vlen(det(s1-s2,s1-s3))-vlen(det(p-s1,p-s2))-vlen(det(p-s2,p-s3))-vlen(det(p-s3,p-s1)));}
//check一个点是否在三角形里(exclusive)
int dot_inplane_ex(point3 p,plane3 s)
int dot_inplane_ex(point3 p,point3 s1,point3 s2,point3 s3){
	return dot_inplane_in(p,s1,s2,s3)&&vlen(det(p-s1,p-s2))>eps&&vlen(det(p-s2,p-s3))>eps&&vlen(det(p-s3,p-s1))>eps;}
//check if two point and a segment in one plane have the same side
int same_side(point3 p1,point3 p2,point3 l1,point3 l2);
int same_side(point3 p1,point3 p2,line3 l){
	return dot(det(l.a-l.b,p1-l.b),det(l.a-l.b,p2-l.b))>eps; }
//check if two point and a segment in one plane have the opposite side
int opposite_side(point3 p1,point3 p2,point3 l1,point3 l2);
int opposite_side(point3 p1,point3 p2,line3 l){
	return dot(det(l.a-l.b,p1-l.b), det(l.a-l.b,p2-l.b))<-eps;}
//check if two point is on the same side of a plane
int same_side(point3 p1,point3 p2,point3 s1,point3 s2,point3 s3);
int same_side(point3 p1,point3 p2,plane3 s){
	return dot(pvec(s),p1-s.a)*dot(pvec(s),p2-s.a)>eps;}
//check if two point is on the opposite side of a plane
int opposite_side(point3 p1,point3 p2,point3 s1,point3 s2,point3 s3);
int opposite_side(point3 p1,point3 p2,plane3 s){
	return dot(pvec(s),p1-s.a)*dot(pvec(s),p2-s.a)<-eps;}
//check if two straight line is parallel
int parallel(point3 u1,point3 u2,point3 v1,point3 v2);
int parallel(line3 u,line3 v){	return vlen(det(u.a-u.b,v.a-v.b))<eps; }
//check if two plane is parallel
int parallel(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3);
int parallel(plane3 u,plane3 v){return vlen(det(pvec(u),pvec(v)))<eps;}
//check if a plane and a line is parallel
int parallel(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3)
int parallel(line3 l,plane3 s){ return zero(dot(l.a-l.b,pvec(s))); }
//check if two line is perpendicular
int perpendicular(point3 u1,point3 u2,point3 v1,point3 v2);
int perpendicular(line3 u,line3 v){return zero(dot(u.a-u.b,v.a-v.b)); }
//check if two plane is perpendicular
int perpendicular(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3)
int perpendicular(plane3 u,plane3 v){	return zero(dot(pvec(u),pvec(v))); }
//check if plane and line is perpendicular
int perpendicular(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3);
int perpendicular(line3 l,plane3 s){return vlen(det(l.a-l.b,pvec(s)))<eps;}
//check 两条线段是否有交点(end point inclusive)
int intersect_in(point3 u1,point3 u2,point3 v1,point3 v2);
int intersect_in(line3 u,line3 v){
	if (!dots_onplane(u.a,u.b,v.a,v.b)) return 0;
	if (!dots_inline(u.a,u.b,v.a)||!dots_inline(u.a,u.b,v.b))
		return !same_side(u.a,u.b,v)&&!same_side(v.a,v.b,u);
	return dot_online_in(u.a,v)||dot_online_in(u.b,v)||dot_online_in(v.a,u)||dot_online_in(v.b,u);}
//check 两条线段是否有交点(end point exclusive)
int intersect_ex(point3 u1,point3 u2,point3 v1,point3 v2);
int intersect_ex(line3 u,line3 v){
	return dots_onplane(u.a,u.b,v.a,v.b)&&opposite_side(u.a,u.b,v)&&opposite_side(v.a,v.b,u);
}
//check线段和三角形是否有交点(end point and border inclusive)
int intersect_in(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3)
int intersect_in(line3 l,plane3 s){
	return !same_side(l.a,l.b,s)&&!same_side(s.a,s.b,l.a,l.b,s.c)&&
		!same_side(s.b,s.c,l.a,l.b,s.a)&&!same_side(s.c,s.a,l.a,l.b,s.b);
}
//check线段和三角形是否有交点(end point and border exclusive)
int intersect_ex(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3)
int intersect_ex(line3 l,plane3 s){
	return opposite_side(l.a,l.b,s)&&opposite_side(s.a,s.b,l.a,l.b,s.c)&&	opposite_side(s.b,s.c,l.a,l.b,s.a)&&opposite_side(s.c,s.a,l.a,l.b,s.b);}
//calculate the intersection of two line
//Must you should ensure they are co-plane and not parallel
point3 intersection(point3 u1,point3 u2,point3 v1,point3 v2)
point3 intersection(line3 u,line3 v){
	point3 ret=u.a; 
	double t=((u.a.x-v.a.x)*(v.a.y-v.b.y)-(u.a.y-v.a.y)*(v.a.x-v.b.x))
			/((u.a.x-u.b.x)*(v.a.y-v.b.y)-(u.a.y-u.b.y)*(v.a.x-v.b.x));
ret+=(u.b-u.a)*t;	return ret;
}
//calculate the intersection of plane and line
point3 intersection(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3)
point3 intersection(line3 l,plane3 s){
	point3 ret=pvec(s);
double t=(ret.x*(s.a.x-l.a.x)+ret.y*(s.a.y-l.a.y)+ret.z*(s.a.z-l.a.z))/
		(ret.x*(l.b.x-l.a.x)+ret.y*(l.b.y-l.a.y)+ret.z*(l.b.z-l.a.z));
	ret=l.a + (l.b-l.a)*t; 	return ret;
}
//calculate the intersection of two plane 
bool intersection(plane3 pl1 , plane3 pl2 , line3 &li) {
	if (parallel(pl1,pl2)) return false;	
	li.a=parallel(pl2.a,pl2.b, pl1) ? intersection(pl2.b,pl2.c, pl1.a,pl1.b,pl1.c) : intersection(pl2.a,pl2.b, pl1.a,pl1.b,pl1.c);	
	point3 fa; fa=det(pvec(pl1),pvec(pl2)); li.b=li.a+fa;	return true;
}
//distance from point to line
double ptoline(point3 p,point3 l1,point3 l2)
double ptoline(point3 p,line3 l){
	return vlen(det(p-l.a,l.b-l.a))/distance(l.a,l.b);}
//distance from point to plane
double ptoplane(point3 p,plane3 s){
	return fabs(dot(pvec(s),p-s.a))/vlen(pvec(s));}
double ptoplane(point3 p,point3 s1,point3 s2,point3 s3)
//distance between two line       当u,v平行时有问题
double linetoline(line3 u,line3 v){
	point3 n=det(u.a-u.b,v.a-v.b); return fabs(dot(u.a-v.a,n))/vlen(n);
}
double linetoline(point3 u1,point3 u2,point3 v1,point3 v2)
//cosine value of the angle formed by two lines
double angle_cos(line3 u,line3 v){
	return dot(u.a-u.b,v.a-v.b)/vlen(u.a-u.b)/vlen(v.a-v.b);
}
double angle_cos(point3 u1,point3 u2,point3 v1,point3 v2)
//cosine value of the angle formed by two planes
double angle_cos(plane3 u,plane3 v){
	return dot(pvec(u),pvec(v))/vlen(pvec(u))/vlen(pvec(v));}
double angle_cos(point3 u1,point3 u2,point3 u3,point3 v1,point3 v2,point3 v3)
//cosine value of the angle formed by plane and line
double angle_sin(line3 l,plane3 s){
	return dot(l.a-l.b,pvec(s))/vlen(l.a-l.b)/vlen(pvec(s));}
double angle_sin(point3 l1,point3 l2,point3 s1,point3 s2,point3 s3)

