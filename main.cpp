#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// First function to disply data in table format.
void display_table(short int arr[50][50])
{
    for(int j=0;j<50;j++)
    {
        cout<<"Person"<<j;
    }
    for(int s=0;s<50;s++)
    {
        cout<<"Person"<<s<<": ";
        for(int t=0;t<50;t++)
        {
            cout<<arr[s][t]<<"	";
        }
        cout<<"\n";
    }
}

// Second function to take input from the user.
void read_input(int *friend1, int *friend2)
{
    int frnd1, frnd2;
    cout<<"Enter two integers: ";
    cin>>frnd1>>frnd2;
    if(frnd1<=0 || frnd1>=50)
    {
        cout<<"Invalid input, number must be between 0 and 50.";
        exit(0);
    }
    if(frnd2<0 || frnd2>=50)
    {
        cout<<"Invalid input, number must be between 0 and 50.";
        exit(0);
    }
    if(frnd1==frnd2)
    {
        cout<<"We can not process common friends for same person.";
        exit(0);
    }
    *friend1 = frnd1;
    *friend2 = frnd2;
}

// Third function to find common friends
void find_common_frnds(int frnd1, int frnd2, short int arr[50][50])
{
    int friends_of_frnd1[50], friends_of_frnd2[50], count1=0, count2=0;
    int k=0;    // Indexing to store first person friends
    int l=0;    // Indexing to store second person friends
    for(int j=0; j<50; j++)
    {
        // Fetching friend list of first person
        if(frnd1 != j)
        {
            if(frnd2 != j)
                if(arr[frnd1][j]==1)
                {
                    count1++;
                    friends_of_frnd1[k]=j;
                    k++;
                }
        }
        // Fetching friend list of second person
        if(frnd2 != j)
        {
            if(frnd1 != j)
                if(arr[frnd2][j]==1)
                {
                    count2++;
                    friends_of_frnd2[l]=j;
                    l++;
                }
        }
    }
    // Matching friends list of both persons to find common friends
    int count_final=0;
    int loop_common_friends = 0;
    int common_friends[48];
    for (int i = 0; i < count1; i++)
    {
        for (int j = 0; j < count2; j++)
        {
            if(friends_of_frnd1[i]==friends_of_frnd2[j])
            {
                common_friends[loop_common_friends]=friends_of_frnd1[i];
                count_final++;
                loop_common_friends++;
            }
        }
    }
    if(count_final==0)
        cout<<"Person # "<<frnd1<<" and "<<frnd2<<" have no common friends."<<"\n";
    else
        cout<<"Person # "<<frnd1<<" and "<<frnd2<<" have "<<count_final<<" common friend(s) which is/are: ";

    for(int z=0; z<count_final; z++)
        cout<<common_friends[z]<<" ";
    cout<<"\n";
}
// Fourth function to take choice from the user
string choice()
{
    string ans;
    cout<<"Continue (Y/N)? "<<"\n";
    cin>>ans;
    if(ans.compare("Y")==0 || ans.compare("y")==0 || ans.compare("N")==0 || ans.compare("n")==0)
        return ans;
    else
    {
        cout<<"Invalid choice...!"<<"\n";
        exit(0);
    }
}
int main()
{
	int no_friends = 0;
	int no_lines = 0;
    int friend1, friend2;

	short int table[50][50]={0};
	string filename = "friends.txt";

	ifstream newfile;
	newfile.open(filename,ios::in); //open a file to perform read operation using file object
   if (newfile.is_open())	//checking whether the file is open
   {
    	string tp;
    	while(getline(newfile, tp))
	  	{
		  	no_lines += 1;
	        stringstream degree(tp);
		    int x = 0;
		    degree >> x;
	        if(no_lines==1)
			{
				no_friends = x;
	        	if(no_friends<2 or no_friends>50)
				{
					cout<<"No. of friends must be between 2 and 50 but given: "<<no_friends<<"\n";
					exit(0);
				}
			}
			if(no_lines>=3)
			{
				vector<int> vect;

			    stringstream ss(tp);

			    for (int i; ss >> i;) {
			        vect.push_back(i);
			        if (ss.peek() == ',' || ss.peek() ==' ')
			            ss.ignore();
			    }
				int frnd1, frnd2;
			    for (size_t i = 0; i < vect.size(); i++)
			    {
			    	if(i==0)
			    		frnd1=vect[i];
			    	else if(i==1)
			    	{
			    		frnd2=vect[i];
					}
			    	else
                    {
                        cout<<"Each line must contain only two friends.";
			    		exit(0);
                    }
				}
				if(frnd1==frnd2)
				{
                    cout<<"A person can not be friend of himself/herself.";
                    exit(0);
				}
				table[frnd1][frnd2]=1;
				table[frnd2][frnd1]=1;
			}
		}
      	newfile.close(); //close the file object.
      	display_table(table);
      	string ans;
      	while(1)
        {
            read_input(&friend1, &friend2);
            find_common_frnds(friend1, friend2, table);
            ans = choice();
            if(ans.compare("Y")==0 || ans.compare("y")==0)
                continue;
            else
                break;
      	}
      	cout<<"Terminated Successfully.";
   }
   else
   {
   	cout<<"File not found.";
   }
	return 0;
}
