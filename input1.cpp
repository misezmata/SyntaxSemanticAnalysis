int main();
int foo();

int main(){
	int a, ara[10];
	ara[9] = 10;
	return 9+ara[0]<9+foo();
}