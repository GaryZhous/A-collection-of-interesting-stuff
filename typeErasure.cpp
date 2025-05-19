#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Context passed to drawing functions (could be more complex in real use)
struct Context {
    std::string surface;
};

// Forward declarations for external DrawShape functions
struct Circle;
struct Square;

void DrawShape(const Context& ctx, const Circle& c);
void DrawShape(const Context& ctx, const Square& s);

// Type-erased Shape class
class Shape {
private:
    struct ShapeConcept {
        virtual ~ShapeConcept() = default;
        virtual void DoDraw(const Context& ctx) const = 0;
    };

    template<typename ShapeT>
    struct ShapeModel : public ShapeConcept {
        ShapeModel(ShapeT shape) : m_shape{ std::move(shape) } {}
        void DoDraw(const Context& ctx) const override {
            DrawShape(ctx, m_shape);
        }
        ShapeT m_shape;
    };

    std::unique_ptr<ShapeConcept> m_pimpl;

public:
    template<typename ShapeT>
    Shape(ShapeT shape)
        : m_pimpl{ std::make_unique<ShapeModel<ShapeT>>(std::move(shape)) } {}

    void Draw(const Context& ctx) const {
        m_pimpl->DoDraw(ctx);
    }
};

// Concrete shapes
struct Circle {
    double radius;
};

struct Square {
    double side;
};

// Free functions to "draw" shapes (simulate rendering)
void DrawShape(const Context& ctx, const Circle& c) {
    std::cout << "Drawing Circle of radius " << c.radius
              << " on " << ctx.surface << std::endl;
}

void DrawShape(const Context& ctx, const Square& s) {
    std::cout << "Drawing Square of side " << s.side
              << " on " << ctx.surface << std::endl;
}

// Main program
int main() {
    Context canvas{ "Canvas1" };

    Shape s1 = Circle{ 5.0 };
    Shape s2 = Square{ 3.0 };

    std::vector<Shape> shapes;
    shapes.push_back(s1);
    shapes.push_back(s2);

    for (const auto& shape : shapes) {
        shape.Draw(canvas);
    }

    return 0;
}
