int foo(int a, int b){
    return 1;
}
int main(){
    int a, b, c;
    foo(a+10, b++%10);
    return 1;
}