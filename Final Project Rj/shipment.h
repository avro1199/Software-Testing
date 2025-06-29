#ifndef SHIPMENT_H
#define SHIPMENT_H
#include "mapping.h"

//double EST_WEIGHT = 1000.0;
//double EST_BOX_SIZE = 36.0;

struct Truck
{

	int truck_id;
	int current_weight;
	int current_volume;
};


/*
* Data structure to work with shipment informaitn
*/
struct Shipment {
	int weight;
	int size; 
	struct Point destination;
};

/* *********************** Function of MS 3 *********************** */

// This function checks whether a truck is overloaded after adding a shipment to it.
// It takes two parameters, 'truck', which represents the truck with its weight capacity,
// and 'ship', which represents the shipment with its weight.
// If the truck's weight capacity is less than or equal to 2500, it adds the weight of the shipment to the truck's capacity
// and then checks if the updated capacity is still less than or equal to 2500.
// If it is, the function returns 1 (true), indicating that the truck is not overloaded.
// Otherwise, it returns 0 (false), indicating that the truck is overloaded.
int isTruckOverloaded(struct Truck truck, struct Shipment ship);


// This function checks whether a truck's volume capacity is exceeded after adding a box to it.
// It takes two parameters, 'truck', which represents the truck with its volume capacity,
// and 'boxSize', which represents the size of the box to be added.
// If the truck's volume capacity is less than or equal to 1000, it adds the size of the box to the truck's capacity
// and then checks if the updated capacity is still less than or equal to 1000.
// If it is, the function returns 1 (true), indicating that the box can be added without exceeding the truck's volume capacity.
// Otherwise, it returns 0 (false), indicating that the box size exceeds the truck's capacity.
int isBoxSizeExceeded(struct Truck truck, int boxSize);

// This function to check the Cargo Valide or not
// It take boxSize as a parameters
// Return it returns 0 (false), and other as true

int validCargo(int boxSize);


/**
 * Function: findValidTruckPaths
 * - Populates the "routes" array with routes that reach the given shipment destination.
 * @param shipment - Shipment struct containing the destination coordinates (row and column) of the shipment.
 * @param truck - Truck struct containing the route the truck travels on the map.
 * @param map - Map struct containing all the points (squares) in the map.
 * @param routes - Array of pointers to Route structs to store the valid routes.
 * @param size - Pointer to an integer to store the number of valid routes.
 * @returns - void, populates the "routes" array and updates the "size" variable.
 */
 void findValidTruckPaths(struct Shipment shipment, struct Truck truck, const struct Map* map, struct Route routes[MAX_ROUTE], int* size);


/**
 * Function: getBestRoute
 * - Finds the index of the route with the shortest distance among the valid routes in the "routes" array.
 * @param routes - Array of Route structs containing all the valid routes.
 * @param shipment - Shipment struct containing the destination coordinates (row and column) of the shipment.
 * @param size - Number of valid routes in the "routes" array.
 * @returns - int, the index of the route in the "routes" array with the shortest distance. Returns -1 if no valid route is found.
 */

int hasDestination(const struct Route* route, struct Shipment shipment);

/**
 * Function: printRoute
 * - Prints the points (coordinates) of a route to the console.
 * @param route - Route struct containing the points (coordinates) of the route.
 * @param shipment - Shipment struct containing the destination coordinates (row and column) of the shipment.
 * @returns - void, does not return a value, only prints to the console.
 */
void printRoute(struct Route route, struct Shipment shipment);


/*
checks if a given route intersects with any buildings on the map.
route (const struct Route): The route to check for intersections with buildings.
map (const struct Map *): A pointer to the Map structure containing the buildings on the map.
returns an integer value: 1 if the route intersects with a building, and 0 if it does not
*/
int isBuildingIntersected(const struct Route route, const struct Map* map);



/*
finds the index of the route with the shortest distance among the valid routes in the routes array that reach the given shipment destination.
routes (struct Route *[MAX_ROUTE]): An array of pointers to Route structures representing different routes
shipment (struct Shipment): A Shipment struct containing the destination coordinates (row and column) of the shipment.
size (int): An integer representing the number of valid routes in the routes array.
returns an integer value, which is the index of the route in the routes array with the shortest distance. If no valid route is found, the function returns -1.
*/
int getBestRoute(struct Route* routes[MAX_ROUTE], struct Shipment shipment, int size);

//new
int getMinIdx(int *distances);

#endif