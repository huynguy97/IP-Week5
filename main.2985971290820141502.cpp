#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

//                          
//                          
/*                                                                                 
                                                
*/
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

char rotate_char (char a, int r, Action e)
{
//                
    assert (r >= 0) ;
/*                 
                                                                                                

*/
    if (a < 32)
    {
        return a ;
    }
    else
    {
        if (e == Encrypt)
        {
            return (a-32+(r%(128-32))+(128-32))%(128-32)+32 ;
        }
        else
        {
            return (a-32-(r%(128-32))+(128-32))%(128-32)+32 ;
        }
    }
}

bool test_rotate_char ()
{
//                
    assert(true);

/*                 
                                                                                        
                                                                                                                              
                                                                                                                             
                                                        
*/

    int r ;
    cout << " Enter positive integer number: " ;
    cin >> r ;
    if (r < 0)
    {
        return false;
    }
    for (int a = 0; a < 126; a++)
    {
        cout << char(a) << endl ;
        cout << a << endl;
        cout << int(rotate_char(char(a), r, Encrypt)) << endl;
        cout << int(rotate_char (rotate_char (char(a), r, Encrypt), r, Decrypt)) << endl;
    }
        return true;
}

bool open_input_and_output_file (ifstream& input_file, ofstream& output_file)
{
//                
    assert (true) ;
/*                 
                                                                                     
                                                                     
                                                              
*/
    cout << "Name of file to open (read, no layout symbols): " ;
    string infile_name ;
    cin >> infile_name ;
    ifstream in_file (infile_name.c_str ()) ;
    cout << "Name of file to open (to write to, no layout symbols): " ;
    string outfile_name;
    cin >> outfile_name;
    ofstream out_file (outfile_name.c_str ()) ;

    if (infile_name == outfile_name)
    {
       cout << "False, these files have the same name"  << endl ;
    }
    else
    {
        if (input_file.is_open () && output_file.is_open ())
        {
            cout << "The files have successfully opened" ;
        }
        else
        {
            cout << "The files have not successfully opened" ;
        }
    }
}

Action get_user_action ()
{
//               
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
//                 
//                         
}

int main()
{
    bool b = true;
    while(b)
        {
            b = test_rotate_char ();
        }
    ifstream input_file;
    ofstream output_file;
    open_input_and_output_file(input_file, output_file);

/*                                             
                          
                          
                                                         
         
                                    
                             
                                                                 
                                                                                            
                                                       
                                                      
     
                                            
                   
     
                                                           
                                                          
                         
                          
                         
                          

                                    
                                   
         
                                    
                             
                                                                 
                                                                                            
                                                       
                                               
                                                                                                 
                   
     
              
*/
}

