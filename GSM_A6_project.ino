#include <LiquidCrystal.h>
#include "SIM900.h"
#include <SoftwareSerial.h>
#include "sms.h"
SMSGSM sms;


int numdata;
boolean started=false;
char smsbuffer[160];
char n[20],number[20]="01515213864";

int i;

const int rs = 6, en = 7, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int mod=0;


#define load1 A0
#define load2 A1
#define load3 A2
#define load4 A3

int L1,L2,L3,L4,LA;


void setup()
{

  L1=0;
  L2=0;
  L3=0;
  L4=0;
  LA=0;
   Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Starting....");
  delay(1000);
  pinMode(load1, OUTPUT);
  pinMode(load2, OUTPUT);
  pinMode(load3, OUTPUT);
  pinMode(load4, OUTPUT);


    digitalWrite(load1,1);
    digitalWrite(load2,1);
    digitalWrite(load3,1);
    digitalWrite(load4,1);
 
   Serial.println("GSM Shield testing.");
    if (gsm.begin(4800)) {
          Serial.println("\nstatus=READY");
          started=true;
     } else Serial.println("\nstatus=IDLE");

     if(started) {
         
          if (sms.SendSMS(number, "Device is ready to take command")){
          Serial.println("\nSMS sent OK");
          }
          for (i = 1; i <= 20; i++)
           {
             sms.DeleteSMS(i);
           }
     }

   lcd.setCursor(0, 0);
  lcd.print("Starting....");
  delay(3000);

    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("L1 Off");
    lcd.setCursor(8, 0);
    lcd.print("L2 Off");
    lcd.setCursor(0, 1);
    lcd.print("L3 Off");
    lcd.setCursor(8, 1);
    lcd.print("Auto");

}


void lod1(int a) {

  digitalWrite(load1, a);
  if (a == 0) {
    Serial.println("LOAD 1 ON");
    if (sms.SendSMS(number, "Load 1 On")) {
      Serial.println("\nSMS sent OK");

    }
    lcd.setCursor(0, 0);
    lcd.print("L1  On");

  }
  if (a == 1) {
    Serial.println("LOAD 1 off");
    if (sms.SendSMS(number, "Load 1 Off")) {
      Serial.println("\nSMS sent OK");

    }
    lcd.setCursor(0, 0);
    lcd.print("L1 Off");
  }
}

void lod2(int a) {

  digitalWrite(load2, a);
  if (a == 0) {
    if (sms.SendSMS(number, "Load 2 On")) {
      Serial.println("\nSMS sent OK");

    }
    lcd.setCursor(8, 0);
    lcd.print("L2  On");
  }
  if (a == 1) {
    if (sms.SendSMS(number, "Load 2 Off")) {
      Serial.println("\nSMS sent OK");

    }
    lcd.setCursor(8, 0);
    lcd.print("L2 Off");
  }
}

void lod3(int a) {

  digitalWrite(load3, a);
  if (a == 0) {
    if (sms.SendSMS(number, "Load 3 On")) {
      Serial.println("\nSMS sent OK");

    }
    lcd.setCursor(0, 1);
    lcd.print("L3  On");
  }
  if (a == 1) {
    if (sms.SendSMS(number, "Load 3 Off")) {
      Serial.println("\nSMS sent OK");

    }
    lcd.setCursor(0, 1);
    lcd.print("L3 Off");
  }
}

void lod4(int a) {

  digitalWrite(load4, a);
  if (a == 1) {
    if (sms.SendSMS(number, "Auto  ")) {
      Serial.println("\nSMS sent OK");

    }
    lcd.setCursor(8, 1);
    lcd.print("Auto  ");
  } if (a == 0) {
    if (sms.SendSMS(number, "Manual")) {
      Serial.println("\nSMS sent OK");

    }
    lcd.setCursor(8, 1);
    lcd.print("Manual");
  }
}

void all(int a) {


  digitalWrite(load1, a);
  digitalWrite(load2, a);
  digitalWrite(load3, a);
  if (a == 0) {
    if (sms.SendSMS(number, "ALL Load  On")) {
      Serial.println("\nSMS sent OK");

    }
    
    lcd.setCursor(0, 0);
    lcd.print("L1  On");
    lcd.setCursor(8, 0);
    lcd.print("L2  On");
    lcd.setCursor(0, 1);
    lcd.print("L3  On");
    
  } if (a == 1) {
    if (sms.SendSMS(number, "ALL Load  Off")) {
      Serial.println("\nSMS sent OK");

    }
    lcd.setCursor(0, 0);
    lcd.print("L1 Off");
    lcd.setCursor(8, 0);
    lcd.print("L2 Off");
    lcd.setCursor(0, 1);
    lcd.print("L3 Off");
    
  }
}

void del(){

  for (i = 1; i <= 20; i++)
           {
             sms.DeleteSMS(i);
           }

}



void loop()
{
  String sms_text;
  
  if(started) {
          //Read if there are messages on SIM card and print them.
     
        if(gsm.readSMS(smsbuffer, 160, n, 20)) {
               Serial.println(n);
               Serial.println(smsbuffer);
               
          }
         
          //get 1st sms
          sms.GetSMS(1,n,20,smsbuffer,160);
          Serial.println(n);
          Serial.println(smsbuffer);
          sms_text=smsbuffer;
         


      String re=sms_text;
      Serial.print(re);

      
     if(mod==0)
      {
      if (re=="LOAD1ON"&&L1==0) {
        //Serial.print("Load 1");
        del();
        lod1(0);
        L1=1;

      }
      if (re=="LOAD1OFF"&&L1==1) {
        //Serial.print("Load f");
        del();
        lod1(1);
        L1=0;
      }

      if (re=="LOAD2ON"&&L2==0) {
        // Serial.print("Load 1");
        del();
        lod2(0);
        L2=1;
      }
      if (re=="LOAD2OFF"&&L2==1) {
        // Serial.print("Load f");
        del();
        lod2(1);
        L2=0;
      }

      if (re=="LOAD3ON"&&L3==0) {
        //Serial.print("Load 1");
        del();
        lod3(0);
        L3=1;
      }
      if (re=="LOAD3OFF"&&L3==1) {
        //Serial.print("Load f");
        del();
        lod3(1);
        L3=0;
      }

      if (re=="ALLON"&&LA==0) {
        //  Serial.print("Load f");
        del();
        all(0);

        L1=1;
        L2=1;
        L3=1;
        LA=1;

      }
      if (re=="ALLOFF"&&LA==1) {
        //  Serial.print("Load f");
        del();
        all(1);
        
        L1=0;
        L2=0;
        L3=0;      
        LA=0;

      }

      
      }

      if (re=="AUTO"&&L4==1) {
        Serial.print("Auto");
        del();
        lod4(1);
        L4=0;
        mod=0;

      }
      if (re=="MANUAL"&&L4==0) {
         Serial.print("Manual");
        del();
        lod4(0);
        L4=1;
        mod=1;

      }
      


    }
    else
    {
      Serial.println("NO NEW SMS,WAITTING");
    }
    delay(500);
  }




