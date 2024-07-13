#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define num_of_conn 5
#define num_of_neurons 64
#define iter 1024

enum neuron_type {
	HIDDEN,
	INPUT,
	OUTPUT
};

typedef struct connection {
	float weight;
	float* destination;
}connection;

typedef struct neuron {
	float input;
	float output;
	connection connections[num_of_conn];
}neuron;

void init(neuron nn[]) {
	srand(time(0));
	for(int i = 0; i < num_of_neurons; i++) {
		
		nn[i].input = 0.0f;
		nn[i].output = 0.5f;
		for(int n = 0; n < num_of_conn; n++) {
			nn[i].connections[n].weight = ((float)rand()/RAND_MAX -0.5f)*2;
			nn[i].connections[n].destination = &nn[(i+n+1)%num_of_neurons].input;
		}	
	}
}
void print_nn(neuron nn[]) {
	printf("\n\nneural_network:\n\n");
	for(int i = 0; i < num_of_neurons; i++) {
		printf("neuron : %f\n",nn[i].output);

		for(int n = 0; n < num_of_conn; n++) {
			printf("\t%f , %p\n",nn[i].connections[n].weight,nn[i].connections[n].destination);
		}
		
		printf("\n");
	}
}
void weight_func(neuron nn[]) {
	for(int i = 0; i < num_of_neurons; i++) {
		for(int n = 0; n < num_of_conn; n++) {
			*nn[i].connections[n].destination += nn[i].output * nn[i].connections[n].weight;
		}
	}
}
void neuron_func(neuron nn[]) {
	for(int i = 0; i < num_of_neurons; i++) {
		nn[i].output = (float) 1/(1+pow(1+(4/(float)num_of_conn), -(double)nn[i].input));
		nn[i].input = 0;
	}
}
int main() {
	neuron neural_network[num_of_neurons];
	init(neural_network);
	print_nn(neural_network);
	for(int i=0; i<iter;i++){
		weight_func(neural_network);
		neuron_func(neural_network);

	}
	
	for(int i = 0; i < num_of_neurons; i++) {
		printf("%f\n",neural_network[i].output);
	}
	printf("Done!\n");

	return 0;
}
