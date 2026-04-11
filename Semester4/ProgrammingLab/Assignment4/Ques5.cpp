#include <iostream>

namespace GeometrySystem {

    const double PI = 3.14;

    class Shape {
    public:
        virtual ~Shape() {}
        virtual double getArea() const = 0; 
    };

    class Triangle : public Shape {
    private:
        double base, height;

    public:
        Triangle(double b = 0.0, double h = 0.0) : base(b), height(h) {}

        double getArea() const override { return 0.5 * base * height; }
        
        double getBase() const { return base; }
        double getHeight() const { return height; }
    };

    class Rectangle : public Shape {
    private:
        double length, width;

    public:
        Rectangle(double l = 0.0, double w = 0.0) : length(l), width(w) {}

        double getArea() const override { return length * width; }
        
        double getLength() const { return length; }
        double getWidth() const { return width; }
    };

    class Circle : public Shape {
    private:
        double radius;

    public:
        Circle(double r = 0.0) : radius(r) {}

        double getArea() const override { return PI * radius * radius; }
        
        double getRadius() const { return radius; }
    };

    class ShapeStack {
    private:
        static const int MAX_CAPACITY = 100;
        Shape* stackArray[MAX_CAPACITY];
        int topIndex;

    public:
        ShapeStack() : topIndex(-1) {}

        void Push(Shape* s);
        Shape* Pop();
        
        void Display() const;
        double TotalAreaCovered() const;
    };

    void ShapeStack::Push(Shape* s) {
        if (topIndex >= MAX_CAPACITY - 1) {
            std::cout << "Stack Overflow! Cannot push more shapes.\n";
            return;
        }
        stackArray[++topIndex] = s;
    }

    Shape* ShapeStack::Pop() {
        if (topIndex < 0) {
            std::cout << "Stack Underflow! No shapes to pop.\n";
            return nullptr;
        }
        return stackArray[topIndex--];
    }

    void ShapeStack::Display() const {
        if (topIndex < 0) {
            std::cout << "ShapeStack is empty.\n";
            return;
        }

        std::cout << "--- Stack Contents (Top to Bottom) ---\n";
        for (int i = topIndex; i >= 0; --i) {
            Shape* currentShape = stackArray[i];

            if (Circle* c = dynamic_cast<Circle*>(currentShape)) {
                std::cout << "[Circle] Radius: " << c->getRadius();
            } 
            else if (Rectangle* r = dynamic_cast<Rectangle*>(currentShape)) {
                std::cout << "[Rectangle] L: " << r->getLength() << ", W: " << r->getWidth();
            } 
            else if (Triangle* t = dynamic_cast<Triangle*>(currentShape)) {
                std::cout << "[Triangle] Base: " << t->getBase() << ", Height: " << t->getHeight();
            } 
            else {
                std::cout << "[Unknown Shape]";
            }

            std::cout << " | Area: " << currentShape->getArea() << "\n";
        }
    }

    double ShapeStack::TotalAreaCovered() const {
        double totalArea = 0.0;
        for (int i = 0; i <= topIndex; ++i) {
            totalArea += stackArray[i]->getArea(); 
        }
        return totalArea;
    }

}

using namespace GeometrySystem;

int main() {
    ShapeStack myStack;

    Shape* s1 = new Circle(5.0);
    Shape* s2 = new Rectangle(4.0, 6.0);
    Shape* s3 = new Triangle(3.0, 8.0);
    Shape* s4 = new Circle(2.0);

    myStack.Push(s1);
    myStack.Push(s2);
    myStack.Push(s3);
    myStack.Push(s4);

    myStack.Display();

    std::cout << "\nTotal Area Covered by all shapes in stack: " 
              << myStack.TotalAreaCovered() << "\n\n";

    std::cout << "--- Popping Shapes ---\n";
    while (Shape* poppedShape = myStack.Pop()) {
        std::cout << "Popped a shape with area: " << poppedShape->getArea() << "\n";
        delete poppedShape; 
    }

    return 0;
}