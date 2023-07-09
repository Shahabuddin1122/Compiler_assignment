#include<bits/stdc++.h>
#include<fstream>
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
    int HashFunc(string t)
    {
        int sum = 0;
        for (int i = 0; i < t.length(); i++)
        {
            sum = sum + static_cast<int>(t[i]);
        }
        sum = sum * 92;
        sum = sum % 20;
        return sum;
    }

    void Insert(SymbolInfo b){

        if(lookup(b.getvar())){
            return;
        }
        else {
            int k=HashFunc(b.getvar());
            int j=a[k].size();
            a[k].push_back(b);
            cout<<"Inserted at position "<<k<<" "<<j<<endl;
            
        }
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
    bool lookup(string s){
        int k=HashFunc(s);
        for(int i=0;i<a[k].size();i++){
            
            //cout<<"lookup arry: "<<a[k][i].getvar()<<endl;
            if(a[k][i].getvar()==s){
                cout<<"Found at "<<k<<","<<i<<endl;
                return true;
            }
        }
        return false;
    }
    void display(){
        //extern  FILE *yyout1;
		//yyout1=fopen("log.txt","w");
        ofstream file;
        file.open("log.txt");
        for(int i=0;i<20;i++){
            //fprintf(yyout1,"%d-->",i);
            file<<i<<"-->";
            for(int j=0;j<a[i].size();j++){
                file<<" <"<<a[i][j].getvar()<<","<<a[i][j].getid()<<"> ";
                //fprintf(yyout1," < %s , %s  > ",a[i][j].getvar(),a[i][j].getid());
            }
            //fprintf(yyout1,"\n");
            file<<endl;
        }
    }

};

//int main(){
////    SymbolInfo a("SHBHABUDDIN","NUMBER");
////    SymbolTable b;
////    b.Insert(a);
////    b.display();
//    string t,s,is;
//    SymbolTable st;
//    ifstream file;
//    file.open("input.txt");
//    if (file.is_open())
//    {
//        while (file >> t)
//        {
//            if (t == "I")
//            {
//                file >> s >> is ;
//                SymbolInfo a(s,is);
//                st.Insert(a);
//            }
//            else if (t == "P")
//            {
//                st.display();
//            }
//            else if (t == "L")
//            {
//                file >> s;
//                st.lookup(s);
//            }
//            else if (t == "D")
//            {
//                file >> s;
//                st.Delete(s);
//            }
//        }
//    }
//    else
//    {
//        cout<<"file is unable to open."<<endl;
//    }
//    file.close();
//    return 0;
//}
