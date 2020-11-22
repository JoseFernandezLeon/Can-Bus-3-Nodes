#include <mcp_can.h>
#include <SPI.h>

INT32U id_tope=0x102;
INT32U rxanterior;
INT32U rxId;
unsigned char len = 0;
unsigned char rxBuf[4]={'A','B','C','D'};
int j=3;
int temp_int;
int temperatura=0;
int inicio=1;
INT32U id_controlador=0x01;


//Temperaturas finales a guardar
int temperatura_B=0;
int temperatura_A=0;

MCP_CAN CAN0(9);                               // Set CS to pin 9


void setup()
{
  Serial.begin(115200);
  CAN0.begin(CAN_500KBPS);                       // init can bus : baudrate = 500k 
  Serial.println("MCP2515 Library Receive...");
  CAN0.sendMsgBuf(0x01,0,4,rxBuf);
}

void loop()
{     
  //PODEMOS METER UN LOOP PARA INICIAR EL SISTEMA, SI NO TENDRIAMOS QUE INICIAR PRIMERO LOS SENDER ANTES DEL RECEPTOR
      delay(2);
      CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxId = CAN0.getCanId();                    // Get message ID
      if(rxId>=100){
        j=3;
        temperatura=0;
      }else{
        j=2;
        temperatura=0;
      }
      leer_paquete();
      if(rxId>10){
      imprimir_pantalla();
      }
      if(rxId!=rxanterior){
      if(rxId>=id_tope){
              Serial.println("enviar siguiente");
        CAN0.sendMsgBuf(0x01,0,4,rxBuf);      
      }else{
              Serial.println("enviar siguiente");
        CAN0.sendMsgBuf(0x02,0,4,rxBuf); 
      }
      }
      rxanterior=rxId;
      }

void leer_paquete(){
        for(int i = 0; i<len; i++)                // Print each byte of the data
      {
        if(j>=0){
        temp_int=(rxBuf[i] -'0');
        temperatura=temperatura+temp_int*pow(10,j);
        }
        j=j-1;
      }
}

void ordenar(){
 if(rxId==11 ||rxId==101){
        temperatura_A=temperatura;
      }
      if(rxId==12 ||rxId==102){
        temperatura_B=temperatura;
      }
}

void imprimir_pantalla(){
      Serial.print("ID: ");
      Serial.print(rxId,HEX);
      Serial.print("  Data: ");  
      Serial.print(temperatura);
      Serial.println();      
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
