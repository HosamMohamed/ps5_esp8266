//-------------------Original Code By Stooged---------------------------//
//----------Idlesouce Implementation By Hossam Mohamed------------------//
//----------------------------------------------------------------------//
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <FS.h>


#define FILESYS SPIFFS


ADC_MODE(ADC_VCC);
ESP8266WebServer webServer;
ESP8266WebServerSecure sWebServer(443);


//-------------------DEFAULT SETTINGS------------------//

//create access point
String AP_SSID = "PS5_ESP8266";
String AP_PASS = "1234567890";
IPAddress Server_IP(10,1,1,1);
IPAddress Subnet_Mask(255,255,255,0);


//server port
int WEB_PORT = 80;


//-----------------------------------------------------//

static const char serverCert[] = "-----BEGIN CERTIFICATE-----\r\nMIIC1DCCAj2gAwIBAgIUFQgjEtkNYfmrrpNQKHVNl3+dl08wDQYJKoZIhvcNAQEL\r\nBQAwfDELMAkGA1UEBhMCVVMxEzARBgNVBAgMCkNhbGlmb3JuaWExEDAOBgNVBAcM\r\nB0ZyZW1vbnQxDDAKBgNVBAoMA2VzcDEMMAoGA1UECwwDZXNwMQwwCgYDVQQDDANl\r\nc3AxHDAaBgkqhkiG9w0BCQEWDWVzcEBlc3AubG9jYWwwHhcNMjEwMjIxMDAwMDQ4\r\nWhcNNDMwNzI4MDAwMDQ4WjB8MQswCQYDVQQGEwJVUzETMBEGA1UECAwKQ2FsaWZv\r\ncm5pYTEQMA4GA1UEBwwHRnJlbW9udDEMMAoGA1UECgwDZXNwMQwwCgYDVQQLDANl\r\nc3AxDDAKBgNVBAMMA2VzcDEcMBoGCSqGSIb3DQEJARYNZXNwQGVzcC5sb2NhbDCB\r\nnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAsrfFqlV5H0ajdAkkZ51HTOseOjYj\r\nNiaUD4MA5mIRonnph6EKIWb9Yl85vVa6yfVkGn3TFebQ96MMdTfZgLuP4ryCwe6Y\r\n+tZs2g6TjGbR0O6yuA8wQ2Ln7E0T05C8oOl88SGNV4tVL6hz64oMzuVebVDo0J9I\r\nybvL0O/LhMvC4x8CAwEAAaNTMFEwHQYDVR0OBBYEFCMQIU+pZQDVySXejfbIYbLQ\r\ncLXiMB8GA1UdIwQYMBaAFCMQIU+pZQDVySXejfbIYbLQcLXiMA8GA1UdEwEB/wQF\r\nMAMBAf8wDQYJKoZIhvcNAQELBQADgYEAFHPz3YhhXQYiERTGzt8r0LhNWdggr7t0\r\nWEVuAoEukjzv+3DVB2O+56NtDa++566gTXBGGar0pWfCwfWCEu5K6MBkBdm6Ub/A\r\nXDy+sRQTqH/jTFFh5lgxeq246kHWHGRad8664V5PoIh+OSa0G3CEB+BXy7WF82Qq\r\nqx0X6E/mDUU=\r\n-----END CERTIFICATE-----";
static const char serverKey[] = "-----BEGIN PRIVATE KEY-----\r\nMIICdgIBADANBgkqhkiG9w0BAQEFAASCAmAwggJcAgEAAoGBALK3xapVeR9Go3QJ\r\nJGedR0zrHjo2IzYmlA+DAOZiEaJ56YehCiFm/WJfOb1Wusn1ZBp90xXm0PejDHU3\r\n2YC7j+K8gsHumPrWbNoOk4xm0dDusrgPMENi5+xNE9OQvKDpfPEhjVeLVS+oc+uK\r\nDM7lXm1Q6NCfSMm7y9Dvy4TLwuMfAgMBAAECgYEApKFbSeyQtfnpSlO9oGEmtDmG\r\nT9NdHl3tWFiydId0fTpWoKT9YwWvdnYIB12klbQicbDkyTEl4Gjnafd3ufmNsaH8\r\nZ9twopIdvvWDvGPIqGNjvTYcuczpXmQWiUnG5OTiVWI1XuZa3uZEGSFK9Ra6bE4g\r\nG2xklGZGdaqqcd6AVhECQQDnBXVXwBxExxSFppL8KUtWgyXAvJAEvkzvTOQfcCel\r\naIM5EEUofB7WZeMtDEKgBtoBl+i5PP+GnDF0zsjDFx2nAkEAxgqVQii6zURSVE2T\r\niJDihySXJ2bmLJUjRIi1nCs64I9Oz4fECVvGwZ1XU8Uzhh3ylyBSG2HjhzA5sTSC\r\n1a/tyQJAOgE12EWFE4PE1FXhm+ymXN9q8DyoEHjTilYNBRO88JwQLpi2NJcNixlj\r\n8+CbLeDqhfHlXfVB10OKa2CsKce5CwJAbhaN+DQJ+3dCSOjC3YSk2Dkn6VhTFW9m\r\nJn/UbNa/KPug9M5k1Er3RsO/OqsBxEk7hHUMD3qv74OIXpBxNnZQuQJASlwk5HZT\r\n7rULkr72fK/YYxkS0czBDIpTKqwklxU+xLSGWkSHvSvl7sK4TmQ1w8KVpjKlTCW9\r\nxKbbW0zVmGN6wQ==\r\n-----END PRIVATE KEY-----";



void Blink(){
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, LOW);
  delay(20);
  digitalWrite(BUILTIN_LED, HIGH);
}


///////////////////////////////////////////////////////////////////////
// HTML Handle
///////////////////////////////////////////////////////////////////////
bool loadIndex() {
    Blink();
    
    File dataFile = FILESYS.open("/index.html", "r");
    
    webServer.streamFile(dataFile, "text/html");

    dataFile.close();

    return true;
}

bool loadCss() {
    Blink();
    
    File dataFile = FILESYS.open("/main.css", "r");
    
    webServer.streamFile(dataFile, "text/css");

    dataFile.close();

    return true;
}
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// Payload Handle
///////////////////////////////////////////////////////////////////////
bool loadVersions() {
    return loadPayload("/_versions.1b.bin");
}

bool loadFtp() {
    return loadPayload("/_ftps5_p.1b.bin");
}

bool loadKstuff() {
    return loadPayload("/_ps5_kstuff_v1.1b.bin");
}

bool loadEtaHen() {
    return loadPayload("/_etaHEN-1.3B.bin");
}

bool loadPs5Debug() {
    return loadPayload("/_ps5debug.elf");
}

bool loadPayload(String Payload) {
    Blink();
    File dataFile = FILESYS.open(Payload, "r");
    webServer.streamFile(dataFile, "application/octet-stream");
    dataFile.close();
    return true;
}
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// JS Handle
///////////////////////////////////////////////////////////////////////
bool loadCustomHost() {
    return loadJS("/custom_host.js");
}

bool loadExploit() {
    return loadJS("/exploit.js");
}

bool loadInt64() {
    return loadJS("/int64.js");
}

bool loadPayloadMap() {
    return loadJS("/payload_map.js");
}

bool loadRop() {
    return loadJS("/rop.js");
}

bool loadRopSlave() {
    return loadJS("/rop_slave.js");
}

bool loadwebkit() {
    return loadJS("/webkit.js");
}

bool loadJS(String JS) {
    Blink();
    File dataFile = FILESYS.open(JS, "r");
    webServer.streamFile(dataFile, "application/javascript");
    dataFile.close();
    return true;
}
///////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////
// Offset Handle
///////////////////////////////////////////////////////////////////////
bool loadOffset300() {
    return loadOffset("/3.00.js");
}

bool loadOffset310() {
    return loadOffset("/3.10.js");
}

bool loadOffset320() {
    return loadOffset("/3.20.js");
}

bool loadOffset321() {
    return loadOffset("/3.21.js");
}

bool loadOffset400() {
    return loadOffset("/4.00.js");
}

bool loadOffset402() {
    return loadOffset("/4.02.js");
}

bool loadOffset403() {
    return loadOffset("/4.03.js");
}

bool loadOffset450() {
    return loadOffset("/4.50.js");
}

bool loadOffset451() {
    return loadOffset("/4.51.js");
}

bool loadOffset(String Offset) {
    Blink();
    File dataFile = FILESYS.open(Offset, "r");
    webServer.streamFile(dataFile, "application/javascript");
    dataFile.close();
    return true;
}
///////////////////////////////////////////////////////////////////////


void setup(void) {

  WiFi.softAPConfig(Server_IP, Server_IP, Subnet_Mask);
  WiFi.softAP(AP_SSID, AP_PASS);

  webServer.on("/index.html", HTTP_GET, loadIndex);
  webServer.on("/main.css", HTTP_GET, loadCss);

  webServer.on("/custom_host.js", HTTP_GET, loadCustomHost);
  webServer.on("/exploit.js", HTTP_GET, loadExploit);
  webServer.on("/int64.js", HTTP_GET, loadInt64);
  webServer.on("/payload_map.js", HTTP_GET, loadPayloadMap);
  webServer.on("/rop.js", HTTP_GET, loadRop);
  webServer.on("/rop_slave.js", HTTP_GET, loadRopSlave);
  webServer.on("/webkit.js", HTTP_GET, loadwebkit);

  webServer.on("/3.00.js", HTTP_GET, loadOffset300);
  webServer.on("/3.10.js", HTTP_GET, loadOffset310);
  webServer.on("/3.20.js", HTTP_GET, loadOffset320);
  webServer.on("/3.21.js", HTTP_GET, loadOffset321);
  webServer.on("/4.00.js", HTTP_GET, loadOffset400);
  webServer.on("/4.02.js", HTTP_GET, loadOffset402);
  webServer.on("/4.03.js", HTTP_GET, loadOffset403);
  webServer.on("/4.50.js", HTTP_GET, loadOffset450);
  webServer.on("/4.51.js", HTTP_GET, loadOffset451);
  
  webServer.on("_etaHEN-1.3B.bin", HTTP_GET, loadEtaHen);
  webServer.on("_ps5_kstuff_v1.2.bin", HTTP_GET, loadKstuff);
  webServer.on("_ftps5_p.elf", HTTP_GET, loadFtp);
  webServer.on("_versions.elf", HTTP_GET, loadVersions);
  webServer.on("_ps5debug.elf", HTTP_GET, loadPs5Debug);
  
  webServer.onNotFound([]() {
    loadIndex();
  });

  webServer.begin(WEB_PORT);

  sWebServer.getServer().setRSACert(new X509List(serverCert), new PrivateKey(serverKey));

  sWebServer.onNotFound([]() {
  sWebServer.sendHeader("Location", String("http://" + Server_IP.toString() + "/index.html" ), true);
  sWebServer.send(301, "text/plain", "");
  });

  sWebServer.begin();

  FILESYS.begin();
}


void loop(void) {
  webServer.handleClient();
  sWebServer.handleClient();
}
