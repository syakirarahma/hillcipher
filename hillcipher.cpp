/*	Nama 		: Syakira Rahma Fauziyah
				  Salma Tri Audryani
	NPM	 		: 140810190013
				  140810190051
	Kelas		: A 
	Deskripsi 	: Program Enkripsi, Deskripsi, dan Find Key Hill Cipher
*/

#include<iostream>
#include<bits/stdc++.h> 
using namespace std;

string removeSpaces(string str){ 
    int count = 0; 
    for (int i = 0; str[i]; i++) 
        if (str[i] == ' ') 
            str[i] = 'X';
	return str; 
} 

int inversedKey[2][2];

void getInverseMatrix(int key[2][2]) {
	int tempKey[2][2];
	tempKey[0][0]=(int)(key[1][1]);
	tempKey[0][1]=(int)((-1) * key[0][1]);
	tempKey[1][0]=(int)((-1) * key[1][0]);
	tempKey[1][1]=(int)(key[0][0]);
	int determinant = (key[0][0]*key[1][1]) - (key[0][1]*key[1][0]);
	int det_inv = 0;
    int flag = 0;
    for (int i = 0; i < 26; i++){
        flag = (determinant * i) % 26;
        if (flag < 0){
        	flag = flag + 26;
		}
        if (flag == 1){
            det_inv = i;
        }
    }
	for(int i=0 ; i<2 ; i++)
		for(int j=0 ; j<2 ; j++){
			if ( tempKey[i][j] < 0 ) {
				int tempNumber = tempKey[i][j]*det_inv;
			    inversedKey[i][j] = ((tempNumber%26) + 26)%26;
			}
			else{
				inversedKey[i][j] = (tempKey[i][j]*det_inv%26);
			}
		}
}

string hillEncrypt(string plain, int key[2][2]) {
	string cipher = "";
	int stringLength = plain.length();
	if (plain.length()%2==1)
		stringLength += 1;
	char plainMatrix[2][stringLength];
	int count=0;
	for(int i=0; i<stringLength/2;i++)
		for(int j=0;j<2;j++){
			if(plainMatrix[j][i] == 32){
				break;
			}
			plainMatrix[j][i] = plain[count];
			count++;
		}
	for(int i = 0; i < stringLength/2; i++){
   		for(int j = 0; j < 2; j++){
   			int tempCipher=0;
   			for(int k = 0; k < 2; k++){
   				int l = key[j][k] * (plainMatrix[k][i]%65);
   				tempCipher += l;	
			}
			tempCipher = (tempCipher%26) +65;
			cipher += (char)tempCipher;	
		   }
	}
	return cipher;
}

string hillDecrypt(string cipher, int key[2][2]) {
	string plain = "";
	int stringLength = cipher.length();
	if (plain.length()%2==1)
		stringLength = cipher.length()+1;
   	getInverseMatrix(key);
   	char cipherMatrix[2][stringLength/2];
	int count=0;
	for(int i=0; i<stringLength/2;i++)
		for(int j=0;j<2;j++){
			cipherMatrix[j][i] = cipher[count];
			count++;
		}
	
	for(int i = 0; i < cipher.length()/2; i++){
   		for(int j = 0; j < 2; j++){
   			int tempPlain=0;
   			for(int k = 0; k < 2; k++){
   				int l = inversedKey[j][k] * (cipherMatrix[k][i]%65);
   				tempPlain += l;
			   }
			tempPlain = (tempPlain%26) +65;
			plain += (char)tempPlain;	
		   }
	}
	return plain;
}

int gcd(int m, int n){
	if (n > m)
		swap(m,n);
	
	do{
		int temp = m % n;
		m = n;
		n = temp;
	} while (n != 0);
	
	return m;
}

int findInvers(int m, int n){
	int t0 = 0,t1 = 1,invers,q,r,b = m;
	while(r != 1){
		q = m/n;
		r = m%n;
		invers = t0 - q * t1;
		if(invers < 0){
			invers = b - (abs(invers)%b);
		}else{
			invers %= b;
		}
		t0 = t1;
		t1 = invers;
		m = n;
		n = r;	
	}
	return invers;
}


void findKey(){
	//deklarasi
	string plainteks,cipherteks;
	int key[2][2],det,detInv,adj[2][2],plainteksInv[2][2],plainMatrix[2][2],cipMatrix[2][2],counter;
	int p,c;
	int transpose[2][2];
	
	//input plainteks
	cout << "Insert Plainteks : ";
	cin.ignore();
	getline(cin,plainteks);
	
	//assign plainteks ke plainMatrix
	counter = 0;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			p = toupper(plainteks[counter]) - 65;
			plainMatrix[i][j] = p;
			counter++;
		}
	}
	
	//input cipherteks
	cout << "Insert Cipherteks : ";
	getline(cin,cipherteks);
	
	//assign cipherteks ke cipMatrix
	counter = 0;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			c = toupper(cipherteks[counter]) - 65;
			cipMatrix[i][j] = c;
			counter++;
		}
	}
	
	// determinan
	det = (plainMatrix[0][0] * plainMatrix[1][1]) - (plainMatrix[0][1] * plainMatrix[1][0]);
	if(gcd(det,26)==1){
		// inverse dari determinan mod 26
		detInv = findInvers(26,det);
		
		//menghitung adjoin
		adj[0][0] = plainMatrix[1][1];
		adj[0][1] = (-1)*plainMatrix[0][1];
		adj[1][0] = (-1)*plainMatrix[1][0];
		adj[1][1] = plainMatrix[0][0];
		
		//menghitung matriks invers dari plainteks
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				plainteksInv[i][j] = detInv * adj[i][j];
				if(plainteksInv[i][j] < 0){
					plainteksInv[i][j] = 26 - (abs(plainteksInv[i][j])%26); 
				}else{
					plainteksInv[i][j] = plainteksInv[i][j];
					plainteksInv[i][j] = plainteksInv[i][j] % 26;
				}
			} 
		}
		
		//Search key
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				key [i][j] = 0;
				for(int k = 0; k < 2; k++){
					key [i][j] += (plainteksInv[i][k] * cipMatrix[k][j]);
				}
				key [i][j] %= 26;
			}
		}
		

		for (int i = 0; i < 2; i++){
    	for (int j = 0; j < 2; j++){
      		transpose[j][i] = key[i][j];
    		}
  		}
  	
	    for(int i = 0; i < 2; i++){
	        for (int j = 0; j < 2; j++){
	            cout << (transpose[i][j]) << "\t";
	        }
	        cout <<endl;
	    } 	 	
	}else{
		cout << "Determinan tidak relatif " <<endl;
		cout << "Key not found" <<endl<<endl;
	}
	system("pause");
	system("cls");
}

int main(){
	bool menuActive = true;
	int key[2][2];
	key[0][0] = 7;
	key[0][1] = 6;
	key[1][0] = 2;
	key[1][1] = 5;
	string plain,cipher;
	int pil;
	while(menuActive){
		cout << "\nProgram Hill Cipher 2x2" <<endl;
		cout << "Menu : " <<endl;
		cout << "1. Enkripsi" <<endl;
		cout << "2. Dekripsi" <<endl;
		cout << "3. Find Key" <<endl;
		cout << "4. Exit" <<endl;
		cout << "Pilih Menu : "; cin >> pil;
		switch(pil){
			case 1:
				cout << "\nInput Plaintext: ";
				cin.ignore();
				getline(cin,plain);
				plain = removeSpaces(plain); 
				transform(plain.begin(), plain.end(), plain.begin(), ::toupper); 
				cout << "Ciphertext : " << hillEncrypt(plain,key) <<endl<<endl;
				break;
			case 2:
				cout << "\nInput Ciphertext: ";
				cin.ignore();
				getline(cin,cipher);
				cipher = removeSpaces(cipher);
				transform(cipher.begin(), cipher.end(), cipher.begin(), ::toupper); 
				cout << "Plaintext : " << hillDecrypt(cipher,key) <<endl<<endl;
				break;
			case 3:
				cout<<endl;
				findKey();
				break;
			case 4:
				menuActive = false;
				break;
			default:
				cout << "\nPilihan salah" <<endl;
				break;
		}
	}
}
