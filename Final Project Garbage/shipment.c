/* Include lib */
#include "mapping.h"
#include "shipment.h"
#include <stdlib.h>
#include <limits.h>



// This function checks whether a truck is overloaded after adding a shipment to it.
// It takes two parameters: 'truck' representing the truck with its weight capacity,
// and 'ship' representing the shipment with its weight.
// If the truck's weight capacity is less than or equal to 2500, it adds the shipment's weight to the truck's capacity
// and checks if the updated capacity is still less than or equal to 2500.
// If it is, the function returns 1 (true), indicating the truck is not overloaded.
// Otherwise, it returns 0 (false), indicating the truck is overloaded.
int isTruckOverloaded(struct Truck truck, struct Shipment ship) {
    int result = 0;

    if (truck.weight_capacity <= 2500)
    {
        truck.weight_capacity += ship.weight;

        if (truck.weight_capacity <= 2500)
        {
            result = 1;
        }
    }

    return result;
}

// This function checks whether a truck's volume capacity is exceeded after adding a box to it.
// It takes two parameters: 'truck' representing the truck with its volume capacity,
// and 'boxSize' representing the size of the box to be added.
// If the truck's volume capacity is less than or equal to 1000, it adds the box size to the truck's capacity
// and checks if the updated capacity is still less than or equal to 1000.
// If it is, the function returns 1 (true), indicating the box can be added without exceeding the truck's volume capacity.
// Otherwise, it returns 0 (false), indicating the box size exceeds the truck's capacity.
int isBoxSizeExceeded(struct Truck truck, float boxSize) {
    int result = 0;

    if (truck.volume_capacity <= 100.0)
    {
        truck.volume_capacity += boxSize;

        if (truck.volume_capacity <= 100)
        {
            result = 1;
        }
    }

    return result;
}

// This function verifies if the cargo box size is valid.
// It takes 'boxSize' as a parameter.
// Returns 0 if the box size is invalid; otherwise, returns 1 if the box size is valid.
int validCargo(float boxSize) {
    //const double minSize = 0.25;
    //const double halfSize = 0.5;
    //const double maxSize = 1.0;

    const double minSize = 1.0;
    const double halfSize = 3.0;
    const double maxSize = 5.0;

    if (boxSize == minSize || boxSize == halfSize || boxSize == maxSize) {
        return 1;
    }

    return 0;
}

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
/*void findValidTruckPaths(struct Shipment shipment, struct Truck truck,
    const struct Map* map, struct Route routes[MAX_ROUTE], int* size) {
    int count = 0;
    for (int i = 0; i < truck.allocated_shipments; i++) {
        // Check if the truck's destination aligns with the shipment's destination
        if (truck.destination_counts[i] == hasDestination(&routes[i], shipment)) {
            // Verify if the route intersects with any buildings on the map
            if (!isBuildingIntersected(routes[i], map)) {
                routes[count++] = routes[i];
            }
        }
    }
    *size = count;
}
*/

void findValidTruckPaths(struct Shipment shipment, struct Truck truck, const struct Map* map, struct Route routes[MAX_ROUTE], int* size)
{
    int count = 0;
    for (int i = 0; i < truck.allocated_shipments; i++)
    {
        // Check if the truck's destination count matches the shipment's destination
        if (truck.destination_counts[i] == hasDestination(&routes[i], shipment))
        {
            // Check if the route intersects with buildings on the map
            if (!isBuildingIntersected(routes[i], map))
            {
                routes[count++] = routes[i];
            }
        }
    }              // zxczxc
    *size = count; // Update the number of valid routes found
}

/**
 * Function: getBestRoute
 * - Finds the index of the route with the shortest distance among the valid routes in the "routes" array.
 * @param routes - Array of Route structs containing all the valid routes.
 * @param shipment - Shipment struct containing the destination coordinates (row and column) of the shipment.
 * @param size - Number of valid routes in the "routes" array.
 * @returns - int, the index of the route in the "routes" array with the shortest distance. Returns -1 if no valid route is found.
 */

int hasDestination(const struct Route* route, struct Shipment shipment) {
    for (int i = 0; i < route->numPoints; i++) {
        // Check if the current point in the route matches the shipment's destination
        if (route->points[i].row == shipment.destination.row && route->points[i].col == shipment.destination.col) {
            return 1; // The route includes the shipment's destination
        }
    }
    return 0; // The route does not include the shipment's destination
}

/**
 * Function: printRoute
 * - Prints the points (coordinates) of a route to the console.
 * @param route - Route struct containing the points (coordinates) of the route.
 * @param shipment - Shipment struct containing the destination coordinates (row and column) of the shipment.
 * @returns - void, does not return a value, only prints to the console.
 */
void printRoute(struct Route route, struct Shipment shipment) {
    printf("Route to Shipment (Destination: (%d, %d)):\n", shipment.destination.row, shipment.destination.col);
    for (int i = 0; i < route.numPoints; i++) {
        printf("(%d, %d) ", route.points[i].row, route.points[i].col);
    }
    printf("\n");
}


/**
 * Function: isBuildingIntersected
 * - Checks if a given route intersects with any buildings on the map.
 * @param route - Route struct containing the points (coordinates) of the route.
 * @param map - Pointer to the Map structure containing the buildings on the map.
 * @returns - int, 1 if the route intersects with a building, and 0 if it does not.
 */
int isBuildingIntersected(const struct Route route, const struct Map* map) {
    for (int i = 0; i < route.numPoints; i++) {
        // Check if the point in the route is a building on the map
        if (map->squares[route.points[i].row][route.points[i].col] == 1) {
            return 1; // The route intersects with a building
        }
    }
    return 0;
}


// Function to get the index of the route with the shortest distance among valid routes
int getBestRoute(struct Route* routes[MAX_ROUTE], struct Shipment shipment, int size)
{
    int shortestDistance = INT_MAX;
    int shortestIndex = -1;

    for (int i = 0; i < size; i++)
    {
        // Calculate the distance from the route's starting point to the shipment's destination
        int routeDistance = distance(&routes[i]->points[0], &shipment.destination);
        if (routeDistance < shortestDistance)
        {
            // Update the shortest distance and corresponding index
            shortestDistance = routeDistance;
            shortestIndex = i;
        }
    }

    return shortestIndex; // Return the index of the route with the shortest distance
}


