#include <bits/stdc++.h>
using namespace std;
#define ll long long

class bucket{
    public:
    int local_depth;
    int capacity;
    set<int> a;
    bool isFull,isEmpty;
    
    bucket(){
        isFull=false;
        isEmpty=true;
        a.clear();
    }

    bool insert(int val){
        if(isFull){
            //cout<<"BDCHSVHSVBFKBSDKFJBV\n";
            return false;
        }
        isEmpty=false;
        if(search(val)){
            cout<<"Element already present\n";
            return true;
        }

        a.insert(val);
        if(a.size()==capacity){
            isFull=true;
        }
        return true;
    }

    bool search(int val){
        return a.find(val)!=a.end();
    }

    void remove(int val){
        if(isEmpty){
            cout<<"Error removing from bucket";
            return;
        }
        isFull=false;
        if(search(val)==0){
            cout<<"Element to be deleted does not exist\n";
            return;
        }
        a.erase(val);
        if(a.size()==0){
            isEmpty=true;
        }
        return;
    }

    void print(){
        for(auto it: a){
            cout<<it<<" ";
        }
        cout<<"\n";
    }

};

class directory{
    public:
    int global_depth;
    map<int,bucket> list;

    directory(int depth,int capacity){
        global_depth=depth;
        for(ll i=0;i<1<<depth;i++){
            list[i]=bucket();
            list[i].capacity=capacity;
            list[i].local_depth=depth;
        }
    }

    void insert(int val){

        for(ll i=1;i<(1<<global_depth);i=i<<1){

            if(list.find(val%i)!=list.end()){

                int t=list[val%i].local_depth;
                int idx=val%(1<<t);

                if(list.find(idx)!=list.end()){

                    bool check=list[idx].insert(val);//bucket insert

                    if(check==false){//container is full
                        //bucket is being split
                        vector<int> temp;//temp stores all values in bucket
                        temp.clear();
                        temp.push_back(val);
                        for(auto it1: list[idx].a)
                            temp.push_back(it1);
                        
                        list[idx].local_depth++;//increase local depth
                        //cout<<t<<"\n";
                        if(global_depth==t)
                            global_depth++;

                        list[idx+1<<t]=bucket();//make new bucket
                        list[idx+1<<t].capacity=list[idx].capacity;
                        list[idx+1<<t].local_depth=t+1;

                        list[idx].a.clear();
                        list[idx].isFull=false;

                        for(auto it2: temp){
                            //cout<<"xyz "<<((it2)&(1<<t))<<" ";
                            if(((it2)&(1<<t))==0){
                                if(list[idx].isFull){
                                    insert(it2);
                                    return;
                                }
                                list[idx].insert(it2);
                                //cout<<it2<<" y ";
                            }
                            else{
                                if(list[idx+1<<t].isFull){
                                    insert(it2);
                                    return;
                                }
                                list[idx+1<<t].insert(it2);
                                //cout<<it2<<" x ";
                            }
                        }
                    }
                    break;
                }
            }
        }
        return;
    }

    void display(){
        cout<<global_depth<<"\n";
        cout<<list.size()<<"\n";
        cout<<"************\n";
        for(auto it: list){
            cout<<it.first<<"\n";
            it.second.print();
            cout<<"************\n";
        }
    }

    void remove(int val){
        for(ll i=1;i<(1<<global_depth);i=i<<1){
            if(list.find(val%i)!=list.end()){
                int t=list[val%i].local_depth;
                int idx=val%(1<<t);
                if(list.find(idx)!=list.end()){
                    if(list[idx].search(val)){
                        list[idx].remove(val);
                    }
                }
            }
        }
        return;
    }

};

int main(){

    int depth,capacity,n,x;
    cin>>depth>>capacity>>n;
    directory main(depth,capacity);
    vector<int> a;

    for(int i=0;i<n;i++){
        cin>>x;
        a.push_back(x);
        main.insert(x);
    }
    main.display();
    for(int i=0;i<n;i++){
        main.remove(a[i]);
        main.display();
    }
    main.remove(x);
    return 0;
}