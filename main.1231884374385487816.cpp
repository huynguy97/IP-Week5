/*
                             
*/

#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

enum Action {Encrypt=1, Decrypt} ;

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
    assert(r > 0);
//                 
//                                      
    if (a >= 32){
        //           
        if (action == 1){
            return (a - 32 + (r%(128-32)))%(128-32)+32;
        }
        //           
        else{
            return (a - 32 - (r%(128-32))+(128-32))%(128-32)+32;
        }
    }
    //                                                        
    else{
        return a;
    }
}

void test_rotate_char ()
{
//                
    assert(true);
//                 
//                              
    int r = 1;
    //                                             
    while(r > 0){
        cout << " Please, enter a number r: ";
        cin >> r;
        char a = 'a';
        //                                      
        char b = rotate_char(a, r, Encrypt);
        char c = rotate_char(b, r, Decrypt);
        cout << "Character: " << a << " with ASCII-code " << int(a)
             << " encrypted with r: " << r << " is equal to " << int(b)
             << " and decryption gives the value " << int(c) << endl;
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile, string& input_file_name,
    string& output_file_name)
{
//                
    assert(true);
//                 
//                             

    cout << "Please, enter the name of the input file: ";
    cin >> input_file_name;
    cout << "Please, enter the name of the output file: ";
    cin >> output_file_name;

    //                                                      
    if (input_file_name == output_file_name){
        cout << "You entered the same file twice - program terminated." << endl;
        return false;
    }

    //                                           
    else {
        fstream input(input_file_name.c_str());
        fstream output(output_file_name.c_str());
        if (input.is_open() && output.is_open()){
            cout << "The files were succesfull opened." << endl;
            input.close();
            output.close();
            return true;
        }
        else {
            cout << "The files couldn't be opened." << endl;
            return false;
        }
    }
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
    assert (true) ;
//                 
//                                                       
    initialise_pseudo_random(initial_value);
    //                
    int random_number = next_pseudo_random_number();

    //                            
    char c;
    //                                                               
    char out;
    infile.get(c);
    while(infile){
        out = rotate_char (c, random_number, action);
        outfile.put(out);
        random_number = next_pseudo_random_number();
        infile.get(c);
    }
}

int main()
{
    const Action ACTION = get_user_action() ;
    ifstream input_file;
    ofstream output_file;
    string input_file_name;
    string output_file_name;

    if (!open_input_and_output_file (input_file,output_file, input_file_name, output_file_name))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }

    input_file.open(input_file_name.c_str());
    output_file.open(output_file_name.c_str());
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

