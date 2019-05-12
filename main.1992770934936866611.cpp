#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

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
char rotate_char (char a, int r, Action action)
{
//                
    assert(a<128 && r>0 && r<=65536); //                                                                                                                                                                                                                  
//                                                                            
    char newchar;
    if (a>=32)  //               
    {
        if (action)//                                                           
        newchar=((a-32-(r%96)+96)%96) +32; //         
    else
        newchar=((a-32+(r%96)+96)%96) +32;
    }
    else
        newchar=a;
    return newchar;
}

void test_rotate_char ()
{
//                
assert(true); //              
//                                                                                                                                                                                              
    int r; //                           
    while (true)//                                                              
    {
        cout<<"Please enter a \" random \" value r to be used in encryption/decryption.";
        cin>> r;
        if (!(r>0)) //              
            break;
        char a;  //                                                           
        cout<<"Please enter a to be encrypted character";
        cin>>a;
        cout<<"The character was "<< a <<" the ASCII code of "<<a<<" is "<<(int)a<<", encryption changes it to "<< (int)rotate_char(a,r,Encrypt)<<" and when decrypted this returns "<<(int)rotate_char(rotate_char(a,r,Encrypt),r,Decrypt)<<".\n";
    }
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true); //                                    
//                                                                                                                              
    string input_name;  //                  
    string output_name;
    cout<<"Please enter the name of the input file:\n"; //             
    cin>>input_name;
    cout<<"Please enter the name of the output file:\n";
    cin>>output_name;
    if (output_name==input_name)
    {
        cout<<"Please do not try to use the same file to read and write.";
        return false; //                         
    }
    else
    {
        infile.open(input_name.c_str()); //                     
        outfile.open(output_name.c_str());
        if (infile && outfile)
        {
            cout<<"Files successfully opened.\n";
            return true; //                 
        }
        else
        {
            cout<<"Something went wrong opening the files.\n"; //                                                                                                         
            if (infile)
                infile.close();//                                  
            else if (outfile)
                outfile.close();
            return false;  //                               
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
    assert (initial_value > 0 && initial_value <= 65536) ; //                                                                                              
//                                                                                                         
    initialise_pseudo_random (initial_value);
    char a;
    char b;  //                                                           
    while (infile)
    {
        seed=next_pseudo_random_number ();
        infile.get(a);
        b=rotate_char(a,seed,action);
        outfile.put(b);
    }
}

int main()
{
    //                                                                               
    const Action ACTION = get_user_action() ;
    ifstream input_file;
    ofstream output_file;
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

