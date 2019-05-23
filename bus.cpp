#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <random>
#include <string>

using namespace std;


struct event{
	double time;
	char type;
	int busNumber, 
	stopNumber; 

	friend bool operator>(const event& lhs, const event& rhs)
    {
        return lhs.time > rhs.time;
    }
 };
int main(){

double timer=0.0;
double simulationTime= 8 * 60 * 60; 

int numBuses = 5;
int boarding_time= 2; 
int meanArrivalRate= 5;
int time_to_next_stop= 2 * 60;
int countBusStop= 15;
long checkpoint=0;

int line[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

priority_queue<event, vector<event>, greater<event> > q;

random_device rd;
mt19937 rng(rd());
uniform_int_distribution<> dist(1,countBusStop);

for (int i=0; i< numBuses ; i++){
	struct event arrivalEvent; 
//	strcpy (arrivalEvent.type, "arrival");
	arrivalEvent.type = 'a';
	arrivalEvent.time = 0;
	arrivalEvent.busNumber = i;
	arrivalEvent.stopNumber= countBusStop/numBuses % countBusStop; 
	q.push(arrivalEvent);
	cout << "arrival\n";
}

for (int i=0; i< countBusStop; i++){
	struct event personEvent;
//	strcpy (personEvent.type, "person");
	personEvent.type = 'p';
	personEvent.time = 0;
	personEvent.busNumber = 0;
	q.push(personEvent);
	cout << "person\n";
}


while(!q.empty()){
		struct event x = q.top();
		q.pop();
		printf("%c\t%f\t%d\t\n",x.type,x.time,x.stopNumber);

		switch (x.type) {
			case 'a':
			 cout << "case a \n";
			 if(line[x.stopNumber] > 0){
			 	struct event boarderEvent;						//boarding
			 	boarderEvent.type = 'b';

			 	int temp = timer + boarding_time;  
			 	boarderEvent.time = temp ; 
			 	int theBus = rand() % 5 ;
			 	boarderEvent.busNumber 	= theBus;
			 	boarderEvent.stopNumber = x.stopNumber;				
				q.push(boarderEvent);
				//cout<<"Generated a boarder event \n";
				cout<<"stopNumber "<<boarderEvent.stopNumber<<" busNumber "<<boarderEvent.busNumber
				<< " time "<< boarderEvent.time<<endl;
			 	//generate boarder event
			 }
			 else{
			 	struct event arrivalEvent;							//arrival
			 	arrivalEvent.type = 'a';
			 	arrivalEvent.time = timer + time_to_next_stop;
			 	cout <<"a timer " <<arrivalEvent.time<< endl;
			 	//cout << "arrivalEvent.time"<< x.time <<"\n";
			 	x.stopNumber= x.stopNumber + 1 % countBusStop;
			 	q.push(arrivalEvent);
			 	//generate arrival event
			 }
			 break;
			
			case 'b':
			 cout << "case b\n";									//arrival
			 if(line[x.stopNumber] == 0){
			 	struct event arrivalEvent;
			 	arrivalEvent.stopNumber= (int)(line[x.stopNumber] + 1) % countBusStop;
			 	
			 	int theBus = rand() % 5 ;
			 	arrivalEvent.busNumber 	= theBus+1 % numBuses;
			 	
			 	arrivalEvent.stopNumber = x.stopNumber +1 % countBusStop;			 	
			 	
			 	q.push(arrivalEvent);
				//generate arrival event at x.stop_num+1
			 }
			 else{
			 	while (line[x.stopNumber] != 0) {					//boarding
					cout <<"boarding at stopNumber " <<x.stopNumber <<" busNumber "<< x.busNumber
					<<"time"<<x.time<< "\n";
					timer  = x.time +boarding_time;
					cout <<"before boarding, the line is: " <<line[x.stopNumber]<< "\n";
					line[x.stopNumber]= line[x.stopNumber]-1;
			 		cout <<"after boarding, the line is: " <<line[x.stopNumber]<< "\n";
			 	//generate boarder event at time = clock + boarding_time
			 }
			}
			 break;
			case 'p':
			cout << "new person\n";
			struct event personEvent;

			int xx = rand() % 30 ;
			//double y= log(1- xx)/5; 

			//time + xx
			personEvent.time = timer + xx ; 

			line[personEvent.stopNumber]++;
			cout <<"p timer " <<personEvent.time<< endl;
			personEvent.stopNumber =x.stopNumber; 
			q.push(personEvent);
			//line[x.stopNumber]+1;
			//generate person event at clock + random()
			 break;

		}
}
}
	 	//printf("%c\t%f\t%d\t\n",x.type,x.time,x.stopNumber);