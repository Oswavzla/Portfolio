/*Program to count how man bills do you have.*/

#include<iostream>

using namespace std;

void num();
void billetes(int& cantidad, int& cien, int& cincuenta, int& veinte, int& diez, int& cinco, int& uno);

int cantidad, cien = 0, cincuenta = 0, veinte = 0, diez = 0, cinco = 0, uno = 0;

int main(){

    num();
    billetes(cantidad, cien, cincuenta, veinte, diez, cinco, uno);
    cout<<"\nBilletes de cien: "<<cien<<"\nBilletes de cicnuenta: "<<cincuenta<<"\nBilletes de veinte: "<<veinte<<"\nBilletes de diez: "<<diez<<"\nBilletes de cinco: "<<cinco<<"\nBilletes de uno: "<<uno<<endl;


    return 0;
}

void num(){

    cout<<"Digite la cantidad de dinero: ";
    cin>>cantidad;

}

void billetes(int& cantidad, int& cien, int& cincuenta, int& veinte, int& diez, int& cinco, int& uno){

    while(cantidad>=100){
        cantidad -= 100;
        cien++;
    }
    while(cantidad>=50){
        cantidad -= 50;
        cincuenta++;
    }
    while(cantidad>=20){
        cantidad -= 20;
        veinte++;
    }
    while(cantidad>=10){
        cantidad -= 10;
        diez++;
    }
    while(cantidad>=5){
        cantidad -= 5;
        cinco++;
    }
    while(cantidad>=1){
        cantidad -= 1;
        uno++;
    }

}
