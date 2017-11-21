#include <iostream>
#include <time.h> //for Sleep() fucntions
#include <cmath>
#include <windows.h>

using namespace std;

int main()
{
    srand(time(0));
    int x = 0;
	system("color 4f"); //console will be red background and white texts 
    for(int i = 0; i<100; i++){
        int r = rand() % 1000;
        x++;
        cout << "\r" << x << "% completed." << flush;
        if(i < 43){
           Sleep(r/6);
           //todo at 0 - 43
        }else if(i > 43 && i < 74){
           Sleep(r/8);
           //todo at 43 - 74
        }else if(i < 97){
           Sleep(r/5);
           //todo at when it's smaller than 97
        }else if(i > 97 && i != 99){
           Sleep(2000);
           //todo at 97 - 100
        }
    }

    cout << endl << endl << "Operation completed successfully.\n" << flush;
    return 0;
}
