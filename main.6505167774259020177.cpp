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

char rotate_char (char a, int r, Action e)
{
//                
    assert ( a >= 0 ) ;
//                 
//                 
    char b;
    if ( e == Encrypt )
    {
        if ( int (a)  < 32 )
            b = a ;
        else
            b = (a - 32 + (r % (128-32)) + (128-32)) % (128-32)+ 32 ;
    }
    if ( e == Decrypt )
    {
        if ( a < 32 )
            b = a ;
        else
            b = (a - 32 - (r % (128-32)) + (128-32)) % (128-32)+ 32 ;
    }
    return b ;
}

/*
      
                 
          
                                                            
                                 
                          
               
                                

      
      
                                                            
                                 
               
         
    
                                        
*/

void test_rotate_char (char a, int r, Action e)
{
//                
    assert ( r > -1 ) ;
//                 
//                                                                                                
    char b = rotate_char ( a, r, Encrypt ) ;
    cout << " Character a is "  << a << "\n And the ASCII-value for a is " << int (a) << endl;
    cout << " The ASCII code of rotate_char (a, r, Encrypt) " << int (b) << endl;
    b = rotate_char ( b, r, Decrypt ) ;
    cout << " The ASCII code of rotate_char (rotate_char (a, r, Encrypt), r, Decrypt) " << int (b)  << endl;
}

/*
                                                                     
 
                  
                   
                   
                                
                                 
                                
                
                        
                         
                      
                       
            
 
*/

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
    assert ( infile.is_open() ) ;
//                 
//                                                                                                                   
    initialise_pseudo_random ( initial_value ) ;
    char c;
    char b;
    int r = next_pseudo_random_number ();
    while ( infile )
    {
        infile.get(c) ;
        b = rotate_char(c, r, action) ;
        cout << b ;
        r = next_pseudo_random_number ();
        outfile.put(b) ;
    }
}

//       
/*
           
 
                  
              
           
                                                                                                       
              
                                   
                                      
                                
              
 
*/

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert ( true ) ;
//                 
//                                                                                         
    cout << " Give file names for input and output " << endl;
    string inname;
    string outname;
    cin >> inname >> outname ;
    if (inname == outname)
        return false;
    infile.open (inname.c_str());
    outfile.open (outname.c_str());
    return true;
}

int main()
{
    const Action ACTION = get_user_action() ;
    ifstream input_file ;
    ofstream output_file ;
    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }
    const int INITIAL_VALUE = initial_encryption_value () ;
    use_OTP (input_file, output_file, ACTION, INITIAL_VALUE);
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

