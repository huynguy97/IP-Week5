#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

enum Action {Encrypt, Decrypt} ;

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
    assert(0<=a && a<128);
//                 
//                                         
    if (a<32)
    {
        return a;
    }
    else if(action==Encrypt)
    {
        return (a-32 + (r % (128-32)) + (128-32)) % (128-32)+32 ;
    }
    else if(action==Decrypt)
    {
        return (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32 ;
    }

}

void test_rotate_char ()
{
//                
assert(true);
//                 
//                                 
cout<<"Give me a random number between 0 and  65536"<<endl;
int r;
cin>>r;
while(!cin){
    cin.clear();
    cin.ignore(1000, '\n');
    cout<<"Not an integer. Give me a random number between 0 and  65536"<<endl;
    cin>>r;
}
cin.ignore( 1000, '\n');

for(int i=0; i<128; i++)
    {
    cout<<(char)i<<", ";
    cout<<i<<", ";
    cout<<rotate_char ((char)i, r, Encrypt)<<", ";
    cout<<rotate_char (rotate_char((char)i, r, Encrypt), r, Decrypt)<<endl;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
assert(true);
//                 
string a;
string b;
cout<<"what is the input name?"<<endl;
cin>>a;
cout<<"what is the output name?"<<endl;
cin>>b;
if(a==b){
    cout<<"error, the file are the same"<<endl;
    return false;
}
else {
    infile.open(a.c_str() );
    outfile.open(b.c_str() );
    return true;
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

//                 

    initialise_pseudo_random(initial_value);

    char a;
    while(infile)
    {
        infile.get(a);
        outfile.put(rotate_char(a, next_pseudo_random_number(), action));
    }

}

int main()
{
    test_rotate_char ();
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

