/*
                        
                        
*/
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
    assert(0<=a && a<=127);                                     //                                                                     
    assert(0<r && r<65536);
    assert(action == Encrypt || action == Decrypt);
//                 
    if (action == 0)                                            //                             
    {
        if (a>31)
            return (a-32 + (r % (128-32)) + (128-32)) % (128-32)+32;
        else
            return a;
    }
    else                                                        //                             
    {
        if (a>31)
            return (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;
        else
            return a;
    }
}

void test_rotate_char()
{
//                
    int r;                                                      //                        
    cin >> r;
    assert(0<r && r<65536);
//                 
    while (0<r && r<65536)
    {
        for (int i=0;i<128;i++)                                 //                                                                             
            cout << char(i) << '\t' << i << '\t' << rotate_char(char(i),r,Encrypt) << '\t' << rotate_char(rotate_char(char(i),r,Encrypt),r,Decrypt) << endl;
        cin >> r;                                               //             
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    string input_file;
    cout << "Input file: ";
    cin >> input_file;                                          //                            
    string output_file;
    cout << "Output file: ";
    cin >> output_file;                                         //                             
    infile.open(input_file.c_str());
    outfile.open(output_file.c_str());
    //                 
    if (!infile.is_open() && !outfile.is_open())                //                                          
    {
        cout << "Both files haven't opened. ";
        return 0;
    }
    else if (!infile.is_open())                                 //                                          
    {
        cout << "Input file hasn't opened. ";
        return 0;
    }
    else if (!outfile.is_open())                                //                                           
    {
        cout << "Output file hasn't opened. ";
        return 0;
    }
    return 1;
}

Action get_user_action ()
{//               
    assert ( true ) ;                                            //                              
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
    assert(infile.is_open() && outfile.is_open());
    assert(0 < initial_value && initial_value < 65536);
//                 
    initialise_pseudo_random(initial_value);                            //                       
    char c;
    while(infile)
    {
        initial_value = next_pseudo_random_number();                    //                                                                          
        infile.get(c);
        c = rotate_char(c,initial_value,action);
        outfile.put(c);                                                 //                         
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

