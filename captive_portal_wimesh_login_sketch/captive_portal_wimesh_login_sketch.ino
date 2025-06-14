#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h> // Thư viện cần thiết cho HTTPS

const char* ssid = "Wi-MESH";
const char* password = "";

// --- THÔNG TIN BẠN CUNG CẤP ---
const char* portal_post_url = "https://login.net.vn/login";
// Dữ liệu payload phải ở dạng String hoặc const char* để POST
String portal_form_data = "dst=http%3A%2F%2Fwww.msftconnecttest.com%2Fredirect&popup=true&username=W906DDAR&password=3782";

// Tạo một đối tượng WiFiClientSecure để xử lý HTTPS
WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  Serial.println(ssid);
  Serial.println(password);
  WiFi.begin(ssid, password);
  Serial.println(WiFi.status());

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected! IP: " + WiFi.localIP().toString());
  
  // Rất quan trọng cho HTTPS: Bỏ qua xác thực chứng chỉ SSL/TLS.
  // Môi trường Captive Portal thường có chứng chỉ tự ký hoặc không hợp lệ.
  // Dòng này nói với ESP32: "Cứ tin tưởng server đi, đừng kiểm tra chứng chỉ".
  client.setInsecure(); 

  delay(2000);

  // Giả sử chúng ta biết mình đang ở trong captive portal và cần login
  Serial.println("Attempting to login to Captive Portal...");
    
  HTTPClient http;

  // Bắt đầu kết nối HTTPS, truyền đối tượng WiFiClientSecure vào
  if (http.begin(client, portal_post_url)) {
    
    // Thêm các header để giả lập trình duyệt
    http.addHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7");
    http.addHeader("Accept-Encoding", "gzip, deflate, br, zstd");
    http.addHeader("Accept-Language", "vi,en-US;q=0.9,en;q=0.8");
    http.addHeader("Cache-Control", "max-age=0");
    http.addHeader("Connection", "keep-alive");
    http.addHeader("Content-Length", "94");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    http.addHeader("Cookie", "_ga_5KED5SHEXB=GS2.1.s1749890115$o1$g1$t1749890311$j54$l0$h0; exRun=EX_LOGIN; exKey=IM_CC960022BFDB8A11E152F0DF800438C4; _ga=GA1.3.1171173223.1749890116; _gid=GA1.3.486642059.1749890999; _gat_gtag_UA_70257152_7=1");
    http.addHeader("Host", "login.net.vn");
    http.addHeader("Origin", "https://ex.login.net.vn");
    http.addHeader("Referer", "https://ex.login.net.vn/");
    http.addHeader("Sec-Fetch-User", "?1");
    http.addHeader("Upgrade-Insecure-Requests", "1");
    http.addHeader("sec-ch-ua", "\"Microsoft Edge\";v=\"137\", \"Chromium\";v=\"137\", \"Not/A)Brand\";v=\"24\"");
    http.addHeader("sec-ch-ua-mobile", "?0");
    http.addHeader("sec-ch-ua-platform", "\"Windows\"");

    Serial.println("Sending POST request...");
    // Gửi yêu cầu POST với dữ liệu đã có
    int httpResponseCode = http.POST(portal_form_data);

    if (httpResponseCode > 0) {
      Serial.printf("POST request sent. HTTP Response code: %d\n", httpResponseCode);
      
      // Đọc và in ra nội dung phản hồi từ server để debug
      String payload = http.getString();
      Serial.println("Response payload:");
      Serial.println(payload);

    } else {
      Serial.printf("Error on sending POST: %s\n", http.errorToString(httpResponseCode).c_str());
    }
    
    http.end();
  } else {
    Serial.printf("[HTTP] Unable to connect to %s\n", portal_post_url);
  }

  // Đợi một chút và kiểm tra lại xem đã có Internet thật sự hay chưa
  // ... (code kiểm tra Internet như các ví dụ trước) ...
}

void loop() {
  // Main code
}