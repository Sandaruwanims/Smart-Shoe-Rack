//------------------------------RFID_libries-----------------------------//

#include <SPI.h>
#include <MFRC522.h>


//---------------------Stepper_slider signals----------------------------//
const int out0_1 = 31;
const int out0_2 = 29;
const int out0_3 = 27;
const int out0_4 = 25;

int i=0;
int negative=0;
int positive=0;


//-------------------Stepper_updown moter signals------------------------//
#define pul_ud 33
#define dir_ud 35
#define ena_ud 37

int steps_ud = 0;
bool down_ud = false;
int updown_diff = 2250;
int small_step = 250;

//-------------------Stepper_main moter signals-------------------------//
#define pul_m 39
#define dir_m 41
#define ena_m 43

int steps_m = 0;
bool positive_m = false;


//-----------------------------LED pins---------------------------------//
#define led_r 24
#define led_g 26
#define led_w 28


//-------------------------RFID_variables-------------------------------//
#define SS_PIN 53
#define RST_PIN 49
#define BAUD 9600

MFRC522 RFID_Reader(SS_PIN, RST_PIN);
byte nUID_PICC[4];
String current_id = "00000000";


//--------------------------RFID_variables------------------------------//
bool shoes[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

String IDs[12] = {"A5D3E414",
                  "059782AB",
                  "55E754AB",
                  "35D0D915",
                  "11111111",
                  "22222222",
                  "551D4615",
                  "D9F23228",
                  "459BC215",
                  "45300515",
                  "33333333",
                  "44444444"
                 };

char up_down = 'u';
int current_block = 0;
int block_step = 967;

int temp = 0;

void setup() {
  
  Serial.begin(BAUD);
  //--------------------RFID_setup-------------------//
  SPI.begin();
  RFID_Reader.PCD_Init();
  pinMode(22,OUTPUT);
  pinMode(24,OUTPUT);
  pinMode(26,OUTPUT);

  //----------------Stepper_0_setup------------------//
  pinMode(out0_1, OUTPUT);
  pinMode(out0_2, OUTPUT);
  pinMode(out0_3, OUTPUT);
  pinMode(out0_4, OUTPUT);

  //----------------Stepper_main_setup------------------//
  pinMode(pul_m,OUTPUT);
  pinMode(dir_m,OUTPUT);
  pinMode(ena_m,OUTPUT);
  digitalWrite(ena_m,LOW);

  //----------------Stepper_updown_setup------------------//
  pinMode(pul_ud,OUTPUT);
  pinMode(dir_ud,OUTPUT);
  pinMode(ena_ud,OUTPUT);
  digitalWrite(ena_ud,LOW);

  //----------------LED_pin_setup------------------//
  pinMode(led_r,OUTPUT);
  pinMode(led_g,OUTPUT);
  pinMode(led_w,OUTPUT);
  
  digitalWrite(out0_1,LOW);
  digitalWrite(out0_2,LOW);

  digitalWrite(out0_3,LOW);
  digitalWrite(out0_4,LOW); 
 }

void loop() {
  read_tag();
}
