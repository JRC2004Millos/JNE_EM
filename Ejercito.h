#include <iostream>

using namespace std;

class Ejercito{
    private:
        string tipo;
        string color;
        int cantidad;
    public:
        Ejercito();
        Ejercito(string, string);
        Ejercito(string, string, int);

        void modificarCantidad(int, char);

        void setTipo(string);
        void setColor(string);
        void setCantidad(int);

        string getTipo();
        string getColor();
        int getCantidad();
};