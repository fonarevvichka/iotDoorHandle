#include <ESP8266WiFi.h>
//------------------ Pin Setup -----------------------//
#define MOSFETPIN 14
//------------------ Pin Setup -----------------------//

//------------------- Wifi Setup -----------------------//
const char* ssid = "";
const char* wifiPassword = "";
const String password = "test123"
String userPassword = "";
//------------------- Wifi Setup -----------------------//

WiFiServer server(80);

String header;

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println();
  Serial.println();
  Serial.println();

  Serial.print("Connecting to");
  Serial.print(ssid);
  WiFi.begin(ssid, wifiPassword);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  server.begin();
  Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
}

String prepareHtmlPage() {
  String htmlPage =
    String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response"  + "\n"  + "\n" +
            "\n"
            "<!DOCTYPE HTML>"  + "\n" +
            "<html>"  + "\n" +
            "<head>"  + "\n" +
            "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"  + "\n" +
            "<link rel=\"icon\" href=\"data:,\">"  + "\n" + 
            "<style>"  + "\n" +
            "body {"  + "\n" +
            "text-align: center;"  + "\n" +
            "font-family: \"Trebuchet MS\", Arial;"  + "\n" +
            "margin-left:auto;"  + "\n" +
            "margin-right:auto;"  + "\n" +
            "}"  + "\n" +
            "</style>"  + "\n" +
            "<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>"  + "\n" +
            "</head>"  + "\n" +
            "<body>"  + "\n" +
            "<button type=\"button\" id=\"pushButton\"  onclick=\"servo()\" />START KETTLE</button>"  + "\n" +
            "<script>"  + "\n" +
            "$.ajaxSetup({timeout:1000});"  + "\n" +
            "function servo() {"  + "\n" +
            "$.get(\"?value=\" + \"20\" + \"&\");"  + "\n" +
            "console.log(\"button pushed\")"  + "\n" +
            "{Connection: close};"  + "\n" +
            "}"  + "\n" +
            "</script>"  + "\n" +
            "</body>"  + "\n" +
            "</html>"  + "\n" +
            "\r\n";
  return htmlPage;
}

void loop() {
  header = "";
  String currentLine = "";
  
	WiFiClient client = server.available();
	
	if (client) {
    	Serial.print("new client");
    	while (client.connected()) {
			if (client.available()) {
				char c = client.read();
			   	Serial.write(c); //DATA ABOUT THE CLIENT
			   	header += c;
			   	if (c == '\n') {
					if (currentLine.length() == 0) {
						client.println(prepareHtmlPage()); //displays page
						if (header.indexOf("GET /?value=")>=0) { //checks for button press
							//code when button is pushed
							for (int i = 0; i < sizeof(validMacs); i++) {
								if (password == userPassword) {
									//unlock door
								}
							}
						}
					client.println();
				  	break;
				} else { currentLine = "";}
			  } else if (c != '\r') {
					currentLine += c;
			  }
		}
   }
    header = "";
    delay(1);

    client.stop();
    Serial.println("[Client disonnected]");
  }
}
