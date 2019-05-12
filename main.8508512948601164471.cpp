//            
//                            

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
    assert(a >= 0 && 0 < r && r <= 65536 && (e == Encrypt || e == Decrypt));
/*                 
                                                                                                        
                                                                                                         
*/
    switch(e)
    {
        case Encrypt:
            if(a < 32) return a;
            else
            {
                return ((a-32+(r%(128-32)))%(128-32)+32);
            }
        case Decrypt:
            if(a < 32) return a;
            else
            {
                return ((a-32-(r%(128-32))+(128-32))%(128-32)+32);
            }
    }
}

void test_rotate_char ()
{
//                
    assert(true); //                                                               
/*                 
                                                                                                                                                                                             
 */
    int r = 1;
    while(true)
    {
        cout << "Enter a value for r: ";
        cin >> r;
        if(r < 0 || !cin) return;
        int a = (r + 65535) % 65536 + 1; //                                                                             
        cout << "Input number " << r << " equals seed " << a << endl << endl;
        for(char c = 0; c >= 0; c++) //                        
        {
            cout << c << "\t" << (int)c << "\t" << (int)rotate_char(c,a,Encrypt) << "\t" << (int)rotate_char(rotate_char(c,a,Encrypt),a,Decrypt) << endl;
        }
    }

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{

//                
    assert(true); //                                                                                       
/*                 
                                                                                       
*/
    string inName;
    string outName;
    bool differentNames = false;

    while(!differentNames)
    {
        cout << "!!!The filenames you enter in the following may not contain any layout symbols!!!" << endl << endl;
        cout << "Enter the name of the input file: ";
        cin >> inName;
        cout << "Enter the name of the output file: ";
        cin >> outName;
        if (inName == outName) cout << "Input and output file cannot have the same name!";
        else differentNames = true;
    }
    infile.open(inName);

    outfile.open(outName);
    if(!(infile && outfile)) cout << endl << "Something went wrong while opening the files!" << endl << "Check the names and place the files in the right directory" << endl;
    return (infile && outfile);

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
    assert(initial_value >= 0 && initial_value <= 65536 && outfile && infile && (action == Encrypt || action == Decrypt));
/*                 
                                                                                                                        
*/
    initialise_pseudo_random(initial_value);
    char c;
    int nextprn;
    while(infile)
    {
        infile.get(c);
        //                                                    
        outfile.put(rotate_char(c,next_pseudo_random_number(),action));
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

