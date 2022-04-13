#include <iostream>
#include <string>
#include <conio.h>
#include <cmath>
#include <fstream>
using namespace std;

string Kn[16];

string leftShifts(string tab, int shift){
	string temp = tab;
	for(int i=0;i<tab.length();i++){
		
		tab[i]=tab[ shift + i];
		if(i >= tab.length() - shift){
			for(int i=0; i < shift;i++)	tab[tab.length() - shift + i] = temp[i];			
		}
	}
	return tab;
}


string f_xor(string p, string q){
	
	string result = "";
	
	for(int i = 0 ; i < p.length(); i++){
			char p_i = p[i];
			char q_i = q[i];
		
			if(p_i == q_i)
				result += "0";
			else
				result += "1";				
	}
	
	return result;	
}


string f(string k, string r){
	int sbox[8][4][16]={
   	{
		14, 4, 13, 1, 2, 15, 11, 8, 3,  10, 6,  12, 5, 9,  0, 7,
	     	0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12,  11, 9, 5,  3, 8,
		 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9,   7, 3, 10, 5, 0,
		15, 12, 8, 2,  4, 9, 1,  7, 5,  11, 3,  14, 10, 0, 6, 13
    	},
	{
		15, 1, 8, 14, 6, 11, 3,  4,  9,  7, 2, 13, 12,  0, 5, 10,
            	3, 13, 4, 7,  15, 2, 8, 14, 12,  0, 1, 10,  6,  9, 11, 5,
            	0, 14, 7, 11, 10, 4, 13, 1,  5,  8, 12, 6,  9,  3,  2, 15,
            	13, 8, 10, 1, 3, 15, 4,  2, 11,  6, 7, 12,  0,  5, 14,  9
	},
	{
		10, 0, 9, 14, 6, 3, 15, 5,  1, 13, 12, 7, 11, 4,  2,  8,
		13, 7, 0, 9,  3, 4,  6, 10, 2, 8,  5, 14, 12, 11, 15, 1,
		13, 6, 4, 9,  8, 15, 3, 0, 11, 1,  2, 12, 5,  10, 14, 7,
		1, 10, 13, 0, 6, 9,  8, 7,  4, 15, 14, 3, 11, 5,  2, 12
	},
	{
		7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
	    	13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
		10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
		3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,
	},
	{
		2,  12, 4, 1,  7, 10, 11, 6, 8, 5, 3,  15, 13, 0, 14, 9,
		14, 11, 2, 12, 4, 7,  13, 1, 5, 0, 15, 10, 3,  9, 8,  6,
		4,  2,  1, 11, 10,13, 7,  8, 15,9, 12, 5,  6,  3, 0,  14,
		11, 8, 12, 7,  1, 14, 2, 13, 6, 15, 0, 9,  10, 4, 5,  3
	},
	{
	    	12, 1, 10, 15,9, 2, 6, 8, 0, 13, 3, 4, 14, 7,  5, 11,
		10, 15, 4, 2, 7, 12,9, 5, 6, 1, 13, 14, 0, 11, 3,  8,
		9,  14,15, 5, 2, 8, 12,3, 7, 0, 4,  10, 1, 13, 11, 6,
		4,  3,  2, 12,9, 5, 15,10,11,14,1,  7,  6, 0,  8, 13
	},
	{
	    	4, 11, 2,  14, 15, 0, 8, 13, 3,  12, 9, 7,  5, 10, 6, 1,
	       	13, 0,  11, 7,  4,  9, 1, 10, 14,  3, 5, 12, 2, 15, 8, 6,
		1, 4,  11, 13, 12, 3, 7, 14, 10, 15, 6,  8, 0,  5, 9, 2,
		6, 11, 13, 8,  1,  4, 10, 7, 9,  5,  0, 15, 14, 2, 3, 12
	},
	{
	 	13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3,  14, 5, 0, 12, 7,
		 1, 15,13, 8, 10, 3, 7,  4, 12, 5, 6,  11, 0, 14, 9, 2,
	     	7, 11, 4, 1, 9, 12, 14, 2,  0, 6, 10, 13, 15, 3, 5, 8,
	     	2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9,  0, 3,  5, 6, 11
	}
   };
   
    int E[48]={
		32, 1, 2, 3, 4, 5,
		4,  5, 6, 7, 8, 9,
		8,  9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32, 1
   };
   
    int P[32]={					
		16, 7, 20, 21, 29, 12, 28, 17,
		1, 15, 23, 26, 5,  18, 31, 10,
		2, 8,  24, 14, 32, 27, 3,  9,
		19,13, 30, 6,  22, 11, 4,  25
   };
	
	string r_E = "";
	
	for(int i = 0; i<48; i++){
		int n = E[i]-1;
		r_E += r[n];
	}

	string xor_e_k = f_xor(r_E, k);
	
	string  boxes = "";
	
	for(int i=0; i<8; i++){
		
			string six = xor_e_k.substr(6*i, 6);

			char row_1 = six[0];
			char row_2 = six[5];
			
			string row = "";
			row += row_1;
			row += row_2;
			string col = six.substr(1, 4);

			int row_id;
			int col_id;
		
			if(row == "00")
				row_id = 0;
			if(row == "01")
				row_id = 1;
			if(row == "10")
				row_id = 2;
			if(row == "11")
				row_id = 3;
				
			if(col == "0000")
				col_id = 0;
			if(col == "0001")
				col_id = 1;
			if(col == "0010")
				col_id = 2;
			if(col == "0011")
				col_id = 3;
			if(col == "0100")
				col_id = 4;
			if(col == "0101")
				col_id = 5;
			if(col == "0110")
				col_id = 6;
			if(col == "0111")
				col_id = 7;
			if(col == "1000")
				col_id = 8;
			if(col == "1001")
				col_id = 9;
			if(col == "1010")
				col_id = 10;
			if(col == "1011")
				col_id = 11;
			if(col == "1100")
				col_id = 12;
			if(col == "1101")
				col_id = 13;
			if(col == "1110")
				col_id = 14;
			if(col == "1111")
				col_id = 15;
		
		int box_int = sbox[i][row_id][col_id];

		if (box_int ==0)
			boxes += "0000";
		if (box_int ==1)
			boxes += "0001";
		if (box_int ==2)
			boxes += "0010";
		if (box_int ==3)
			boxes += "0011";
		if (box_int ==4)
			boxes += "0100";
		if (box_int ==5)
			boxes += "0101";
		if (box_int ==6)
			boxes += "0110";
		if (box_int ==7)
			boxes += "0111";
		if (box_int ==8)
			boxes += "1000";
		if (box_int ==9)
			boxes += "1001";
		if (box_int ==10)
			boxes += "1010";
		if (box_int ==11)
			boxes += "1011";
		if (box_int ==12)
			boxes += "1100";
		if (box_int ==13)
			boxes += "1101";
		if (box_int ==14)
			boxes += "1110";
		if (box_int ==15)
			boxes += "1111";			
	}

	string f_p = "";
	
	for(int i=0; i<32;i++){
		int n = P[i]-1;
		f_p += boxes[n];
	}

	return f_p;
}
string DES(string M, string K, bool process)
{
	
	string Kp="zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
	int pc1[56] = {	
		57, 49, 41, 33, 25, 17, 9,
		1,  58, 50, 42, 34, 26, 18,
	 	10, 2,  59, 51, 43, 35, 27,
    	19, 11, 3,  60, 52, 44, 36,
    	63, 55, 47, 39, 31, 23, 15,
    	7,  62, 54, 46, 38, 30, 22,
    	14, 6,  61, 53, 45, 37, 29,
    	21, 13, 5,  28, 20, 12, 4};
	
	
	int pc2[48]={
		14, 17, 11, 24, 1,  5,  3, 28,
		15, 6,  21, 10, 23, 19, 12, 4,
		26, 8,  16, 7,  27, 20, 13, 2,
		41, 52, 31, 37, 47, 55, 30, 40,
		51, 45, 33, 48, 44, 49, 39, 56,
		34, 53, 46, 42, 50, 36, 29, 32
  };
  
	for(int i=0;i<56;i++){
		Kp[i]=K[pc1[i]-1];	
	}
		
	string C0="zzzzzzzzzzzzzzzzzzzzzzzzzzzz", D0="zzzzzzzzzzzzzzzzzzzzzzzzzzzz";
	string tableofC[17], tableofD[17];

		
	for(int i=0; i<28; i++) C0[i]=Kp[i]; 
	for(int i=28; i<57; i++) D0[i-28]=Kp[i];
	
		tableofC[0] = C0;
		tableofD[0] = D0;
		tableofC[1] = leftShifts(tableofC[0],1);
		tableofD[1] = leftShifts(tableofD[0],1);
		tableofC[2] = leftShifts(tableofC[1],1);
		tableofD[2] = leftShifts(tableofD[1],1);
		tableofC[3] = leftShifts(tableofC[2],2);
		tableofD[3] = leftShifts(tableofD[2],2);
		tableofC[4] = leftShifts(tableofC[3],2);
		tableofD[4] = leftShifts(tableofD[3],2);
		tableofC[5] = leftShifts(tableofC[4],2);
		tableofD[5] = leftShifts(tableofD[4],2);
		tableofC[6] = leftShifts(tableofC[5],2);
		tableofD[6] = leftShifts(tableofD[5],2);
		tableofC[7] = leftShifts(tableofC[6],2);
		tableofD[7] = leftShifts(tableofD[6],2);
		tableofC[8] = leftShifts(tableofC[7],2);
		tableofD[8] = leftShifts(tableofD[7],2);
		tableofC[9] = leftShifts(tableofC[8],1);
		tableofD[9] = leftShifts(tableofD[8],1);
		tableofC[10] = leftShifts(tableofC[9],2);
		tableofD[10] = leftShifts(tableofD[9],2);
		tableofC[11] = leftShifts(tableofC[10],2);
		tableofD[11] = leftShifts(tableofD[10],2);
		tableofC[12] = leftShifts(tableofC[11],2);
		tableofD[12] = leftShifts(tableofD[11],2);
		tableofC[13] = leftShifts(tableofC[12],2);
		tableofD[13] = leftShifts(tableofD[12],2);
		tableofC[14] = leftShifts(tableofC[13],2);
		tableofD[14] = leftShifts(tableofD[13],2);
		tableofC[15] = leftShifts(tableofC[14],2);
		tableofD[15] = leftShifts(tableofD[14],2);
		tableofC[16] = leftShifts(tableofC[15],1);
		tableofD[16] = leftShifts(tableofD[15],1);
		
		string CD[16] = {
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",
		"zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",				
		};

		for(int i=0;i<16;i++){
			CD[i]= tableofC[i+1]+tableofD[i+1];

		}
			
		
		
		for(int i=0;i<16;i++){
						string temp = "";
			for(int j=0;j<48;j++){
						
					int n = pc2[j] -1;
					char cd = CD[i][n];
					temp += cd;
								
			}
			Kn[i]=temp;			
		}
		if(process ==1){
			int i = 15;
			int j = 0;
				while(i > j)
				{
					string temp = Kn[i];
					Kn[i] = Kn[j];
					Kn[j] = temp;
					i--;
					j++;
				}				
			}	
	
	int IP[64] = {
			58 ,   50 ,  42   , 34   , 26   ,18 ,   10  ,  2,
            60 ,   52 ,  44   , 36   , 28   ,20 ,   12  ,  4,
            62 ,   54 ,  46   , 38   , 30   ,22 ,   14  ,  6,
            64 ,   56  , 48   , 40   , 32   ,24 ,   16  ,  8,
            57 ,   49  , 41   , 33   , 25   ,17 ,    9  ,  1,
            59 ,   51  , 43   , 35   , 27   ,19 ,   11  ,  3,
            61 ,   53  , 45   , 37   , 29   ,21 ,   13  ,  5,
            63 ,   55  , 47   , 39   , 31   ,23 ,   15  ,  7
	};
	
  	
	//string M =	"0123456789ABCDEF"; // do zakodowania
	string 	M_bin = "";
	
	for(int i=0; i<M.length(); i++)	{
		int letter = M[i];
		
		if (letter =='0')
			M_bin += "0000";
		if (letter =='1')
			M_bin += "0001";
		if (letter =='2')
			M_bin += "0010";
		if (letter =='3')
			M_bin += "0011";
		if (letter =='4')
			M_bin += "0100";
		if (letter =='5')
			M_bin += "0101";
		if (letter =='6')
			M_bin += "0110";
		if (letter =='7')
			M_bin += "0111";
		if (letter =='8')
			M_bin += "1000";
		if (letter =='9')
			M_bin += "1001";
		if (letter =='A')
			M_bin += "1010";
		if (letter =='B')
			M_bin += "1011";
		if (letter =='C')
			M_bin += "1100";
		if (letter =='D')
			M_bin += "1101";
		if (letter =='E')
			M_bin += "1110";
		if (letter =='F')
			M_bin += "1111";
	}			

		string M_IP = "";
		
		for( int i=0; i<64; i++){
			int n = IP[i]-1;
			M_IP += M_bin[n];
		}
		
		string prev_L = M_IP.substr(0,32);
		string prev_R = M_IP.substr(32,64);

	string last_L = "";
	string last_R = "";
	
	for(int i=0; i<16; i++){
		string L_i = prev_R;
		string key = Kn[i];
		string f_result = f(key, prev_R);
		string R_i = f_xor(prev_L, f_result);
		
		prev_L = L_i;
		prev_R = R_i;
		if(i == 15){
			last_L = L_i;
			last_R = R_i;
		}
		
	}
	
	
	string R_L = last_R + last_L;
	
	int inv_IP[64]={   					
		40, 8, 48, 16, 56, 24, 64, 32,
		39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30,
		37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28,
		35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26,
		33, 1, 41, 9,  49, 17, 57, 25	
   };
	
	string encoded = "";
	
	for(int i=0; i < 64; i++){
		int n = inv_IP[i]-1;
		encoded += R_L[n];
	}
	
	string hex_encoded = "";
	
	for(int i =0; i<16; i++){
		string bin = encoded.substr(i*4,4);
		char letter;
		if(bin == "0000")
			letter = '0';
		if(bin == "0001")
			letter = '1';
		if(bin == "0010")
			letter = '2';
		if(bin == "0011")
			letter = '3';
		if(bin == "0100")
			letter = '4';
		if(bin == "0101")
			letter = '5';
		if(bin == "0110")
			letter = '6';
		if(bin == "0111")
			letter = '7';
		if(bin == "1000")
			letter = '8';
		if(bin == "1001")
			letter = '9';
		if(bin == "1010")
			letter = 'A';
		if(bin == "1011")
			letter = 'B';
		if(bin == "1100")
			letter = 'C';
		if(bin == "1101")
			letter = 'D';
		if(bin == "1110")
			letter = 'E';
		if(bin == "1111")
			letter = 'F';
		hex_encoded += letter;
	}
	return hex_encoded;
}

	
int main()
{
	string linia;
	ifstream odczyt("input.txt");
	

    while (!odczyt.eof())
    {
    string des1, des2, des3;
	getline(odczyt, linia);
	
	/*//SZYFROWANIE 3DES
	des1 = DES(linia, "0001001100110100010101110111100110011011101111001101111111110001", 0); //Wiadomosc szyfrowana jest kluczem K1 
	des2 = 	DES(des1, "0101010000011011110100101010100101010000111110010101010100111111", 1); //Wynik kroku 1. deszyfrowany jest kluczem K2 
	des3 = DES(des2,  "0101010100001010101010101010101011111110101010010100101010101001", 0); //Wynik kroku 2. jest ponownie szyfrowany kluczem K3.  
	*/
	//DESZYFROWANIE 3DES	
	des1 = DES(linia, "0101010100001010101010101010101011111110101010010100101010101001", 1); //Kryptogram deszyfrowany jest kluczem K3 
	des2 = 	DES(des1, "0101010000011011110100101010100101010000111110010101010100111111", 0); //Wynik kroku 1. szyfrowany jest kluczem K2 
	des3 = DES(des2,  "0001001100110100010101110111100110011011101111001101111111110001", 1); //Wynik kroku 2. jest powtornie deszyfrowany kluczem K1 
	//cout<<linia<<  " "<<des3<<endl;
	
    }

}


