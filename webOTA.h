#include <WebServer.h>
WebServer serverOTA(88);
const char* host = "ELMER";

String style =
"<style>#file-input,input{width:100%;height:44px;border-radius:4px;margin:10px auto;font-size:15px}"
"<meta charset='UTF-8'>"
"input{background:#f1f1f1;border:0;padding:0 15px}body{background:#1d6fa5;font-family:sans-serif;font-size:14px;color:#777}"
"#file-input{padding:0;border:1px solid #ddd;line-height:44px;text-align:left;display:block;cursor:pointer}"
"#bar,#prgbar{background-color:#f1f1f1;border-radius:10px}#bar{background-color:#3498db;width:0%;height:20px}"
"form{background:#fff;max-width:480px;margin:75px auto;padding:30px;border-radius:5px;text-align:center}"
".btn{background:#3498db;color:#fff;cursor:pointer}</style>";

String serverIndex = 
"<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>"
"<meta charset='UTF-8'>"
"<form method='POST' action='#' enctype='multipart/form-data' id='upload_form'>"
"<title> Aktualizace ESP32 Elmer </title>"
"<h1> ESP32 Elmer </h1><br>"
"<input type='file' name='update' id='file' onchange='sub(this)' style=display:none>"
"<label id='file-input' for='file'>   Vyber soubor...</label>"
"<input type='submit' class=btn value='Aktualizuj'>"
"<br><br>"
"<div id='prg'></div>"
"<br><div id='prgbar'><div id='bar'></div></div><br></form>"
"<script>"
"function sub(obj){"
"var fileName = obj.value.split('\\\\');"
"document.getElementById('file-input').innerHTML = '   '+ fileName[fileName.length-1];"
"};"
"$('form').submit(function(e){"
"e.preventDefault();"
"var form = $('#upload_form')[0];"
"var data = new FormData(form);"
"$.ajax({"
"url: '/update',"
"type: 'POST',"
"data: data,"
"contentType: false,"
"processData:false,"
"xhr: function() {"
"var xhr = new window.XMLHttpRequest();"
"xhr.upload.addEventListener('progress', function(evt) {"
"if (evt.lengthComputable) {"
"var per = evt.loaded / evt.total;"
"$('#prg').html('průběh: ' + Math.round(per*100) + '%');"
"$('#bar').css('width',Math.round(per*100) + '%');"
"}"
"}, false);"
"return xhr;"
"},"
"success:function(d, s) {"
"console.log('hotovo!') "
"},"
"error: function (a, b, c) {"
"}"
"});"
"});"
"</script>" + style;

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
void setupOTA() {  if (!MDNS.begin(host)) { //http://esp32.local
    Serial.println("Error setting up MDNS responder!"); while (1) { delay(1000); } }  Serial.println("mDNS responder started");  
    serverOTA.on("/", HTTP_GET, []() { serverOTA.sendHeader("Connection", "close"); serverOTA.send(200, "text/html", serverIndex);  });    serverOTA.on("/update", HTTP_POST, []() { serverOTA.sendHeader("Connection", "close"); 
  serverOTA.send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK"); ESP.restart(); }, []() { HTTPUpload& upload = serverOTA.upload(); if (upload.status == UPLOAD_FILE_START) { Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { Update.printError(Serial); } } else if (upload.status == UPLOAD_FILE_WRITE) {
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) { Update.printError(Serial); } } else if (upload.status == UPLOAD_FILE_END) { if (Update.end(true)) { Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize); }
      else { Update.printError(Serial);  } } });  serverOTA.begin(); 
}/*==============================================================================================================================================================================*/
