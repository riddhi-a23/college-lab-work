#include <iostream>

namespace WarehouseSystem
{

    const double PI = 3.14;

    class Container
    {
    public:
        virtual ~Container() {}

        virtual double getVolume() const = 0;

        virtual void displayDetails() const;
    };

    class Box : public Container
    {
    private:
        double length, width, height;

    public:
        Box(double l = 0.0, double w = 0.0, double h = 0.0)
            : length(l), width(w), height(h) {}

        double getVolume() const override
        {
            return length * width * height;
        }

        void displayDetails() const override;
    };

    class Cylinder : public Container
    {
    private:
        double radius, height;

    public:
        Cylinder(double r = 0.0, double h = 0.0)
            : radius(r), height(h) {}

        double getVolume() const override
        {
            return PI * radius * radius * height;
        }

        void displayDetails() const override;
    };

    class Pyramid : public Container
    {
    private:
        double baseLength, baseWidth, height;

    public:
        Pyramid(double bl = 0.0, double bw = 0.0, double h = 0.0)
            : baseLength(bl), baseWidth(bw), height(h) {}

        double getVolume() const override
        {
            return (baseLength * baseWidth * height) / 3.0;
        }

        void displayDetails() const override;
    };

    void Container::displayDetails() const
    {
        std::cout << "Generic Container\n";
    }

    void Box::displayDetails() const
    {
        std::cout << "Box [L: " << length << ", W: " << width << ", H: " << height
                  << "] -> Volume: " << getVolume() << "\n";
    }

    void Cylinder::displayDetails() const
    {
        std::cout << "Cylinder [R: " << radius << ", H: " << height
                  << "] -> Volume: " << getVolume() << "\n";
    }

    void Pyramid::displayDetails() const
    {
        std::cout << "Pyramid [Base L: " << baseLength << ", Base W: " << baseWidth
                  << ", H: " << height << "] -> Volume: " << getVolume() << "\n";
    }

}

using namespace WarehouseSystem;

int main()
{
    std::cout << "=== Warehouse Container System ===\n\n";

    const int numContainers = 4;
    Container *warehouse[numContainers];

    warehouse[0] = new Box(10.0, 5.0, 4.0);
    warehouse[1] = new Cylinder(3.0, 10.0);
    warehouse[2] = new Pyramid(6.0, 6.0, 5.0);
    warehouse[3] = new Box(2.0, 2.0, 2.0);

    double totalVolume = 0.0;

    std::cout << "--- Individual Containers ---\n";

    for (int i = 0; i < numContainers; ++i)
    {
        warehouse[i]->displayDetails();
        totalVolume += warehouse[i]->getVolume();
    }

    std::cout << "\n--------------------------------\n";
    std::cout << "Total Volume occupied by all containers: " << totalVolume << " cubic units\n";
    std::cout << "--------------------------------\n";

    for (int i = 0; i < numContainers; ++i)
    {
        delete warehouse[i];
    }

    return 0;
}