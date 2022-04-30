#include <iostream>
#include <algorithm>

using namespace std;
//Wcze�niejsza deklaracja klasy "Autokar", aby by�a widoczna w klasie "Pasa�er".
class Bus;
class Passenger{
private:
    string name, secName;
    int age;
    //Deklaracje przyja�ni z przeci��eniami operator�w, kt�re odnosz� si� do p�l tej klasy oraz do funkcji "por�wnaj", kt�ra bierze udzia� w sortowaniu pasa�er�w w tablicy.
    friend ostream& operator<<(ostream& str, const Passenger& ps);
    friend bool compare(Passenger p1, Passenger p2);
    friend Bus& operator-=(const Bus& b, const Passenger& p);
public:
    //Konstruktory (kolejno domy�lny i parametryzuj�cy).
    Passenger(){};
    Passenger(string name, string secName, int age){
        this->name=name;
        this->secName=secName;
        this->age=age;
    }
    //Akcesory
    string getName(){
        return this->name;
    }
    string getsName(){
        return this->secName;
    }
    int getAge(){
        return this->age;
    }
};

class Bus{
private:
    string destination;
    int ticket_price, space_limit;
    Passenger* passengers=new Passenger[space_limit];
    //Deklaracja przyja�ni z przeci��onym operatorem -=, kt�ry odwo�uje si� do p�l tej klasy.
    friend Bus& operator-=(const Bus& b, const Passenger& p);
public:
    //Konstruktor parametryzuj�cy.
    Bus(string destination, int ticket_price, int space_limit){
        this->destination=destination;
        this->ticket_price=ticket_price;
        this->space_limit=space_limit;
    }
    //Akcesor, wykorzystany przy przeci��aniu operatora ++, kt�ry zwi�ksza cen� biletu.
    int getPrice(){
        return this->ticket_price;
    }
    //Metoda "pokazInfo()" wy�wietla informacje o utworzonym obiekcie klasy "Autokar".
    void showInfo(){
        cout<<"Information about the bus:"<<endl;
        cout<<"Destination: "<<destination<<endl;
        cout<<"Ticket price: "<<ticket_price<<endl;
        cout<<"Number of seats: "<<space_limit<<endl<<endl;
    }
    //Przeci��enie operatora preinkrementacji.
    Bus operator++(int ){
        ++ticket_price;
        return *this;
    }
    //Przeci��enie operatora postinkrementacji.
    Bus& operator++(){
        ++ticket_price;
        return *this;
    }
    //Przeci��enie operatora +=. Przyjmuje on za argument obiekt klasy "Pasa�er".
    //Deklarowana jest sta�a warto�� iteratora.
    //Wska�nik na pasa�era jest wpisywany w pierwsze wolne miejsce w tablicy.
    //Iterator jest zwi�kszany o 1.
    Bus& operator+=(Passenger p){
        static int i=0;
        this->passengers[i]=p;
        i++;
    }
    //Metoda "poka�Pasa�er�w()" wypisuje wszystkie dane o pasa�erach b�d�cych w autokarze, tzn wy�wietla pola obiekt�w, na kt�re wskazuj� wska�niki zawarte w tablicy.
    //Poniewa� nie wszystkie miejsca w tablicy s� zape�nione, dlatego trzeba by�o znale�� spos�b na to, by metoda wy�wietla�a dane tylko z tych miejsc w tablicy, do kt�rych jest przypisany wska�nik.
    //Idealn� opcj� jest wy�wietlenie tylko tych miejsc, w kt�rych pole "wiek" jest r�ne od 0, to znaczy, �e tam jest wska�nik na pasa�era.
    void showPass(){
        for (int i=0;i<space_limit;i++){
            if(passengers[i].getAge()!=0){
                cout<<passengers[i].getName()<<" "<<passengers[i].getsName()<<" who is "<<passengers[i].getAge()<<" years old."<<endl;
            }
        }
        cout<<endl;
    }
    //Metoda "Usuwanie()" dealokuj�ca pami�� zaj�t� przez tablic� wska�nik�w.
    //Napis jest form� sprawdzenia, czy ta metoda dzia�a.
    void Deleting(){
        delete [] passengers;
        cout<<"Trip cancelled. The bus went down :("<<endl;
    }
};
//Przeci��enie operatora <<, kt�ry u�atwia wypisywanie danych obiekt�w klasy "Pasa�er".
ostream& operator<<(ostream& str, const Passenger& ps){
        str<<ps.name<<" "<<ps.secName<<" who is "<<ps.age<<" years old"<<endl;
        return str;
    }
//Funkcja globalna "por�wnaj()" por�wnuj�ca wiek pasa�er�w. Jest wykorzystywana przy sortowaniu pasa�er�w.
bool compare(Passenger p1, Passenger p2){
        return p1.age>p2.age;
    }
//Przeci��anie operatora -=. Przyjmuje za argumenty referencje do obiekt�w obu klas.
//Najpierw przechodzimy po wszystkich miejscach w autokarze.
//Je�li jakie� miejsce w tablicy wska�nik�w ma przypisane imi� i nazwisko, tzn, �e jest tam przypisany obiekt.
//Wtedy przesuwamy wska�niki nast�puj�ce po wskazanym obiekcie w tablicy wska�nik�w o 1 miejsce w ty�, usuwaj�c dany wska�nik z tablicy.
Bus& operator-=(const Bus& b, const Passenger& p){
    for (int i=0;i<b.space_limit;i++){
        if(b.passengers[i].name==p.name&&b.passengers[i].secName==p.secName){
            for (int j=i;j<b.space_limit-1;j++){
                b.passengers[j]=b.passengers[j+1];
            }
        }
    }
}
int main(){
    //Tablica obiekt�w klasy "Pasa�er".
    Passenger pass[5]={{"Jan","Kowalski",35},
                {"Michal","Wilk",46},
                {"Anna","Dera",54},
                {"Julia","Kolecka",23},
                {"Adam","Skladam",25}};
    //Wy�wietlenie warto�ci p�l obiekt�w klasy "Pasa�er" zawartych w tablicy z wykorzystaniem przeci��onego operatora <<.
    cout<<"The passengers are:"<<endl;
    for (int i=0;i<5;i++){
        cout<<pass[i];
    }
    cout<<endl;

    //Sortowanie obiekt�w w tablicy ze wzgl�du na wiek.
    sort(pass, pass+5, compare);
    //Ponowne wy�wietlenie obiekt�w klasy "Pasa�er zawartych w tablicy, tym razem w kolejno�ci malej�cej wzgl�dem wieku.
    cout<<"Passengers after sort:"<<endl;
    for (int j=0;j<5;j++){
        cout<<pass[j];
    }
    cout<<endl;

    //Utworzenie obiektu klasy "Autokar" i wy�wietlenie zawarto�ci p�l.
    Bus bus1("Barcelona", 40, 55);
    bus1.showInfo();

    //Podniesienie cen bilet�w za pomoc� przeci��onych operator�w pre- i postinkrementacji oraz wy�wietlenie cen przed i po podwy�ce.
    cout<<"Ticket price before increase: "<<bus1.getPrice()<<endl;
        ++bus1;
        bus1++;
        ++bus1;
    cout<<"Ticket price after increase: "<<bus1.getPrice()<<endl<<endl;

    //Przypisanie obiekt�w klasy "Pasa�er" do tablicy wska�nik�w na nich w obiekcie klasy "Autokar" z wykorzystaniem przeci��onego operatora +=.
    bus1+=pass[0];
    bus1+=pass[3];
    bus1+=pass[1];
    bus1+=pass[4];
    //Wy�wietlenie danych pasa�er�w przypisanych do utworzonego obiektu klasy "Autokar".
    cout<<"Passengers after getting into a bus:"<<endl;
    bus1.showPass();

    //Usuni�cie wska�nika na obiekt klasy "Pasa�er" z tablicy wska�nik�w obiektu klasy "Autokar". Jest to r�wnoznaczne z usuni�ciem pasa�era z listy.
    //Odbywa si� to za pomoc� przeci��onego operatora -=.
    //Po posortowaniu 1. elementem tablicy obiekt�w klasy "Pasa�er" jest najstarszy pasa�er.
    bus1-=pass[0];
    //Wy�wietlenie pozosta�ych pasa�er�w.
    cout<<"Passengers, when one of them left the bus:"<<endl;
    bus1.showPass();

    //Dealokacja pami�ci z wykorzystaniem metody "Usuwanie()".
    bus1.Deleting();
    return 0;
}
