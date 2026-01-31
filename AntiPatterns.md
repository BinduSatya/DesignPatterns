# Anti Pattern

## 1. God Object

- One Class maintaining all the responsibilities.
- Causes too many errors.

## 2. Spaghetti Code

- Mutliple classes being dependent on each other causing hard time to debug, and
- it will be tightly coupled, changing some line of code causes many problems.

## 3. Hard-Coding Things

- We should avoid hard coding things, as much as possible untill we know that those values
- will be same for the whole lifetime of the application.

## 4. Gold-Plating / Over Engineering

- Over complicating things just because we know those concepts or thinking may be they
- are usefull in future use cases.

## 5. DRY (Donot Repeat Yourself)

## 6. Constructor Overloading

- Solution will be Builder Designer Pattern

## 7. Over use of getter and setters

- Only when we want validation before reading or
- writing the values for a variable we should use getters and setters but not everytime.

## 8. Premature Optimisation

- Focusing more on optimisation before making the code work is bad,
- _(First Make it work, then make it fast)_
- _(Brute Force -> Better -> Optimise)_

## 9. Overusing of Inheritance

- With multiple or overuse of Inheritance the code becomes too much complicated
