#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

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

char rotate_char (char a, int r, Action action)
{
//                
    assert(r > 0 && r <= 65536);
//                 
/*                                                                                                           
*/
    int b;
    if (action==Encrypt)
    {
        if (a<32)
        {
            b=a;
        }
        else
        {
            b=(a-32 + (r % (128-32))+ (128-32)) % (128-32)+32;
        }
    }
    else
    {
        b=(a-32 - (r % (128-32))+(128-32)) % (128-32)+32;
    }
    if (a<32)
    {
        b=a;
    }
    else
    return b;
}

void show_results(char a,int a_,int b, int A,int rand_num )
{
//                
    assert(a_<127 && a_>0 && b>0 && rand_num>0 && rand_num <= 65536);
//                 
/*                                                                                              
*/
    if (a_==b && (rand_num%(128-32)!=0)|| a_==1)
    {
        a=' ';
    }
    cout << a << "\t" << a_ << "\t" << b << "\t\t" << A << endl;
}

void test_rotate_char ()
{
//                
    assert(true);
//                 
/*                                                                                                                                             
                                                                                           
*/
    char ASCII,c;
    int value=1, i, rand_num;;
    while (value > 0 && value < 65536)
    {
    cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536): " << endl;
    cin >> value;
    if (value <0 || value > 65536)
    {
        return;
    }
    initialise_pseudo_random(value);
    cout << "char" << "\t" << "ASCII" << "\t" << "ASCII rot_char" << "\t" << "ASCII rot_char(rot_char)" << endl;
    for (i=1; i<127; i++)
    {
        ASCII=i;
        rand_num=next_pseudo_random_number();
        show_results(ASCII, ASCII, rotate_char(ASCII,rand_num,Encrypt), rotate_char(rotate_char(ASCII,rand_num,Decrypt), rand_num, Encrypt),rand_num);

    }
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
//                 
/*                                                                                                                             
                                     
*/
    string filename_input, filename_output;
    cout << "Enter your input file name (without spaces): " << endl;
    cin >> filename_input;
    cout << "Enter your output file name (without spaces): " << endl;
    cin >> filename_output;
    //                                                                                                           
    while (filename_input==filename_output)
    {
        cout << "ERROR: The input filename and the output filename are the same, please enter different filenames." << endl;
        cout << "Enter your input file name (without spaces): " << endl;
        cin >> filename_input;
        cout << "Enter your output file name (without spaces): " << endl;
        cin >> filename_output;
    }
    infile.open(filename_input.c_str());
    outfile.open(filename_output.c_str());
    if (infile.is_open())
    {
        cout << "Your entered input file does exist, and is successfully opened." << endl;
        return true;
    }
    else
    {
        cout << "Your entered input file does not exist." << endl;
        return false;
    }
}

Action get_user_action ()
{//               
    assert ( true ) ;
/*                 
                                                                                               
*/
    cout << "Do you want to Encrypt of Decrypt the file? (E/D): " ;
    string answer ;
    cin  >> answer ;
    if (answer == "E" || answer == "e")
        return Encrypt;
    else
        return Decrypt;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(infile.is_open() && outfile.is_open());
//                 
/*                                                                                                        
*/
    int rand_num;
    initialise_pseudo_random(initial_value);
    rand_num=next_pseudo_random_number();
    if (action==Decrypt)
    {
        char c,d;
        //                                  
        infile.get(c);
        while (infile)
        {
            //                                                              
            d=rotate_char(c,rand_num,Decrypt);
            //                                            
            outfile.put(d);
            //                  
            infile.get(c);
            rand_num=next_pseudo_random_number();
        }
    }
    else if (action==Encrypt)
    {
        char c,d;
        //                                  
        infile.get(c);
        while (infile)
        {
            //                                                              
            d=rotate_char(c,rand_num,Encrypt);
            //                                            
            outfile.put(d);
            //                  
            infile.get(c);
            rand_num=next_pseudo_random_number();
        }
    }
}

int main()
{
    string answer;
    cout << "Do you want to use the function test_rotate_char?(y/n)" << endl;
    cin >> answer;
    if (answer=="n" || answer=="N")
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
    return 0;
    }
    else if (answer=="y" || answer == "Y")
    {
        test_rotate_char();
    }
    else
    {
        cout << "You entered an unavailable answer" << endl;
    }
}

