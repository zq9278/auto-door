#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// �滻Ϊ���WiFi������Ϣ
const char* ssid = "SANITLOOK_2.4G";
const char* password = "slk888888";

// ����һ��Web���������˿�80
ESP8266WebServer server(80);

// GPIO���ź�
const int gpioPin = 0; // ʾ��ʹ��GPIO 0

void setup() {
  Serial.begin(115200);

  // ��ʼ��GPIO����Ϊ���ģʽ
  pinMode(gpioPin, OUTPUT);

  // ����WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("���ӵ�WiFi��IP��ַ: ");
  Serial.println(WiFi.localIP());

// �����Ŀ¼��������
server.on("/", [](){
  String html = 
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>" // ȷ��ҳ�����ֻ�����ȷ����
    "<style>"
    "body, html { "
    "  height: 100%; " // ����body��html�ĸ߶�Ϊ100%
    "  margin: 0; "
    "  padding: 0; "
    "  background-color: #000; "
    "  background-image: url('https://www.transparenttextures.com/patterns/stardust.png'); "  // ��������
    "}"
    "h1 { "
    "  text-align: center; "
    "  font-family: Arial, sans-serif; "
    "  color: white; "  // ��ɫ����
    "}"
    "@media only screen and (max-width: 600px) { " // ý���ѯ������ֻ���
    "  button { "
    "    display: block; "
    "    width: 80%; "  // ��ť��������Ļ���
    "    height: 10vh; " // ��ť�߶�Ϊ�ӿڸ߶ȵ�40%
    "    margin: 10px auto; "
    "    font-size: 18px; " // �����С
    "    background-color: #4CAF50; "
    "    color: white; "
    "    border: none; "
    "    border-radius: 5px; "
    "    cursor: pointer; "
    "  }"
    "  button:hover { "
    "    background-color: #45a049; "
    "  }"
    "}"
    "</style>"
    "</head>"
    "<body>"
    "<h1>���忭ҽ���Ž�</h1>"
    "<button onclick=\"toggleGPIO()\">����</button>"
    "<script>function toggleGPIO() { fetch('/toggle'); }</script>"
    "</body>"
    "</html>";

  server.send(200, "text/html", html);
});



  // �����л�GPIO״̬��������
  server.on("/toggle", [](){
     digitalWrite(gpioPin, LOW);
     delay(500);  
     digitalWrite(gpioPin, HIGH); 
    server.send(200, "text/plain", "GPIO״̬���л�");
  });

  // ����������
  server.begin();
}

void loop() {
  // ����ͻ�������
  server.handleClient();
}
