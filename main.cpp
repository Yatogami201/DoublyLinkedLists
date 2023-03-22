#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct nodo {
    string nombre;
    int habitacion;
    nodo* sig;
    nodo* ant;
};

class lista{
private:
    nodo *cabeza;
    nodo *cola;

public:
    lista(){
        cabeza = nullptr;
        cola = nullptr;
    }

    //añade un nuevo huesped
    void nuevo(string nombre, int habitacion) {
        ifstream file("C:\\Users\\samiv\\OneDrive\\Documentos\\hotel.txt");//abre el archivo en lectura
        bool ocupado = false;
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string huesped;
            int habitacionH;
            if (iss >> huesped >> habitacionH && habitacionH == habitacion) {
                ocupado = true;
                break;
            }

        }
        file.close();

        if (ocupado) {
            cout << "La habitacion " << habitacion << " ya esta ocupada." << endl;
            return;
        }

        //revisa si la habitacion siguiente esta disponible
        bool siguienteDisponible = false;
        int siguiente = habitacion + 1;
        while (!siguienteDisponible) {
            file.open("C:\\Users\\samiv\\OneDrive\\Documentos\\hotel.txt");
            siguienteDisponible = true;
            while (getline(file, line)) {
                istringstream iss(line);
                string huesped;
                int habitacionH;
                if (iss >> huesped >> habitacionH && habitacionH == siguiente) {
                    siguienteDisponible = false;
                    siguiente++;
                    break;
                }
            }
            file.close();
        }

        //crear el nuevo nodo y lo añade a la lista
        nodo *nuevo = new nodo;
        nuevo->nombre = nombre;
        nuevo->habitacion = habitacion;
        nuevo->sig = nullptr;
        nuevo->ant = nullptr;

        if (cabeza == nullptr) {
            cabeza = nuevo;
            cola = nuevo;
        } else {
            cola->sig = nuevo;
            nuevo->ant = cola;
            cola = nuevo;
        }

        //guarda el huesped en el archivo
        ofstream outFile("C:\\Users\\samiv\\OneDrive\\Documentos\\hotel.txt", ios::app);//abre el archivo en modo escritura
        if (outFile.is_open()) {
            outFile << nombre << " " << habitacion << endl;
            outFile.close();
        } else {
            cout << "No se pudo abrir el archivo." << endl;
        }
        cout << " El huesped " << nombre << " ha sido agregado a la habitacion " << habitacion << endl;
    }

    //busca huespedes en el archivo
    void buscar (string buscar){
        ifstream file("C:\\Users\\samiv\\OneDrive\\Documentos\\hotel.txt");
        if(file.is_open()){
            string line;
            bool encontrado = false;
            bool esInt = true;
            for (char c : buscar){
                if(!std::isdigit(c)){
                    esInt = false;
                    break;

                }
            }
            while (getline(file, line)){
                istringstream iss(line);
                string nombre;
                int habitacion;
                if(!(iss>>nombre>>habitacion)){
                    continue;
                }
                if ((nombre == buscar || (esInt && habitacion == std::stoi(buscar)))||(nombre +" "+std::to_string(habitacion)==buscar)){
                    encontrado = true;
                    cout << "El huesped " << nombre << " esta en la habitacion " << habitacion << endl;
                }
            }
            if(!encontrado){
                cout << "No se encontro el huesped " << buscar << endl;
            }
            file.close();
        }else{
            cout << "No se pudo abrir el archivo" << endl;
        }
    }
    //imprime huespedes en orden alfabetico
    void alfa(){
        ifstream file("C:\\Users\\samiv\\OneDrive\\Documentos\\hotel.txt");
        if(file.is_open()){
            vector<pair<string, int>>huespedes;//crea un vector de pares
            string line;
            while(getline(file,line)){
                istringstream iss(line);
                string nombre;
                int habitacion;
                if(iss>>nombre>>habitacion){
                    huespedes.push_back(make_pair(nombre,habitacion));
                }
            }
            file.close();

            //ordena los huespedes en orden alfabetico
            sort(huespedes.begin(),huespedes.end());

            //imprime la lista de huespedes
            for(auto huesped:huespedes){
                cout << "Huesped " << huesped.first << ", Habitacion " << huesped.second << endl;
            }
        }else{
            cout << "No se pudo abrir el archivo" << endl;
        }

    }

    void llegada(){
        ifstream file("C:\\Users\\samiv\\OneDrive\\Documentos\\hotel.txt");
        if(file.is_open()){
            string nombre;
            int habitacion;
            bool existe = false;
            while (file>>nombre>>habitacion){
                existe=true;
                cout << "Huesped " << nombre << ", Habitacion " << habitacion << endl;
            }
            file.close();
            if(!existe){
                cout << "No hay huespedes en el hotel" << endl;
            }
        }else{
            cout << "No se pudo abrir el archivo" << endl;
        }
    }

};

int main(){
    lista list;
    while(true){
        int choice;
        cout <<"Ingrese una opcion: "<<endl;
        cout <<"1. Agregar huesped"<<endl;
        cout <<"2. Buscar huesped"<<endl;
        cout <<"3. Imprimir lista de huespedes alfabeticamente"<<endl;
        cout <<"4. Imprimir lista de huespedes por orden de llegada"<<endl;
        cout <<"5. Salir"<<endl;
        cin >> choice;
        switch(choice){
            case 1:{
                string nombre;
                int habitacion;
                cout << "Ingrese el nombre del huesped:";
                cin >> nombre;
                cout << "Ingrese el numero de habitacion: ";
                cin >> habitacion;
                list.nuevo(nombre,habitacion);
                break;
            }
            case 2:{
                string buscar;
                cout << "Ingrese el nombre del huesped a buscar: ";
                cin >> buscar;
                list.buscar(buscar);
                break;
            }
            case 3:{
                list.alfa();
                break;
            }
            case 4:{
                list.llegada();
                break;
            }
            case 5:{
                return 0;
            }
            default:{
                cout << "Opcion invalida" << endl;
                break;
            }
        }

    }
}