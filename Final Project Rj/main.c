#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "mapping.h"
#include "shipment.h"

// only for VsCode
#include "mapping.c"
#include "shipment.c"

int main(void)
{
	int tempDestRow;
	char tempDest[4], tempDestCol;

	struct Point destn;
	struct Map baseMap = populateMap();
	struct Route blueRoute = getBlueRoute();
	struct Route greenRoute = getGreenRoute();
	struct Route yellowRoute = getYellowRoute();
	struct Route allRoutes[] = {blueRoute, greenRoute, yellowRoute};

	struct Truck truck[3];
	struct Shipment shipment;

	for (int i = 0; i < 3; i++)
	{
		truck[i].current_weight = 0;
		truck[i].current_volume = 0;
		truck[i].truck_id = 2 << i;
	}

	printf("=================\n");
	printf("Seneca Polytechnic Deliveries\n");
	printf("=================\n");

	while (1)
	{
		printf("Enter shipment weight, box size and destination (0 0 x to stop): ");
		scanf("%d%d%s", &shipment.weight, &shipment.size, &tempDest);

		if (shipment.weight == 0 && shipment.size == 0 && !strcmp(tempDest, "x"))
		{
			printf("Exit Condition!\n");
			break;
		}
		sscanf(tempDest, "%d%c", &tempDestRow, &tempDestCol);

		shipment.destination.row = tempDestRow - 1;
		shipment.destination.col = tempDestCol - 'A';

		if (shipment.weight <= 0 || shipment.weight > 2500)
		{
			printf("Invalid weight (must be 1-2500 Kg.)\n");
			continue;
		}
		if (!validCargo(shipment.size))
		{
			printf("Invalid size\n");
			continue;
		}
		if (shipment.destination.row < 0 || shipment.destination.row >= MAP_ROWS || shipment.destination.col < 0 || shipment.destination.col >= MAP_COLS)
		{
			printf("Invalid Destination\n");
			continue;
		}

		int idx[3], original_dist[3];
		struct Route div[3];

		for (int i = 0; i < 3; i++)
		{
			idx[i] = getClosestPoint(&allRoutes[i], shipment.destination);

			// shortestPath function has bugs (segmentation fault)
			div[i] = shortestPath(&baseMap, allRoutes[i].points[idx[i]], shipment.destination);
			original_dist[i] = div[i].numPoints - 1;
		}

		// Debug only (show everything)
		/*
		for (int i = 0; i < 3; i++)
		{
			switch (i)
			{
			case 0:
				printf("Blue Route: \n");
				break;
			case 1:
				printf("Green Route: \n");
				break;
			case 2:
				printf("Yellow Route: \n");
				break;
			default:
				break;
			}
			printf("  * Closest Point: %d%c\n", allRoutes[i].points[idx[i]].row + 1, allRoutes[i].points[idx[i]].col + 'A');
			printf("  * Euclidean Dist: %lf\n", distance(&allRoutes[i].points[idx[i]], &shipment.destination));
			printf("  * Actual Distance: %d\n", original_dist[i]);
			printf("  * Diversion: ");
			if (div[i].numPoints < 1)
			{
				printf("Delivery Not Possible!");
			}
			else if (div[i].numPoints == 1)
			{
				printf("No Diversion");
			}
			else
			{
				for (int j = 0; j < div[i].numPoints; j++)
				{
					printf("%d%c, ", div[i].points[j].row + 1, div[i].points[j].col + 'A');
				}
			}

			printf("\n\n");
		}
		*/


		if (original_dist[0] == -1 && original_dist[1] == -1 && original_dist[2] == -1)
		{
			printf("Delivery not possible!\n");
			continue;
		}

		int delivered = 0;
		for (int i = 0; i < 3; i++)
		{
			int min_idx = getMinIdx(original_dist);
			if (!isTruckOverloaded(truck[min_idx], shipment) || !isBoxSizeExceeded(truck[min_idx], shipment.size))
			{
				original_dist[min_idx] = INT_MAX;
				continue;
			}
			truck[min_idx].current_weight += shipment.weight;
			truck[min_idx].current_volume += shipment.size;
			switch (min_idx)
			{
			case 0:
				printf("Ship on BLUE line,");
				break;
			case 1:
				printf("Ship on GREEN line,");
				break;
			case 2:
				printf("Ship on YELLOW line,");
				break;
			default:
				break;
			}
			if (original_dist[min_idx] == 1)
			{
				printf(" no diversion\n");
			}
			else if (original_dist[min_idx] > 1)
			{
				printf(" divert: ");
				for (int j = 0; j < div[min_idx].numPoints; j++)
				{
					printf("%d%c, ", div[min_idx].points[j].row + 1, div[min_idx].points[j].col + 'A');
				}
				printf("\n");
			}
			delivered = 1;

			//for debug only
			printf("Curr_weight = %d, Curr_vol = %d\n\n", truck[min_idx].current_weight, truck[min_idx].current_volume);

			break;
		}
		if(!delivered){
			printf("Ships tomorrow\n");
		}
	}

	printf("Thanks for shipping with Seneca Polytechnic!\n");

	return 0;
}