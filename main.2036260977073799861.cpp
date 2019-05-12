#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

enum Action {Encrypt, Decrypt} ;

/*                              
                                     

*/

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
    if (a < 32)
    {
        return a;
    }
    else
    {
        switch(action)
        {
        case Encrypt:
            return (a-32 + (r% (128-32)) +(128-32))%(128-32)+32;
        case Decrypt:
            return (a-32 - (r% (128-32)) +(128-32))%(128-32)+32;
        default:
            return -1;
        }
    }
}

int print_values ()
{
    int r;

    while (r>= 0)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        int a;
        a=0;
        do
        {
            printf("%c %d %d %d \n", a,a, rotate_char(a,r,Encrypt), rotate_char(rotate_char(a,r,Encrypt),r,Decrypt));
            a++;
        }
        while(a<=127);
        cout << "next value, for exit enter a negative integer";
        cin >> r;
    }

    return 0;
}

void test_rotate_char ()
{
//                

    int r;
    cout << "Enter random value between 0 and 65536";
    cin >> r;
    assert(r > 0 && r <= 65536);

    //                                                                                                         
    while (!cin)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "No, please enter an integer between 0 and 65536";
        cin >> r;
    }
    print_values();

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                

    cout << "Enter input file name (without spaces): ";
    string infilename;
    cin >> infilename;
    cout << "Enter output file name (without spaces): ";
    string outfilename;
    cin >> outfilename;

    assert(infilename != outfilename);

//                                                                                                   

   if(infilename != outfilename)
    {

    infile.open(infilename.c_str());
    outfile.open(outfilename.c_str());
        cout << "files have been opened successfully" << endl;
    }
    else
    {
        cout << "files have not opened successfully" << endl;
    }

    return 1;

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
    assert (infile.is_open() && outfile.is_open());
//                 
    int r = 0; //                                                                                                                   
    //                                
    char input_char;
    infile.get(input_char);
    while (infile)
    {
        outfile.put(rotate_char(input_char,r,Encrypt));
        infile.get(input_char);
        input_char++;
    }

    infile.close();
    outfile.close();

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

/*

 */

