#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       
#include <ctype.h>

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
int inputR(){
    //                                                           

    //                                                                                                                                      
    cout << "Enter a value for r between 1 and 65536. If r is negative, this function will terminate, else this function is going to show you the encoding for all ASCII characters for that r. \n";
    int r = 0;
    cin >> r;
    while(!cin){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "That is not an integer. Enter an integer.";
        cin >> r;
    }
    cin.ignore(1000, '\n');
    return r;
}

//                                                      
string inputFName(){
    //                                                           

    //                                                                                                                                      
    cout << "Enter name of file to open, one that looks like ****.txt\n";
    string r = "";
    cin >> r;
    while(!cin){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "That is not a valid filename. Enter one that looks like ****.txt \n";
        cin >> r;
    }
    cin.ignore(1000, '\n');
    return r;
}

char rotate_char (char a, int r, Action action)
{   a = int(a);
//                                                                                                                                                                      
    assert(a >= 0 && a <= 128);

//                 
    if(action == 0){
        if(a < 32) return char(a); else return char((a-32 + (r %(128-32))) % (128-32)+32);
    } else if (action == 1){
        if(a < 32) return char(a); else return char((a-32 - (r %(128-32)) + (128-32)) % (128-32)+32);
    }
}

void test_rotate_char ()
{
//                                                 

//                 
    int r = inputR();
    if (r < 0){
        return;
    } else {
        cout << " R = " << r << endl;
        initialise_pseudo_random(r); //                                                                                                                              
        int y = next_pseudo_random_number();
        for(int i = 0; i <= 128; i++){ //                                                                                                                                                                                                                          
        char b = rotate_char(i, y, Encrypt);
            cout << "Character: " << char(i) << " ASCII: " << int(i) << " ASCII Rotated with key " << r << " " << b << " and decrypted: " << rotate_char(b, y, Decrypt) << "\n" << endl;
            y = next_pseudo_random_number();
        }
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
//                                                                                                                                 
    string inname, outname = "";
    inname = inputFName();
    outname = inputFName();
    infile.open(inname.c_str());
    outfile.open(outname.c_str());
    if(infile.is_open() && outfile.is_open()){ return true;}
    cout << " You are trying to open the same file as both input and output. Bad.";
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

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(infile && outfile && initial_value >= 0 && initial_value <= 65535 );

//                                                                         
    initialise_pseudo_random(initial_value);
    int y = next_pseudo_random_number();

    //                                                          
    /*
                  
               
                      
                                           
                       
                                        
     
    */
    //                                        
    char c;
    infile.get(c);
    while(infile){
        char b = rotate_char(c, y, action);
        outfile.put(b);
        y = next_pseudo_random_number();
        infile.get(c);
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

