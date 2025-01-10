# SkyNav AI

**SkyNav** is an advanced navigation system built with C++ to provide optimized routing and navigation solutions.

## Features

- **Flight Data Representation**:
  - Parsing flight data into a graph with proper representation of vertices and edges.
  - Visualization of nodes and edges using SFML, including tooltips for flight details.

- **Flight Booking**:
  - Display of direct and connecting flights with smooth input handling.
  - Highlighted routes in the graph and visualization of layover feasibility.

- **Shortest and Cheapest Route Finder**:
  - Dijkstra’s algorithm implementation for shortest paths by time and cost.
  - Dynamic computation of optimal paths with evaluated and non-evaluated nodes visually distinguished.
  - Highlighting optimal routes for better clarity.

- **Custom Flight Paths and Preferences**:
  - Filtering flights based on user preferences like time, cost, and layover options.
  - Adaptable to dynamic changes and recalculated paths highlighted visually.

- **Layover Management**:
  - Accurate layover calculations using data structures like queues.
  - Smooth transitions for connecting flights and visualization with dashed lines.

- **Advanced Route Generation**:
  - Management of multi-leg journeys with interactive path adjustments.
  - Visualization of linked lists with arrows for clear path tracking.

- **Graphical Query and Subgraph Generation**:
  - Efficient subgraph generation and filtering of cities/routes based on queries.
  - Displaying active routes clearly while fading irrelevant nodes.

- **Dynamic Data Management**:
  - Real-time navigation capabilities by reading data from external files.

- **Enhanced Graphics and Usability**:
  - Intuitive user interface with a welcome screen and a colorful goodbye screen.
  - Visual clarity enhanced through tooltips, dashed lines, and highlighted routes.

- **Audio and Interactive Feedback**:
  - Audio cues for key navigation events to enhance the user experience.

## Getting Started

### Prerequisites

- Visual Studio (or a compatible C++ IDE)
- C++20 or later
- Necessary headers and libraries included in the repository:
  - `GraphVisualizer.h`
  - `ascii.h`
  - `color.h`

### Installation

1. Clone the repository:
   ```sh
   git clone https://github.com/waris206/SkyNav_ai.git
   ```
2. Open the project in Visual Studio.
3. Build the solution to compile the project.

### Usage

1. Run the executable file after building the project.
2. Enjoy the welcome screen upon startup.
3. Explore the following features:
   - Visualize paths dynamically using SFML.
   - Choose between travel modes: transit, flight, or direct.
   - Filter paths by date, time, or cost.
   - Utilize Dijkstra's algorithm for efficient route calculations.
   - View graphical representations of data and path adjustments.
   - Manage layovers and visualize transitions dynamically.
4. Upon exit, enjoy the colorful goodbye screen and review the contributors list.

## Repository Structure

- **Source Files**: Core navigation and logic implementation.
- **Headers**: Modular code organization using headers like `GraphVisualizer.h`, `ascii.h`, and `color.h`.
- **Assets**: Includes audio files, ASCII art, and data files for dynamic input.

## Contributors

This project was collaboratively developed by:

- Muhammad Akash Waris
- Habib Ahmed
- Abdullah Noman
