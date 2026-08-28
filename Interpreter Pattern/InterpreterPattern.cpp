#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <stdexcept>

// ==========================================
// 1. CONTEXT: Stores variables and global state
// ==========================================
class Context {
private:
    std::unordered_map<std::string, int> varMap;
public:
    void setVariable(const std::string& name, int value) {
        varMap[name] = value;
    }

    int getVariable(const std::string& name) const {
        auto it = varMap.find(name);
        if (it != varMap.end()) {
            return it->second;
        }
        throw std::runtime_error("Variable not defined: " + name);
    }
};

// ==========================================
// 2. ABSTRACT EXPRESSION INTERFACE
// ==========================================
class Expression {
public:
    virtual ~Expression() = default;
    virtual int interpret(const Context& context) const = 0;
};

// ==========================================
// 3. TERMINAL EXPRESSIONS (Leaf Nodes)
// ==========================================
class NumberExpression : public Expression {
private:
    int number;
public:
    explicit NumberExpression(int val) : number(val) {}

    int interpret(const Context& context) const override {
        return number;
    }
};

class VariableExpression : public Expression {
private:
    std::string name;
public:
    explicit VariableExpression(std::string varName) : name(std::move(varName)) {}

    int interpret(const Context& context) const override {
        return context.getVariable(name);
    }
};

// ==========================================
// 4. NON-TERMINAL EXPRESSIONS (Branch Nodes)
// ==========================================
class AddExpression : public Expression {
private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
public:
    AddExpression(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)) {}

    int interpret(const Context& context) const override {
        return left->interpret(context) + right->interpret(context);
    }
};

class SubtractExpression : public Expression {
private:
    std::unique_ptr<Expression> left;
    std::unique_ptr<Expression> right;
public:
    SubtractExpression(std::unique_ptr<Expression> l, std::unique_ptr<Expression> r)
        : left(std::move(l)), right(std::move(r)) {}

    int interpret(const Context& context) const override {
        return left->interpret(context) - right->interpret(context);
    }
};

// ==========================================
// 5. CLIENT CODE
// ==========================================
int main() {
    std::cout << "===========================================" << std::endl;
    std::cout << "  INTERPRETER PATTERN DEMO (CS202)         " << std::endl;
    std::cout << "===========================================" << std::endl;

    // Initialize context with variables
    Context context;
    context.setVariable("x", 10);
    context.setVariable("y", 5);

    // Expression 1: "3 + 5 - 2" -> AST: SubtractExpression(AddExpression(3, 5), 2)
    auto expr1 = std::make_unique<SubtractExpression>(
        std::make_unique<AddExpression>(
            std::make_unique<NumberExpression>(3),
            std::make_unique<NumberExpression>(5)
        ),
        std::make_unique<NumberExpression>(2)
    );

    std::cout << "Expression 1: '3 + 5 - 2'" << std::endl;
    std::cout << "Result: " << expr1->interpret(context) << " (Expected: 6)" << std::endl << std::endl;

    // Expression 2: "x + y - 3" -> AST: SubtractExpression(AddExpression(x, y), 3)
    auto expr2 = std::make_unique<SubtractExpression>(
        std::make_unique<AddExpression>(
            std::make_unique<VariableExpression>("x"),
            std::make_unique<VariableExpression>("y")
        ),
        std::make_unique<NumberExpression>(3)
    );

    std::cout << "Expression 2: 'x + y - 3' (with x = 10, y = 5)" << std::endl;
    std::cout << "Result: " << expr2->interpret(context) << " (Expected: 12)" << std::endl;

    return 0;
}