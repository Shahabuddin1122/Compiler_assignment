#include<bits/stdc++.h>
#include"202114092_Akhon.cpp"
using namespace std;
string key[15] = {"if","else","if else","for","while","do","break","int","char","float","double","const","unsigned","return","include"};
bool keyword(string k){
    for(int i=0;i<15;i++){
        if(key[i]==k){
            return true;
        }
    }
    return false;
}
int check(string s){
    unordered_map<string,bool>op[4];
    ifstream oper("operator.txt");
    int k=0;
    string temp="";
    while(getline(oper,temp)){
        stringstream st(temp);
        while(st>>temp){
            op[k][temp]=true;
        }
        k++;
    }
    for(int i=0;i<4;i++){
        if(op[i][s]){
            return i;
        }
    }
    return -1;

}
bool operator_check(string s,int line){
    ofstream out("output_operator.txt");
    unordered_map<char,bool>op;
    op['+']=true;
    op['-']=true;
    op['*']=true;
    op['&']=true;
    op['|']=true;
    op['<']=true;
    op['>']=true;
    op['=']=true;
    op['/']=true;
    op['%']=true;

    int sz=s.size();
    int i=0;
    while(i<sz){
        string s1="";
        string s2="";
        string s3="";
        if(op[s[i]]){
            s1=s[i];
            s2=s1+s[i+1];
            s3=s[i+1];
            i=i+2;
        }
        else
        {
            i++;
        }
        int a=check(s1);
        int b=check(s2);
        int c=check(s3);
        if(b!=-1){
            if(b==0){
                cout<<s2<<" Arithmetic_operator2 "<<line<<endl;
                out<<s2<<" Arithmetic_operator2 "<<line<<endl;
                return true;
            }
            else if(b==1){
                cout<<s2<<" Logical_operator2 "<<line<<endl;
                out<<s2<<" Logical_operator2 "<<line<<endl;
                return true;
            }
            else if(b==2){
                cout<<s2<<" Bitwise_operator2 "<<line<<endl;
                out<<s2<<" Bitwise_operator2 "<<line<<endl;
                return true;
            }
            else if(b==3){
                cout<<s2<<" Assignment_operator2 "<<line<<endl;
                out<<s2<<" Assignment_operator2 "<<line<<endl;
                return true;
            }
        }
        else {
            if(a!=-1){
                if(a==0){
                    cout<<s1<<" Arithmetic_operator1 "<<line<<endl;
                    out<<s1<<" Arithmetic_operator1 "<<line<<endl;
                    return true;
                }
                else if(a==1){
                    cout<<s1<<" Logical_operator1 "<<line<<endl;
                    out<<s1<<" Logical_operator1 "<<line<<endl;
                    return true;
                }
                else if(a==2){
                    cout<<s1<<" Bitwise_operator1 "<<line<<endl;
                    out<<s1<<" Bitwise_operator1 "<<line<<endl;
                    return true;
                }
                else if(a==3){
                    cout<<s1<<" Assignment_operator1 "<<line<<endl;
                    out<<s1<<" Assignment_operator1 "<<line<<endl;
                    return true;
                }
            }
            if(c!=-1){
                if(c==0){
                cout<<s3<<" Arithmetic_operator3 "<<line<<endl;
                out<<s3<<" Arithmetic_operator3 "<<line<<endl;
                return true;
                }
                else if(c==1){
                    cout<<s3<<" Logical_operator3 "<<line<<endl;
                    out<<s3<<" Logical_operator3 "<<line<<endl;
                    return true;
                }
                else if(c==2){
                    cout<<s3<<" Bitwise_operator3 "<<line<<endl;
                    out<<s3<<" Bitwise_operator3 "<<line<<endl;
                    return true;
                }
                else if(c==3){
                    cout<<s3<<" Assignment_operator3 "<<line<<endl;
                    out<<s3<<" Assignment_operator3 "<<line<<endl;
                    return true;
                }
            }
        }

    }
    return false;
}

void lexeme(string s,int line)
{
    bool queta=false;
    int l;
    int lb=0;
    int fun=0;


    for(int i=0;i<s.size();i++){
        if(s[i]==' '|| s[i]=='\n' || s[i]=='\t'){

            lb=lb+1;
            //cout<<"SPACE "<<i<<" "<<lb<<endl;
        }
        else if(s[i]=='"'){

            for(int j=i+1;j<s.size();j++){
                if(s[j]=='"'){
                    queta=true;
                    l=j;

                    break;
                }


            }
            if(queta){
                ofstream out("literal.txt",ios::app);
                string k;
                k=s.substr(i+1,(l-i-1));
                cout<<"Literal: "<<k<<" "<<line<<endl;
                out<<"Literal: "<<k<<" "<<line<<endl;
                i=l+1;
                lb=i;
                queta=false;
                out.close();
            }
        }
        else if( (s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z') ||(s[i]>='0' && s[i]<='9')|| s[i]=='_'){

            if(s[i+1]==' ' || s[i+1]==')' || s[i+1]==',' ){
                //cout<<"A"<<i<<" "<<lb<<endl;
                int x=i;
                string k=s.substr(lb,abs(x-lb)+1);
                i++;
                while(s[i]==' ' || s[i]==')' || s[i]==';' || s[i]==','  ){
                    //cout<<"SPACE2 "<<i<<" "<<lb<<endl;
                    i=i+1;
                    lb=i;

                }
                if(keyword(k)){
                        cout<<"Keyword2: "<<k<<" "<<line<<endl;
                }
                else {
                    cout<<"ID2: "<<k<<" "<<line<<endl;

                }

               lb=i;
               i=i-1;

            }
            else if(s[i+1]=='('){
                fun=1;



                for(int k=i+1;k<s.size();k++){
                    if(s[k]==')'){
                        fun=0;
                        break;
                    }
                }
                if(fun==0){
                    string f=s.substr(lb,abs(i-lb)+1);
                    if(keyword(f)){
                        cout<<"Keyword3:"<<f<<" "<<line<<endl;
                    }
                    else {
                        cout<<"Function3:"<<f<<" "<<line<<endl;
                    }
                    lb=i+2;
                    i=i+1;


                }

            }


          }
          else if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/' || s[i]=='%' || s[i]=='=' || s[i]=='!' || s[i]=='>'){
                //cout<<s[lb]<<endl;
                //cout<<"+"<<i<<" "<<lb<<endl;
                string k=s.substr(lb,abs(i-lb));
                if(k[0]!=' ' && k.size()!=0){
                    i++;
                    while(s[i]==' ' || s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/' || s[i]=='%' || s[i]=='=' || s[i]=='!'){
                        i++;
                        lb=i;
                    }
                    if(keyword(k)){
                        cout<<"Keyword1: "<<k<<" "<<line<<endl;
                    }
                    else {
                        cout<<"ID1: "<<k<<" "<<line<<endl;
                    }
                    lb=i;
                }
                else {

                    lb=i+1;

                }

          }
           else if(s[i]==';' || s[i]=='\n'){
                string k=s.substr(lb,abs(i-lb));
                if(keyword(k)){
                    cout<<"Keyword;: "<<k<<" "<<line<<endl;
                }
                else {
                    cout<<"ID;: "<<k<<" "<<line<<endl;
                }
                lb=i+1;


          }
          else if(s[i]=='{' || s[i]=='}'  || s[i]==',' || s[i]=='>' || s[i]=='<'){
             continue;
        }
        else {

            cout<<s[i]<<" lexical error"<<endl;
        }

    }

}

 int main()
{
    ifstream file;
    file.open("simple_input1.txt");
    int line=0;
    string a;
    if (file.is_open())
    {
        while(getline(file,a))
        {

            lexeme(a,line);
            //operator_check(a,line);
            line++;

        }

    }
    else
    {
        cout<<"Enable to open the file"<<endl;
    }

}

