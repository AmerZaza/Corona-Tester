#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

/*Put your SSID & Password*/
const char* ssid = "########";  
const char* password = "########";  

ESP8266WebServer server(80);   

float tempAmbientC, tempAmbientF, tempObjectC , tempObjectF;

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit MLX90614 test");  
  mlx.begin();  


  Serial.println("Connecting to ");
  Serial.println(ssid);

    //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
    }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  /*
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  Serial.println();
  delay(500);
  */
  
  server.handleClient(); // !!!!
}


void handle_OnConnect() {

   tempAmbientC = mlx.readAmbientTempC(); 
   tempObjectC  = mlx.readObjectTempC();   
   tempAmbientF = mlx.readAmbientTempF();  
   tempObjectF  = mlx.readObjectTempF();

  server.send(200, "text/html", SendHTML(tempAmbientC,tempObjectC ) ); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float tempAmbientC,float tempObjectC){
  String ptr = "<!DOCTYPE html>";
  ptr +="<html>";
  ptr +="<head>";
  ptr +="<title>Amer Tempratur Server</title>";
  ptr +="<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  ptr +="<link href='https://fonts.googleapis.com/css?family=Open+Sans:300,400,600' rel='stylesheet'>";
  ptr +="<style>";
  ptr +="html { font-family: 'Open Sans', sans-serif; display: block; margin: 0px auto; text-align: center;color: #444444;}";
  ptr +="body{margin-top: 50px;} ";
  ptr +="h1 {margin: 50px auto 30px;} ";
  ptr +=".side-by-side{display: table-cell;vertical-align: middle;position: relative;}";
  ptr +=".text{font-weight: 600;font-size: 19px;width: 200px;}";
  ptr +=".temperature{font-weight: 300;font-size: 50px;padding-right: 15px;}";
  ptr +=".living-room .temperature{color: #3B97D3;}";
  ptr +=".bedroom .temperature{color: #F29C1F;}";
  ptr +=".kitchen .temperature{color: #26B99A;}";
  ptr +=".superscript{font-size: 17px;font-weight: 600;position: absolute;right: -5px;top: 15px;}";
  ptr +=".data{padding: 10px;}";
  ptr +=".container{display: table;margin: 0 auto;}";
  ptr +=".icon{width:82px}";
  ptr +="</style>";
  ptr +="</head>";
  ptr +="<body>";
  ptr +="<h1>Amer Temperature Monitor</h1>";
  ptr +="<div class='container'>";
  ptr +="<div class='data living-room'>";
  ptr +="<div class='side-by-side icon'>";
  ptr +="<!--svg enable-background='new 0 0 65.178 45.699'height=45.699px id=Layer_1 version=1.1 viewBox='0 0 65.178 45.699'width=65.178px x=0px xml:space=preserve xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink y=0px><polygon fill=#3B97D3 points='8.969,44.261 8.969,16.469 7.469,16.469 7.469,44.261 1.469,44.261 1.469,45.699 14.906,45.699 ";
  ptr +="14.906,44.261 '/><polygon fill=#3B97D3 points='13.438,0 3,0 0,14.938 16.438,14.938 '/><polygon fill=#3B97D3 points='29.927,45.699 26.261,45.699 26.261,41.156 32.927,41.156 '/><polygon fill=#3B97D3 points='58.572,45.699 62.239,45.699 62.239,41.156 55.572,41.156 '/><path d='M61.521,17.344c-2.021,0-3.656,1.637-3.656,3.656v14.199H30.594V21c0-2.02-1.638-3.656-3.656-3.656";
  ptr +="c-2.02,0-3.657,1.636-3.657,3.656v14.938c0,2.021,1.637,3.655,3.656,3.655H61.52c2.02,0,3.655-1.637,3.655-3.655V21";
  ptr +="C65.177,18.98,63.54,17.344,61.521,17.344z'fill=#3B97D3 /><g><path d='M32.052,30.042c0,2.02,1.637,3.656,3.656,3.656h16.688c2.019,0,3.656-1.638,3.656-3.656v-3.844h-24";
  ptr +="L32.052,30.042L32.052,30.042z'fill=#3B97D3 /><path d='M52.396,6.781H35.709c-2.02,0-3.656,1.637-3.656,3.656v14.344h24V10.438";
  ptr +="C56.053,8.418,54.415,6.781,52.396,6.781z'fill=#3B97D3 /></g></svg -->";
  ptr +="</div>";
  ptr +="<div class='side-by-side text'>Ambient Temperature</div>";
  ptr +="<div class='side-by-side temperature'>";
  ptr +=(int)tempAmbientC;  
  ptr +="<span class='superscript'>&deg;C</span></div>";
  ptr +="</div>";
  ptr +="<div class='data bedroom'>";
  ptr +="<div class='side-by-side icon'>";
  ptr +="<!-- svg enable-background='new 0 0 43.438 35.75'height=35.75px id=Layer_1 version=1.1 viewBox='0 0 43.438 35.75'width=43.438px x=0px xml:space=preserve xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink y=0px><g><path d='M25.489,14.909H17.95C13.007,14.908,0,15.245,0,20.188v3.688h43.438v-3.688";
  ptr +="C43.438,15.245,30.431,14.909,25.489,14.909z'fill=#F29C1F /><polygon fill=#F29C1F points='0,31.25 0,35.75 2.5,35.75 4.5,31.25 38.938,31.25 40.938,35.75 43.438,35.75 43.438,31.25 ";
  ptr +="43.438,25.375 0,25.375   '/><path d='M13.584,11.694c-3.332,0-6.033,0.973-6.033,2.175c0,0.134,0.041,0.264,0.105,0.391";
  ptr +="c3.745-0.631,7.974-0.709,10.341-0.709h1.538C19.105,12.501,16.613,11.694,13.584,11.694z'fill=#F29C1F /><path d='M30.009,11.694c-3.03,0-5.522,0.807-5.951,1.856h1.425V13.55c2.389,0,6.674,0.081,10.444,0.728";
  ptr +="c0.069-0.132,0.114-0.268,0.114-0.408C36.041,12.668,33.34,11.694,30.009,11.694z'fill=#F29C1F /><path d='M6.042,14.088c0-2.224,3.376-4.025,7.542-4.025c3.825,0,6.976,1.519,7.468,3.488h1.488";
  ptr +="c0.49-1.97,3.644-3.489,7.469-3.489c4.166,0,7.542,1.801,7.542,4.025c0,0.17-0.029,0.337-0.067,0.502";
  ptr +="c1.08,0.247,2.088,0.549,2.945,0.926V3.481C40.429,1.559,38.871,0,36.948,0H6.49C4.568,0,3.009,1.559,3.009,3.481v12.054";
  ptr +="c0.895-0.398,1.956-0.713,3.095-0.968C6.069,14.41,6.042,14.251,6.042,14.088z'fill=#F29C1F /></g></svg -->";
  ptr +="</div>";
  ptr +="<div class='side-by-side text'>Object Temperature</div>";
  ptr +="<div class='side-by-side temperature'>";
  ptr +=(int)tempObjectC; 
  ptr +="<span class='superscript'>&deg;C</span></div>";
  ptr +="</div>";
   /*
  ptr +="<div class='data kitchen'>";
  ptr +="<div class='side-by-side icon'>";
  ptr +="<svg enable-background='new 0 0 48 31.5'height=31.5px id=Layer_1 version=1.1 viewBox='0 0 48 31.5'width=48px x=0px xml:space=preserve xmlns=http://www.w3.org/2000/svg xmlns:xlink=http://www.w3.org/1999/xlink y=0px><circle cx=24.916 cy=15.75 fill=#26B99A r=15.75 /><path d='M14.917,15.75c0-5.522,4.478-10,10-10c2.92,0,5.541,1.26,7.369,3.257l1.088-1.031";
  ptr +="c-2.103-2.285-5.106-3.726-8.457-3.726c-6.351,0-11.5,5.149-11.5,11.5c0,3.127,1.252,5.958,3.277,8.031l1.088-1.031";
  ptr +="C16.011,20.945,14.917,18.477,14.917,15.75z'fill=#FFFFFF /><path d='M45.766,2.906c-1.232,0-2.232,1-2.232,2.234v11.203c0,0,2.76,0,3,0v12H48v-12V2.906";
  ptr +="C48,2.906,46.035,2.906,45.766,2.906z'fill=#26B99A /><path d='M6.005,2.917v5.184c0,0.975-0.638,1.792-1.516,2.083V2.917H3.021v7.267c-0.878-0.29-1.516-1.107-1.516-2.083";
  ptr +="V2.917H0v5.458c0,1.802,1.306,3.291,3.021,3.592v16.376H4.49v-16.38c1.695-0.318,2.979-1.8,2.979-3.588V2.917H6.005z'fill=#26B99A /></svg>";
  ptr +="</div>";
 
  ptr +="<div class='side-by-side text'>Kitchen</div>";
  ptr +="<div class='side-by-side temperature'>";
  ptr +=(int)tempSensor3;
  */
  //ptr +="<span class='superscript'>&deg;C</span>";
  ptr +="</div>";
  ptr +="</div>";
  ptr +="</div>";
  ptr +="</body>";
  ptr +="</html>";
  return ptr;
}
