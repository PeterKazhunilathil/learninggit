
#include <windows.h>
#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include <tchar.h>
#include <iomanip>
#include<string>
// #include "Protocol.h"
#include "Expected_data.h"

using namespace std;
ofstream MyFile("AssociationResponse.txt");
ofstream PollResultFile("PollResultFile.cvc");


/*
+--------+                                   +--------+
| Client |                                   | Server |
|   PC   |                                   |  ECG   |
|        |----- Association Request ----->   |        |
|        |                                   |        |
|        |   <--------- Association Result --|        |
|        |                                   |        |
|        |   <------ MDS Create Event Report |        |
|        |                                   |        |
|        |-- MDS Create Event Result ---->   |        |
|        |                                   |        |
|        |-- Poll Data Request ---------->   |        |
|        |                                   |        |
|        |   <--------- Poll Data Response --|        |
|        |                                   |        |
|        |                  ...              |        |
|        |                                   |        |
|        |        (Data Exchange Continues)  |        |
|        |                                   |        |
|        |                  ...              |        |
|        |                                   |        |
|        |-- Association Release Request --> |        |
|        |                                   |        |
|        |  <-- Association Release Result --|        |
+--------+                                   +--------+
*/
/*
                *********** FRAMING********

BOF Beginning Of Frame (0xC0)
Hdr Header Information
User Data Association Control or Data Export Command message
FCS 16 bit Frame Check Sequence using CRC-CCITT algorithm
EOF End Of Frame (0xC1)


Hdr Header Information
    For Association Req -   {BOF,0x11,0x01,0x00,0xee,USERDATA ,0XE8,0X50,0XC1}
    For MDSCreateEventResult - {BOF, 0x11,0x01,0x00,0x1C,USERDATA, 0x39,0x17,EOF}    
    For SinglePollDataRequest - {BOF, 0xC0, 0x11,0x01,0x00,0x24,USERDATA,0xF8,0x48,EOF}                                           øHÁ

    NOTE - The contents of the Hdr and User Data fields is unrestricted. This can lead to problems if a BOF or 
EOF character appear in the Hdr, User Data, or FCS field. A Control Escape byte is defined as 0x7D. 
The sender must examine each byte in the User Data and FCS fields; for each byte with the value 
0xC0, 0xC1, 0x7D it does the following:
• insert a 0x7D byte proceeding the byte
• complement bit 5 of the byte (XOR with 0x20).




*/
/*


                     ***** UserData Structure ******
ASNLength length : 72 {0x48}

****MDSEUserInfoStd***

ProtocolVersion protocol_version : MDDL_VERSION1
NomenclatureVers.nomenclature_version : NOMEN_VERSION
FunctionalUnits functional_units : 0
SystemType system_type : SYST_CLIENT
StartupMode startup_mode : COLD_START
 {0x80 0x00 0x00 0x00 0x40 0x00 0x00 0x00 
 0x00 0x00 0x00 0x00 0x80 0x00 0x00 0x00 
 0x20 0x00 0x00 0x00}

***Option List*** 

AttributeList count : 0
 length : 0
 {0x00 0x00 0x00 0x00}

***Supported Profiles***

AttributeList count : 1
 length : 44
 {0x00 0x01 0x00 0x2c}

***AVAType***

OIDType attribute_id : NOM_POLL_PROFILE_SUPPORT
u_16 length : 40
 {0x00 0x01 0x00 0x28} 


***PollProfileSupport (attribute_val)***

PollProfileRev. poll_profile_revision : POLL_PROFILE_REV_0 
RelativeTime min_poll_period : 800000
u_32 max_mtu_rx : 1000
u_32 max_mtu_tx : 1000
u_32 max_bw_tx : 0xffff 0xffff
PollProfileOpt. options : 0x6000 0x0000
 {0x80 0x00 0x00 0x00 0x00 0x00 0x09 0xc4 
 0x00 0x00 0x09 0xc4 0x00 0x00 0x03 0xe8 
 0xff 0xff 0xff 0xff 0x60 0x00 0x00 0x00}


***Optional Packages***
AttributeList count : 1
length : 12
 {0x00 0x01 0x00 0x0c} 

***AVAType*** 
OIDType attribute_id : NOM_ATTR_POLL_PROFILE_EXT
u_16 length : 8 
 {0xf0 0x01 0x00 0x08}

***PollProfileExt (attribute_val)***

PollProfileExtOpt.options : POLL_EXT_PERIOD_NU_AVG_60SEC
AttributeList count : 0
 length : 0
 {0x20 0x00 0x00 0x00 0x00 0x00 0x00 0x00}
 
With this User Data, the length field of the Presentation Header must be set to 220 (0xDC) and the 
length field of the Session Header must be set to 236 (0xEC)

*/

uint16_t swap16(uint16_t value) {
    return (value >> 8) | (value << 8);
}

uint32_t swap32(uint32_t value) {
    return ((value >> 24) & 0xff) |
           ((value << 8) & 0xff0000) |
           ((value >> 8) & 0xff00) |
           ((value << 24) & 0xff000000);
}
uint64_t swap64(uint64_t value) {
    return ((value >> 56) & 0x00000000000000FF) |
           ((value << 40) & 0x00FF000000000000) |
           ((value >> 24) & 0x000000FF00000000) |
           ((value << 8)  & 0x0000FF0000000000) |
           ((value >> 8)  & 0x00000000FF000000) |
           ((value << 24) & 0x0000000000FF0000) |
           ((value >> 40) & 0x000000000000FF00) |
           ((value << 56) & 0xFF00000000000000);
}
vector<uint8_t> PollResult;

void ReadPollValues()   //Read the poll result (incomplete) 
{
    PollResult.erase(PollResult.begin(), PollResult.begin() + 5);
    PollResult.erase(PollResult.end() - 3, PollResult.end());
    uint16_t PollResultSize = size(PollResult);
    printf("size of poll result %d\n",PollResultSize); 
    uint8_t var[3] = {PollResult[141], PollResult[142], PollResult[143]};
    uint32_t var32 = ( ((uint32_t)var[0] << 16) | ((uint32_t)var[1] << 8) | var[2]);


    printf("\n\n %d \n\n",var32);
  
  
}





/*           ************* END OF DATA STUCTURES ***************/

HANDLE hSerial ;
void IsHandle(LPCSTR COM)
{
    hSerial = CreateFileA(COM,
                            GENERIC_READ | GENERIC_WRITE,
                            0,
                            0,
                            OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL,
                            0);
    if (hSerial == INVALID_HANDLE_VALUE) {
    std::cerr << "Error opening serial port" << std::endl;
    }
}
void Init_COM()
{
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        // Error getting current serial parameters
        std::cerr << "Error getting serial port state" << std::endl;
    }
    dcbSerialParams.BaudRate = 115200;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
 
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        // Error setting serial parameters
        std::cerr << "Error setting serial port state" << std::endl;
    }
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) 
    {
        // Error setting timeouts
        std::cerr << "Error setting serial timeouts" << std::endl;
    }
}
void writedata(const std::vector<uint8_t> combinedVec) // Send data to COM3
{
    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
    DWORD bytesSent;
    if (!WriteFile(hSerial, combinedVec.data(), combinedVec.size(), &bytesSent, NULL)) {
            printf("Failed to send association request\n");
            CloseHandle(hSerial);
    }
    else 
    {
        printf("sizeofdata: %d, data : %bytesSent: %d\n", combinedVec.size(), bytesSent);
    }
}
void read_data(HANDLE hSerial, uint8_t IsPollResult = false)
{
    PollResult.clear();
    BYTE buffer[1024];
    DWORD bytesRead;
    // int temp = 0;
    PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
    ZeroMemory(buffer, sizeof(buffer)); // Clear the buffer before reading

    
    if (ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL)) 
    {
        printf("\nBytes Read: %lu\n", bytesRead); 

       for (DWORD i = 0; i < bytesRead; ++i) 
        {
            if(IsPollResult)
            {
                PollResult.push_back(buffer[i]);
            }       
            MyFile << "0x" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]) << ",";
            if ((i + 1) % 16 == 0) MyFile << std::endl; 
           //printf("%02x ", buffer[i]);   

          //  if(buffer[i]== 0xc1)MyFile << std::endl<<std::endl; 

        }
      

        printf("\nBytes Read: %lu\n", bytesRead); 
        MyFile<<endl;
         MyFile  << std::endl; 
         MyFile  << std::endl; 

    }
    else 
    {
        printf("Error reading from COM port.\n");
    }
}
std::vector<uint8_t> combinedVec;
void CombineVec()
{


    combinedVec.insert(combinedVec.end(), AssocReqSessionHeader.begin(), AssocReqSessionHeader.end());
    combinedVec.insert(combinedVec.end(), AssocReqSessionData.begin(), AssocReqSessionData.end());
    combinedVec.insert(combinedVec.end(), AssocReqPresentationHeader.begin(), AssocReqPresentationHeader.end());
    combinedVec.insert(combinedVec.end(), AssocReqSessionData.begin(),AssocReqSessionData.end());
    combinedVec.insert(combinedVec.end(), AssocReqTrailer.begin(), AssocReqTrailer.end());

    for (int i = 0; i< combinedVec.size();i++) {
       // printf("0x%x ",combinedVec[i]);

    }
    return ;
}
int main(void)
{
    IsHandle("COM3");   // initializing the COM TO COM3
    Init_COM(); // CONFIGURING THE COM3

    // vector<uint8_t> temp = {0x00};
    CombineVec();
    writedata(CombinedAssoReq); // Sending the combined Association Request
    read_data(hSerial); // Reading the combined Association Response and MDS Create Response
    writedata(MDSCreateEvent);  // Sending the MDS Create Event Result
    read_data(hSerial); 
    writedata(SinglePollDataRequest); // Sending the MDS Single Poll DataRequest
    read_data(hSerial,true); // Reading the MDS Single Poll DataRequest
    ReadPollValues();
    while(1)
    {
      
        Sleep(100);
        writedata(SinglePollDataRequest); // Sending the MDS Single Poll DataRequest
        read_data(hSerial,true); // Reading the MDS Single Poll DataRequest
        ReadPollValues();
        
        
        
    }

    
    writedata(ReleaseRequest); // Sending the MDS Single Poll DataRequest
    // read_data(hSerial);
    CloseHandle(hSerial);                                                                           
    return 0;

}