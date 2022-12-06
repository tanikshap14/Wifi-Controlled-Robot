#include<ESP8266WiFi.h>
const char* ssid="tanu";
const char* password="taniksha";
int IN1=12;
int IN2=13;  
int IN3=14;
int IN4=15;
WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  Serial.println();
  Serial.print("Connecting to");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(50);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println("Use this URL to connect:");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() 
{
  WiFiClient client=server.available();
  if(!client)
 {
  return;
  
  }
Serial.println("new client");
  while(!client.available())
  {
    delay(0.5);
    }
String request=client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    int value=LOW;
    if(request.indexOf("/motor=forward")!= -1)
    {
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      value=HIGH;
    }
   if(request.indexOf( "/motor=backward")!= -1)
     {
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      value=HIGH;
      }
      if(request.indexOf( "/motor=off")!= -1)
     {
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,HIGH);
      value=LOW;
      }
      if(request.indexOf( "/motor=rightside")!= -1)
     {
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,LOW);
      value=HIGH;
      }
      if(request.indexOf( "/motor=leftside")!= -1)
     {
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      value=HIGH;
      }
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type:text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.print("MOTOR is now:");
      if(value==HIGH)
      {
        client.print("ON");
      
        }
  else
  {
    client.print("OFF");
      
    }      
  client.println("<br><br>");

  client.println("<a href=\"/motor=forward\"\"><button>Turn forward </button></a>");
  client.println("<a href=\"/motor=backward\"\"><button>Turn backward </button></a><br/>");
  client.println("<a href=\"/motor=off\"\"><button>Turn off </button></a><br/>");
  client.println("<a href=\"/motor=off\"\"><button>Turn off </button></a><br/>");
  client.println("<a href=\"/motor=rightside\"\"><button>Right side </button></a><br/>");
  client.println("<a href=\"/motor=leftside\"\"><button>Left side </button></a><br/>");


  client.println("</html>");
  delay(1);
  Serial.println("Client disconnected");
  Serial.println(""); 
}
