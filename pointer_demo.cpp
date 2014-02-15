#include <iostream>
using namespace std;
 
 
int dublin_pbv(int n);
void dublin_pbr(int &n);
void dublin_pbv_ptr(int *n);
 
int main()
{
cout<< "values!" <<endl;

int input= 12;
int *in_ptr = &input; 

cout<<"input before running anything: " <<input<<endl;
cout<<"dublin_pbv(input)" << dublin_pbv(input)<<endl;

dublin_pbr(input);
cout<<"input after running dublin_pbr(input)" << input<<endl;
dublin_pbv_ptr(in_ptr);
cout<<"input after dublin_pbv_prt(in_prt)" << *in_ptr<<endl;

cout<<" the value of in_ptr: " << in_ptr<<endl; 
cout<<" the value of *in_ptr: " << *in_ptr <<endl; 
cout<<" the value of &in_ptr: " << &in_ptr <<endl;
return 0;


}
int dublin_pbv(int n)
{
return 2 * n;
}
void dublin_pbr(int &n)
{
n *= 2;

}
void dublin_pbv_ptr(int *n)
{

*n *= 2;
}