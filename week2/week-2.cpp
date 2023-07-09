#include<bits/stdc++.h>
#include"202114092_Akhon.cpp"
using namespace std;
string key[15] = {"if","else","if else","for","while","do","break","int","char","float","double","const","unsigned","return","include"};
void token(string lex,string type)
{
    SymbolInfo a(lex,type);
    SymbolTable b;
    b.Insert(a);
    b.display();
}
bool keyword(string k){
    for(int i=0;i<15;i++){
        if(key[i]==k){
            return true;
        }
    }
    return false;
}
bool number(string k){
    int t=0;
    for(int i=0;i<k.size();i++){
        if(k[i]<'0' || k[i]>'9'){
            t=1;
            break;
        }
    }
    if(t==1){
        return false;
    }
    else {
        return true;
    }
}
bool error(string k){
    if(k[0]>='0' && k[0]<='9'){
        return true;
    }
    return false;
}
int check(string s){
    //cout<<s<<endl;
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
    op['!']=true;

    int sz=s.size();
    int i=0;

    while(i<sz){
        // cout<<s[i]<<endl;
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
                token(s2,"OPERATOR");
                cout<<s2<<" Arithmetic_operator2 "<<line<<endl;
                out<<s2<<" Arithmetic_operator2 "<<line<<endl;

            }
            else if(b==1){
                token(s2,"OPERATOR");
                cout<<s2<<" Logical_operator2 "<<line<<endl;
                out<<s2<<" Logical_operator2 "<<line<<endl;

            }
            else if(b==2){
                token(s2,"OPERATOR");
                cout<<s2<<" Bitwise_operator2 "<<line<<endl;
                out<<s2<<" Bitwise_operator2 "<<line<<endl;

            }
            else if(b==3){
                token(s2,"OPERATOR");
                cout<<s2<<" Assignment_operator2 "<<line<<endl;
                out<<s2<<" Assignment_operator2 "<<line<<endl;

            }
        }
        else {
            if(a!=-1){
                if(a==0){
                    token(s1,"OPERATOR");
                    cout<<s1<<" Arithmetic_operator1 "<<line<<endl;
                    out<<s1<<" Arithmetic_operator1 "<<line<<endl;

                }
                else if(a==1){
                    token(s1,"OPERATOR");
                    cout<<s1<<" Logical_operator1 "<<line<<endl;
                    out<<s1<<" Logical_operator1 "<<line<<endl;

                }
                else if(a==2){
                    token(s1,"OPERATOR");
                    cout<<s1<<" Bitwise_operator1 "<<line<<endl;
                    out<<s1<<" Bitwise_operator1 "<<line<<endl;

                }
                else if(a==3){
                    token(s1,"OPERATOR");
                    cout<<s1<<" Assignment_operator1 "<<line<<endl;
                    out<<s1<<" Assignment_operator1 "<<line<<endl;

                }
            }
            if(c!=-1){
                if(c==0){
                    token(s3,"OPERATOR");
                cout<<s3<<" Arithmetic_operator3 "<<line<<endl;
                out<<s3<<" Arithmetic_operator3 "<<line<<endl;

                }
                else if(c==1){
                    token(s3,"OPERATOR");
                    cout<<s3<<" Logical_operator3 "<<line<<endl;
                    out<<s3<<" Logical_operator3 "<<line<<endl;

                }
                else if(c==2){
                    token(s3,"OPERATOR");
                    cout<<s3<<" Bitwise_operator3 "<<line<<endl;
                    out<<s3<<" Bitwise_operator3 "<<line<<endl;

                }
                else if(c==3){
                    token(s3,"OPERATOR");
                    cout<<s3<<" Assignment_operator3 "<<line<<endl;
                    out<<s3<<" Assignment_operator3 "<<line<<endl;

                }
            }
        }

    }

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
                token(k,"Literal");
                i=l+1;
                lb=i;
                queta=false;
                out.close();

            }
            i=i-1;
        }
        else if( (s[i]>='A' && s[i]<='Z') || (s[i]>='a' && s[i]<='z') ||(s[i]>='0' && s[i]<='9')|| s[i]=='_'){
            ofstream key("Keyword.txt",ios::app);
            ofstream func("Function.txt",ios::app);
            ofstream id("Identifier.txt",ios::app);

            if(s[i+1]==' ' || s[i+1]==')' || s[i+1]==',' ){
                int x=i;
                string k=s.substr(lb,abs(x-lb)+1);
                i++;
                while(s[i]==' ' || s[i]==')' || s[i]==';' || s[i]==','  ){

                    i=i+1;
                    lb=i;

                }
                if(keyword(k)){
                        cout<<"Keyword: "<<k<<" "<<line<<endl;
                        key<<"Keyword: "<<k<<" "<<line<<endl;
                        token(k,"Keyword");
                }
                else if(error(k)){
                    cout<<"Lexical error "<<k<<" "<<line<<endl;
                }
                else if(number(k)){
                    cout<<"Number: "<<k<<" "<<line<<endl;
                    id<<"Number: "<<k<<" "<<line<<endl;
                    token(k,"NUMBER");
                }
                else {
                    cout<<"ID: "<<k<<" "<<line<<endl;
                    id<<"ID: "<<k<<" "<<line<<endl;
                    token(k,"ID");

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
                        cout<<"Keyword:"<<f<<" "<<line<<endl;
                        key<<"Keyword:"<<f<<" "<<line<<endl;
                        token(f,"Keyword");
                    }
                    else {
                        cout<<"Function:"<<f<<" "<<line<<endl;
                        func<<"Function:"<<f<<" "<<line<<endl;
                        token(f,"Function");
                    }
                    lb=i+2;
                    i=i+1;

                }

            }
            key.close();
            func.close();
            id.close();


          }
          else if(s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/' || s[i]=='%' || s[i]=='=' || s[i]=='!' || s[i]=='>' || s[i]=='&'){
                ofstream key("Keyword.txt",ios::app);
                ofstream func("Function.txt",ios::app);
                ofstream id("Identifier.txt",ios::app);
                string k=s.substr(lb,abs(i-lb));
                if(k[0]!=' ' && k.size()!=0){
                    i++;
                    while(s[i]==' ' || s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/' || s[i]=='%' || s[i]=='=' || s[i]=='!'){
                        i++;
                        lb=i;
                    }
                    if(keyword(k)){
                        cout<<"Keyword: "<<k<<" "<<line<<endl;
                        key<<"Keyword: "<<k<<" "<<line<<endl;
                        token(k,"Keyword");
                    }
                    else if(error(k)){
                        cout<<"Lexical error "<<k<<" "<<line<<endl;
                    }
                    else if(number(k)){
                        cout<<"Number "<<k<<" "<<line<<endl;
                        id<<"Number: "<<k<<" "<<line<<endl;
                        token(k,"NUMBER");
                    }
                    else {
                        cout<<"ID: "<<k<<" "<<line<<endl;
                        id<<"ID: "<<k<<" "<<line<<endl;
                        token(k,"ID");

                    }
                        lb=i;
                        i=i-1;
                    }
                else{

                    lb=i+1;


                }
                key.close();
                func.close();
                id.close();

          }
           else if(s[i]==';' || s[i]=='\n'){
                string k=s.substr(lb,abs(i-lb));
                if(keyword(k)){
                    cout<<"Keyword: "<<k<<" "<<line<<endl;
                }
                else {
                    cout<<"ID: "<<k<<" "<<line<<endl;
                }
                lb=i+1;


          }
          else if(s[i]=='{' || s[i]=='}'  || s[i]==',' || s[i]=='>' || s[i]=='<'||s[i]==')'){
            lb=lb+1;
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
    file.open("sample_input1.txt");
    int line=0;
    string a;
    if (file.is_open())
    {
        while(getline(file,a))
        {

            lexeme(a,line);
            operator_check(a,line);
            line++;

        }

    }
    else
    {
        cout<<"Enable to open the file"<<endl;
    }

}
