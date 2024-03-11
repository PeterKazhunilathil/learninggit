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

uint8_t ahex[] = {0xE1,0x00,0x00,0x02,0x00,0x02,0x01,0xC0,0x00,0x01,0x00,0x07,0x01,0xBA,0x00,0x21
,0x00,0x00,0x00,0x00,0x0C,0x16,0x01,0xB0,0x00,0x01,0x00,0x09,0x5C,0x00,0xFF,0xFF
,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x01,0x00,0x21,0x00,0x00,0x00,0x01,0x01,0x98
,0x00,0x00,0x00,0x01,0x01,0x92,0x00,0x00,0x00,0x13,0x01,0x8C,0x09,0x46,0x00,0x02
,0x20,0x00,0x09,0x0D,0x00,0x02,0x00,0x02,0x09,0x35,0x00,0x02,0x00,0x01,0x09,0x82
,0x00,0x02,0x00,0x02,0x09,0x0C,0x00,0x02,0x00,0x00,0xF1,0xFA,0x00,0x14,0x00,0x01
,0x00,0x10,0x00,0x01,0x00,0x0C,0x00,0x06,0x00,0x00,0x86,0x2B,0x00,0x06,0x00,0x00
,0x86,0x2B,0x09,0xA7,0x00,0x02,0x00,0x06,0x09,0x84,0x00,0x08,0x00,0x06,0x00,0x09
,0xFB,0x70,0xD3,0x5B,0x09,0x1E,0x00,0x24,0x00,0x22,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x09,0x87,0x00,0x08
,0x20,0x24,0x03,0x11,0x10,0x46,0x48,0x00,0x09,0x8F,0x00,0x04,0x00,0x09,0x5C,0x00
,0x09,0x86,0x00,0x04,0x00,0x01,0x11,0x4D,0x09,0x1D,0x00,0x02,0x01,0xD4,0x09,0x21
,0x00,0x02,0x00,0x00,0x09,0x28,0x00,0x12,0x00,0x08,0x50,0x68,0x69,0x6C,0x69,0x70
,0x73,0x00,0x00,0x06,0x4D,0x38,0x30,0x30,0x30,0x00,0x09,0x2D,0x00,0x8E,0x00,0x08
,0x00,0x8A,0x00,0x01,0x00,0x08,0x00,0x0A,0x44,0x45,0x38,0x31,0x31,0x30,0x31,0x38
,0x31,0x33,0x00,0x02,0x00,0x08,0x00,0x0E,0x4D,0x32,0x37,0x30,0x35,0x41,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x58,0x00,0x0E,0x53,0x2D,0x4D,0x32
,0x37,0x30,0x33,0x2D,0x31,0x35,0x30,0x31,0x41,0x20,0x00,0x04,0x00,0x58,0x00,0x08
,0x4C,0x2E,0x33,0x33,0x2E,0x36,0x35,0x20,0x00,0x02,0x00,0x10,0x00,0x0E,0x53,0x2D
,0x4D,0x32,0x37,0x30,0x33,0x2D,0x31,0x34,0x30,0x31,0x41,0x20,0x00,0x04,0x00,0x10
,0x00,0x08,0x4C,0x2E,0x33,0x33,0x2E,0x36,0x35,0x20,0x00,0x02,0x00,0x18,0x00,0x0E
,0x53,0x2D,0x4D,0x38,0x30,0x30,0x30,0x2D,0x31,0x33,0x30,0x31,0x41,0x20,0x00,0x04
,0x00,0x18,0x00,0x08,0x41,0x2E,0x31,0x36,0x2E,0x33,0x33,0x00,0x09,0x85,0x00,0x34
,0x00,0x01,0x00,0x30,0x01,0x02,0x00,0x2C,0x00,0x05,0x00,0x28,0x00,0x01,0x00,0x21
,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x06,0x00,0x00,0x01,0x19,0x00,0x01,0x00,0x09
,0x00,0x00,0x00,0x4C,0x00,0x01,0x00,0x2A,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x36
,0x00,0x00,0x00,0x01,0x09,0x48,0x00,0x04,0x00,0x01,0x00,0x00,0x09,0x37,0x00,0x08
,0x06,0x6E,0x06,0x6E,0x00,0x01,0x00,0x0B


};

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

// uint8_t AssocReqSessionHeader[];
 struct AVAType
 {
    // uint16_t OIDType;
    uint16_t attribute_id;
    uint16_t length;
    uint16_t attribute_val;
} ;
 struct AttributeList{
    uint16_t count;
    uint16_t length;
    struct AVAType avatype[]; 
 
} ;
 struct MDSEUserInfoStd {

 uint32_t protocol_version : 32 ; 
 uint32_t nomenclature_version :32;
 uint32_t functional_units :32;
 uint32_t system_type :32;
 uint32_t startup_mode :32;

} ;
struct ROIVapdu
{
    uint16_t invoke_id; /* identifies the transaction */
    uint16_t command_type; /* identifies type of command */
    uint16_t length;
};



struct AssocReqUserData{
    uint8_t ASMLength: 8 ; 

    struct MDSEUserInfoStd MDSEUserInfoStd_T;
    
    // struct AttributeList OptionList;
    // struct AttributeList SupportedProfiles;

   
   uint32_t PollProfileRevision = POLL_PROFILE_REV_0;
   uint32_t RelativeTime = 800000;
    uint32_t max_mtu_rx = 1000;
    uint32_t max_mtu_tx = 1000;
    uint32_t max_bw_tx = 0xffffffff;
    uint32_t PollProfileOptions =  0x60000000;
    struct AVAType ;      ///#define NOM_ATTR_POLL_PROFILE_EXT 61441
                            /* id for poll profile extensions opt. package */

    uint32_t PollProfileExtOptions = POLL_EXT_PERIOD_NU_1SEC ;
    AttributeList PollProfileExtOptoptions{0,0};
   

} ;
/**********************************Numeric*****************************/

 struct __attribute__((packed)) NuObsValue {
 uint16_t physio_id;
 uint16_t MeasurementState ;
 uint16_t unit_code;
 uint32_t value;
} ;
 struct NuObsValueCmp{
uint16_t count;
uint16_t length;
struct NuObsValue value[1];
} ;



/*********************************Parsing SINGLE POLL DATA RESULT ***************/
struct SPpdu
{
    uint16_t session_id;
    uint16_t p_context_id;
};
struct ROapdus
{
    uint16_t ro_type;
    uint16_t length;
};
struct RorlsId
{
    uint16_t state;
    uint16_t count;
    uint16_t invoke_id;
    uint16_t CMDType;
    uint16_t length;

};
struct ActionResult
{
    uint16_t m_obj_class;
    uint16_t MdsContext;
    uint16_t Handle;
    uint16_t action_type;
    uint16_t length;


};
struct RORSapdu
{
    uint16_t invoke_id;
    uint16_t CMDType;
    uint16_t length;


};
struct ManagedObjectId
{
    uint16_t m_obj_class;
    uint16_t MdsContext;
    uint16_t Handle;
 
};
 struct TYPE {
   
} ;

 struct __attribute__((packed)) PollMdibDataReply
 {
    uint16_t poll_number;
    uint32_t rel_time_stamp;
    uint64_t abs_time_stamp;
    uint16_t partition;
    uint16_t code;
    uint16_t polled_attr_grp;
    
} ;

struct ObservationPoll{
    uint16_t obj_handle;
    struct AttributeList attributes;
} ;
struct __attribute__((packed)) SingleContextPoll{
    uint16_t context_id;
    struct __attribute__((packed)) poll_info{
        uint16_t count;
        uint16_t length;
        struct ObservationPoll value[];
    }info ;
} ;
struct __attribute__((packed)) PollInfoList
{
    uint16_t count;
    uint16_t length;
    struct SingleContextPoll value[]; 
};

struct __attribute__((packed)) SinglePollDataResult
{

    struct SPpdu SPpdu1;
    struct ROapdus ROapdus1;
    struct RORSapdu RorlsId1;
    struct ActionResult ActionResult1;

    struct PollMdibDataReply  pollMdibDataReply;
    struct PollInfoList pollInfoList;
    
    

}*SinglePollDataResultPointer;
std::vector<uint8_t> PollResult;

void ReadPollValues()   //Read the poll result (incomplete) 
{
    PollResult.erase(PollResult.begin(), PollResult.begin() + 5);
    PollResult.erase(PollResult.end() - 3, PollResult.end());
    uint16_t PollResultSize = size(PollResult);
    printf("size of poll result %d\n",PollResultSize); 
    // printf("last bit 0x%x \n",PollResult[PollResultSize-1]);

  //  if (PollResult.size() >= sizeof(SinglePollDataResult)) 
  if(1)
    {
    //    SinglePollDataResultPointer = reinterpret_cast<SinglePollDataResult*>(PollResult.data());
        SinglePollDataResultPointer = reinterpret_cast<SinglePollDataResult*>(&ahex);

    // printf("PollInfoList.ObservationPoll: %u\n", swap16(SinglePollDataResultPointer->SPpdu1.p_context_id));
     printf("SPpdu.session_id: %x\n", swap16(SinglePollDataResultPointer->SPpdu1.session_id));
     // Initialization and assignments as necessary

    // printf("SPpdu.session_id: %x\n", swap16(SinglePollDataResultPointer->SPpdu1.session_id));
    printf("SPpdu.p_context_id: %x\n", swap16(SinglePollDataResultPointer->SPpdu1.p_context_id));
    
    printf("ROapdus.ro_type: %x\n", swap16(SinglePollDataResultPointer->ROapdus1.ro_type));
    printf("ROapdus.length: %x\n", swap16(SinglePollDataResultPointer->ROapdus1.length));
    
    printf("RORSapdu.invoke_id: %x\n", swap16(SinglePollDataResultPointer->RorlsId1.invoke_id));
    printf("RORSapdu.CMDType: %x\n", swap16(SinglePollDataResultPointer->RorlsId1.CMDType));
    printf("RORSapdu.length: %x\n", swap16(SinglePollDataResultPointer->RorlsId1.length));
    
    printf("ActionResult.m_obj_class: %x\n", swap16(SinglePollDataResultPointer->ActionResult1.m_obj_class));
    printf("ActionResult.MdsContext: %x\n", swap16(SinglePollDataResultPointer->ActionResult1.MdsContext));
    printf("ActionResult.Handle: %x\n", swap16(SinglePollDataResultPointer->ActionResult1.Handle));
    printf("ActionResult.action_type: %x\n", swap16(SinglePollDataResultPointer->ActionResult1.action_type));
    printf("ActionResult.length: %x\n", swap16(SinglePollDataResultPointer->ActionResult1.length));
    
    printf("PollMdibDataReply.poll_number: %x\n", swap16(SinglePollDataResultPointer->pollMdibDataReply.poll_number));
    printf("PollMdibDataReply.rel_time_stamp: %x\n", swap32(SinglePollDataResultPointer->pollMdibDataReply.rel_time_stamp));
    printf("PollMdibDataReply.abs_time_stamp: %llx\n", swap64(SinglePollDataResultPointer->pollMdibDataReply.abs_time_stamp));
    printf("PollMdibDataReply.partition: %x\n", swap16(SinglePollDataResultPointer->pollMdibDataReply.partition));
    printf("PollMdibDataReply.code: %x\n", swap16(SinglePollDataResultPointer->pollMdibDataReply.code));
    printf("PollMdibDataReply.polled_attr_grp: %x\n", swap16(SinglePollDataResultPointer->pollMdibDataReply.polled_attr_grp));
    uint16_t TotalSinglePoll = swap16(SinglePollDataResultPointer->pollInfoList.count);
    printf("PollInfoList.count: %x\n", TotalSinglePoll);
    if(TotalSinglePoll == 0)return;
    printf("PollInfoList.length: %x\n", swap16(SinglePollDataResultPointer->pollInfoList.length));
    for(uint16_t i = 0 ; i<TotalSinglePoll; i++)
    {
        
        printf("PollInfoList.value[%d].context_id: %x\n",i, swap16(SinglePollDataResultPointer->pollInfoList.value[i].context_id));
        uint16_t TotalPollinfoList = swap16(SinglePollDataResultPointer->pollInfoList.value[i].info.count);
        printf("PollInfoList.value[%d].info.count: %d\n",i, TotalPollinfoList);
        printf("PollInfoList.value[%d].info.length: %x\n",i, swap16(SinglePollDataResultPointer->pollInfoList.value[i].info.length));
        
        for(uint16_t j = 0 ; j<TotalPollinfoList; j++)
        {
            printf("PollInfoList.value[%d].info.value[%d].objhandle: %x\n",i,j, swap16(SinglePollDataResultPointer->pollInfoList.value[i].info.value[j].obj_handle));
            uint16_t TotalAttributeCount = swap16(SinglePollDataResultPointer->pollInfoList.value[i].info.value[j].attributes.count);

            printf("PollInfoList.value[%d].info.value[%d].attribute.count: %d\n",i,j, TotalAttributeCount);
            printf("PollInfoList.value[%d].info.value[%d].attrubute.length: %x\n", i,j,swap16(SinglePollDataResultPointer->pollInfoList.value[i].info.value[j].attributes.length));
            for(uint16_t k = 0; k < TotalAttributeCount; k++)
            {
                printf("PollInfoList.value[%d].info.value[%d].attributes.avatype[%d].attribute_id: %x\n",i,j,k, swap16(SinglePollDataResultPointer->pollInfoList.value[i].info.value[j].attributes.avatype[k].attribute_id));
                printf("PollInfoList.value[%d].info.value[%d].attributes.avatype[%d].length: %x\n",i,j,k, swap16(SinglePollDataResultPointer->pollInfoList.value[i].info.value[j].attributes.avatype[k].length));
                printf("PollInfoList.value[%d].info.value[%d].attributes.avatype[%d].attribute_val: %d\n",i,j,k, swap16(SinglePollDataResultPointer->pollInfoList.value[i].info.value[j].attributes.avatype[k].attribute_val));
        
            }
            

        }
   }

    

            // printf("\n 0x%x \n", SinglePollDataResultPointer->SPpdu1.session_id);
    } 
   else
    {
        printf("PollResult does not contain enough data for SinglePollDataResult.\n");
    }
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
    // IsHandle("COM3");   // initializing the COM TO COM3
    // Init_COM(); // CONFIGURING THE COM3

    // vector<uint8_t> temp = {0x00};
    // CombineVec();
    // writedata(CombinedAssoReq); // Sending the combined Association Request
    // read_data(hSerial); // Reading the combined Association Response and MDS Create Response
    // writedata(MDSCreateEvent);  // Sending the MDS Create Event Result
    // read_data(hSerial); 
    // writedata(SinglePollDataRequest); // Sending the MDS Single Poll DataRequest
    // read_data(hSerial,true); // Reading the MDS Single Poll DataRequest
    ReadPollValues();
    while(0)
    {
      
        writedata(SinglePollDataRequest); // Sending the MDS Single Poll DataRequest
        read_data(hSerial,true); // Reading the MDS Single Poll DataRequest
        ReadPollValues();
        
        
        Sleep(1000);
        
    }

    
    writedata(ReleaseRequest); // Sending the MDS Single Poll DataRequest
    // read_data(hSerial);
    CloseHandle(hSerial);                                                                           
    return 0;

}