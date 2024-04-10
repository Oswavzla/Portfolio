/*This is a program taken from a C++ programming course to select and list people with disabilities. */

#include<iostream>

using namespace std;

struct person{
	char name[20];
	int dis; //disability
}pe[100];

int main(){
	
	int n, non_disabled[100], disabled[100], i=0, j=0;
	
	cout<<"Indicate how many people will be evaluated: ";
	cin>>n;
	cout<<"\nNext enter the data of the people, (Disability: 1 | No Disability: 0)"<<endl;
	
	for(int p=0;p<n;p++){
		cout<<"\nName: ";
		cin.ignore();
		cin.getline(pe[p].name,20,'\n');
		cout<<"Disability: ";
		cin>>pe[p].dis;
		
			if(pe[p].dis==1){
				disabled[i]=p;
				i++;
			}
			
			else if(pe[p].dis==0){
				non_disabled[j]=p;
				j++;
			}
			
	}
	
	cout<<endl;
	
	cout << "\nPeople with disability: ";
	for(int p=0;p<i;p++){
		cout<<endl<<pe[disabled[p]].name;
	}
	
	cout<<endl;
	
	cout << "\nPeople without disability: ";
	for(int p=0;p<j;p++){
		cout<<endl<<pe[non_disabled[p]].name;
	}
	
	cout<<endl;
	
	return 0;
}
