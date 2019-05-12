#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

/*

                                         
                                         

*/

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
    assert (true) ;
//                 

    int b;
    if(a < 32)
        b = a;
    else
    {
        if(action == Encrypt)
        {
            b = (a-32 + (r % (128-32)) + (128-32)) % (128-32)+32;
        }
        else
        {
            b = (a-32 - (r % (128-32)) + (128-32)) % (128-32)+32;
        }
    }
    return (b);

}

void test_rotate_char ()
{
//                

//                 

}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(infile && outfile);
    /*                 
                                                                                                                      
                                                                                                 
    */

    string i;
    string o;

    cout << "Please specify your input file." << endl;
    cin >> i;
    //                                     
    if(i.length()<=4 || i.substr(i.length()-4,i.length()) != ".txt")
    {
        cout << "Please enter a .txt file.\n";
        return false;
    }
    //                                                                  
    infile.open(i.c_str());
    if(!infile)
    {
        cout << "File could not be found.\n";
        return false;
    }

    cout << "Please specify your output file.\n";
    cin >> o;
    //                                      
    if(o.length()<= 4 || o.substr(o.length()-4,o.length()) != ".txt")
    {
        cout << "Please enter a .txt file\n";
        return false;
    }
    //                                                              
    if(i == o)
    {
        cout << "The input file cannot have the same name as the output file.\n";
        return false;
    }

    //                                                                   
    outfile.open(o.c_str());
    if(!outfile)
    {
        cout << "File could not be found.\n";
        return false;
    }

    //                                          
    cout << "The files have been initialized correctly.\n";
    return true;

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
    assert(infile && outfile);
    /*                 
                                                                                                
    */
    char c;
    infile.get(c);
    int r = next_pseudo_random_number();
    while(infile)
    {
        cout << seed << endl;
        outfile << rotate_char(c,r,action);
        infile.get(c);
        r=next_pseudo_random_number();
    }

}

int main()
{

    /*
		                                                         

                   
         
                   
                  
                                                            
                     
                                                          
                     
                     
                         
                                                                                                                                                        
         

    */

    const Action ACTION = get_user_action() ;

    ifstream input_file  ;
    ofstream output_file ;

    //                    
    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program aborted." << endl ;
        return -1 ;
    }

    //                     
    const int INITIAL_VALUE = initial_encryption_value () ;
    initialise_pseudo_random(INITIAL_VALUE);

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

