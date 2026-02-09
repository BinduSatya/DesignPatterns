````mermaid
---
config:
  theme: neo-dark
---
classDiagram
    direction LR
    class RateLimiterStrategy {
        <<interface>>
        +allowRequest(userId: string) bool
    }
    class TokenBucket {
        -capacity: int
        -refillRate: double
        -tokens: map<string, double>
        -lastRefill: map<string, time_point>
        +allowRequest(userId: string) bool
    }

    class LeakyBucket {
        -capacity: int
        -leakRate: double
        -reqs: map<string, int>
        -lastLeak: map<string, time_point>
        +allowRequest(userId: string) bool
    }

    class FixedWindow {
        -limit: int
        -windowSize: int
        -counter: map<string, int>
        -windowStart: map<string, time_t>
        +allowRequest(userId: string) bool
    }

    class SlidingWindow {
        -limit: int
        -windowSize: int
        -requests: map<string, deque<time_point>>
        +allowRequest(userId: string) bool
    }
    class RateLimiterContext {
        -strategy: RateLimiterStrategy*
        +allowRequest(userId: string) bool
    }
    class Server {
        -limiter: RateLimiterContext
        +handleRequest(userId: string) void
    }
    RateLimiterStrategy <|-- TokenBucket
    RateLimiterStrategy <|-- LeakyBucket
    RateLimiterStrategy <|-- FixedWindow
    RateLimiterStrategy <|-- SlidingWindow
    RateLimiterContext --> RateLimiterStrategy : uses
    Server --> RateLimiterContext : delegates
    ```
````
