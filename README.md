# 🎮 C-Based PID Motor Control Simulator

## 📖 Overview

This project simulates a **closed-loop control system**, a fundamental concept in robotics, automation, and embedded engineering. It mimics how a microcontroller would read a sensor (motor speed), compare it to a target setpoint, and use a **PID (Proportional-Integral-Derivative)** algorithm to calculate the necessary power adjustment to minimize the error.

The entire system runs in the terminal without requiring any physical hardware, making it an ideal tool for learning and demonstrating control theory.

-----

## ✨ Key Features

  - **PID Control Engine**: A robust implementation of the PID algorithm with tunable gains (`Kp`, `Ki`, `Kd`) to control system response.
  - **Physics-Based Motor Model**: A simulated DC motor with configurable `inertia` and `friction` to model real-world behavior.
  - **Real-Time Simulation Loop**: A main loop governed by a fixed time step (`dt`) to replicate the behavior of an embedded scheduler.
  - **Data Logging & Analysis**: Automatically logs key metrics (`target`, `speed`, `error`, `output`) to a `.csv` file for easy visualization.
  - **Modular and Clean Code**: The project is logically separated into modules (`pid_controller`, `motor_model`, `logger`) for clarity and maintainability.
  - **Cross-Platform**: Compiles and runs on any system with a standard C compiler (GCC/Clang/MSVC).

-----

## 🧱 System Architecture & Data Flow

This project simulates a **closed-loop PID control system** for a DC motor using pure C code. It models real-world motor physics (inertia, friction), applies PID feedback control, and logs system performance — all without hardware.

<p align="center">
  <img src="images/Flow%20diagram.png" alt="PID Control System Flow Diagram" width="850"/>
  <br/>
  <em>PID Feedback Loop — Simulated Motor Control System</em>
</p>


---

### 🧪 Stage 1: Motor Simulation

- **Motor Model**: Models real DC motor dynamics using simplified physics  
  - Parameters: inertia, friction, torque-to-speed behavior  
- **Target Setpoint**: A desired speed is set in `main.c` for the motor to reach



### 🔁 Stage 2: PID Controller

A classic **PID feedback loop** continuously calculates error and applies corrections:

```c
control_signal = Kp * error + Ki * integral + Kd * derivative;
````

* **`Kp`**: Proportional gain — reacts to current error
* **`Ki`**: Integral gain — eliminates steady-state error
* **`Kd`**: Derivative gain — dampens overshoot



### 📊 Stage 3: Output & Logging

* **🖥️ Console Output**

  * Prints target speed, current speed, error, and control signal in real-time

* **📁 `log.csv` Logging**

  * Stores every cycle's values: target, actual speed, error, and output
  * Enables plotting of performance curves using Python or Excel

---

## 🚀 Getting Started

### Prerequisites

  - A C compiler such as **GCC**. (On Windows, you can use [MinGW](https://www.mingw-w64.org/) or WSL).
  - The **make** utility (optional, but highly recommended for convenience).

### Installation & Execution

1.  **Clone the repository:**

    ```sh
    git clone https://github.com/AkshayTiwari27/PID-Motor-Simulator.git
    cd PID-Motor-Simulator
    ```

2.  **Compile the project:**

      * **With `make` (recommended):**
        ```sh
        make
        ```
      * **Manually with GCC:**
        ```sh
        gcc -o pid_sim main.c pid_controller.c motor_model.c logger.c -std=c99 -Wall
        ```

3.  **Run the simulation:**

    ```sh
    ./pid_sim
    ```

    The simulation will run for the duration specified in `main.c` and print live data to your console.

-----

## ⚙️ How It Works

The simulation operates on a simple, powerful feedback loop:

1.  **Calculate Error**: The `pid_controller` calculates the `error` between the `target_speed` and the `actual_speed` of the motor.
2.  **Compute Control Signal**: The PID algorithm computes a new `control_signal` (simulated voltage) based on the proportional, integral, and derivative of the error.
3.  **Update Motor**: The `motor_model` receives the `control_signal` and updates its `current_speed`, factoring in physical properties like inertia and friction.
4.  **Log Data**: The state of the system for the current cycle is printed to the console and logged to `log.csv`.
5.  **Delay**: The system waits for a small duration (`TIME_STEP_S`) before starting the next cycle, simulating a real-time system.

### Project Structure

```
PID-Motor-Simulator/
├── .gitignore
├── Makefile
├── README.md
├── assets/
│   └── simulation_plot.png
├── include/
│   ├── logger.h
│   ├── motor_model.h
│   ├── pid_controller.h
│   └── utils.h
├── src/
│   ├── logger.c
│   ├── main.c
│   ├── motor_model.c
│   └── pid_controller.c
└── plotter.py
```

-----

## 🔧 Tuning the Controller

The magic of a PID controller lies in tuning the three gain constants (`Kp`, `Ki`, `Kd`) defined in `main.c`. Experiment by changing these values to see how they affect the motor's response.

  - **`KP` (Proportional Gain):** The primary driver. A higher `Kp` results in a faster response but can lead to instability and **overshoot**.
  - **`KI` (Integral Gain):** Eliminates **steady-state error**. It accumulates past errors, ensuring the system eventually reaches its target. Too high an `Ki` can cause significant overshoot.
  - **`KD` (Derivative Gain):** "The dampener." It counters overshoot by reacting to the rate of error change. A higher `Kd` helps the system settle faster but can make it sensitive to noise.

-----

## 📈 Visualizing the Results

The simulation generates `log.csv`. This file can be imported into any spreadsheet program or plotted with the provided Python script.

1.  **Install Python libraries:**

    ```sh
    pip install pandas matplotlib
    ```

2.  **Run the plotting script:**

    ```python
    # plotter.py
    import pandas as pd
    import matplotlib.pyplot as plt

    df = pd.read_csv("log.csv")

    plt.style.use('seaborn-v0_8-grid')
    fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(12, 9), sharex=True)

    # Plot 1: Speed vs Target
    ax1.plot(df['cycle'], df['target_speed'], 'r--', label='Target Speed')
    ax1.plot(df['cycle'], df['actual_speed'], 'b-', lw=2, label='Actual Speed')
    ax1.set_title('Motor Speed Response')
    ax1.set_ylabel('Speed (RPM)')
    ax1.legend()

    # Plot 2: Error and Control Signal
    ax2.plot(df['cycle'], df['control_signal'], 'g-', label='Control Signal (Output)')
    ax2.set_title('PID Controller Output')
    ax2.set_xlabel('Simulation Cycle')
    ax2.set_ylabel('Signal Strength')
    ax2.legend()

    plt.tight_layout()
    plt.savefig("simulation_plot.png")
    plt.show()
    ```

-----

## 💡 Future Enhancements

This project has a strong foundation for future expansion:

  - [ ] **Dynamic Setpoints**: Modify `main.c` to change the `TARGET_SPEED` mid-simulation to see how the controller adapts.
  - [ ] **Load Disturbance**: Introduce a "load" that randomly applies negative force to the motor, testing the controller's robustness.
  - [ ] **Interactive Tuning**: Allow PID gains to be changed at runtime via user input.
  - [ ] **Terminal GUI**: Use a library like `ncurses` to create a more sophisticated, real-time dashboard in the console.

-----

## 📜 License

This project is licensed under the MIT License. See the `LICENSE` file for details.
