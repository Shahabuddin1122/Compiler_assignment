#include<bits/stdc++.h>

using namespace std;

class SymbolInfo
{
    string var1;
    string identifier;
public:
    SymbolInfo(string a,string b)
    {
        var1=a;
        identifier=b;
    }
    string getvar(){
        return var1;
    }
    string getid(){
        return identifier;
    }

};
class SymbolTable
{
    vector<SymbolInfo>a[20];
public:
    SymbolTable(){

    }
    int HashFunc(string t){
        //string t=k.getvar();
        int sum=0;
        for(int i=0;i<3;i++)
        {
            sum=sum+t[i];
        }
        sum=sum*92;
        sum=sum%20;
        return sum;
    }
    void Insert(SymbolInfo b){
        int k=HashFunc(b.getvar());
        int j=a[k].size();
        a[k].push_back(b);
        cout<<"Inserted at position "<<k<<" "<<j<<endl;
    }
    void Delete(string s){
        int i = HashFunc(s);
        int id = 0;
        for(auto it = a[i].begin();it!=a[i].end();it++)
        {
            if(it->getvar()==s)
            {
                cout<<"Deleted from "<<i<<", "<<id<<endl;
                a[i].erase(it);
                return;
            }
            id++;
        }
        cout<<"Symbol not found."<<endl;
        return;
    }
    void lookup(string s){
        int k=HashFunc(s);
        for(int i=0;i<a[k].size();i++){
            if(a[k][i].getvar()==s){
                cout<<"Found at "<<k<<","<<i<<endl;
            }
        }
    }
    void display(){
        for(int i=0;i<20;i++){
            cout<<i<<"-->";
            for(int j=0;j<a[i].size();j++){
                cout<<" <"<<a[i][j].getvar()<<","<<a[i][j].getid()<<"> ";
            }
            cout<<endl;
        }
    }

};

int main(){
//    SymbolInfo a("SHBHABUDDIN","NUMBER");
//    SymbolTable b;
//    b.Insert(a);
//    b.display();
    string t,s,is;
    SymbolTable st;
    ifstream file;
    file.open("input.txt");
    if (file.is_open())
    {
        while (file >> t)
        {
            if (t == "I")
            {
                file >> s >> is ;
                SymbolInfo a(s,is);
                st.Insert(a);
            }
            else if (t == "P")
            {
                st.display();
            }
            else if (t == "L")
            {
                file >> s;
                st.lookup(s);
            }
            else if (t == "D")
            {
                file >> s;
                st.Delete(s);
            }
        }
    }
    else
    {
        cout<<"file is unable to open."<<endl;
    }
    file.close();
    return 0;
}
