#include <iostream>
#include <vector>
#include<string>
#include<iomanip>
using namespace std;

void getAllocation(vector<vector<int>>&allocation,int,int);
void getMax(vector<vector<int>>&allocation,int,int);
void getAvailable(vector<int>&available,int);
void getNeed(vector<vector<int>>&need,vector<vector<int>>&max,vector<vector<int>>&allocation,int,int);
void printMatrix(vector<vector<int>>&,int,int);
void initalize(vector<int>&finish,int value,int n);
void safeCheck(vector<int>&finish,vector<vector<int>>&need,vector<vector<int>>&allocation,vector<int>&available,int process_no);
int choose();
void requestAlgorithm(vector<int>finish,vector<vector<int>>allocation,vector<vector<int>>need,vector<int>available);
int main()
{
    
    int again = 1;
    do{
    int n,m;
    
    vector<vector<int>>allocation;
    vector<vector<int>>max;
    vector<int>available;
    vector<vector<int>>need;
    vector<int>finish;
    
    cout<<"Enter Number of Processes: ";
    cin>>n;
    while(n <= 0)
    {
        cout<<"Number of Processes must be greater than 0";
        cout<<"\nEnter Number of Processes: ";
        cin>>n;
    }
    cout<<"Enter number of resources types: ";
    cin>>m;
    while(m <= 0)
    {
        cout<<"Number of resources types must be greater than 0";
        cout<<"\nEnter Number of resources types: ";
        cin>>m;
    }
    getAllocation(allocation,n,m);
    getMax(max,n,m);
    getAvailable(available,m);
    getNeed(need,max,allocation,n,m);
    printMatrix(need,n,m);
    int choice = choose();
    initalize(finish,0,n);

    if(choice == 0)
    {
    safeCheck(finish,need,allocation,available,-1);
    }
    else if(choice == 1)
    {
      int another_try = 1;
      while(another_try)
      {
       requestAlgorithm(finish,allocation,need,available); 
       cout<<"Do you want to check another immediate request?"<<endl<<"0-No\n1-Yes"<<endl;
       cin>>another_try;
       cout<<endl;
      }
    }
    else if(choice == 2)
    {
        return 0;
    }
    else
    {
        cout<<"Please Enter valid input: ";
    }
    cout<<"0-Main Menu\n1-Exit"<<endl;
    cin>>again;
    cout<<endl<<endl;
    }while(!again);


   
   
    return 0;
}
 
  
  
  
   
void getAllocation(vector<vector<int>>&allocation,int n,int m){
    int num;
    int check = 0;
    vector<int>help;
    for(int i = 0;i < n;i++)
    {
        do
        {
         check = 0;
         help.clear();
         cout<<"Enter P"+to_string(i)+" resources allocation separated by space: ";
        for(int j = 0;j < m;j++)
         {
            cin>>num;
            help.push_back(num);
         }
         for(int k = 0;k < m;k++)
         {
             if(help[k] < 0)
             {
                 check = 1;
                 cout<<"Negative Numbers can't be entered\n";
                 break;
             }
         }
        }while(check);
        allocation.push_back(help);
    }
}

void getMax(vector<vector<int>>&max,int n,int m){
    int num;
    int check = 0;
    vector<int>help;
    for(int i = 0;i < n;i++)
    {
      do
      {
        check = 0;
        help.clear();

        cout<<"Enter P"+to_string(i)+" max resources separated by space: ";
        for(int j = 0;j < m;j++)
        {
            cin>>num;
            help.push_back(num);
        }
        for(int k = 0;k < m;k++)
        {
            if(help[k] < 0)
            {
                cout<<"Negative Numbers can't be entered"<<endl;
                check = 1;
                break;
            }
        }
      }while(check);
       max.push_back(help);
    }
}

void getAvailable(vector<int>&available,int m){
    int num;
    int check = 0;
    do{
        available.clear();
        check = 0;
        cout<<"Enter Number of available resources of each type separated by space: ";
        for(int j = 0;j < m;j++)
        {
            cin>>num;
            available.push_back(num);
        }
        for(int k = 0;k < m;k++)
        {
            if(available[k] < 0)
            {
                cout<<"Negative Numbers can't be entered"<<endl;
                check = 1;
            }
        }
    }while(check);
}


void getNeed(vector<vector<int>>&need,vector<vector<int>>&max,vector<vector<int>>&allocation,int n,int m){
    int num;
    vector<int>help;
    for(int i = 0;i < n;i++)
    {
        need.push_back(help);
        for(int j = 0;j < m;j++)
        {
            need[i].push_back(max[i][j] - allocation[i][j]);
        }
        cout<<endl;
    }
}

void printMatrix(vector<vector<int>>&need,int n,int m)
{
    cout<<endl<<endl<<"************Need Matrix************"<<endl;
    for(int i = 0;i < m;i++)
    {
        cout<<setw(8)<<"R" + to_string(i)<<" ";
    }
    cout<<endl;
    for(int i = 0;i < n;i++)
    {
      cout<<"P"+to_string(i);
        for(int j = 0;j < m;j++)
        {
            if(j == 0)
            cout<<setw(6)<<need[i][j]<<" ";
            else
            cout<<setw(8)<<need[i][j]<<" ";
        }
        cout<<endl;
    }
}
void initalize(vector<int>&finish,int value,int n)
{
    for(int i = 0;i < n;i++)
    {
        finish.push_back(0);
    }
}
void safeCheck(vector<int>&finish,vector<vector<int>>&need,vector<vector<int>>&allocation,vector<int>&available,int process_no){
    bool flag = 0;
    vector<int>work;
    vector<int>safe_state_sequence;
    int counter = 0;
    int finished = 0,i = 0;
    
   
    for(int i = 0;i < available.size();i++)
    {
        work.push_back(available[i]);
    }
    while(1)
    {
      for(int i = 0;i < finish.size();i++)
       {
         for(int j = 0;j < available.size();j++)
         {
            if(need[i][j] > work[j])
            {
                flag = 1;
                break;
            }
         }
          if(flag == 0 && finish[i] == 0)
            {
                finish[i] = true;
                for(int k = 0;k < available.size();k++)
                   {
                       work[k] = work[k] + allocation[i][k];
                   }
                safe_state_sequence.push_back(i);
                counter++;
            }
            flag = 0;
       }
       if(counter == finish.size())
       { if(process_no == -1)
         {
            cout<<"Yes, Safe state <";
             i = 0;   
           while(i < counter-1)
            {
              cout<<"P"+to_string(safe_state_sequence[i])<<",";
               i++;
            }   
            cout<<"P"+to_string(safe_state_sequence[counter-1])+">"<<endl<<endl;
             return;
         }
         else
         {
             cout<<"Yes request can be granted with safe state , Safe state <P"+to_string(process_no)+"req,";
             for(i = 0;i < counter-1;i++)
             {
                 cout<<"P"+to_string(safe_state_sequence[i])+",";
             }
             cout<<"P"+to_string(safe_state_sequence[counter-1])+">"<<endl<<endl;
             return;
         }
       }
       if(finished == counter)
       {
          if(process_no == -1)
          {
           cout<<"No safe state"<<endl<<endl;
           return;
          }
          else
          {
              cout<<"No,request can't be granted with safe state"<<endl<<endl;
              return;
          }
       }
       finished = counter;
    }
}
 
int choose()
{
    cout<<"0-Check if the system in safe state"<<endl;
    cout<<"1-Check if an immediate request can be granted"<<endl;
    cout<<"2-Exit";
    cout<<endl;
    int choice;
    cin>>choice;
    return choice;
}
void requestAlgorithm(vector<int>finish,vector<vector<int>>allocation,vector<vector<int>>need,vector<int>available)
{
    vector<int>instances;
    int process_no;
    cout<<"Enter the number of process that wants to request: ";
    cin>>process_no;
    cout<<"Enter the number of instances of each resource separated by space: ";
    for(int i = 0;i < available.size();i++)
    {
        int resource;
        cin>>resource;
        instances.push_back(resource);
    }
    
    for(int i = 0;i < available.size();i++)
    {
        if(instances[i] > need[process_no][i] || instances[i] > available[i])
        {
            cout<<"No,Request can't be granted with safe state"<<endl<<endl;
            return;
        }
    }
    for(int i = 0;i < available.size();i++)
    {
        available[i] -= instances[i];
        allocation[process_no][i] += instances[i];
        need[process_no][i] -= instances[i];
    }
    safeCheck(finish,need,allocation,available,process_no);
}

