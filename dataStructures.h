#define P2_0 7
#define P2_1 8
#define P2_2 2


typedef struct 
{
  byte header[1];
  byte message[10];
}packet;

typedef struct {
  byte red[2];
  byte green;
  byte blue;
} color_t;

typedef struct{
  byte device_ID[4];   //4 byte
  byte  timestamp[4]; //4byte
  byte fieldName[10]; //10 byte
  byte fieldValue[4];    
}tx_Bytes;
 
const char fieldName[10][10] = {
  "_____longt",
  "_____lattd",
  "______PM10",
  "_____PM2.5",
  "_______C02",
  "_______temp",
  "___humidity",
  "______ozone",
  "________JPT",
  "_______addr" 
  };

typedef struct{
  char device_ID[4];
  unsigned long  timestamp;  //4 byte
  float lon;
  float lat;
  float PM10;
  float PM2_5;
  float C02;
  float temp;
  float humidity;
  float ozone;
  char address[12];
}node_data;
