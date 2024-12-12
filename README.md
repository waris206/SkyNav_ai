# SkyNav AI

SkyNav AI is an advanced navigation system built with C++ to provide intelligent routing and navigation solutions. This project leverages modern AI techniques to enhance user experience and optimize travel paths.

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
