#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad.h>
#include <esp_now.h>
#include <WiFi.h>
#include "Bitmaps.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const int buzzerPin = 1;

const byte ROWS = 3; 
const byte COLS = 3; 
char keys[ROWS][COLS] = {
    {'U', 'L', 'D'},
    {'R', 'S', 'T'},
    {'A', 'B', ' '}};
byte rowPins[ROWS] = {20, 10, 0}; 
byte colPins[COLS] = {7, 8, 9};   

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

const unsigned char *smileys[] = {balade, coeur, content, drole, enerve,faux,heure,livre,musique,photo,shopping,tele,triste,vrai};
const char *smileyNames[] = {"balade", "coeur", "content","drole", "enerve", "faux", "heure", "livre", "musique", "photo","shopping", "tele", "triste", "vrai"};
int currentSmileyIndex = 0;
bool fullSize = false;


uint8_t broadcastAddress[] = {0x7C,0xDF,0xA1,0xBE,0x7C,0x4C};

//0x58,0xCF,0x79,0x07,0x34,0xE8 //Emma

//0x7C,0xDF,0xA1,0xBE,0x7C,0x4C //Stan


String success;


typedef struct struct_message
{
  uint8_t smileyID; 
} struct_message;

struct_message receivedData;
struct_message sendData;


void data_sent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status == 0)
  {
    success = "Delivery Success :)";

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    delay(1000);
    display.println("Send " + String(smileyNames[sendData.smileyID]) );
    
    display.display();
    delay(3000); 

    displayMenu();
  }
  else
  {
    success = "Delivery Fail :(";
  }
}

bool messageReceived = false;
bool screenOff = false;


void data_receive(const uint8_t *mac, const uint8_t *incomingData, int len)
{
  memcpy(&receivedData, incomingData, sizeof(receivedData));
  Serial.print("Bytes received: ");
  Serial.println(len);

  messageReceived = true;


  if (screenOff)
  {
    display.ssd1306_command(SSD1306_DISPLAYON);
    screenOff = false;
  }

  for (int i = 0; i < 5; ++i)
  {
    display.clearDisplay();
    display.display();
    delay(100);
    display.setCursor(15, 20);
    display.setTextSize(2);
    display.println("MESSAGE");
    display.display();

    tone(buzzerPin, 600); 
    delay(100);
    tone(buzzerPin, 900); 
    delay(100);
    noTone(buzzerPin); 
    delay(100);
    display.clearDisplay();
  display.setTextSize(5);
  display.setTextColor(WHITE);
  display.setCursor(15, 20);
  display.println("!!!");
  display.display();
    //displayMenu();
    delay(100);
  }


  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Press 'B' to reveal emoji");
  display.display();
}

void displayMenu()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Choose a");
  display.println("Smiley:");
  display.print(smileyNames[currentSmileyIndex]);
  display.display();
}

void displaySmiley(bool halfSize)
{
  display.clearDisplay();
  display.setTextSize(fullSize ? 2 : 1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  if (!halfSize)
  {
    display.drawBitmap(0, fullSize ? 16 : 0, smileys[currentSmileyIndex], SCREEN_WIDTH, SCREEN_HEIGHT - (fullSize ? 16 : 0), WHITE);
  }
  else
  {
    display.drawBitmap(0, 0, smileys[currentSmileyIndex], SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
  }

  display.display();
}

void setup()
{
  Serial.begin(115200);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); 

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_send_cb(data_sent);

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }

  esp_now_register_recv_cb(data_receive);

  displayMenu();
}

void loop()
{
  char key = keypad.getKey();
  esp_err_t result;

  if (key != NO_KEY)
  {
    switch (key)
    {

    case 'L':
    currentSmileyIndex = (currentSmileyIndex - 1 + 14) % 14;
    displayMenu();
    break;

case 'R':
    currentSmileyIndex = (currentSmileyIndex + 1) % 14;
    displayMenu();
    break;

    case 'A':
      fullSize = !fullSize;
      displaySmiley(fullSize);

      sendData.smileyID = currentSmileyIndex;
      result = esp_now_send(broadcastAddress, (uint8_t *)&sendData, sizeof(sendData));

      if (result == ESP_OK)
      {
        Serial.println("Sent with success");
      }
      else
      {
        Serial.println("Error sending the data");
      }
      break;

    case 'S':
      fullSize = false;
      displayMenu();
      break;

    case 'T':
     
      screenOff = !screenOff;
      if (screenOff)
      {
        display.ssd1306_command(SSD1306_DISPLAYOFF);
      }
      else
      {
        display.ssd1306_command(SSD1306_DISPLAYON);
        //displayMenu();
      }
      break;

    case 'B':
      if (messageReceived && !screenOff)
      {
       
        display.clearDisplay();
        display.drawBitmap(0, 0, smileys[receivedData.smileyID], SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
        display.setCursor(0, 0);
       
        display.display();

        messageReceived = false;
      }
      break;
    }
  }
}
