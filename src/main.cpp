#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// 替换为你的WiFi网络信息
const char* ssid = "SANITLOOK_2.4G";
const char* password = "slk888888";

// 创建一个Web服务器，端口80
ESP8266WebServer server(80);

// GPIO引脚号
const int gpioPin = 0; // 示例使用GPIO 0

void setup() {
  Serial.begin(115200);

  // 初始化GPIO引脚为输出模式
  pinMode(gpioPin, OUTPUT);

  // 连接WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("连接到WiFi，IP地址: ");
  Serial.println(WiFi.localIP());

// 定义根目录的请求处理
server.on("/", [](){
  String html = 
    "<!DOCTYPE html>"
    "<html>"
    "<head>"
    "<meta name='viewport' content='width=device-width, initial-scale=1.0'>" // 确保页面在手机上正确缩放
    "<style>"
    "body, html { "
    "  height: 100%; " // 设置body和html的高度为100%
    "  margin: 0; "
    "  padding: 0; "
    "  background-color: #000; "
    "  background-image: url('https://www.transparenttextures.com/patterns/stardust.png'); "  // 星链背景
    "}"
    "h1 { "
    "  text-align: center; "
    "  font-family: Arial, sans-serif; "
    "  color: white; "  // 白色标题
    "}"
    "@media only screen and (max-width: 600px) { " // 媒体查询，针对手机端
    "  button { "
    "    display: block; "
    "    width: 80%; "  // 按钮宽度相对屏幕宽度
    "    height: 10vh; " // 按钮高度为视口高度的40%
    "    margin: 10px auto; "
    "    font-size: 18px; " // 字体大小
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
    "<h1>晟洛凯医疗门禁</h1>"
    "<button onclick=\"toggleGPIO()\">开关</button>"
    "<script>function toggleGPIO() { fetch('/toggle'); }</script>"
    "</body>"
    "</html>";

  server.send(200, "text/html", html);
});



  // 定义切换GPIO状态的请求处理
  server.on("/toggle", [](){
     digitalWrite(gpioPin, LOW);
     delay(500);  
     digitalWrite(gpioPin, HIGH); 
    server.send(200, "text/plain", "GPIO状态已切换");
  });

  // 启动服务器
  server.begin();
}

void loop() {
  // 处理客户端请求
  server.handleClient();
}
