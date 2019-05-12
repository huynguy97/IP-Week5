//                    
//                      

#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

enum Action {Encrypt, Decrypt} ;

ifstream input_file  ;
ofstream output_file ;

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
assert(r>0&&r<65536);
int b;
if (action==Encrypt)
{

if (a<32)
{
    b=a;
  /*                                            */
}
if (a>=32)
{
    b=(a-32+(r%(128-32)))%(128-32)+32;
  /*                                           */
}
}

if (action==Decrypt)
{
if (a<32)
{
    b=a;
   /*                                           */
}
else b=(a-32-(r%(128-32))+(128-32))%(128-32)+32;
  /*                                            */
}
//                 
return b;
}

void test_rotate_char ()
{
//                
    /*           
                 
     
                              
             
                                 
            
                    
                                
     
    */
//                 

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                

//                                          
return infile.is_open() && outfile.is_open();
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

}

int main()
{

cout << "please enter the input file name:" ;
string input_file_name;
cin >> input_file_name;
input_file.open(input_file_name.c_str());
if (input_file.is_open())
{
cout << "give number r:" ;
    int r;
    int b;
    cin >> r;
    initialise_pseudo_random (r);
    if (r<0)
        terminate();
    next_pseudo_random_number();
    test_rotate_char();
    const Action ACTION = get_user_action() ;
    cout << "give letter a:" ;
    char a;
    cin >> a;
    rotate_char (a,r, ACTION);

    cout << b << endl;

}
else
{
    cout << input_file_name << "could not be opened\n";
    return 1;
}
cout << "please enter the output file name:" ;
string output_file_name;
cin >> output_file_name;
output_file.open(output_file_name.c_str());

if (input_file_name == output_file_name)
    terminate();

    const Action ACTION = get_user_action() ;

    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program does not work." << endl ;
        return -1 ;
    }
    else
    {
        cout << "files were opened succesfully" ;
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

