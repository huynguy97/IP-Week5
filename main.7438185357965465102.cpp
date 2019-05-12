#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

//                                              
//                                             

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
    assert (r > 0 && (a>0 || a < 128));
    /*                 
                                                           
    */
    if (a < 32)
    {
        return a;
    }
    switch(action)
    {
    case Encrypt:
        return ((a-32+(r%(128-32))+(128-32))%(128-32)+32);
    case Decrypt:
        return ((a-32-(r%(128-32))+(128-32))%(128-32)+32);
    }
}

void test_rotate_char ()
{
//                
    assert (true);
//                                                                                                                                                             
    int r = 1;
    while (r > 0)
    {
        cout << "Give a symbol to test" << endl;
        char a;
        cin >> a;
        cout << "letter \t" << a << '\t' << int (a)  << '\t'  << int (rotate_char(a, r, Encrypt)) << '\t' << int(rotate_char(rotate_char(a, r, Encrypt), r, Decrypt)) << endl;
        cout << "Give an r, negative will stop the program" << endl;
        cin >> r;
    }

}

void ask_filenames (string& inputfile, string&outputfile)
{
    //               
    assert (true);
    //                                                          
    cout << "Enter the inputfile(without spaces): " ;
    cin >> inputfile;
    cout << "Enter a name for the outputfile: ";
    cin >> outputfile;
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert (!(infile.is_open() && outfile.is_open()));
//                                                                                                       
    string inputfile = "1", outputfile = "2";
    ask_filenames (inputfile, outputfile);
    if (inputfile == outputfile)
    {
        cout << "Error, inputfile is the same as outputfile";
        return -1;
    }
    infile.open (inputfile.c_str());
    outfile.open (outputfile.c_str());
    if (infile && outfile)
    {
        return true;
    }
    else
    {
        return false;
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
{
    //              
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
    assert (infile.is_open() && outfile.is_open() && (action == 1 || action == 2) && initial_value > 0 || initial_value < 65536);
//                                                                                                                                                      
    initialise_pseudo_random(initial_value);
    char c;
    infile.get (c);
    while (infile)
    {
        int r = next_pseudo_random_number();
        outfile.put(rotate_char(c, r, action));
        cout << rotate_char(c, r, action);
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

