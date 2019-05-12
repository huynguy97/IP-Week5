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
int b;
//                
assert(r >= 0 );
assert(r < 65536);
//                 
    int ascii = (int) a;

    if( ascii < 32){
        b = ascii;

    }
    else if ( action == 0){
        b = (a - 32 + ( r %(128-32))) %(128-32)+32;

    }
    else {
        b = (a - 32 - ( r %(128-32))+ (128-32)) %(128-32)+32;

    }
    return(char) b;
}

void test_rotate_char (int r)
{
//                

//                 
while(r > 0){
    cout << "Input a random number to continue and a negative number to stop: \n";
    cin >> r;

    for(int i = 0; i < 128; i++){

    char b = char (i);
    cout << b << " " ;
    cout << i << " " ;
    cout << (int) rotate_char(b, r, Encrypt) << " ";
    cout << (int) rotate_char( rotate_char(b, r, Encrypt), r, Decrypt);
    cout << "\n";

    //                                                                                      

    }

}
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{

//                
    assert(true);
    //                                           

//                 
    cout << "What name do you want your input and output file to have?\n";
    string inputname, outputname;
    cin >> inputname;
    cin >> outputname;
    if(inputname == outputname){
        cout << "ERROR: The names you entered are the same!";
        return false;
    }
    infile.open(inputname.c_str());
    outfile.open(outputname.c_str());
    if (infile.is_open() && outfile.is_open()){
        cout << "Opening the files was a success! \n";
    }
    return infile.is_open() && outfile.is_open();

}

Action get_user_action ()
{//               
    assert ( true ) ;
/*                 
                                                                                              
*/
    cout << "Do you want to encrypt the file? (y: for yes i want to encrypt/n: for no i want to decrypt): " ;
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
    cout << "The number you entered was: " << initial_value << "\n";
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
assert (infile.is_open() && outfile.is_open());
//                 

initialise_pseudo_random(initial_value);
int q ;
char c;
while(infile.get(c)){
    q = next_pseudo_random_number();
    outfile.put(rotate_char(c, q, action));
}

}

int main()
{
    /*
                  
              
                                                                 
                 
                
                                                                  
                  
*/
    const Action ACTION = get_user_action() ;
    //                                   

    //          
    //                        

    ifstream input_file;
    ofstream output_file;

    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }
    const int INITIAL_VALUE = initial_encryption_value () ;
    initialise_pseudo_random(INITIAL_VALUE);
    //                
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

