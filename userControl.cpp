#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int getTotalUser(){//get total line
	ifstream f("users.dat");
	int i = 0;
	string line;
	while (getline(f,line)){
		++i;
	}
	return i;
}

int userControl(string username , string password){
	string userData;
  	string passData;
  	string accessData;
  	string line;
  	ifstream myfile ("users.dat");
  	
  	/*****************
  	
	  example user in users.dat
	  alpii4=123=admin=
	  esref=1234=user= 
	  
	  *****************/
  	
  	bool admin;
  	int match=0;
  	for (int i=0;i<getTotalUser();i++){
  		getline (myfile,userData,'=');
    	getline (myfile,passData,'=');
    	getline (myfile,accessData,'=');
    	getline (myfile,line,'=');//\n operator cleaner
   		if(username==userData && password==passData){
   			if(accessData=="admin")
   				{admin=true;
				}
   				++match; //matched account
		   }
	}
		if(admin==true && match==1)
			return 2;//admin login
		else if(admin==false && match==1){
			
			return 1;//user login
		}
		else 
			return 0;//failed login
}
int main(){
int a= userControl("user","1234");
cout << a;
}

