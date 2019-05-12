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
    int start ;
    if(action == Encrypt)
    {
        if (a >= 32)
        {
            start = ((int)a-32 + (r % (128-32)) + (128-32)) % (128-32)+32 ;
        }
        else
        {
        int start = (int)a ;
        }
    }
    else if (action == Decrypt)
    {
     if (a >= 32)
        {
            start = ((int)a-32 - (r % (128-32)) + (128-32)) % (128-32)+32 ;
        }
        else
        {
        int start = (int)a ;
        }
    }
    return (char)start;
//                                                                                                          

}

void test_rotate_char ()
{
//                
    assert(true);
    int something = 1;
    while (0 < something)
    {
        cout << "Please enter a valid seed \n" ;
        cin >> something;
        initialise_pseudo_random(something);
       for(char letter= 32; letter < 'z' ; letter++)
       {
           int r = next_pseudo_random_number();
           cout << letter <<"\t\t" << rotate_char (letter, r , Encrypt)<< "\t\t" << rotate_char (rotate_char (letter, r , Encrypt), r, Decrypt) << "\n";
       }
    }
    cout << "I thought I said a valid seed \n" ;
//                                                                                                                                                          
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
//                                                                                       

    if (infile && outfile)
    {
        cout << "Both files have been opened! \n";
        return true;
    }
    else
    {
        return false;
    }
}

Action get_user_action ()
{//               
    assert ( true ) ;
/*                 
                                                                                              
*/
    cout << "Do you want to encrypt (e) or decrypt (d) the file? (e/d): " ;
    string answer ;
    cin  >> answer ;
    if (answer == "e")
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
    assert(open_input_and_output_file);
//                                                                                                                                                                             
    initialise_pseudo_random(initial_value);
    char character;
    infile.get(character);

    while(!infile.eof())
    {
        int r = next_pseudo_random_number();
        if(character == '\n')
        {
            outfile.put('\n');
            infile.get(character);
        }
        else
        {
            outfile.put(rotate_char(character,r,action));
            infile.get(character);
        }
    }
}

int main()
{
    //                   

    const Action ACTION = get_user_action() ;

    cout << "Enter the input file name (without white spaces): ";
    string inputfilename;
    cin >> inputfilename;

    cout << "Enter the output file name (without white spaces): ";
    string outputfilename;
    cin >> outputfilename;

    ifstream input_file;
    ofstream output_file;

    if(inputfilename != outputfilename)
    {
        input_file.open(inputfilename.c_str());
        output_file.open(outputfilename.c_str());

    }
    else
    {
        cout << "Error: the filenames are identical.";
        return -1;
    }

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

