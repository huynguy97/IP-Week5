#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

//                                              

using namespace std;

enum Action {Encrypt, Decrypt} ;

int seed = 0 ;
void initialise_pseudo_random (int r)
{
//                
    assert (r > 0 && r <= 65536);
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

char rotate_char (char a, int r, Action e)
{
//              
assert (r >=0);
//               
//                                                                                               
    int b;
        if (a < 32)
        b = a;
        //                                                                                                                                                                     
        //                                      
        else if (e == Encrypt)
        {
            b = (a - 32 + (r % (128-32)) + (128-32)) % (128-32)+32;
        }
        else if (e == Decrypt)
        {
            b = (a - 32 - (r % (128-32)) + (128-32))% (128-32)+32;
        }
return static_cast<char>(b);
}

void test_rotate_char ()
/*
                                                                                                         
                                                                                                                                                                 

                                                                           
                                                                                                            */

{
//              
//                                                                          
assert (true);
//                
//                                                                                                                      
//                                                                                                                           
//                                                                                                                       
    int r = 0;
//                                                                                         
    char a;
    while (r>=0)
    {
    cout << "Enter a number value//                                                                                                                             
//                                                                                                                                              
//                                                                                                                                      
//                                                                     
    cin >> r;
    cout << "Enter a single character" << endl;
    cin >> a;

        //                                                                                                                  
        //                                                                                                                      
        //                                                                                                                                                                                       

    cout << a << " " <<  static_cast<int>(a) << " " << static_cast<int>(rotate_char(a, r, Encrypt)) << " " << static_cast<int>(rotate_char (rotate_char (a, r, Encrypt), r, Decrypt)) << endl;
    //                                                       
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
/*
                                                                                                                               
                                                                     
                                                                                                             
                                                                                                      
                                                                   */

{
//              
//                                                                          
assert (true);
//               
//                                                                                                                     

//                                                                           
//                                                                   
string input_file;
cout << " Enter input file" << endl;

cin >> input_file;
string output_file;

cout << " Enter output file" << endl;
cin >> output_file;
//                                                                    
    if (input_file == output_file)
    {
        cout << "Error: Input file and Output file are identical" << endl;
        return false;
    }
//                                                      
infile.open(input_file.c_str());
    if (!infile.is_open())
    {
        cout << "Error: Input file has not opened" << endl;
        return false;
    }
//                                                      
outfile.open(output_file.c_str());
    if (!outfile.is_open())
    {
        cout << "Error: Output file has not opened" << endl;
        return false;
    }
else return (cout << " Input file and Output file are opened succesfully");
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
/*                                                                                                                          
                                                                                                                                        
                                             */

{
//              
//                                                                          
//               
//                                                                                                                                       
//                                                                                                                                

//                                                                            
//                                                                        
initialise_pseudo_random(initial_value);
int r;

//                                                                                              
//                                                                                                                              
//                                                                           
    char c;
    infile.get (c);
    while (infile)
    {
        r = next_pseudo_random_number();
        char b = rotate_char(c, r, action);
        outfile.put (b);
        infile.get (c);
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
//                                              

