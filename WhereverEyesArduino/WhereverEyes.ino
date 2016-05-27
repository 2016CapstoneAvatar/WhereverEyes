
#include<SoftwareSerial.h>  // �뇡遺억펷占쎈떮占쎈뮞 占쎈꽰占쎈뻿占쎌뱽 占쎌맄占쎈립 SoftwareSerial 占쎌뵬占쎌뵠�뇡�슢�쑎�뵳�됵옙占� �겫�뜄�쑎占쎌궔占쎈뼄.
#include<Servo.h>
byte buffer[2048]; // 占쎈쑓占쎌뵠占쎄숲 占쎈땾占쎈뻿 甕곌쑵�쓠
int bufferPosition; // 甕곌쑵�쓠占쎈퓠 疫꿸퀡以됵옙釉� 占쎌맄燁삼옙

Servo yawServo;
Servo pitchServo;

float accrueYawValue=0.0f;
float changeYawAngle=0.0f;
float nowYawValue=90.0f;
float nowPitchValue=45.0f;

float beforeYawValue=0.0f;

float differencePitch=0.0f;
float differenceYaw=0.0f;
int nowPitchLevel=1;

boolean start=false;

void setup () {
  yawServo.attach(9);
  pitchServo.attach(2);
  
  Serial.begin(9600);
  Serial.println("  Arduino start! ");
  delay(1000);
  yawServo.write(90);
  pitchServo.write(45);
  delay(1000);
        
}

void loop () {
  
  if (Serial.available()) {
      int yawVal= Serial.parseInt();
      int pitchVal= Serial.parseInt();
      if(yawVal>0 && yawVal<360 && pitchVal<0 && pitchVal >=-90)
      {
        Serial.println(yawVal); 
        Serial.println(pitchVal);
        if(start) angleSet(yawVal,nowYawValue, pitchVal); //獄쏄퀣肉� 占쎈뼄 筌�袁⑹뒭�⑨옙 占쎈뻻占쎌삂
        
        nowYawValue = yawServo.read();            //占쎌돳占쎌읈占쎈립 占쎌뜎占쎌벥 占쎌겱占쎌삺 占쎄퐣癰귣��걟占쎄숲占쎌벥 占쎌돳占쎌읈揶쏅�れ몵嚥∽옙 nowvalue 占쎈땾占쎌젟.
        nowPitchValue = pitchServo.read(); 
        Serial.print("nowYaw : ");
        Serial.println(nowYawValue);
        
        Serial.print("nowPitch : ");
        Serial.println(nowPitchValue);
        
        beforeYawValue=yawVal;
        
        start=true;
      }       
  }
}


void angleSet(int yawVal, float nowYawValue, int pitchVal){ // 占쎈툧占쎈굡嚥≪뮇�뵠占쎈굡 疫꿸퀣�뒻疫꿸퀗而わ옙�뱽 占쎈꽰占쎈퉸 占쎄퐣癰귣��걟占쎄숲�몴占� 占쎌젫占쎈선占쎈릭占쎈뮉 占쎈맙占쎈땾
    
    float differenceYaw=0;
    differenceYaw=yawVal- beforeYawValue; // 占쎌겱占쎌삺揶쏉옙 - 占쎌읈揶쏉옙

    if(differenceYaw < - 275)  // 365占쎈퓠占쎄퐣 0占쎌몵嚥∽옙 癰귨옙占쎈뻥占쎌뱽 占쎈르      now 10 before 365  -365
    {
          changeYawAngle = ( yawVal+365-beforeYawValue); // 10+ 365 - 365        /// 365 - >0  占쎌궎�몴紐꾠걹 獄쎻뫚堉� 
    }
    else if(differenceYaw > 275)  // 0占쎈퓠占쎄퐣 365嚥∽옙 癰귨옙占쎈뻥占쎌뱽 占쎈르  now 365  before 10
    {
      changeYawAngle = -(beforeYawValue+365-yawVal); // -( 10 + 365- 365) 
    }
    else changeYawAngle = differenceYaw; //占쎌젟占쎄맒占쎌읅占쎌뵥 占쎌돳占쎌읈                       // 0占쎈퓠占쎄퐣 365占쎈뮉 占쎌뇢筌잞옙 獄쎻뫚堉� 

   int settingYawValue= round(-changeYawAngle); //占쎈섰筌띾뜄彛뷂옙寃� 占쎌돳占쎌읈占쎈퉸占쎈튊 占쎈릭占쎈뮉筌욑옙 value 獄쏆룇釉섓옙�긾. 獄쎻뫚堉� 占쎄퐬占쎌젟  
   int settingPitchValue=0;
   
    if( (nowYawValue-changeYawAngle) < 0){ // 0癰귣��뼄 占쎈쐭 占쎌삂占쎈툡筌욑옙疫뀐옙 占쎌뜚占쎈립占쎈뼄筌롳옙 0占쎌몵嚥∽옙 �⑥쥙�젟占쎈뻻�녹뮆�뵬. 
      yawServo.write(0);
      settingYawValue=0;
    } 
    else if( (nowYawValue-changeYawAngle >180) ){ // 180癰귣��뼄 �뚣끉占쏙쭖占� 180占쎌몵嚥∽옙 �⑥쥙�젟
      yawServo.write(180); //筌뤴뫂苑ｏ옙�벥 占쎈립�④쑴肉됵옙苑뚳옙�뮉 筌롫뜆�븘
      settingYawValue=0;
    }
    pitchVal=-pitchVal;
    
    if(pitchVal <=15){
      settingPitchValue=nowPitchValue-90;
    }
    else if(pitchVal <25){
      settingPitchValue = nowPitchValue-79;
    }
    else if(pitchVal <=32){
      settingPitchValue=nowPitchValue-64;
    }else if(pitchVal <=49){
      settingPitchValue=nowPitchValue-45;
    }
    else if(pitchVal <=57){
      settingPitchValue=nowPitchValue-33;
    }
    else if(pitchVal <=64){
      settingPitchValue=nowPitchValue-22;
    }else if(pitchVal <=70){
      settingPitchValue=nowPitchValue-11;
    }else {
      settingPitchValue=0;
    }
    //settingValue揶쏉옙 占쎈펶占쎌뵠筌롳옙 占쎈툡占쎌삋嚥≪뮆沅∽옙�젻揶쏉옙  占쎌벉占쎌뵠筌롳옙 占쎌맄嚥∽옙
    
    int forUpYawCount=0;
    int forDownYawCount=0;
    
    int forUpPitchCount=0;
    int forDownPitchCount=0;
    boolean passYaw=false;
    boolean onPitchMove=false;

    settingPitchValue=-settingPitchValue;

    if(abs(settingYawValue)>=1) {
      accrueYawValue+=settingYawValue;
    }
    while(true)
    {
       delay(15);
       if(settingYawValue > 10 && settingYawValue>forUpYawCount) // 占쎈펶占쎌벥 揶쏉옙 占쎌돳占쎌읈 // 
       {
         yawServo.write(nowYawValue+forUpYawCount+1); // forUpCount揶쏉옙 1嚥∽옙 筌욑옙占쎈꺗占쎈┷筌롳옙  300 -> 301 揶쏉옙�⑨옙 域밸챸�뜎嚥∽옙 �⑥쥙�젟占쎈쭡.
                                           // 300 301 301 301 301   .... 300 301 302 303 
         forUpYawCount++;
         accrueYawValue=0;
       }
       else if(settingYawValue <-10 && settingYawValue<forDownYawCount )               //占쎌벉占쎌벥 揶쏉옙 占쎌돳占쎌읈
       {
         yawServo.write(nowYawValue+forDownYawCount-1);
         forDownYawCount--;
         accrueYawValue=0;
       }
       else if(accrueYawValue>10 || accrueYawValue<-10 && forUpYawCount==0 && forDownYawCount==0)
       {
        if(accrueYawValue>10)
        {
          for(int k=1; k<=accrueYawValue; k++)
         {
          delay(25);
          yawServo.write(nowYawValue+k);
         }
        }
        else if(accrueYawValue<-10)
        {
          for(int k=1; k<=abs(accrueYawValue); k++)
         {
          delay(25);
          yawServo.write(nowYawValue-k);
         }
        }
        accrueYawValue=0;
       }
          
       if(settingPitchValue >0 && settingPitchValue >forUpPitchCount)
       {
          onPitchMove=true;
          pitchServo.write(nowPitchValue+forUpPitchCount+1);
          forUpPitchCount++;
       }
       else if(settingPitchValue <0 && settingPitchValue <forDownPitchCount)
       {
          onPitchMove=true;
          pitchServo.write(nowPitchValue+forDownPitchCount-1);
          forDownPitchCount--;
       }
//       if( -10<=settingYawValue && settingYawValue <=10) passYaw=true;
       if( (settingYawValue == forUpYawCount || settingYawValue ==forDownYawCount || ( -10<=settingYawValue && settingYawValue <=10))
                  && (settingPitchValue ==forUpPitchCount || settingPitchValue ==forDownPitchCount || onPitchMove==false ) ) break;
    }     
}


