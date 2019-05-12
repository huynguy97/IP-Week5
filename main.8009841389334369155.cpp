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
//                        
//                            

//      

char rotate_char (char a, int r, Action action)
{
//                
    assert (a>=0 && a<128) ;
/*                 
                                                
                                                         
*/
    if (a<32)
        return a ; //                                                                                         
    else
    {
        switch(action)
        {
        case Encrypt:
            return (a-32+(r%(128-32)))%(128-32)+32 ; //                                  
        case Decrypt:
            return (a-32-(r%(128-32))+(128-32))%(128-32)+32 ; //                                  
        }
    }

}

void test_rotate_char ()
{
//                
    assert (true) ; //             
/*                 
                                                                                                          
                                                                             
*/
    while (true) //                                                                                            
    {
        int r ;
        cout << "Enter a value for r: \n" ;
        cin >> r ;
        assert (r > 0 && r <= 65536) ; //                                       
        int i = 0 ;
        while (i < 128) //                             
        {
            char a = i ;
            int int_a_encrypt = rotate_char(a, r, Encrypt) ;
            int int_a_encrypt_decrypt = rotate_char(rotate_char(a, r, Encrypt), r, Decrypt) ;
            cout << a << "\t" << i << "\t" << int_a_encrypt << "\t" << int_a_encrypt_decrypt << endl;
            i++ ;
        }
    }
}
/*
          
 
                        
 
                                              
*/

//      

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(infile && outfile) ;
/*                 
                                                                                              
                                          
*/
    string first_filename ;
    string second_filename ;
    cout << "Enter a name for the input file (Note that file names may not contain layout symbols.): \n" ;
    cin >> first_filename ;
    cout << "Enter another name for the output file (Note that file names may not contain layout symbols.): \n" ;
    cin >> second_filename ;
    if (first_filename == second_filename) //                           
    {
        cout << "ERROR: names for input and output file are the same. \n" ; //                             
        assert(false) ; //                                    
    }
    infile.open(first_filename.c_str()) ;
    outfile.open(second_filename.c_str()) ;
    return (infile && outfile) ; //                                                                         
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

//      

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert (infile && outfile) ;
/*                 
                                                                              
*/
    initialise_pseudo_random(initial_value) ;
    char c ;
    infile.get(c) ;
    while (infile) //                                          
    {
        int r ;
        r = next_pseudo_random_number() ;
        outfile.put(rotate_char(c, r, action)) ; //                                                 
        infile.get(c) ; //                                     
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

