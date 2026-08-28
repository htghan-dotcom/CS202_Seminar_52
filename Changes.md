# Changes Log (Since Last Presentation)

**Course:** CS202 - Programming Systems (Class 25A02)  
**Institution:** VNUHCM - University of Science (HCMUS)  
**Topic:** Interpreter Design Pattern (Report 1)  
**Team Members:**  
- Trần Thành Lợi (`25125059`)  
- Huỳnh Trần Gia Hân (`25125043`)  

---

## 1. Codebase Improvements

- **Architecture Refactoring:** Transitioned from a procedural, single-function string parser (`main_naive.cpp`) to a structured, object-oriented Abstract Syntax Tree (AST) implementation following the GoF Interpreter Pattern.
- **Modern C++ Adoption:** Replaced raw pointers with modern C++ standard smart pointers (`std::shared_ptr`) for automatic memory management and safe composite node ownership.
- **Clean Modular Layout:** Reorganized code into distinct header (`include/`) and source (`src/`) directories matching standard engineering practices:
  - `Context.h`: Manages global runtime variable symbols.
  - `Expression.h`: Abstract base class for AST nodes.
  - `NumberExpression.h`: Terminal node for constants and variables.
  - `AddExpression.h` & `SubtractExpression.h`: Nonterminal operator nodes.
- **Variable Evaluation & Parser Integration:** Enhanced the interpreter to support dynamic context lookups (`a + b - 3`) and added an AST parser helper in `main_pattern.cpp`.

---

## 2. Presentation & Report Content Enhancements

- **In-Depth Theoretical Analysis:** Expanded theoretical explanations covering formal grammar rules, terminal vs. nonterminal expressions, and the role of context.
- **Visual Diagrammatic Models:** Integrated high-resolution Mermaid UML class diagrams for both generic pattern architecture and domain-specific expression tree evaluation.
- **Architectural Flaw Evaluation:** Documented a comprehensive critique of procedural string parsing based on SOLID principles (Open/Closed Principle & Single Responsibility Principle violations).
- **Industry Applications & Trade-Offs:** Added real-world use cases (SQL query engines, `std::regex`, business rule engines) alongside a trade-off matrix comparing naive procedural code, Interpreter Pattern, and parser generators (ANTLR).
- **Interactive Review Quiz:** Added a 5-question multiple-choice self-assessment quiz with detailed explanations to support presentation engagement and peer review.
