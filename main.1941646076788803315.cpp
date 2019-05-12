#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

//                                                               
//                                                       

enum Action {Encrypt=1, Decrypt=2} ;

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
assert(true);
//                 
//                                                      
if (a< 32)
    return a;
else
    { switch(action)
        {case 1:
            {return ((a-32+(r%(128-32)))%(128-32)+32);
            break; }

        case 2:
           {
               return (a-32-(r%(128-32))+(128-32))%(128-32)+32;
               break;
           }

        }
    }
}

void test_rotate_char (int r, char a)
{
//                
assert(true);
//                                                                                   
while (r >= 0)
{
    a=0;
    cout<< "enter a positive integer for r" << endl ;
    cin>> r;
 if (r<0)
   {
    cout<< "r should be a positive integer" ;
    return;
   }
 else {
        while (a<128 && a>=0)
        {
            cout<< "a: " << a << endl ;
            cout<< "the ASCII of a " << int(a) << endl ;
            cout<< "a in ASCII encryption = b " << static_cast<int>((rotate_char(a, r, Encrypt))) << endl;
            cout << "b decrypted " << static_cast<int>((rotate_char(rotate_char(a, r, Encrypt), r, Decrypt))) << endl << endl ;
            a++;
        }
    }
}
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
assert(true);
//                                                                                                                                  
string infilename;
cout<< "enter a input file name " << endl;
cin >> infilename;

string outfilename;
cout<< "enter a output file name " << endl;
cin>> outfilename;

if(infilename == outfilename)
    {
        cout<< "the file names are identical" << endl;
        return false;
    }
else {

        outfile.open(outfilename.c_str());
        infile.open(infilename.c_str());

        if(infile.is_open() && outfile.is_open())
        {
            cout<< "files opened succesfully ";
            return true;
        }
        else
        {
            cout<< "files not opened succesfully";
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
assert(infile.is_open() && outfile.is_open());
//                                                                                                                      
char c;
infile.get(c);
initialise_pseudo_random(initial_value);
while (infile)
    {
    outfile.put(rotate_char(c, next_pseudo_random_number(), action));
    infile.get(c);
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

