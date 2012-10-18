template<class T>
double romberg(const T&f,double a,double b,double eps=1e-8){
		std::vector<double>t;
		double h=b-a,last,curr;
		int k=1,i=1;
		t.push_back(h*(f(a)+f(b))/2); // 梯形
		do{
			last=t.back();
			curr=0;
			double x=a+h/2;
			for(int j=0;j<k;++j){
				curr+=f(x);
				x+=h;
			}
			curr=(t[0]+h*curr)/2;
			double k1=4.0/3.0,k2=1.0/3.0;
			for(int j=0;j<i;j++){
				double temp=k1*curr-k2*t[j];
				t[j]=curr;
				curr=temp;
				k2/=4*k1-k2; // 防止溢出
				k1=k2+1;
			}
			t.push_back(curr);

			k*=2;
			h/=2;
			i++;
		}while(std::fabs(last-curr)>eps);
		return t.back();
}

template<class T>
double simpson(const T&f,double a,double b,int n){
	const double h=(b-a)/n;
	double ans=f(a)+f(b);
	for(int i=1;i<n;i+=2)ans+=4*f(a+i*h);
	for(int i=2;i<n;i+=2)ans+=2*f(a+i*h);
	return ans*h/3;
}

double test(double x){
	if(x==0)return 1;
	else return sin(x)/x;
}
int main(){
	printf("%lf\n",romberg(test,0,1));
	printf("%lf\n",simpson(test,0,1,(int)1e6));
}

