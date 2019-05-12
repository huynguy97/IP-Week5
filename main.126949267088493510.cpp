#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

enum Action {Encrypt, Decrypt} ;
int neg;
char b;
int seed = 0 ;
void initialise_pseudo_random (int r)
{
//                
    assert (r > 0 && r <= 65536) ;
/*                 
                     
*/
    seed = r ;
}

int next_pseudo_random_number ()
{
//                
    assert (seed > 0 && seed <= 65536) ;
/*                 
                                                                                            
*/
    const int seed75 = seed * 75 ;
    int next = (seed75 & 65535) - (seed75 >> 16) ;
    if (next < 0)
        next += 65537 ;
    seed = next ;
    return next ;
}

char rotate_char (char a, int r, Action action)
{
//                
    assert(r>=0);

//                 
    if (a<32)
    {
        return a;
    }
    else
    {
        if (Action(action)==Encrypt)
        {
            neg=1;
        }
        else
        {
            neg=-1;
        }
        b=(a-32 + neg*(r%(128-32))+(128-32))%(128-32)+32;
        return b;
    }
}

void test_rotate_char ()
{
//                
    assert(true);

//                 
    int r_user;
    cout<<"please enter a non-negative value for r...";
    cin>> r_user;
    if (r_user<0)
    {
        return;
    }
    else
    {
        int i=0;
        while(i<=128)
        {
            cout<< char(i)<<"\t The Ascii code is: "<< i << "\t The ascii code of rotate)char is: "<< rotate_char(char(i), r_user, Encrypt)<< "\t The ascii code of the check of rotate_char is: " << rotate_char(rotate_char(char(i),r_user,Encrypt),r_user, Decrypt)<<endl;
            i++;
        }
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);

//                 
    string filepath_in;
    string filepath_out;
    cout<<"please enter a file name for the first file(write it like example.txt): "<< endl;
    cin >> filepath_in;
    cout<< "please enter a file name for where the output needs to go(write it like example.txt): "<< endl;
    cin >> filepath_out;

    infile.open(filepath_in.c_str());
    outfile.open(filepath_out.c_str());

    if(filepath_in==filepath_out)
    {
        return false;
    }
    else
    {
        if(infile.is_open() && outfile.is_open())
        {
            return true;
        }
        else
        {
            return false;
        }
    }

}

Action get_user_action ()
{//               
    assert ( true ) ;
/*                 
                                                                                              
*/
    cout << "Do you want to encrypt the file? (y/n): " ;
    string answer ;
    cin  >> answer ;
    if (answer == "y")
        return Encrypt;
    else
        return Decrypt;
}

int initial_encryption_value ()
{//              
    assert (true) ;
/*                 
                                                          
*/
    int initial_value = -1 ;
    while (initial_value < 0 || initial_value > 65535)
    {
        cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536)" << endl ;
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(infile && outfile);
//                 

initialise_pseudo_random(initial_value);

char data;

while(infile)
{
    infile.get(data);
    initial_value=next_pseudo_random_number();
    outfile.put(rotate_char(data, initial_value, action));
}
}

/*                                               
                                                 
                                                 
                                               */

int main()
{
    const Action ACTION = get_user_action() ;
    ifstream input_file  ;
    ofstream output_file ;
    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }
    const int INITIAL_VALUE = initial_encryption_value () ;
    use_OTP (input_file,output_file,ACTION,INITIAL_VALUE);
    input_file.clear () ;
    output_file.clear () ;
    input_file.close () ;
    output_file.close () ;

    if (!input_file || !output_file)
    {
        cout << "Not all files were closed succesfully. The output might be incorrect." << endl ;
        return -1 ;
    }
    return 0 ;

}

