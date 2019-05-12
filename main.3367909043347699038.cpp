#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <string>

using namespace std;
//                             

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
//                                                                            
char rotate_char (char a, int r, Action action)
{
//                 
   assert (a >= 0 && a  < 128);
/*                
                                                                           
*/
    if(action == Encrypt)
    {
        if (int(a) < 32)
        {
            return a;
        }
        else
        {
            return (a-32+(r%(128-32)))%(128-32)+32;
        }
    }
    else
    {
        if (int(a) < 32)
        {
            return a;
        }
        else
        {
            return (a-32-(r%(128-32))+(128-32))%(128-32)+32;
        }
    }
}
//                                                                                            
void test_rotate_char ()
{
//                
    assert(true); //                                                                                
//                 
    //                                        
    int r = 0;

    while (r >= 0)
    {
        cout << "Please enter an integer number below 65535, enter a negative number to terminate the function" << endl;
        cin >> r;
        if (r >= 0)
        {
            for (int a = 0; a < 128; a++)
            {
                cout << "the character : " << char(a) << " The Ascii code of a is : " << a << " The encryption : " << int(rotate_char(char(a),r,Encrypt)) << " The decryption : " << int(rotate_char(rotate_char(char(a),r,Encrypt),r,Decrypt)) << endl;
            }
        }

    }

}
//                                                                                                 
bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{

//                
    assert(true);
//                 
    //                                                                        
    string nameinput, nameoutput;
    cout << "Please enter the file name you want to open" << endl;
    cin >> nameinput;
    cout << "Please enter the file name you want to output to be called" << endl;
    cin >> nameoutput;
    if (nameinput == nameoutput)
    {
        cout << "Error: You named the input and output file the exact same" << endl;
        return false; //                                                       
    }
    infile.open(nameinput.c_str());
    outfile.open(nameoutput.c_str());
    if(infile && outfile)
        return true;
    return false;
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
//                                                                                                    
void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(infile.is_open() && outfile.is_open());
//                 
    //                                                                        
    char a,b;
    while(infile && outfile)
    {
        infile.get(a);
        b = rotate_char(a,next_pseudo_random_number(),action);
        outfile.put(b);
    }

}

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
    initialise_pseudo_random(INITIAL_VALUE); //                  
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
    //                                                             
    return 0 ;
}

