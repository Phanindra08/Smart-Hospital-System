///////////////////////////////////////////////////////////////////////
////  For Ventilator Machines                         ///
///////////////////////////////////////////////////////////////////////
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <InfluxDb.h>
#include <WiFiClient.h> 
const char *ssid = "Helix 4G";
const char *password = "Snowdeni386";
#define INFLUXDB_HOST "192.168.1.104"
#define INFLUXDB_PORT "8086"
#define INFLUXDB_DATABASE "mydb"
#define INFLUXDB_USER "admin"
#define INFLUXDB_PASS "admin"
long randNumber;
Influxdb influx("192.168.1.104", 8086);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_OFF); //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  WiFi.begin(ssid,password);     //Connect to your WiFi router
  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    //Serial.print(".");
  }
  //If connection successful show IP address in serial monitor
  //Serial.println("");
  //Serial.print("Connected to ");
  //Serial.println(ssid);
  //Serial.print("IP address: ");
  //Serial.println(WiFi.localIP());
  influx.setDb(INFLUXDB_DATABASE);
  //influx.setDbAuth(INFLUXDB_DATABASE,"admin","admin");
}

void loop() {
  //Serial.println("Sending data to InfluxDB");
  String mid[] = {"1000","1001","1002","1003","1004","1005"};
  for(int ik=0; ik<6; ik++){
    InfluxData row("ventilator");
    row.addTag("mid", mid[ik]);
    row.addTag("typeParam", "breathingRate");
    row.addValue("value", random(10, 30));
    boolean success = influx.write(row);
    Serial.println(success);
  }
    for(int ik=0; ik<6; ik++){
    InfluxData row("dialysis");
    row.addTag("mid", mid[ik]);
    row.addTag("room", "512");
    row.addValue("value", random(60, 120));
    boolean success = influx.write(row);
    //Serial.println(success);
  }
  delay(5000);
}
