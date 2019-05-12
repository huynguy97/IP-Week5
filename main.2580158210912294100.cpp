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

char rotate_char (char a, int r, Action action)
{
//                
	assert(a >= 0 and a < 128);
	assert(r > 0 && r <= 65536);
	assert(action == Encrypt or action == Decrypt);
//                 
//		                                                     
//		                                                    
	if (a < 32){//                                        
		return a;
	}
	if (action == Encrypt){
		return (a-32+(r%(128-32))+(128-32))%(128-32)+32;
	}
	else{ //                                                   
		return (a-32-(r%(128-32))+(128-32))%(128-32)+32;
	}
}

void test_rotate_char ()
{
//                
	assert(true);
/*                 
	                                      
		                               
			             
			                          
			                                    
			                                                      
	                                                                                            
*/
	int key;
	do{
		cout << "enter value for the key\n";
		cin >> key;
		if (key >= 0){
			//                                                                                          
			for (unsigned char c = 0;c<128;c++){ //                          
				cout << c;
				cout << " ";
				cout << (int)c;
				cout << " ";
				cout << (int)rotate_char(c,key,Encrypt);
				cout << " ";
				cout << (int)rotate_char(rotate_char(c,key,Encrypt),key,Decrypt);
				cout << '\n';
			}
		}
	} while(key > 0);
}

bool open_input_and_output_file (ifstream& infile, ofstream& outfile)
{
//                
	assert(true);
//                 
//                                                           
	cout << "Please, enter the file names for the input and output files" << endl;
	string inp, outp;
	cin>>inp>>outp;
	
	assert(inp!=outp);

	infile.open(inp);
	outfile.open(outp);

	if(infile.is_open()&&outfile.is_open())
		return true;
	else if(infile.is_open()){
		cout << "outfile failed to open" << endl;
	} else if(outfile.is_open()){
		cout << "infile failed to open" << endl;
	} else {
		cout << "infile and outfile failed to open" << endl;
	}
	return false;
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
    while (initial_value <= 0 || initial_value > 65535)
    {
        cout << "Please enter the initial coding value (greater than 0 and less than 65536)" << endl ;
        cin  >> initial_value ;
    }
    return initial_value ;
}

void use_OTP (ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
//                
	assert(infile.is_open()&&outfile.is_open() && initial_value>0 && initial_value<65536);
	assert(action == Encrypt or action == Decrypt);
//                 
	//                                                                
	initialise_pseudo_random(initial_value);
	char c;
	while(infile.get(c)){
		outfile << rotate_char(c, next_pseudo_random_number(), action);
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

