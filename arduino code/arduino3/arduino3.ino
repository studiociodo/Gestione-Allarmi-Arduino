#include <Wire.h>             // libreria ufficiale
#include <MCP23017.h>         // https://github.com/kasperskaarhoj/MCP23017-Arduino-Library
#include <SPI.h>              // libreria ufficiale
#include <Ethernet.h>         // libreria ufficiale per W5100
#include <PubSubClient.h>     // https://github.com/Suxsem/pubsubclient

#define MCUNAME "arduino3"    // nome directory mqtt primario


MCP23017 GPIOchip1;           // inizializzo oggetti per moduli espansione
MCP23017 GPIOchip2; 


byte mac[]    = {  0x00, 0x08, 0xDC, 0xC1, 0x0D, 0x03 };      // imposta il mac address della LAN
IPAddress iplan (192, 168, 1, 103);                           // imposta l'indirizzo IP della LAN
IPAddress ipgw(192, 168, 1, 1);                                // imposta il gateway della LAN            
IPAddress subnet(255, 255, 255, 0);                           // imposta la netmask della LAN
IPAddress server(192, 168, 1, 100);                           // l'indirizzo del server MQTT


EthernetClient ethClient;                                     // inizializzo oggetti per la scheda LAN
PubSubClient client(ethClient);

long lastReconnectAttempt = 0;                                // variabili globali
String datainput = "FFFFFFFF";
String pinstatus = "FFFFFFFF";
uint8_t delivery = 0;
uint8_t fail = 0;


void setup()
{
  Serial.begin(57600);                                        // porta COM a 57600bps, solo per debug
  
  Serial.println(F("Init I2C"));
  delay(2000);
  Wire.begin();                                               // inizializza bus I2C
  GPIOchip1.begin(B000);                                      // inizializza gli integrati MCP23017
  GPIOchip2.begin(B001);  
  GPIOchip1.init();
  GPIOchip2.init(); 
  GPIOchip1.inputOutputMask(65535);                           // impostali tutti come input e abilita la resistenza interna di pullup
  GPIOchip1.internalPullupMask(65535);
  GPIOchip2.inputOutputMask(65535);
  GPIOchip2.internalPullupMask(65535);

  Serial.println(F("Init Ethernet"));
  client.setServer(server, 1883);                             // imposta l'IP del server
  client.setCallback(callback);                               // quando ricevi una risposta dala sottoscrizione avvia la funzione callback
  Ethernet.begin(mac, iplan, ipgw, subnet);                   // fai partire l'interfaccia di rete
  delay(10000);                                                // aspetta che parta

  
  lastReconnectAttempt = 0;
}


void loop()
{
  pinstatus = String(GPIOchip1.digitalWordRead(), HEX);                     // lettura di tutti i piedini degli integrati e creazione stringa
  while (pinstatus.length() < 4) pinstatus = "0" + pinstatus;
  pinstatus = String(GPIOchip2.digitalWordRead(), HEX) + pinstatus;
  while (pinstatus.length() < 8) pinstatus = "0" + pinstatus;
  pinstatus.toUpperCase();
  
  if(pinstatus != datainput) {                                              // se ci sono stati cambiamenti...
    if (delivery == 0){
      Serial.print(F("Sending "));
      Serial.println(pinstatus);
      delivery = delivery + 1;
      
      char senddata[16];
      pinstatus.trim();
      pinstatus.toCharArray(senddata, 17);
      client.publish("/"MCUNAME"/pinout",senddata, 1 , false);              // invia al server e aspettati una risposta
    } else {
      if (delivery <= 254){                                                 // ...anche per 254 volte se necessario...
        Serial.print(F("."));
        delivery = delivery + 1;
      
      char senddata[16];
      pinstatus.trim();
      pinstatus.toCharArray(senddata, 17);
      client.publish("/"MCUNAME"/pinout",senddata, 1 , false);
      } else {
        Serial.println(F("Reset!"));                                      // ...altrimenti mi resetto!
        pinMode(4, OUTPUT);
        digitalWrite(4, LOW);
        delay(200);
        pinMode(5, OUTPUT);
        digitalWrite(5, LOW);
      }
      
    }
    
    
    
  }
  
 
  
  if (!client.connected()) {                                        // se sei disconnesso dal server...
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {                        // prova a ricollegarti ogni 5 secondi...
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
        fail = 0;
        Serial.println(F("Done!"));                                 // ...se va bene ok...
      } else {
        fail = fail + 1;
        Serial.println(fail);
        if (fail == 30) {                                           // ...se fallisce resetta tutto!
          Serial.println(F("Reset!"));
          pinMode(4, OUTPUT);
        digitalWrite(4, LOW);
        delay(200);
        pinMode(5, OUTPUT);
        digitalWrite(5, LOW);
        }
      }
    }
  } else {

    client.loop();                                                  // funzione principale del protocollo MQTT
  }

}



boolean reconnect() {
  Serial.print(F("(Re)Connect "));
  if (client.connect( MCUNAME , "/"MCUNAME"/status", 1 ,false,"OFFLINE" )) {           // connettiti e lascia un messaggio di lastwill, viene mandato dopo 15 secondi da scollegata
    client.publish("/"MCUNAME"/status","OK", 1 , false);                               // manda un messaggio che informa il server che è connessa
    client.subscribe("/"MCUNAME"/check", 1);                                           // canale di ritorno sottoscritto
  }
  return client.connected();
}


void callback(char* topic, byte* payload, unsigned int length) {

  payload[length] = '\0';        
String received = String((char*)payload);
if (received = pinstatus) {                                                             // se dalla sottoscrizione hai ricevuto lo stesso che hai inviato al server...
  datainput = pinstatus;                                                                // ...aggiorna l'informazione sull'ultimo stato...
  if (delivery != 0){
    Serial.println(F("OK!"));
  }
  delivery = 0;                                                                        // e smettila di inviare!
  
}

  
}
