#include <iostream>
#include <filesystem>
#include <vector>
#include <wiringPi.h>
#include <unistd.h>
#include <random>

#define GERI 2
#define DURDUR 3
#define BASLAT 4
#define ILERI 5

#define LED 6

using namespace std;
namespace fs = filesystem;

int main(){
    vector<string> vec;
    for(auto& entry : fs::directory_iterator("./sounds")){
    	vec.emplace_back(entry.path().filename().stem());
    }

    for(string s : vec){
    	cout << s << "\n";
    }

    int index = 0;

    wiringPiSetup();
	
    pinMode(GERI, INPUT);
    pinMode(DURDUR, INPUT);
    pinMode(BASLAT, INPUT);
    pinMode(ILERI, INPUT);
    
    pinMode(LED, OUTPUT);

    digitalWrite(LED, HIGH);

    delay(1000);

    digitalWrite(LED, LOW);

    srand(time(0));

    system(("python ekran.py -write '" + vec.at(index) + "'").c_str());
	
    bool cal = false;
    while(true){
	int status = system("kill -0 $(cat /tmp/mpg123.pid) > /dev/null 2>&1");
	if(cal && status){
		int i = rand() % vec.size();
		system(("mpg123 ./sounds/" + vec.at(i) + ".mp3 & echo $! > /tmp/mpg123.pid").c_str());
	}

    	if(digitalRead(GERI)==HIGH){
		if(index==0){
			index = vec.size()-1;
		}else{
			index--;
		}
		cout << "Geri gidildi. \nYeni Sarki: " << vec.at(index) << endl;
		system(("python ekran.py -write '" + vec.at(index) + "'").c_str());
		delay(100);
	}else if(digitalRead(DURDUR)==HIGH){
		system("pkill mpg123");
		cout << "Durduruldu.\n";
		cal = false;
		delay(100);
	}else if(digitalRead(BASLAT)==HIGH){
		system(("mpg123 -q ./sounds/" + vec.at(index) + ".mp3 & echo $! > /tmp/mpg123.pid").c_str());
		cout << "Başlatıldı.\n";
		cal = true;
		delay(100);
	}else if(digitalRead(ILERI)==HIGH){
		if(index+1 == vec.size()){
			index = 0;
		}else{
			index++;
		}
		cout << "İleri gidildi.\nYeni Sarki: " << vec.at(index) << endl;
		system(("python ekran.py -write '" + vec.at(index) + "'").c_str());
		delay(100);
	}
	cout << "\n";
	delay(250);
    }
}
