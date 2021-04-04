# G-P Mapping Scheme Documentation by File
This is not a walkthrough of each function, it is a basic description of the purpose and methods used
in each file(at least the ones I got to. A lot of effort was put into making each function name self 
explanatory however, where that falls short, additional comments in-line should help. I am well aware 
this is poor practice and I do apologize for past me, but since I am no longer a part of this project 
I will leave that for future researchers to fix. 

## CellArrayScaffold.cpp

### Purpose
This file stores a function which returns a CellArray. It exists to allow resimulation in testmode

### Functionality and Explanation
The C++ code for this function is produced by a print function in the CellArray.cpp file and can be 
copied directly from the terminal output and pasted here to recreate the simulation.

## Cell.cpp

### Purpose
A Cell is a fundamental class of the program which stores information about how the simulation
will run.

### Functionality and Explanation
Cells were built with the idea of real stem cells in mind. While each Cell could be anything at the start 
of the program, it will be built as one of 5 types, either a "Neuron", "Photosensor", "Infra-Red Sensor", 
"Left Motor", or "Right Motor." Neurons do some sort of math on data before passing it on, photosensors 
record light levels, Infra-Red sensors use light to determine distance of objects, and motors are wheels.

Cells are circular and exist in a 2D plane, starting from the origin with a 
radius of 0. Each Cell stores its CellArray index(see" CellArray.cpp"), its Gene(see "Gene.cpp"),
its position, its speed, its growthrate, whether it has finished moving, whether it has finished growing,
and whether it has attached to a SensorDot(see "SensorDot.cpp" and "SensorArray.cpp"). Cells 
additionally hold a vector of Cell indices representing connections to other cells for easy access.

While optimizing I tried not to copy Cells as variables in, or arguments to, functions and instead
passed the Cell's index and a pointer to the CellArray. This severely decreases the amount of data 
that needs to be moved during the simulation and saves time and resources

## CellArray.cpp

### Purpose
A CellArray offers a compact and concise method to store the vector of Cells that will be 
repeatedly referenced throughout the simulation.

### Functionality and Explanation
Despite its name, CellArray does not store or implement an array, it uses a vector instead. While
add(Cell &Cell) is implemented, it suffers in performance when compared with 
emplace(std::string type, int index) due to emplace building the object in its position rather than 
having to create the object then pass it to add() to move it into place.

## Connection.cpp

### Purpose
Connections between Cells store the direction and weight of their links. 

### Functionality and Explanation
A Connection is made when one Cell overlaps with another, however Motors and Sensors cannot
attach to Cells of the same general type(Photosensors cannot attach to Infra-Red sensors for example).
In addition, both Cells have to have started moving and growing before a connection can be made. 

The direction that information flows is determined by a variety of factors. Most simple are Neurons,
where information from bigger Cells "flows" to smaller Cells. A sensor will always "flow" outward, 
giving but never receiving information. Vice versa Motors will always receive information.

Connection Weight will be explained in ConnectionWeight.cpp

## ConnectionWeight.cpp

### Purpose


### Functionality and Explanation
Connection Orientation is what I will call the positive or negative value of ConnectionWeight which
determines whether increases in stimuli provide direct or inverse effects.

## Gene.cpp

### Purpose
Gene's carry the basic instructions to build a Cell

### Functionality and Explanation
Each Cell stores its own gene and often references the data contained in it to build the simulation.

## GenerateGene.cpp

### Purpose
Generates a Gene based on preset range variables

### Functionality and Explanation
Gene characteristics are randomly generated within a preset range. The type of the Cell can either
be left blank for that to be randomly assigned or can be given as input. Left and Right motors are
restricted to their respective halves of the polygon

## Genotype.cpp

### Purpose
Calculates and stores the sum of the results of the Genes in the form of a CellArray and 
ConnectionVector

### Functionality and Explanation
Moves Cells to their new positions and adjusts their size based on Gene specifications

Records intersections between Cells by checking if the distance between them is less than the 
sum of their radii. Uses several prechecks to stop excessive calculations.

Finalizes Connection directions, orientations, and weights based on Cell type, Diameter, and Theta

## GlobalVariables.cpp

### Purpose
### Functionality and Explanation

## PolygonCalculations.cpp

### Purpose
### Functionality and Explanation

## random.cpp

### Purpose
Implements randomization for intergers or floats in a given range

### Functionality and Explanation
The mix function and its use in srand() inside each function was a solution found on StackOverflow for 
programs where randomization had to happen multiple times per second. I don't fully understand how
it works but a significant number of test runs have shown the values to be good pseudo-random
numbers for this simulation.

## Phenotype.cpp

### Purpose
### Functionality and Explanation

## RunSimulation.cpp

### Purpose
### Functionality and Explanation

## SensorArray.cpp

### Purpose
### Functionality and Explanation

## SensorDot.cpp

### Purpose
### Functionality and Explanation
