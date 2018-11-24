 #include<iostream>
#include<stdio.h>
#include<string.h>
#include<conio.h>

using namespace std;

class Substitution // Substitution Cipher class
{
	char str[500];

public:
	void sgetstring(void);      // method to get input string and key
	void sencryption(void);     // encryption method for Substitution Cipher
	void sdecryption(void);		// decryption method for Substitution Cipher
};
void Substitution::sgetstring()
{
	int size = 500;
	cout << "\n Enter the Input String: ";      // Input for Substitution Cipher
	cin.getline(str, size, '\n');
}
void Substitution::sencryption()
{
	int key, i, t1;
	char c;
	cout << "\n Enter Key: ";
	cin >> key;
	cout << "\n Encryption : ";
	//Encryption
	for (i = 0; i<strlen(str); i++)
	{
		c = str[i];

		if (c == -1)
			break;
		if (isupper(c))
		{
			t1 = (int)c - (int) 'A';
			t1 = (t1 + key) % 26;
			t1 = t1 + (int) 'A';
			cout << (char)t1;
		}
		else if (islower(c))
		{
			t1 = (int)c - (int) 'a';
			t1 = (t1 + key) % 26;
			t1 = t1 + (int) 'a';
			cout << (char)t1;
		}
		else{
			cout << c;
		}
	}
}
void Substitution::sdecryption()
{
	int key, i, t1;
	char c;
	cout << "\n Decryption : \n";
	//decryption
	for (key = 0; key<26; key++)
	{
		for (i = 0; i<strlen(str); i++)
		{
			c = str[i];

			if (c == -1)
				break;
			if (isupper(c))
			{
				t1 = (int)c - (int) 'A';
				t1 = (t1 - key + 26) % 26;
				t1 = t1 + (int) 'A';
				cout << (char)t1;
			}
			else if (islower(c))
			{
				t1 = (int)c - (int) 'a';
				t1 = (t1 - key + 26) % 26;
				t1 = t1 + (int) 'a';
				cout << (char)t1;
			}
			else{
				cout << c;
			}
		}
		cout << "\n";
	}
	//ending
}

class Transposition            // Transposition Cipher class
{
	char arr[22][22], darr[22][22], message[111], emessage[111], retmessage[111], key[55];
	char temp[55], temp2[55];

public:
	void tgetstring();		      // method to get input string and key
	void tencryption();           // encryption method for Transposition Cipher
	void tdecryption();           // decryption method for Transposition Cipher
	void tcipher(int i, int c);   // Transposition Cipher module
	int tfindMin();               // method to find the minimum values from the given key
	void tmakeArray(int, int);    // method to get the result encrypted / decrypted array
};
void Transposition::tgetstring()
{
	cout << "\n Enter the key\n";
	cin.getline(key, 111, '\n');
	//gets(key);
	cout << "\n Enter message to be ciphered\n";
	cin.getline(message, 111, '\n');
	//gets(message);
}
void Transposition::tencryption()
{
	int i, j, klen, emlen, flag = 0;
	int r, c, index, rows, k = 0;

	strcpy_s(temp, key);
	klen = strlen(key);

	k = 0;
	for (i = 0;; i++)
	{
		if (flag == 1)
			break;

		for (j = 0; key[j] != '\0'; j++)
		{
			if (message[k] == '\0')
			{
				flag = 1;
				arr[i][j] = '-';
			}
			else
			{
				arr[i][j] = message[k++];
			}
		}
	}
	r = i;
	c = j;

	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			cout << arr[i][j];
		}
		cout << "\n";
	}
	cout << "\n Encrypted message is\n";
	k = 0;
	for (i = 0; i < klen; i++)
	{
		index = this->tfindMin();
		this->tcipher(index, r);
	}
	emessage[k] = '\0';
	//printf("\nEncrypted message is\n");
	//for (i = 0; i<strlen(emessage); i++)
	//{
	//    printf("%c", emessage[i]);
	//}
	cout << "\n\n";
}
void Transposition::tdecryption()
{
	int i, j, klen, emlen, flag = 0;
	int r, c, index, rows, k;
	//deciphering
	emlen = strlen(message);
	klen = strlen(key);
	//emlen is length of encrypted message
	strcpy_s(temp, key);
	rows = emlen / klen;
	//rows is no of row of the array to made from ciphered message
	k = 0;
	for (i = 0;; i++)
	{
		if (flag == 1)
			break;

		for (j = 0; key[j] != '\0'; j++)
		{
			if (message[k] == '\0')
			{
				flag = 1;
				arr[i][j] = '-';
			}
			else
			{
				arr[i][j] = message[k++];
			}
		}
	}
	r = i;
	c = j;

	j = 0;
	for (i = 0, k = 1; i<emlen; i++, k++)
	{
		//printf("\nEmlen=%d",emlen);
		temp2[j++] = message[i];
		if ((k % rows) == 0)
		{
			temp2[j] = '\0';
			index = this->tfindMin();
			this->tmakeArray(index, rows);
			j = 0;
		}
	}
	cout << "\n Array Retrieved is\n";

	k = 0;
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			cout << darr[i][j];
			//retrieving message
			retmessage[k++] = darr[i][j];

		}
		cout << "\n";
	}
	retmessage[k] = '\0';

	cout << "\n Message retrieved is\n";

	for (i = 0; retmessage[i] != '\0'; i++)
		cout << retmessage[i];
}
void Transposition::tcipher(int i, int r)
{
	int j, k = 0;
	for (j = 0; j < r; j++)
	{
		{
			emessage[k++] = arr[j][i];
			cout << emessage[k - 1];
		}
	}
	// emessage[k]='\0';
}

void Transposition::tmakeArray(int col, int row)
{
	int i, j;

	for (i = 0; i < row; i++)
	{
		darr[i][col] = temp2[i];
	}
}

int Transposition::tfindMin()
{
	int i, j, min, index;

	min = temp[0];
	index = 0;
	for (j = 0; temp[j] != '\0'; j++)
	{
		if (temp[j] < min)
		{
			min = temp[j];
			index = j;
		}
	}

	temp[index] = 123;
	return (index);
}

int main(int argc, char** argv)    // main method
{
	int opa, ope;
	char flag;

	cout << "\n Select Algorithm: \n";
	cout << "\n 1. Substitution :";
	cout << "\n 2. Transposition :";
	cin >> opa;
	fflush(stdin);
	if (opa == 1)
	{
		Substitution s;           			// creating object of Substitution class
		cout << "\n Substitution Cipher \n";
		s.sgetstring();

		cout << "\n What do you want to perform: \n";
		cout << "\n 1. Encryption :";
		cout << "\n 2. Decryption :";
		cin >> ope;

		if (ope == 1)
		{
			s.sencryption();
		}
		else
		{
			s.sdecryption();
		}
	}
	if (opa == 2)
	{
		Transposition t;						// creating object of Transposition class
		cout << "\n Transposition Cipher \n";
		t.tgetstring();

		cout << "\n What do you want to perform: \n";
		cout << "\n 1. Encryption :";
		cout << "\n 2. Decryption :";
		cin >> ope;

		if (ope == 1)
		{
			t.tencryption();
		}
		else
		{
			t.tdecryption();
		}
	}

	cout << "\n\n\n Done";
	//getch();
	cin >> flag;

	return (0);
}
