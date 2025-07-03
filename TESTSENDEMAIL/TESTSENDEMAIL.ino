#include <Arduino.h>
#include <WiFi.h>  // assuming ESP32; change if you use ESP8266

#include <ESP_Mail_Client.h>

// Wi-Fi credentials
#define WIFI_SSID "............."
#define WIFI_PASSWORD "............"

// Email account (App Password must be used)
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465  // SSL port

#define AUTHOR_EMAIL "................."
#define AUTHOR_PASSWORD ".............."  // App password from Google
#define RECIPIENT_EMAIL "................."

SMTPSession smtp;

void smtpCallback(SMTP_Status status)
{
  Serial.println(status.info());
  if (status.success())
  {
    Serial.printf("Email sent successfully! Sent count: %d, Failed count: %d\n", status.completedCount(), status.failedCount());
    smtp.sendingResult.clear();
  }
}

void connectWiFi()
{
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
}

void sendEmail()
{
  Session_Config config;
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;
  config.login.user_domain = F("127.0.0.1");

  // Time settings (adjust timezone)
  config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
  config.time.gmt_offset = 3;  // your timezone offset
  config.time.day_light_offset = 0;

  if (!smtp.connect(&config))
  {
    Serial.printf("SMTP connection failed. Code: %d Reason: %s\n", smtp.statusCode(), smtp.errorReason().c_str());
    return;
  }

  if (!smtp.isLoggedIn())
  {
    Serial.println("Not logged in!");
    return;
  }

  smtp.callback(smtpCallback);
  smtp.debug(1);

  SMTP_Message message;
  message.sender.name = F("ESP32");
  message.sender.email = AUTHOR_EMAIL;
  message.subject = F("Hello from ESP32");
  message.addRecipient(F("Receiver"), RECIPIENT_EMAIL);

  message.text.content = F("Hello world");
  message.text.charSet = F("utf-8");
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  if (!MailClient.sendMail(&smtp, &message))
  {
    Serial.printf("Error sending Email. Code: %d Reason: %s\n", smtp.statusCode(), smtp.errorReason().c_str());
  }

  smtp.closeSession();
}

unsigned long lastEmailSent = 0;
const unsigned long interval = 60000;  // 60 seconds

void setup()
{
  Serial.begin(115200);
  connectWiFi();
}

void loop()
{
  unsigned long now = millis();
  if (now - lastEmailSent > interval || lastEmailSent == 0)
  {
    sendEmail();
    lastEmailSent = now;
  }
}
