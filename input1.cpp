// int a, b;

// int foo(int a){
//     return 1;
// }

// int main(){
//     // float a[10];
//     a[2] = 10*10+1.2;
//     return foo(a) + 2;
// }

int x,y,z; float a;

void foo();

int var(int a, int b){
	return a+b;
}

void foo(){
	x=2;
	y=x-5;
}

int main(){
	int a[2],c,i,j ; float d;
	a[0];
	a[1]=5;
	i= a[0]+a[1];
	j= 2*3+(5%3 < 4 && 8) || 2 ;
	d=var(1,2*3)+3.5*2;
	return 0;
}