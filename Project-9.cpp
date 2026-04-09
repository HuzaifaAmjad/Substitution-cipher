#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//converting to lowercase
void toLowerCase(string &message)
{
 for (int i=0;i<message.length();i++)
 {
 if (message[i]>=65 && message[i]<=90)
 {
  message[i]=message[i]+ 32;
 }
 }
}
//lookup table
void buildCodeTable(int code[],int offset,int spacing)
{
 for (int n=0;n<26;n++)
 {
 code[n]=(offset+spacing*n)%26;
 }
}
void displayCodeTable(const int code[])
{
 cout<<"\nLookup Table:\n";
 for (int i=0; i<26;i++)
 {
 cout<<"code["<<i<<"] : "<<code[i]<<endl;
 }
}
//encoding message 
void encodeMessage(string &message,int code[])
{
 for (int i=0;i<message.length();i++)
 {
 if (97<=message[i] && message[i]<=122)
 {
 int letterValue=message[i]- 97;
 int codedValue=code[letterValue];
 message[i]=char(codedValue+ 97);
 }
 }
}
//decoding message 
void decodeMessage(string &message,int code[])
{
 for (int i=0;i<message.length();i++)
 {
 if (message[i]>=97 && message[i]<=122)
 {
 int codedValue=message[i]- 97;
 int m=0;
 while (m<26 && code[m]!=codedValue)
 {
  m++;
 }
 if (m<26)
 {
  message[i]=char(m+ 97);
 }
 }
 }
}

int main()
{
 string inputFileName,outputFileName;
 string message;
 char choice;
 cout<<"Enter input file name: ";
 cin>>inputFileName;
 ifstream fin(inputFileName);
 if (!fin)
 {
 cout<<"Error: Could not open input file"<<endl;
 return 1;
 }
 getline(fin, message);
 fin.close();
 int length=message.length();
 int offset=length % 25 + 1;
 int spacing=(length % 6) * 2 + 1;
 int code[26];
 buildCodeTable(code,offset,spacing);
 displayCodeTable(code);
 cout<<"\nInput message:"<<endl;
 cout<<message<<endl;
 cout<<"\nNumber of characters in message: "<<length<<endl;
 cout << "Offset: "<<offset<<endl;
 cout<<"Spacing: "<<spacing<<endl;
 cout<<"\nEnter E to encode or D to decode: ";
 cin>>choice;
 toLowerCase(message);
 if (choice=='E'||choice=='e')
 {
  encodeMessage(message,code);
  cout<<"\nEncoded message:"<<endl;
  cout<<message<<endl;
 }
 else if (choice=='D'||choice=='d')
 {
  decodeMessage(message, code);
  cout<<"\nDecoded message:"<<endl;
  cout<<message<<endl;
 }
 else
 {
  cout<<"Invalid choice"<<endl;
  return 1;
 }
 cout<<"\nEnter output file name: ";
 cin>>outputFileName;
 ofstream fout(outputFileName);
 if (!fout)
 {
  cout<<"Error: Could not create output file"<<endl;
  return 1;
 }
 fout<<message;
 fout.close();
 cout<<"Output saved successfully to "<<outputFileName<<endl;
 return 0;
}