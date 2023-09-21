#include <iostream>
#include <string>

class Alquilable
{
    public:
        virtual std::string getDescripcion() = 0;
        virtual std::string getTipo() = 0;
        virtual float obtenerPresupuesto() = 0;
    };

class Hotel : public Alquilable
{
    private:
        double coste_base = 100;
        std::string tipo = "Hotel";
        std::string descripcion;

    public:
        Hotel(std::string descripcion)
        :descripcion(descripcion) {}

        std::string getDescripcion() override
        {
            return descripcion;
        }

        std::string getTipo() override
        {
            return tipo;
        }

        float obtenerPresupuesto() override
        {
            return static_cast<float>(coste_base);
        }
};

class AlquilableDecorator : public Alquilable
{
    private:
        Alquilable *alquilable;

    public:
        AlquilableDecorator(Alquilable *alquilable)
        : alquilable(alquilable) {}

        std::string getDescripcion() override
        {
            return alquilable->getDescripcion();
        }

        std::string getTipo() override
        {
            return alquilable->getTipo();
        }

        float obtenerPresupuesto() override
        {
            return alquilable->obtenerPresupuesto();
        }
};

class PrimeraLineaDePlaya : public AlquilableDecorator
{
    // Ejemplo de implementacion de un decorador concreto, notese como dentro del creador
    // del mismo se hace un llamado a AlquilableDecorator, clase que contiene un puntero
    // a un objeto de la clase base Alquilable.
    public:
        PrimeraLineaDePlaya(Alquilable *alquilable)
        : AlquilableDecorator(alquilable) {}

        std::string getDescripcion() override
        {
            return AlquilableDecorator::getDescripcion() + " (vistas al mar)";
        }

        float obtenerPresupuesto() override
        {
            return AlquilableDecorator::obtenerPresupuesto() + 100;
        }
    };

class PensionCompleta : public AlquilableDecorator
    {
    public:
        PensionCompleta(Alquilable *alquilable)
        : AlquilableDecorator(alquilable) {}

        std::string getDescripcion() override
        {
            return AlquilableDecorator::getDescripcion() + " (pension completa)";
        }

        float obtenerPresupuesto() override
        {
            return AlquilableDecorator::obtenerPresupuesto() + 65;
        }
};

class DescuentoClienteVIP : public AlquilableDecorator
{
    public:
        DescuentoClienteVIP(Alquilable *alquilable)
        : AlquilableDecorator(alquilable) {}

        std::string getDescripcion() override
        {
            return AlquilableDecorator::getDescripcion() + " (descuento cliente VIP)";
        }

        float obtenerPresupuesto() override
        {
            return AlquilableDecorator::obtenerPresupuesto() * 0.85;
        }
};

int main()
{
    Alquilable *hotel_mardelplata = new Hotel("Hotel en Mar del Plata (Guerrero)");
    hotel_mardelplata = new PensionCompleta(hotel_mardelplata);

    std::cout << hotel_mardelplata->getDescripcion() << std::endl;
    std::cout << "Precio final: $ " << hotel_mardelplata->obtenerPresupuesto() <<  std::endl;

    // Cada instancia de hotel_denia es un nuevo objeto el cual es "decorado" con su respectivo decorador.
    Alquilable *hotel_denia = new Hotel("Hotel en Denia (Alicante)");

    // En este caso, el hotel_denia es "decorado" con el decorador PrimeraLineaDePlaya, lo que modifica sus atributos sin
    // como si le agregara una "capa".
    hotel_denia = new PrimeraLineaDePlaya(hotel_denia);
    hotel_denia = new PensionCompleta(hotel_denia);
    hotel_denia = new DescuentoClienteVIP(hotel_denia);

    // Finalmente obtenemos la descripcion del hotel con todas sus modificaciones.
    std::cout << hotel_denia->getDescripcion() << std::endl;
    std::cout << "Precio final: $ " << hotel_denia->obtenerPresupuesto() << std::endl;

    // Limpia la memoria asignada dinámicamente
    delete hotel_mardelplata;
    delete hotel_denia;

    return 0;
}
