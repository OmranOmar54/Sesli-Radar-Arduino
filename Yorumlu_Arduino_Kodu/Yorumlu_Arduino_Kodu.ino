//servonun kütüphanesini içeri aktarıyoruz
#include <Servo.h> 

//servomuzu scriptimize tanıtıyoruz
Servo myServo;

//arduino kartına takılı servonun pinini ve açı aralığını tanıtıyoruz
int servoPin = 7;
int minAngle = 15;
int maxAngle = 165;

//servonun baktığı anlık açıyı belirten bir integer tanıtıyoruz
int currentAngle;

//servonun dönme hızını sayısal değişkene atıyoruz 
//hız değeri arttıkça dönme hızı azalır
int speed = 20;

//sensör ve buzzerin pinlerini tanımlıyoruz
#define trigPin 10
#define echoPin 11
#define buzzerPin 12

//sensörün mesafeyi hesaplayabilmesi için gerekli değişkenleri tanıtıyoruz
long duration;
int distance;

//buzzerin ötme katsayısı
int buzzerKatsayisi;

//arduino güç alacağı zaman çalışacak olan kodlar
void setup(){
  //pinlerin giriş pini mi çıkış pini mi olduğunu tanımlıyoruz
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myServo.attach(servoPin);
  Serial.begin(9600);
  currentAngle = 90;//servonun açılış açısını 90 olarak belirliyoruz ve yazdırıyoruz
  myServo.write(90);
  buzzerKatsayisi = 5; //buzzerkatsayisi ni belirliyoruz
}

//mesafe diye bir sayı tanımlıyoruz. bu sayı sensörle cisim arasındaki mesafeyi temsil ediyor
//bu sayı çağırıldığında aşağıdaki işlemler çalıştırılıyor
int range(){
  digitalWrite(trigPin, LOW);//mesafe sensöründen düşük frekanslı dalga gönderiyoruz ve 5 mikrosaniye bekliyoruz 
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);//mesafe sensöründen yüksek frekanslı dalga gönderiyoruz ve 5 mikrosaniye bekliyoruz
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);//baştaki işlemi tekrardan gerçekleştiriyoruz ve 5 mikrosaniye bekliyoruz
  delayMicroseconds(5);
  duration = pulseIn(echoPin, HIGH);//geri dönen dalgayı duration adlı değişkene tanımlıyoruz
  
  distance = duration * 0.0344 / 2;//mesafeyi duration'un ses hızının yarısıyla çarpılarak buluyoruz
  delayMicroseconds(5);//5 mikrosaniye bekliyoruz
  
  //distance değişkenini range çıktısı olarak gönderiyoruz
  return distance;
}

//burada bir fonksiyon tanımlıyoruz. fonksiyon çağırıldığında yanında bir değişkenle çağırılacak
//bu değişken mesafeyi temsil ediyor. bu fonksiyon sayesinde mesafe aralığına göre buzzerin çıkaracağı sesi belirliyoruz
void buzzerSesi(int mesafe){
  if(mesafe > 40){//mesafe 40 tan fazla ise buzzeri sustur
    digitalWrite(buzzerPin, LOW);
  }
  else if(mesafe <= 40 && mesafe > 30){
    digitalWrite(buzzerPin, HIGH);
    delay(mesafe * (buzzerKatsayisi + 4));
    digitalWrite(buzzerPin, LOW);
    delay(mesafe * (buzzerKatsayisi + 4));
  }
  else if(mesafe <= 30 && mesafe > 20){
    digitalWrite(buzzerPin, HIGH);
    delay(mesafe * (buzzerKatsayisi + 3));
    digitalWrite(buzzerPin, LOW);
    delay(mesafe * (buzzerKatsayisi + 3));
  }
  else if(mesafe <= 20 && mesafe > 10){
    digitalWrite(buzzerPin, HIGH);
    delay(mesafe * (buzzerKatsayisi + 2));
    digitalWrite(buzzerPin, LOW);
    delay(mesafe * (buzzerKatsayisi + 2));
  }
  else if(mesafe <= 10 && mesafe > 0){
    digitalWrite(buzzerPin, HIGH);
    delay(mesafe * (buzzerKatsayisi + 1));
    digitalWrite(buzzerPin, LOW);
    delay(mesafe * (buzzerKatsayisi + 1));
  }
  else{//mesafe 0 veya negatif ise susturuyoruz
       //0 da susturmamızın sebebi oluşabilecek buglar sayesinde mesafenin 0 a eşit olabilmesi
    digitalWrite(buzzerPin, LOW);
  }
}

//çalıştıktan sonra döngüye alınacak kodlar
void loop() { 
  //açıyı minimum açıya eşitle ve maksimum açıya gelene kadar arttırmaye devam et
  //bu hareket sayesinde servo pozitif yönde dönüş yapar ve maksimum açıya geldiğinde for döngüsü biter
  //for döngüsü bittiğinde program ters yöne döneceğini anlar ve ardındaki for döngüsünü başlatır
  for (int angle = minAngle; angle <= maxAngle; angle++) {
    myServo.write(angle); 
    delay(speed);
    currentAngle = angle;
    distance = range(); // mesafeyi hesapla

    //mesafeyi ve anlık açıyı görüntüleme ekranında gösterebilmek için yazdırıyoruz
    Serial.print(currentAngle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    buzzerSesi(distance);//distance değişkenine göre buzzerin ses çıkarmasını sağlıyoruz
  }

  //açıyı maksimum açıya eşitle ve minimum açıya gelene kadar azaltmaya devam et
  //bu hareket sayesinde servo negatif yönde dönüş yapar ve maksimum açıya geldiğinde for döngüsü biter
  for (int angle = maxAngle; angle >= minAngle; angle--) {
    myServo.write(angle);
    delay(speed);
    currentAngle = angle;
    distance = range(); //mesafeyi hesapla

    //mesafeyi ve anlık açıyı görüntüleme ekranında gösterebilmek için yazdırıyoruz
    Serial.print(currentAngle);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");
    buzzerSesi(distance);//distance değişkenine göre buzzerin ses çıkarmasını sağlıyoruz
  }
  
}




