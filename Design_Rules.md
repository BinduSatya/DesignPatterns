# Basic_Rules:
1. **When to use inheritance**: Inheritance should be only used when we need both *sub type polymorphism* and *reuse of the parent code*, not even if one among them is required
    - **Subtype Polymorphism**: When you just want to implement a method in a child class in its own way (overriding) instead of implementing the parent code use **Interfaces**
    - **Reuse of code**: When you just want to use/implement the parent methods then **use *has-a*** functionality, meaning creating a object (instance) of the parent class in the child sub-class rather than inheriting from the parent class. 
