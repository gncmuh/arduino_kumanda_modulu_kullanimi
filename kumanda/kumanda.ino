#include <IRremote.h>
const int pin[]={7};

IRrecv irrecv(pin[0]);
decode_results results;

struct sensor_veriler {

  int veri;
  const byte hafiza_tusu PROGMEM=111;
  const byte artir PROGMEM=87;const byte azalt PROGMEM=31;
  
};
struct sensor_veriler sens;
int sayac=0;int hafiza_sayaci=0;int veri_gonderme_sayaci=0;
static bool bayrak=false;
static bool hafiza_iptal=true;
bool depola=false;
byte hafiza[50];int giden_veri;
void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.start();
  if(!Serial)
  {
    Serial.println("Seri haberlesme baslatilamadi");
  }
  else
  {
    for(int i=0; i<1; i++) pinMode(pin[i],INPUT);
    kumanda_hafiza();
  }

}

void loop() {
 
  sens.veri=kumanda_hafiza();
  Serial.print("HAFIZADA OLAN=");
  Serial.println(sens.veri);
  Serial.println("*****************");
  delay(1000);
  

  
}

int kumanda_hafiza() {

  if(!bool(0))
  {
    while(hafiza_iptal)
    {
      if(irrecv.decode(&results))
      {
        byte gelen=results.value;
        if(gelen==sens.hafiza_tusu)
        {
          Serial.println("hafiza acik");      
          sayac++;
          if(sayac==2) hafiza_iptal=false; depola=false;
          depola=!depola;
        }   
        if(depola==true)
        {
          if(gelen==sens.artir)
          {
            Serial.println("hafiza artimada");
            hafiza[hafiza_sayaci]=gelen;
            hafiza_sayaci++;
          }
          else if(gelen==sens.azalt)
          {
            Serial.println("hafiza azaltmada");
            hafiza[hafiza_sayaci]=gelen;
            hafiza_sayaci++;
          }      
       }
      }
      irrecv.resume();
    }
    Serial.println("hafizaya alindi..");
    Serial.println("----------------");  
  }
  if(!bool(0))
  {
      giden_veri=hafiza[veri_gonderme_sayaci];
      giden_veri=(int)giden_veri;
      veri_gonderme_sayaci++;
      if(veri_gonderme_sayaci>=hafiza_sayaci) veri_gonderme_sayaci=0;
  }
  return giden_veri;
}
