# Elevator System Design (Single-Threaded)

## Overview

This project implements a simplified yet architecturally correct **Elevator Management System** using C++.  
Although the problem looks simple at first, it becomes non-trivial once multiple elevators, floors, safety rules, and optimization goals are introduced.

The primary focus of this project is **correct responsibility assignment, clean object-oriented design, and extensibility**, rather than premature optimization or concurrency.

---

## Why This Is a Tricky Design Problem

- Requests originate from multiple sources (outside floors, inside elevators)
- Elevator behavior must strictly follow safety rules
- Scheduling decisions impact both passenger wait time and system efficiency
- Poor responsibility separation quickly leads to unscalable designs
- Correctness must be ensured before adding concurrency

---

## Key Requirements

1. Support multiple elevators operating across many floors
2. Handle multiple concurrent requests from different floors
3. Optimize elevator selection to reduce wait time
4. Enforce correct elevator behavior (doors open only when idle)
5. Support emergency handling
6. Keep the system scalable and extensible

---

## Architecture Overview

The system is intentionally designed as a **single-threaded, step-driven simulation** to ensure deterministic behavior and correctness.

### High-Level Flow

---

## Core Components

### Elevator
- Represents a single physical elevator
- Maintains current floor, state, and destination queue
- Executes assigned requests
- Enforces safety rules using explicit states
- Never makes scheduling decisions

### ElevatorController
- Acts as the central coordinator
- Receives outside (hall) requests
- Selects the best elevator using a scoring strategy
- Drives the system using a `step()` method

### FloorPanel
- Represents the outside panel on each floor
- Generates hall requests (Up / Down)
- Has no knowledge of elevator assignment

### HallRequest
- Encapsulates an outside request
- Contains floor number and direction
- Requires global scheduling decisions

### ElevatorState
Defines valid elevator states:
- IDLE
- MOVING_UP
- MOVING_DOWN
- DOOR_OPEN
- EMERGENCY

---

## Design Patterns Used

### State Pattern
- Used in the Elevator to model movement, door operations, and emergency handling
- Prevents invalid state transitions

### Strategy Pattern
- Used in the ElevatorController for elevator selection logic
- Allows scheduling logic to evolve independently

### Command Pattern
- Hall requests are modeled as command objects
- Requests can be queued, routed, and analyzed independently

---
### Observer Pattern
- FloorPanels notify the ElevatorController of new requests
- Decouples request generation from handling
---