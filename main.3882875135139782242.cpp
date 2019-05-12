#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;
/*
                                                         
                                          
                                                         
*/
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
    assert(r>0);
//                 
//                
    char b;
    if (action==0){
      if (a>=32)
        {
            b=(a-32 + (r % (128-32))) % (128-32)+32;
        }
      else
        {
            b=a;
        }
    }
    else
        {
            if(a>=32)
            {
                b=(a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;
            }
            else
            {
                b=a;
            }
        }
    return b;
}

void test_rotate_char ()
{
//                
    assert(true);
//                                                                                        
    int r;
    char b, b2;
    char a;
    if (r<0)
        cout<<"r is smaller than 0, program was terminated"<<endl;
    else
    while(r>=0)
    {
        cout<<"Enter a single char"<<endl;
        cin>>a;
        cout<<"Please enter 'r' value between 1 and 65535"<<endl;
        cin>>r;
        b= rotate_char(a,r,Encrypt);
        cout<<"Show encrypted value of a is "<<b<<endl;
        b2= rotate_char(rotate_char(a,r,Encrypt),r,Decrypt);
        cout<<"Show decrypted value of a is "<<b2<<endl;;
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
//                 
    string f;
    string g;
    cout << "Enter file name for input and output"<<endl;
    cin>>f;
    cin>>g;

    infile.open(f.c_str());

    outfile.open(g.c_str());
    if (g==f)
    {
      cout<<"ERROR!!!, File names are the same " <<endl;
      return false;
    }

    if (infile.is_open())
    {
      cout<<"Input file is open"<<endl;
    }
    else
    cout<<"Input file cannot be opened"<<endl;;
    if (outfile.is_open())
    cout<<"Output file is open"<<endl;
    else
    cout<<"Output file cannot be opened"<<endl;;

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
    assert((infile.is_open() && outfile.is_open())&& initial_value>=0 && initial_value<=65535);
//                                                                                                                                     
    char k;
    char g;
    initialise_pseudo_random(initial_value);
    infile.get(k);
    while(infile)
    {

        g=rotate_char(k,next_pseudo_random_number(),action);
        outfile.put(g);
        infile.get(k);
    }

}

int main()
{
    //                   
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

