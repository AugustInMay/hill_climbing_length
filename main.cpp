#include <iostream>
#include <string>
#include <ctime>
#include <math.h>
#include <bitset>
#include <iomanip>
using namespace std;

void neighb_fill(bitset<5> inp, bitset<5> *out){
    for(int i=0; i<5; i++){
        bitset<5> fl=inp;
        out[i]=fl.flip(i);
    }
}

int max_around(bitset<5> inp, bitset<5> *out, int *Q){
    int ret=(int)(inp.to_ulong());
    for(int i=0; i<5; i++){
        if(Q[(int)(out[i].to_ulong())]>Q[ret]){
            ret=(int)(out[i].to_ulong());
        }
    }
    return ret;
}

int main() {
    srand(time(0));
    bitset<5> field[32], neighb[5];
    int Q[32], n, cur_p=rand()%32, step=1;
    bool by_neighb=false;
    cin>>n;
    cout<<"The field and landscape are:  "<<endl;
    for(int i=0; i<32; i++){
        field[i]=i;
        Q[i]=rand()%101;
        cout<<fixed;
        cout<<field[i]<<" - Q = "<<setw(5)<<left<<Q[i]<<" ";
        if((i+1)%5==0){
            cout<<"\n";
        }
    }
    cout<<"\nRandom choice is "<<field[cur_p]<<" - Q = "<<Q[cur_p];
    while(step!=n+1){
        cout<<"\n\n-----\n\nSTEP "<<step<<" -----\nCurrent max is "<<field[cur_p]<<" with max Q = "<<Q[cur_p];
        neighb_fill(field[cur_p], neighb);
        cout<<"\nHere are the neighbours: ";
        for(int i=0; i<5; i++){
            cout<<neighb[i]<<" Q = "<<Q[(int)(neighb[i].to_ulong())]<<" ; ";
        }
        if(cur_p==max_around(field[cur_p], neighb, Q)){
            cout<<"\nThere are no better neighbours left... Finished with "<<field[cur_p]<<" Q = "<<Q[cur_p]<<" --- in "<<step<<" STEPS\n";
            by_neighb=true;
            break;
        }
        else{
            step++;
            cur_p=max_around(field[cur_p], neighb, Q);
            cout<<"\nThere is a better neigjbour, and it is a NEW max!\nCurrent max is "<<field[cur_p]<<" with max Q = "<<Q[cur_p];
        }
    }
    if(step==n && !by_neighb){
        cout<<"\n\n!The limit of steps is reached!\n\n-----Finished with "<<field[cur_p]<<" Q = "<<Q[cur_p]<<" --- in "<<step<<" STEPS\n";
    }
    return 0;
}