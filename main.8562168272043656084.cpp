/*                            
                           
                             
                            */

#include <iostream>
#include <fstream>          //             
#include <cassert>          //                       

using namespace std;

enum Action { Encrypt, Decrypt };

int seed = 0;
void initialise_pseudo_random(int r)
{
	//                
	assert(r > 0 && r <= 65536);
	/*                 
		                 
	*/
	seed = r;
}

int next_pseudo_random_number()
{
	//                
	assert(seed > 0 && seed <= 65536);
	/*                 
		                                                                                        
	*/
	const int seed75 = seed * 75;
	int next = (seed75 & 65535) - (seed75 >> 16);
	if (next < 0)
		next += 65537;
	seed = next;
	return next;
}

char rotate_char(char a, int r, Action action)
{
	//                
    assert(a >= 0 && a < 128 && r>=0);
	//                 
	/*                            
	                                        
                                                                                 
                                                                                 
                                                               
	                               */

    if (a < 32)
    {
        return a;
    }

    int b = 0;

    switch(action)
    {
        case Encrypt:
        b = (a - 32 + (r % (128-32))) % (128 - 32) + 32;
        break;
        case Decrypt:
        b = (a - 32 - (r % (128-32)) + (128-32)) % (128 - 32) + 32;
        break;
    }

    return b;

}

void test_rotate_char()
{
	//                
    assert(true);
	//                 
	/*                           
	                                         
	                                
	                                   
	                                                               
	                            */
	int r = 0;
	while(r>=0)
	{
        cout << "Please enter a value for r: $  ";
        cin >> r;
        int i = 0;
        cout << endl << "a\tASCII a\t\tASCII a Enc\t ASCII a EncDec\n";
        cout << "==================================================" << endl;
        while(i <= 127)
        {
            char a = i;
            int b = i;
            int c = rotate_char(a, r, Encrypt);
            int d = rotate_char(rotate_char(a, r, Decrypt), r, Encrypt);
            cout << a << "\t" << b << "\t\t" << c << "\t\t" << d << endl;
            i++;
        }

	}

}

bool open_input_and_output_file(ifstream& infile, ofstream& outfile)
{
	//                
	assert(true);
	//                 
	/*                        
	                                                                      
	                         */

	cout << "Please enter a file name for input:  $  ";
	string input_filename = "";
	cin >> input_filename;

	cout << "Please enter a file name for output:  $  ";
	string output_filename = "";
	cin >> output_filename;

	if(input_filename == output_filename)
	{
        cout << "Input filename must be different than output filename";
        return false;
	}

	infile.open(input_filename.c_str());
	if(!infile)
	{
        cout << "Failed to open file " << input_filename << endl;
        return false;
	}

    outfile.open(output_filename.c_str());
	if(!outfile)
	{
        cout << "Failed to open file " << output_filename << endl;
        return false;
	}

	return true;
}

Action get_user_action()
{//               
	assert(true);
	/*                 
		                                                                                          
	*/
	cout << "Do you want to encrypt the file? (y/n): ";
	string answer;
	cin >> answer;
	if (answer == "y")
		return Encrypt;
	else
		return Decrypt;
}

int initial_encryption_value()
{//              
	assert(true);
	/*                 
		                                                      
	*/
	int initial_value = -1;
	while (initial_value < 0 || initial_value > 65535)
	{
		cout << "Please enter the initial coding value (greater or equal to 0 and less than 65536)" << endl;
		cin >> initial_value;
	}
	return initial_value;
}

void use_OTP(ifstream& infile, ofstream& outfile, Action action, int initial_value)
{
	//                
    assert(infile.is_open() && outfile.is_open());
	//                 
	/*                        
	                                                    
	                                         
	                         */

	initialise_pseudo_random(initial_value);
    char c = 0;
    infile.get(c);
    while(infile)
    {
        outfile.put(rotate_char(c, next_pseudo_random_number(), action));
        infile.get(c);
    }
}

int main()
{
    //                   
	const Action ACTION = get_user_action();
	ifstream input_file;
	ofstream output_file;
	if (!open_input_and_output_file(input_file, output_file))
	{
		cout << "Program aborted." << endl;
		return -1;
	}
	const int INITIAL_VALUE = initial_encryption_value();
	use_OTP(input_file, output_file, ACTION, INITIAL_VALUE);
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

