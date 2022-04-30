#include <iostream>
#include <algorithm>

using namespace std;
//Wczeœniejsza deklaracja klasy "Autokar", aby by³a widoczna w klasie "Pasa¿er".
class Bus;
class Passenger{
private:
    string name, secName;
    int age;
    //Deklaracje przyjaŸni z przeci¹¿eniami operatorów, które odnosz¹ siê do pól tej klasy oraz do funkcji "porównaj", która bierze udzia³ w sortowaniu pasa¿erów w tablicy.
    friend ostream& operator<<(ostream& str, const Passenger& ps);
    friend bool compare(Passenger p1, Passenger p2);
    friend Bus& operator-=(const Bus& b, const Passenger& p);
public:
    //Konstruktory (kolejno domyœlny i parametryzuj¹cy).
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
    //Deklaracja przyjaŸni z przeci¹¿onym operatorem -=, który odwo³uje siê do pól tej klasy.
    friend Bus& operator-=(const Bus& b, const Passenger& p);
public:
    //Konstruktor parametryzuj¹cy.
    Bus(string destination, int ticket_price, int space_limit){
        this->destination=destination;
        this->ticket_price=ticket_price;
        this->space_limit=space_limit;
    }
    //Akcesor, wykorzystany przy przeci¹¿aniu operatora ++, który zwiêksza cenê biletu.
    int getPrice(){
        return this->ticket_price;
    }
    //Metoda "pokazInfo()" wyœwietla informacje o utworzonym obiekcie klasy "Autokar".
    void showInfo(){
        cout<<"Information about the bus:"<<endl;
        cout<<"Destination: "<<destination<<endl;
        cout<<"Ticket price: "<<ticket_price<<endl;
        cout<<"Number of seats: "<<space_limit<<endl<<endl;
    }
    //Przeci¹¿enie operatora preinkrementacji.
    Bus operator++(int ){
        ++ticket_price;
        return *this;
    }
    //Przeci¹¿enie operatora postinkrementacji.
    Bus& operator++(){
        ++ticket_price;
        return *this;
    }
    //Przeci¹¿enie operatora +=. Przyjmuje on za argument obiekt klasy "Pasa¿er".
    //Deklarowana jest sta³a wartoœæ iteratora.
    //WskaŸnik na pasa¿era jest wpisywany w pierwsze wolne miejsce w tablicy.
    //Iterator jest zwiêkszany o 1.
    Bus& operator+=(Passenger p){
        static int i=0;
        this->passengers[i]=p;
        i++;
    }
    //Metoda "poka¿Pasa¿erów()" wypisuje wszystkie dane o pasa¿erach bêd¹cych w autokarze, tzn wyœwietla pola obiektów, na które wskazuj¹ wskaŸniki zawarte w tablicy.
    //Poniewa¿ nie wszystkie miejsca w tablicy s¹ zape³nione, dlatego trzeba by³o znaleŸæ sposób na to, by metoda wyœwietla³a dane tylko z tych miejsc w tablicy, do których jest przypisany wskaŸnik.
    //Idealn¹ opcj¹ jest wyœwietlenie tylko tych miejsc, w których pole "wiek" jest ró¿ne od 0, to znaczy, ¿e tam jest wskaŸnik na pasa¿era.
    void showPass(){
        for (int i=0;i<space_limit;i++){
            if(passengers[i].getAge()!=0){
                cout<<passengers[i].getName()<<" "<<passengers[i].getsName()<<" who is "<<passengers[i].getAge()<<" years old."<<endl;
            }
        }
        cout<<endl;
    }
    //Metoda "Usuwanie()" dealokuj¹ca pamiêæ zajêt¹ przez tablicê wskaŸników.
    //Napis jest form¹ sprawdzenia, czy ta metoda dzia³a.
    void Deleting(){
        delete [] passengers;
        cout<<"Trip cancelled. The bus went down :("<<endl;
    }
};
//Przeci¹¿enie operatora <<, który u³atwia wypisywanie danych obiektów klasy "Pasa¿er".
ostream& operator<<(ostream& str, const Passenger& ps){
        str<<ps.name<<" "<<ps.secName<<" who is "<<ps.age<<" years old"<<endl;
        return str;
    }
//Funkcja globalna "porównaj()" porównuj¹ca wiek pasa¿erów. Jest wykorzystywana przy sortowaniu pasa¿erów.
bool compare(Passenger p1, Passenger p2){
        return p1.age>p2.age;
    }
//Przeci¹¿anie operatora -=. Przyjmuje za argumenty referencje do obiektów obu klas.
//Najpierw przechodzimy po wszystkich miejscach w autokarze.
//Jeœli jakieœ miejsce w tablicy wskaŸników ma przypisane imiê i nazwisko, tzn, ¿e jest tam przypisany obiekt.
//Wtedy przesuwamy wskaŸniki nastêpuj¹ce po wskazanym obiekcie w tablicy wskaŸników o 1 miejsce w ty³, usuwaj¹c dany wskaŸnik z tablicy.
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
    //Tablica obiektów klasy "Pasa¿er".
    Passenger pass[5]={{"Jan","Kowalski",35},
                {"Michal","Wilk",46},
                {"Anna","Dera",54},
                {"Julia","Kolecka",23},
                {"Adam","Skladam",25}};
    //Wyœwietlenie wartoœci pól obiektów klasy "Pasa¿er" zawartych w tablicy z wykorzystaniem przeci¹¿onego operatora <<.
    cout<<"The passengers are:"<<endl;
    for (int i=0;i<5;i++){
        cout<<pass[i];
    }
    cout<<endl;

    //Sortowanie obiektów w tablicy ze wzglêdu na wiek.
    sort(pass, pass+5, compare);
    //Ponowne wyœwietlenie obiektów klasy "Pasa¿er zawartych w tablicy, tym razem w kolejnoœci malej¹cej wzglêdem wieku.
    cout<<"Passengers after sort:"<<endl;
    for (int j=0;j<5;j++){
        cout<<pass[j];
    }
    cout<<endl;

    //Utworzenie obiektu klasy "Autokar" i wyœwietlenie zawartoœci pól.
    Bus bus1("Barcelona", 40, 55);
    bus1.showInfo();

    //Podniesienie cen biletów za pomoc¹ przeci¹¿onych operatorów pre- i postinkrementacji oraz wyœwietlenie cen przed i po podwy¿ce.
    cout<<"Ticket price before increase: "<<bus1.getPrice()<<endl;
        ++bus1;
        bus1++;
        ++bus1;
    cout<<"Ticket price after increase: "<<bus1.getPrice()<<endl<<endl;

    //Przypisanie obiektów klasy "Pasa¿er" do tablicy wskaŸników na nich w obiekcie klasy "Autokar" z wykorzystaniem przeci¹¿onego operatora +=.
    bus1+=pass[0];
    bus1+=pass[3];
    bus1+=pass[1];
    bus1+=pass[4];
    //Wyœwietlenie danych pasa¿erów przypisanych do utworzonego obiektu klasy "Autokar".
    cout<<"Passengers after getting into a bus:"<<endl;
    bus1.showPass();

    //Usuniêcie wskaŸnika na obiekt klasy "Pasa¿er" z tablicy wskaŸników obiektu klasy "Autokar". Jest to równoznaczne z usuniêciem pasa¿era z listy.
    //Odbywa siê to za pomoc¹ przeci¹¿onego operatora -=.
    //Po posortowaniu 1. elementem tablicy obiektów klasy "Pasa¿er" jest najstarszy pasa¿er.
    bus1-=pass[0];
    //Wyœwietlenie pozosta³ych pasa¿erów.
    cout<<"Passengers, when one of them left the bus:"<<endl;
    bus1.showPass();

    //Dealokacja pamiêci z wykorzystaniem metody "Usuwanie()".
    bus1.Deleting();
    return 0;
}
