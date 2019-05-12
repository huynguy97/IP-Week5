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

/*                                                                 
                                                                        
                                                                             
                                                                                          
                                                                                
                                                                                           
                                                                            
*/
char rotate_char (char encryption_char, int random_value, Action action)
{
//                
    assert(encryption_char>=0 && encryption_char<128);
    assert(random_value>=0);
    assert(action==Encrypt || action==Decrypt);
    /*                 
                                                                                           
                                            
    */
    //                                                                                   
    if(encryption_char<32)
    {
        return encryption_char;
    //                                                                   
    } else if(action==Encrypt){
        return ((encryption_char-32 + (random_value%(128-32)) +(128-32)) % (128-32)) + 32;
    } else{
        return ((encryption_char-32 - (random_value%(128-32)) +(128-32)) % (128-32)) + 32;
    }
}

/*                                                                                            
                                                                                                         
                                                                     
                                                                                                          
                   
*/
void test_rotate_char ()
{
//                
    assert(true);
    /*                 
                                                                                   
                                                                                                 
                                                                         
                                                                                                  
                                                    
    */
    //                                                 
    int random_value=0;
    while(random_value>=0){
        cout << "Please enter a value for r" << endl;
        cin >> random_value;
        //                                                      
        if(!cin || random_value<0){
            cin.clear();
            cin.ignore(1000,'\n');
            return;
        }
        //                                                            
        for(int i=0;i<128;i++){
            cout << char(i) << '\t' << i << '\t' << int(rotate_char(char(i),random_value,Encrypt)) << '\t'
                 << int(rotate_char(rotate_char(char(i),random_value,Encrypt),random_value,Decrypt)) << endl;
        }
    }
}

/*                                                                   
                                                             
*/
bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
    assert(true);
    /*                
                                                                                           
                                                                                                 
                                                                                               
                                               
    */
    string input_file_name, output_file_name;
    cout << "Please enter the name of the input file:" << endl;
    cin >> input_file_name;
    cout << "Please enter the name of the output file:" << endl;
    cin >> output_file_name;
    //                                           
    if(input_file_name==output_file_name){
        cout << "ERROR: input and output file have the same name." << endl;
        return false;
    }
    infile.open(input_file_name.c_str());
    outfile.open(output_file_name.c_str());
    if(infile.is_open() && outfile.is_open()){
        return true;
    } else{
        cout << "ERROR: Files were not opened successfully." << endl;
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

/*                                                                                                             
                                                                                     
*/
void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
    assert(infile.is_open() && outfile.is_open());
    assert(action==Encrypt || action==Decrypt);
    assert(initial_value>=0 && initial_value<65536);
    /*                
                                                                                            
                                                                             
    */
    //                         
    initialise_pseudo_random(initial_value);
    char encryption_char = infile.get();
    //                                                                               
    //                                                                      
    //                                                                             
    //                                        
    while(infile){
        outfile << rotate_char(encryption_char, next_pseudo_random_number(), action);
        encryption_char = infile.get();
    }
    return;
}

//                         

/*                                                                                                  
                                                                                                             
                                                                             
*/
int main()
{
    const Action ACTION = get_user_action();
    ifstream input_file;
    ofstream output_file;
    if (!open_input_and_output_file (input_file,output_file))
    {
        cout << "Program aborted." << endl;
        return -1;
    }
    const int INITIAL_VALUE = initial_encryption_value();
    use_OTP (input_file,output_file,ACTION,INITIAL_VALUE);
    //                                
    input_file.clear();
    output_file.clear();
    input_file.close();
    output_file.close();

    if (!input_file || !output_file)
    {
        cout << "Not all files were closed succesfully. The output might be incorrect." << endl;
        return -1;
    }
    return 0;
}

