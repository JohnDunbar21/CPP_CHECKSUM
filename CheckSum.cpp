//
// Created by John Dunbar on 08/10/2023.
//
#include <string>
#include <iostream>
using namespace std;

string onesComplement( string dataBinaries )
{
    for (char dataBinary : dataBinaries)
    {
        if( dataBinary == '0' )
        {
            dataBinary = '1';
        }
        else if( dataBinary == '1' )
        {
            dataBinary = '0';
        }
    }
    return dataBinaries;
}

string checkSum( string dataBinaries, int blockSize )
{
    int dataBinariesSize = dataBinaries.length();
    if( dataBinariesSize % blockSize != 0 )
    {
        int paddingSize = blockSize - ( dataBinariesSize % blockSize );
        for( int i = 0; i < paddingSize; i++ )
        {
            dataBinaries = '0' + dataBinaries;
        }
    }

    string checkSumResult;

    for( int i = 0; i < blockSize; i++ )
    {
       checkSumResult += dataBinaries[i];
    }

    for( int i = blockSize; i < dataBinariesSize; i += blockSize )
    {
        string nextBlock;

        for( int j = i; j < ( i + blockSize ); j++ )
        {
            nextBlock += dataBinaries[j];
        }

        string additions;
        int sum = 0;
        int carry = 0;

        for( int k = ( blockSize - 1 ); k >= 0; k-- )
        {
            sum += ( ( nextBlock[k] - '0' ) + ( checkSumResult[k] - '0') );
            carry = sum / 2;

            if( sum == 0 )
            {
                additions = '0' + additions;
                sum = carry;
            }
            else if( sum == 1 )
            {
                additions = '1' + additions;
                sum = carry;
            }
            else
            {
                additions = '1' + additions;
                sum = carry;
            }
        }

        string finalResult;

        if( carry == 1 )
        {
            for( int l = ( additions.length() - 1 ); l >= 0; l-- )
            {
                if( carry == 0 )
                {
                    finalResult = additions[l] + finalResult;
                }
                else if( ( ( additions[l] - '0') + carry ) % 2 == 0 )
                {
                    finalResult = '0' + finalResult;
                    carry = 1;
                }
                else {
                    finalResult = '1' + finalResult;
                    carry = 0;
                }
            }

            checkSumResult = finalResult;
        }
        else
        {
            checkSumResult = additions;
        }
    }

    return onesComplement( checkSumResult );
}

int unsetBitCounter( string receiverChecksum )
{
    int unsetBits = 0;
    for( char bit : receiverChecksum )
    {
        if( bit == '0')
        {
            unsetBits++;
        }
    }
    return unsetBits;
}

bool checker( string sentMessage, string receivedMessage, int blockSize )
{
    string senderCheckSum = checkSum( sentMessage, blockSize );
    string receiverCheckSum = checkSum( ( receivedMessage + senderCheckSum ), blockSize );

    if(unsetBitCounter( receiverCheckSum ) == blockSize )
    {
        return true;
    }
    return false;
}

int main()
{
    string sentMessage =  "10000101011000111001010011101101";
    string receivedMessage = "10000101011000111001010011101101";
    int blockSize = 8;

    if( checker( sentMessage, receivedMessage, blockSize ) )
    {
        cout << "Data Sent: " << sentMessage << "\n";
        cout << "Data Received: " << receivedMessage << "\n";
        cout << "No Error Encountered: {Checksum Passed}\n";
    }
    else
    {
        cout << "Data Sent: " << sentMessage << "\n";
        cout << "Data Received: " << receivedMessage << "\n";
        cout << "Error Encountered: {Checksum Failed}";
    }
    return 0;
}