struct Point_3 {
    double x, y, z;
    void Input() { scanf("%lf%lf%lf", &x, &y, &z); }
    Point_3 Unit() const;
    Point_3 Rotate(const Point_3 &a, double delta) const;
};
double Mix(const Point_3 &a, const Point_3 &b, const Point_3 &c) {
    return Dot(a, Det(b, c));
}
void printed(vector<Point_3> &a) {
	int i;
	printf("face: \n");
	rep(i,a.size()) {
		printf("%lf %lf %lf	\n",a[i].x,a[i].y,a[i].z);
	}
	printf("\n\n");
}
vector<Point_3> a,b;
int n,m;
bool have[70][70][70];
class Tface{
public:
	vector<Point_3> p;
	Point_3 regular;
};
vector<Tface> face;
bool check_Inface(Point_3 a1, Point_3 a2, Point_3 a3 , vector<Point_3> &a) {
	int i;
	double tmp=0;
	Point_3 regular=Det(a2-a1,a3-a1);
	
	double k;
	rep(i,a.size()){
        k=(Dot(regular, a[i]-a1));
        if (k==0) continue;
        if (tmp==0) tmp=k;
        if (k*tmp<0) return false;
	}
	return true;
}
bool compareab(const Point_3 &a, const Point_3 &b){
    if (sign(a.x-b.x)) return sign(a.x-b.x)<0;
    if (sign(a.y-b.y)) return sign(a.y-b.y)<0;
    return sign(a.z-b.z)<0;
}

int num[70],numtot;
Tface find_face(Point_3 a1, Point_3 a2, Point_3 a3 , vector<Point_3> &a) {
	int i;
	double tmp=0;
	Point_3 regular=Det(a2-a1,a3-a1);
	double k;
	Tface now;
	now.p.clear();
	now.regular=regular;
	numtot=0;
	rep(i,a.size()){
        k=(Dot(regular, a[i]-a1));
        if (k==0) {
            now.p.push_back(a[i]);
            numtot++;
            num[numtot]=i;
        }
	}
    
	int j,kk;
	foru(i,1,numtot)
    foru(j,i,numtot)
    foru(kk,j,numtot) have[num[i]][num[j]][num[kk]]=true;
	
	sort(now.p.begin() , now.p.end(), compareab);
	vector<Point_3> con;
	con.clear();
	int open,closed;
	closed=-1;
	rep(i,now.p.size()) {
		con.push_back(now.p[i]); closed++;
		while (closed>=2 && Mix( now.regular , con[closed-1]-con[closed-2], con[closed]-con[closed-2])<0) {
			con[closed-1]=con[closed];
			con.pop_back();
			closed--;
		}
	}
	open=closed;
	ford(i,now.p.size()-2,0) {
		con.push_back(now.p[i]); closed++;
		while (closed>=open+2 && Mix( now.regular , con[closed-1]-con[closed-2], con[closed]-con[closed-2])<0) {
			con[closed-1]=con[closed];
			con.pop_back();
			closed--;
		}
	}
	closed--;
	
	while (con.size()>closed+1)
		con.pop_back();
	
	now.p=con;
	return now;
}
void count_center(Point_3 o , Tface face , double &x, double &y, double &z , double &tot) {
	int i,j,k;
	Point_3 o2;
	o2=face.p[0];
	double volume;
	double xx,yy,zz;
	foru(i,1,face.p.size()-2){
		volume=fabs(Mix( o2-o,face.p[i]-o,face.p[i+1]-o))/6;
		tot+=volume;
		
		xx=(o.x+o2.x+face.p[i].x+face.p[i+1].x)/4.0;
		yy=(o.y+o2.y+face.p[i].y+face.p[i+1].y)/4.0;
		zz=(o.z+o2.z+face.p[i].z+face.p[i+1].z)/4.0;
		x=x+xx*volume;
		y=y+yy*volume;
		z=z+zz*volume;
	}
}

double work(vector<Point_3> &a) {
	int n=a.size();
	int i,j,k;
	memset(have,0,sizeof(have));
	sort(a.begin(),a.end(),compareab);
	face.clear();
	rep(i,n)
    foru(j,i+1,n-1)
    foru(k,j+1,n-1)  if (!have[i][j][k]) if (check_Inface(a[i],a[j],a[k],a)){
        face.push_back(find_face(a[i],a[j],a[k],a));
    }
	
	Point_3 o;
	Point_3 ans;
	double volume=0;
	ans.x=ans.y=ans.z=0;
	o=a[0];
	rep(i,face.size()) {
		count_center(o,face[i],ans.x,ans.y,ans.z,volume);
	}
    
	ans=ans/volume;
	double len=dis(ans,a[0]);
	rep(i,face.size()) {
		len=min(len, fabs(Dot(face[i].regular,ans-face[i].p[0]) / face[i].regular.Length()));
	}
	return len;
}
int main(){
    int i,j,k,test;
    while (scanf("%d",&n)==1) {
		a.clear();
		Point_3 tmp;
		rep(i,n) {
			tmp.Input();
			a.push_back(tmp);
		}
		double ans1,ans2;
		ans1=work(a);
		printf("%.5lf\n",ans1);
	}
    return 0;
}

