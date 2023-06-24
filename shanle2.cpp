
#include <iostream>
using namespace std;

class Complex
{
        friend ostream& operator <<(ostream& cout,Complex &c);
public:
    double real, imag;//实部，虚部
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i){}
    Complex operator-(const Complex &c);
    Complex &nixu();
};
// Complex operator +(const Complex &a, const Complex &b){
//         return Complex(a.real + b.real, a.imag + b.imag);
// }
// Complex Complex ::operator-(const Complex &c) {
//         return Complex(real - c.real, imag - c.imag);
// }
Complex operator +(const Complex a,const Complex b){
        return Complex(a.real+b.real,a.imag+b.imag);
}
Complex Complex::operator-(const Complex &c){
        return Complex(real-c.real,imag-c.imag);
        
}
ostream& operator <<(ostream& cout,Complex&c){
        cout<<"real:"<<c.real<<"image:"<<c.imag;
        return cout;

}
Complex &Complex::nixu(){
        swap(this->imag,this->real);


        return *this;//return the result of the function as the return type of the function.

}

int main(){
        Complex c(1,2);
        // c.nixu();
        cout<<c.nixu()<<endl;
}
