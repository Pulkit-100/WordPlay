#include <iostream>
#include <cstdlib>
#include <cmath>
#include <windows.h>
#include <time.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;
struct leader
{
    char name[20];
    int marks;
    int perc;
    char category[20];
    char diff[20];
    //bool operator <(const struct leader &other)
    //{
    //    return perc<other.perc;
    //}
}temp2;
struct words
{
    char word[16];
}temp;
struct node
{
    char name[20];
    float perc;
    char category[20];
    char diff[20];
    struct node* next;
}*head;
int file_handle(char* w, char* file)
{
    FILE *P;
    if( access( file, F_OK ) != -1 )
    {
        P=fopen(file,"rb");
    }
    else
    {
        return(1);
    }
    while(fread(&temp,sizeof(temp),1,P)!=NULL)
    {
        //cout<<temp.word<<endl;
        if (strcmpi(temp.word,w)==0)
        {
            fclose(P);
            return(0);
        }
    }
    fclose(P);
    return(1);

}
void insert_word(char* w, char* file)
{
    FILE *P;
    struct words temp;
    /*P=fopen("Words2.txt","rb");
    cout<<"HELLO\n";
    fread(&temp,sizeof(temp),1,P);
    cout<<"HELL@";
    cout<<temp.word[0];
    cout<<temp.word[3];
    fclose(P);*/
    P=fopen(file,"ab");
    strcpy(temp.word,w);
    fwrite(&temp,sizeof(temp),1,P);
    fclose(P);
}
void display(vector < vector <char> > &V, int s)
{
    cout<<"\n\n\n\n\n\t\t   ";
    for(int i=0;i<s;i++)
    {
        cout<<i+1<<"  ";
    }
    cout<<"\n\t\t   ";
    for(int i=0;i<3*s;i++)
    {
        cout<<"-";
    }
    cout<<"\n";
    for(int i=0;i<s;i++)
    {
        cout<<"\t\t"<<i+1<<"| " ;
        for(int j=0;j<s;j++)
        {
            cout<<V[i][j]<<"  ";
        }
        cout<<"\n\n";
        Sleep(250);
    }
}
int check_word(string word)
{
    int x;
    x=word.size();
    for(int i=0;i<x;i++)
    {
        if (! isalpha(word[i]))
        {
            return 0;
        }

    }
    return 1;
}
int file_size(char* cat)
{
    int count=0;
    FILE* P;
    P=fopen(cat,"rb");
    while(fread(&temp,sizeof(temp),1,P)!=NULL)
    {
        count++;
    }
    fclose(P);
    return count;
}

struct words get_word(int ra, char* cat, int s, int f_size)
{
    FILE* P;
    P=fopen(cat,"rb");
    fseek(P,ra*sizeof(temp),SEEK_SET);
    fread(&temp,sizeof(temp),1,P);
    if (strlen(temp.word)>s-1)
    {
        fclose(P);
        return get_word(rand()%f_size,cat,s,f_size);
    }
    //cout<<"RANDOM WORD - "<<temp.word<<endl;
    fclose(P);
    return temp;
};
int check_vector(vector<string> &A,string word)
{
    //cout<<"Checkin\n";
    for(int i=0;i<A.size();i++)
    {
        if (A[i]==word)
        {
            return 0;
        }
    }
    return 1;
}
vector<string> assign(vector < vector <char> > &V,int s,char* cat)
{
    //display(V,s);
    time_t tim;
    tim=time(NULL)+2;
    int f_size=file_size(cat);
    cout<<"Words in file "<<cat<<" are "<<f_size<<endl;
    if (f_size<s)
    {
        cout<<"\n Atleast "<<s<<" words required in "<<cat<<endl;
        exit(0);
    }
    srand(time(NULL));
    int ra,i=0,p,a,b,c,cont;
    struct words W;
    vector<string> A;
    while(i<s)
    {
        if(time(NULL)>tim)
        {
            cout<<"REBUILDING THE GAME \n";
            vector<char> A1(s,'1');
            vector< vector <char> > V1;
            for(int pk=0;pk<s;pk++)
            {
                V1.push_back(A1);
            }
            V=V1;
            return assign(V,s,cat);
        }
        //display(V,s);
        ra=rand()%f_size;
        W=get_word(ra,cat,s,f_size);
        p=check_vector(A,W.word);
        if(p==0)
        {
            continue;
        }
        while(1)
        {
            if(time(NULL)>tim)
            {
                cout<<"REBUILDING THE GAME \n";
                vector<char> A1(s,'1');
                vector< vector <char> > V1;
                for(int pk=0;pk<s;pk++)
                {
                    V1.push_back(A1);
                }
                V=V1;
                return assign(V,s,cat);
            }
            else
            {
                //cout<<"\n Sahi hai \n";
            }
            a=rand()%2;
            //cout<<"random dimension "<<a<<endl;
            cont=0;
            if (a==0)
            {
                b=rand()%s;
                c=rand()%(s-strlen(W.word));
                for (int j=0;j<strlen(W.word);j++)
                {
                    if (V[b][c+j]!='1')
                    {
                        cont=0;
                        break;
                    }
                    cont=1;
                }
                if (cont==0)
                {
                    //cout<<"No Space in Horizontal \n";
                }
                if (cont==1)
                {
                    for(int j=0;j<strlen(W.word);j++)
                    {
                        V[b][c+j]=W.word[j];
                    }
                    break;
                }

            }
            else
            {
                c=rand()%s;
                b=rand()%(s-strlen(W.word));
                for(int j=0;j<strlen(W.word);j++)
                {
                    if(V[b+j][c]!='1')
                    {
                        cont=0;
                        break;
                    }
                    cont=1;
                }
                if(cont==0)
                {
                    //cout<<"No Space in Vertical \n";
                }
                if (cont==1)
                {
                    for(int j=0;j<strlen(W.word);j++)
                    {
                        V[b+j][c]=W.word[j];
                    }
                    break;
                }
            }
        }
        i++;
        A.push_back(W.word);
    }
    return A;
}
void random (vector < vector <char> > &V, int s)
{
    srand(time(NULL));
    for(int i=0;i<s;i++)
    {
        for(int j=0;j<s;j++)
        {
            if(V[i][j] =='1')
            {
                V[i][j]=char(65+rand()%26);
            }
        }
    }
}
void traverse(vector<string> A)
{
    cout<<"\t\tWords to be displayed \n\n";
    cout<<"\t\t";
    float pk;
    pk=ceil(A.size()/2);
    for(int i=0;i<A.size();i++)
    {
        if(i==pk)
        {
            cout<<"\n\t\t";
        }
        cout<<A[i]<<"  ";
    }
}
string fill(int p,int q,int r,int s, vector < vector <char> > &V)
{
    //cout<<"checkin\n";
    vector <char> X;
    if(p==r)
    {
        for(int i=q-1;i<s;i++)
        {
            //cout<<V[p-1][i]<<endl;
            X.push_back(V[p-1][i]);
        }
    }
    else if (q==s)
    {
        for(int i=p-1;i<r;i++)
        {
            X.push_back(V[i][q-1]);
        }
    }
    else
    {
        for(int i=p-1, j=q-1;i<p || j<q;i++,j++)
        {
            X.push_back(V[i][j]);
        }
    }
    return string(X.begin(),X.end());
}
int check(string x, vector <string> &A)
{
    for(int i=0;i<A.size();i++)
    {
        if(x==A[i])
        {
            A.erase(A.begin()+i);
            return 1;
        }
    }
    return 0;
}
void change(int p,int q,int r,int s, vector< vector< char > > &V)
{
    //cout<<"checkin 1"<<endl;
    if(p==r)
    {
        for(int i = q-1;i<s;i++)
        {
            //cout<<V[p-1][i]<<endl;
            V[p-1][i]=' ';
        }
    }
    if(q==s)
    {
        for(int i=p-1;i<r;i++)
        {
            //cout<<V[i][q-1]<<endl;
            V[i][q-1]=' ';
        }
    }
    //cout<<"Checkout 1"<<endl;
}
int input(vector < vector <char> > &V, queue <string> &Q, vector<string> &A)
{
    char chh,temp;
    int p,q,r,s;
    cout<<"\n\nEnter 1 if you found a word \n";
    cout<<"Enter 2 if you end up finding words \n";
    cout<<"\n Enter your choice ";
    cin >> chh;
    string x;
    int pk;
    switch(chh)
    {
        case '1':
            cout<<"\n\n Enter the coordinates in the form a,b:c,d  ";
            cin>>p>>temp>>q>>temp>>r>>temp>>s;
            //cout<<p<<" "<<q<<" "<<r<<" "<<s<<endl;
            if (p<1 || p>V.size() || q<1 || q>V.size() || r<1 || r>V.size() || s<1 || s>V.size())
            {
                cout<<"\n Out of bond Co-ordinates \n";
                return 0;
            }
            x=fill(p,q,r,s,V);  //Make word from co-ordinates
            cout<<x<<endl;
            //Sleep(2000);
            Q.push(x);  // Push the word in queue of entered words
            pk=check(x,A);  //Check if it is in list of words to be entered
            if (pk==1)
            {
                //cout<<"Word Mila \n";
                change(p,q,r,s,V);  // Delete the word from matrix
                return 1;
            }
            break;
        case '2':
            return -1;
            break;
        default:
            cout<<"Arghhh !! Wrong Input \n";
            return 0;
    }
    return 0;
}
void insert_list(char* name, char ch1, char ch2,int marks, float perc)
{
    struct node* temp=new(struct node);
    strcpy(temp->name,name);
    temp->perc=perc;
    char* pk;
    if(ch1=='1')
    {
        pk="Easy";
    }
    if (ch1=='2')
    {
        pk="Medium";
    }
    if (ch1=='3')
    {
        pk="Hard";
    }
    strcpy(temp->diff,pk);
    if (ch2=='1')
    {
        pk="Celebrities";
    }
    if (ch2=='2')
    {
        pk="Singers";
    }
    if (ch2=='3')
    {
        pk="Sports";
    }
    if (ch2=='4')
    {
        pk="Random";
    }
    strcpy(temp->category,pk);
    strcpy(temp2.name,temp->name);
    temp2.marks=marks;
    temp2.perc=perc;
    strcpy(temp2.category,temp->category);
    strcpy(temp2.diff,temp->diff);
    FILE* P;
    P=fopen("Leader.txt","ab");
    fwrite(&temp2,sizeof(temp2),1,P);
    fclose(P);
    if(head==NULL)
    {
        head=temp;
        head->next=NULL;
    }
    else
    {
        temp->next=head;
        head=temp;
    }
}
void display_list()
{
    struct node* temp= new struct node;
    if (head==NULL)
    {
        cout<<"\nNo history Available\n";
    }
    else
    {
        cout<<"History\n";
        temp=head;
        cout<<setw(12)<<"*NAME*"<<" "<<"*DIFFICULTY*"<<setw(12)<<"*CATEGORY*"<<" "<<"*PERCENTAGE*"<<endl;

        while(temp!=NULL)
        {
            cout<<setw(12)<<temp->name<<setw(12)<<temp->diff<<setw(12)<<temp->category<<setw(12)<<temp->perc<<endl;
            temp=temp->next;
        }
    }
}
void display_file()
{
    vector <struct leader> Lead;
    FILE* P;
    P=fopen("Leader.txt","rb");
    while(fread(&temp2,sizeof(temp2),1,P)!=NULL)
    {
        Lead.push_back(temp2);
    }
    fclose(P);
    int rankk=1;
    cout<<setw(12)<<"*RANK*"<<setw(12)<<"*NAME*"<<setw(12)<<"*MARKS*"<<" "<<"*PERCENTAGE*"<<setw(12)<<"*CATEGORY*"<<" "<<"*DIFFICULTY*"<<endl;

    for(int p=100;p>=0;p--)
    {
        for(int i=0;i<Lead.size();i++)
        {
            if (Lead[i].perc==p)
            {
                cout<<setw(12)<< rankk<<setw(12)<< Lead[i].name<<setw(12)<<Lead[i].marks<<setw(12)<<Lead[i].perc<<setw(12)<<Lead[i].category<<setw(12)<<Lead[i].diff<<endl;
                rankk++;
            }
        }
    }
}
void intro()
{
    cout<<"\n\n\n\n" ;
    cout<<"                                                                                        dddddddd\n" ;Sleep(250) ;
    cout<<"                                                                                        d::::::d                   lllllll\n" ;Sleep(250) ;
    cout<<"                                                                                        d::::::d                   l:::::l\n" ;Sleep(250) ;
    cout<<"                                                                                        d:::::d                    l:::::l\n" ;Sleep(250) ;
    cout<<"wwwwwww           wwwww           wwwwwww ooooooooooo   rrrrr   rrrrrrrrr       ddddddddd:::::dppppp   ppppppppp    l::::l                yyyyyyy          yyyyyyy\n" ;Sleep(250) ;
    cout<<"w:::::w         w:::::w         w:::::woo:::::::::::oo r::::rrr:::::::::r    dd::::::::::::::dp::::ppp:::::::::p    l::::l            a::::ay:::::y       y:::::y\n" ;Sleep(250) ;
    cout<<"   w:::::w     w:::::::::w     w:::::w o:::::ooooo:::::orr::::::rrrrr::::::rd:::::::ddddd:::::dpp::::::ppppp::::::p l::::l            a::::a y:::::y     y:::::y\n" ;Sleep(250) ;
    cout<<"    w:::::w   w:::::w:::::w   w:::::w  o::::o     o::::o r:::::r     r:::::rd::::::d    d:::::d p:::::p     p:::::p l::::l     aaaaaaa:::::a  y:::::y   y:::::y\n" ;Sleep(250) ;
    cout<<"     w:::::w w:::::w w:::::w w:::::w   o::::o     o::::o r:::::r     rrrrrrrd:::::d     d:::::d p:::::p     p:::::p l::::l   aa::::::::::::a   y:::::y y:::::y\n" ;Sleep(250) ;
    cout<<"      w:::::w:::::w   w:::::w:::::w    o::::o     o::::o r:::::r            d:::::d     d:::::d p:::::p     p:::::p l::::l  a::::aaaa::::::a    y:::::y:::::y\n" ;Sleep(250) ;
    cout<<"       w:::::::::w     w:::::::::w     o::::o     o::::o r:::::r            d:::::d     d:::::d p:::::p    p::::::p l::::l a::::a    a:::::a     y:::::::::y\n" ;Sleep(250) ;
    cout<<"        w:::::::w       w:::::::w      o:::::ooooo:::::o r:::::r            d::::::ddddd::::::ddp:::::ppppp:::::::pl::::::la::::a    a:::::a      y:::::::y\n" ;Sleep(250) ;
    cout<<"         w:::::w         w:::::w       o:::::::::::::::o r:::::r             d:::::::::::::::::dp::::::::::::::::p l::::::la:::::aaaa::::::a       y:::::y\n" ;Sleep(250) ;
    cout<<"          w:::w           w:::w         oo:::::::::::oo  r:::::r              d:::::::::ddd::::dp::::::::::::::pp  l::::::l a::::::::::aa:::a     y:::::y\n" ;Sleep(250) ;
    cout<<"           www             www            ooooooooooo    rrrrrrr               ddddddddd   dddddp::::::pppppppp    llllllll  aaaaaaaaaa  aaaa    y:::::y\n" ;Sleep(250) ;
    cout<<"                                                                                                p:::::p                                         y:::::y\n" ;Sleep(250) ;
    cout<<"                                                                                                p:::::p                                        y:::::y\n" ;Sleep(250) ;
    cout<<"                                                                                               ppppppppp \n" ;Sleep(250) ;

}
int main()
{
    system("color F0");
    intro();
    cout<<"\n\n";
    system("pause");
    system("cls");
    char ch;
    do
    {
        system("cls");

        cout<<"\n\n\n\n";
        cout<<"\t 1. Play Game \n";
        cout<<"\t 2. Add Words \n";
        cout<<"\t 3. History \n";
        cout<<"\t 4. LeaderBoard \n";
        cout<<"\t 0. Exit \n\n";
        cout<<"\t Enter Your Choice - ";
        cin>>ch;
        //string word;
        char name[20];
        vector <vector <char> > V;
        switch(ch)
        {
            case '0':
            {
                cout<<"\n\n Good Bye \n\n";
                Sleep(1000);
                system("cls");
                ch='0';
                break;
            }
            case '1':
            {
                system("cls");
                cout<<"\n\n\t Enter Your Name - ";
                cin>>name;
                system("cls");
                char chh1;
                cout<<"\n\n\t Choose The Difficulty Level ";
                cout<<"\n\n\n\n";
                cout<<"\t 1. Easy \n";
                cout<<"\t 2. Medium \n";
                cout<<"\t 3. Hard \n\n\n";
                cin>>chh1;
                system("cls");
                char chh2;
                cout<<"\n\n\t Choose Category ";
                cout<<"\n\n\n\n";
                cout<<"\t 1. Celebrities\n";
                cout<<"\t 2. Singers \n";
                cout<<"\t 3. Sports \n";
                cout<<"\t 4. Random \n\n\n";
                cin>>chh2;
                system("cls");
                int s;
                int timing;
                switch(chh1)
                {
                    case '1':
                    {


                        s=6;
                        timing=200;
                        vector <char> A(s,'1');
                        for(int i=0;i<s;i++)
                        {
                            V.push_back(A);
                        }
                        //cout<<V[0][0],V[1][1];
                        break;
                    }
                    case '2':
                    {
                        s=10;
                        timing=180;
                        vector <char> B(s,'1');
                        for(int i=0;i<s;i++)
                        {
                            V.push_back(B);
                        }
                        break;
                    }
                    case '3':
                    {
                        timing=150;
                        s=15;
                        vector <char> C(s,'1');
                        for(int i=0;i<s;i++)
                        {
                            V.push_back(C);
                        }
                        break;
                    }
                    default :
                        cout<<"Arghh !! Wrong Input ";
                        system("pause");
                        continue;

                }
                cout<<V.size();
                vector<string> A;
                char* cat;
                switch(chh2)
                {
                    case '1':
                        cat="Celebrities.txt";
                        break;
                    case '2':
                        cat="Singers.txt";
                        break;
                    case '3':
                        cat="Sports.txt";
                        break;
                    case '4':
                        cat="Random.txt";
                        break;
                    default:
                        cout<<"Arghh !! Wrong Input ";
                        system("pause");
                        continue;
                }
                //display(V,s);
                A=assign(V,V.size(),cat);  // Make 2-D Matrix by words
                //display(V,s);
                random(V,V.size());  // Assign random words to matrix
                system("cls");
                display(V,s);   // Display WORDPLAY
                cout<<"\n";
                traverse(A);  // Display A - words to be found
                cout<<"\n\n";
                //system("pause");
                int marks=0,pk;
                time_t over=time(NULL)+timing;
                queue <string> Q;
                while(1)
                {
                    cout<<"\nYou have "<<over-time(NULL)<<" seconds left to finish the game \n";
                    pk=input(V,Q,A);
                    system("cls");
                    if(pk==-1)
                    {
                        system("cls");
                        cout<<"\nYour Entered words are \n";
                        while(Q.size()!=0)
                        {
                            cout<<Q.front()<<endl;
                            Q.pop();
                        }
                        break;
                    }
                    if (time(NULL)>=over)
                    {
                        system("cls");
                        cout<<"\n\nOoops !! TIME UP \n\n";
                        cout<<"\nYour Entered words are \n";
                        while(Q.size()!=0)
                        {
                            cout<<Q.front()<<endl;
                            Q.pop();
                        }
                        break;
                    }
                    if(pk==1)
                    {
                        marks+=1;
                        cout<<marks<<" Words Found \n";
                    }
                    else
                    {
                        cout<<"\n Ooops !! This was not meant to be Searched \n\n";
                    }
                    display(V,s);
                    traverse(A);
                }
                float perc;
                perc=marks*100.0/s;
                cout<<"\n Total Marks--("<<marks<<"/"<<s<<")\n Percentage --- "<<perc<<"%"<<endl;
                insert_list(name,chh1,chh2,marks,perc);

                //Insert for History;
                //Insert for leaderboard;
                system("pause");
                system("cls");
                break;
            }
            case '2':
            {
                system("cls");
                char word[16];
                char *wor;
                char chh;
                char chh2;
                int p;
                char* file;
                do
                {
                    system("cls");
                    cout<<"\n\nChoose The Cagtegory \n\n";
                    cout<<"\t 1. Celebrities\n";
                    cout<<"\t 2. Singers \n";
                    cout<<"\t 3. Sports \n";
                    cout<<"\t 4. Random \n\n\n";
                    cin>>chh2;
                    switch(chh2)
                    {
                        case '1':
                            {
                                file="Celebrities.txt";
                                break;
                            }
                        case '2':
                            {
                                file="Singers.txt";
                                break;
                            }
                        case '3':
                            {
                                file="Sports.txt";
                                break;
                            }
                        case '4':
                            {
                                file="Random.txt";
                                break;
                            }
                        default:
                            cout<<"\n Arghh ! Wrong Input \n";
                            Sleep(500);
                            continue;
                    }
                    cout<<"\n\n Enter Word ";
                    cin>>word;
                    //transform(word.begin(), word.end(),word.begin(),::toupper);
                    //cout<<word;
                    wor=strupr(word);
                    p=check_word(wor);
                    if (p==0)
                    {
                        cout<<"\n\nSeriously ??? Is this a word !!! \n\n";
                    }
                    else
                    {
                        p=file_handle(wor,file);
                        if (p==1)
                        {
                            insert_word(wor,file);
                            cout<<"\n"<<wor<<" Word Accepted \n";
                        }
                        else
                        {
                            cout<<"\n Word Already exists in Database \n";
                        }
                    }
                    cout<<"\n Enter Y to enter more words ";
                    cin>>chh;

                }while(chh=='Y' or chh=='y');
                break;
            }
            case '3':
                system("cls");
                cout<<"\n\nHistory for only current session will be showed \n\n\n";
                display_list();
                cout<<"\n\n";
                system("pause");
                system("cls");
                break;
            case '4':
                system("cls");
                cout<<"\n\n";
                if (access("Leader.txt",F_OK)==-1)
                {
                    cout<<"\n\tLEADERBOARD NOT AVAILABE \n\n";
                    break;
                }
                cout<<"\n\t LEADERBOARD \n\n";
                display_file();
                system("pause");
                break;
            default:
                cout<<"Arghh ! Wrong Input !! ";
                Sleep(500);
                system("cls");
        }

    }while(ch!='0');

}
