// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>
#include <Adafruit_MLX90614.h>

MCP_CAN CAN0(9);                                      // Set CS to pin 9
//Direcciones de sensores
  Adafruit_MLX90614 Freno = Adafruit_MLX90614(0x5D);
  INT32U rxId;
  INT32U ide;
  unsigned char len = 0;
  unsigned char rxBuf[4];
  
//Guardado de datos
  int objeto4;
  unsigned char object4 [4];
  
void setup(){
  Freno.begin(); 
  Serial.begin(115200);
  // init can bus, baudrate: 500k
  if(CAN0.begin(CAN_500KBPS) == CAN_OK) Serial.print("can init ok!!\r\n");
  else Serial.print("Can init fail!!\r\n");
}

void loop(){
  leer_temperatura();
  CAN0.readMsgBuf(&len,rxBuf);
  ide=CAN0.getCanId();
  if(ide==2){
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  Serial.println("Sending packet ... ");
  enviar_freno();
  Serial.println("done"); 
}
}

void leer_temperatura(){
    Serial.println("Leemos temperatura");
  //LEEMOS LA TEMPERATURA
  objeto4=(int)Freno.readObjectTempC();
  sprintf (object4, "%03i", objeto4); 
}

/*void enviar_amortiguador(){
    if(objeto1>999){
  CAN0.sendMsgBuf(0x102, 0, 4, object1); 
  }else{
  CAN0.sendMsgBuf(0x12, 0, 4, object1); 
  }
}*/

void enviar_freno(){
  if(objeto4>999){
  CAN0.sendMsgBuf(0x102, 0, 4, object4); 
  }else{
  CAN0.sendMsgBuf(0x12, 0, 4, object4); 
  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
