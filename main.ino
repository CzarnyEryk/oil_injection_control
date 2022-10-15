#include <Stepper.h>

// 7 SEG SETTING
#define A 2 //SEGMENT A
#define B 3 //SEGMENT B
#define C 4 //SEGMENT C
#define D 5 //SEGMENT D
#define E 6 //SEGMENT E
#define F 7 //SEGMENT F
#define G 8 //SEGMENT G
#define H 9 //SEGMENT H dot


//ENGINE SPEED POTENTIOMETER CONTROL
#define potencjometr A0

//SWITCH TO CONTROL MENU
#define przycisk 1

//ENGINE CONTROL RELAY
#define przekaznik 0


//CONTROL VARIABLES

//ENGINE STEPPER
const int kroki = 200;
//ENGINE SPEED
int predkosc_silnika = 0;
//POTENTIOMETER DATA
int odczyt_potencjometr = 0;
//MENU OPTIONS
int menu = 1;
//CONTROL TIME INJECTION / SWITCH
unsigned long czas = 0;
unsigned long zapamietany_czas = 0;
//SWITCH DELAY TIME
unsigned long opoznienie = 100;
//INJECTION TIME
unsigned long czas_wtrysku = 0;
unsigned long czas_wtrysku_zap = 0;

//ENGINE PINS
Stepper Silnik(kroki, 10, 11, 12, 13);

void setup()
{
    //POTENTIOMETER SETTING
    pinMode(potencjometr, INPUT);

    //ENGINE COIL
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);

    //7 SEG SETTIN
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(F, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(H, OUTPUT); //DOT

    //SWITCH MODE SETTING
    pinMode(przycisk, INPUT_PULLUP);

    //RELAY MODE SETTING
    pinMode(przekaznik, OUTPUT);
}

void loop()
{
    sterowanie_silnikiem(speed_control());
}


//READ AND CONTROL ENGINE SPEED
int speed_control()
{
    menu = sterowanie_przycisk();

    switch (menu)
    {

        case 1:
            //ON
            digitalWrite(przekaznik, LOW);
            //READ DATA FROM POTENTIOMETER
            odczyt_potencjometr = analogRead(potencjometr);
            //CHANGE POTENTIOMETER DATA FOR SPEED ENGINE
            predkosc_silnika = map(odczyt_potencjometr, 0, 1023, 30, 330);
            //RETURN ENGINE SPEED
            return predkosc_silnika;
            break;
        case 2:
            //INJECTION TIME
            czas_wtrysku = millis();
            //READ DATA FROM POTENTIOMETER
            odczyt_potencjometr = analogRead(potencjometr);
            //CHANGE POTENTIOMETER DATA FOR SPEED ENGINE
            predkosc_silnika = map(odczyt_potencjometr, 0, 1023, 30, 330);
            // OIL INJECTION ON
            if (czas_wtrysku - czas_wtrysku_zap >= 1200UL)
            {
                //ENGINE ON
                digitalWrite(przekaznik, HIGH);
            }
            //OIL INJECTION OFF
            if (czas_wtrysku - czas_wtrysku_zap >= 4200UL)
            {
                czas_wtrysku_zap = czas_wtrysku;
                digitalWrite(przekaznik, LOW);
            }
            return predkosc_silnika;
            break;
        //CLEAR MENU OPTION
        case 3:
            menu = 0;
            odczyt_potencjometr = analogRead(potencjometr);
            predkosc_silnika = map(odczyt_potencjometr, 0, 1023, 30, 330);
            return predkosc_silnika;
            break;
    }
}

//CONTROL ENGINE
void sterowanie_silnikiem(int engine_speed)
{
    engine_speed = engine_speed;
    //SET RPM FROM VOID SPEED_CONTROL() LINE: 81-126
    Silnik.setSpeed(engine_speed);
    //ROTATE ENGINE
    Silnik.step(kroki / 100);

    //SHOW ENGINE SPEED
    if (engine_speed >= 30 && engine_speed <= 45)
    {
        wyswietlacz(2);
    }

    else if (engine_speed >= 46 && engine_speed <= 60)
    {
        wyswietlacz(3);
    }

    else if (engine_speed >= 61 && engine_speed <= 75)
    {
        wyswietlacz(4);
    }

    else if (engine_speed >= 76 && engine_speed <= 90)
    {
        wyswietlacz(5);
    }

    else if (engine_speed >= 91 && engine_speed <= 105)
    {
        wyswietlacz(6);
    }

    else if (engine_speed >= 106 && engine_speed <= 120)
    {
        wyswietlacz(7);
    }

    else if (engine_speed >= 121 && engine_speed <= 135)
    {
        wyswietlacz(8);
    }

    else if (engine_speed >= 136 && engine_speed <= 150)
    {
        wyswietlacz(9);
    }

    else if (engine_speed >= 151 && engine_speed <= 165)
    {
        wyswietlacz(10);
    }

    else if (engine_speed >= 166 && engine_speed <= 180)
    {
        wyswietlacz(11);
    }

    else if (engine_speed >= 181 && engine_speed <= 195)
    {
        wyswietlacz(12);
    }

    else if (engine_speed >= 196 && engine_speed <= 210)
    {
        wyswietlacz(13);
    }

    else if (engine_speed >= 211 && engine_speed <= 225)
    {
        wyswietlacz(14);
    }

    else if (engine_speed >= 226 && engine_speed <= 240)
    {
        wyswietlacz(15);
    }

    else if (engine_speed >= 241 && engine_speed <= 255)
    {
        wyswietlacz(16);
    }

    else if (engine_speed >= 256 && engine_speed <= 270)
    {
        wyswietlacz(17);
    }

    else if (engine_speed >= 271 && engine_speed <= 285)
    {
        wyswietlacz(18);
    }

    else if (engine_speed >= 286 && engine_speed <= 300)
    {
        wyswietlacz(19);
    }

    else if (engine_speed >= 301 && engine_speed <= 315)
    {
        wyswietlacz(20);
    }

    else if (engine_speed >= 316 && engine_speed <= 330)
    {
        wyswietlacz(21);
    }
    else
    {
        wyswietlacz(404);
    }

}
//7 SEG CONTROL
void wyswietlacz(int cyfra)
{
    switch (cyfra)
    {
        //0
        case 1:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, HIGH);
            digitalWrite(H, HIGH);

            break;
        //1
        case 2:
            digitalWrite(A, HIGH);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, HIGH);
            digitalWrite(E, HIGH);
            digitalWrite(F, HIGH);
            digitalWrite(G, HIGH);
            digitalWrite(H, HIGH);

            break;
        //1.
        case 3:
            digitalWrite(A, HIGH);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, HIGH);
            digitalWrite(E, HIGH);
            digitalWrite(F, HIGH);
            digitalWrite(G, HIGH);
            digitalWrite(H, LOW);

            break;
        //2
        case 4:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, HIGH);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, HIGH);
            digitalWrite(G, LOW);
            digitalWrite(H, HIGH);

            break;
        //2.
        case 5:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, HIGH);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, HIGH);
            digitalWrite(G, LOW);
            digitalWrite(H, LOW);

            break;
        //3
        case 6:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, HIGH);
            digitalWrite(F, HIGH);
            digitalWrite(G, LOW);
            digitalWrite(H, HIGH);

            break;
        //3.
        case 7:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, HIGH);
            digitalWrite(F, HIGH);
            digitalWrite(G, LOW);
            digitalWrite(H, LOW);

            break;
        //4
        case 8:
            digitalWrite(A, HIGH);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, HIGH);
            digitalWrite(E, HIGH);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            digitalWrite(H, HIGH);

            break;
        //4.
        case 9:
            digitalWrite(A, HIGH);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, HIGH);
            digitalWrite(E, HIGH);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            digitalWrite(H, LOW);

            break;
        //5
        case 10:
            digitalWrite(A, LOW);
            digitalWrite(B, HIGH);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, HIGH);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            digitalWrite(H, HIGH);

            break;
        //5.
        case 11:
            digitalWrite(A, LOW);
            digitalWrite(B, HIGH);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, HIGH);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            digitalWrite(H, LOW);

            break;
        //6
        case 12:
            digitalWrite(A, LOW);
            digitalWrite(B, HIGH);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            digitalWrite(H, HIGH);

            break;
        //6.
        case 13:
            digitalWrite(A, LOW);
            digitalWrite(B, HIGH);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            digitalWrite(H, LOW);

            break;
        //7
        case 14:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, HIGH);
            digitalWrite(E, HIGH);
            digitalWrite(F, HIGH);
            digitalWrite(G, HIGH);
            digitalWrite(H, HIGH);

            break;
        //7.
        case 15:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, HIGH);
            digitalWrite(E, HIGH);
            digitalWrite(F, HIGH);
            digitalWrite(G, HIGH);
            digitalWrite(H, LOW);

            break;
        //8
        case 16:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            digitalWrite(H, HIGH);

            break;
        //8.
        case 17:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            digitalWrite(H, LOW);

            break;
        //9
        case 18:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, HIGH);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            digitalWrite(H, HIGH);

            break;
        //9.
        case 19:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, HIGH);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            digitalWrite(H, LOW);

            break;
        //B
        case 20:
            digitalWrite(A, HIGH);
            digitalWrite(B, HIGH);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            digitalWrite(H, HIGH);
            break;
        //B.
        case 21:
            digitalWrite(A, HIGH);
            digitalWrite(B, HIGH);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            digitalWrite(H, LOW);
            break;
        //ERROR E
        case 404:
            digitalWrite(A, LOW);
            digitalWrite(B, HIGH);
            digitalWrite(C, HIGH);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            digitalWrite(H, HIGH);
    }
}

//CONTROL MENU
int sterowanie_przycisk()
{
    if (digitalRead(przycisk) == LOW)
    {
        czas = millis();
        if (czas - zapamietany_czas >= opoznienie)
        {
            zapamietany_czas = czas;
            menu += 1;
        }
    }
    return menu;
}