#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
  char name[100];
}stop_name;
typedef struct
{
  stop_name route[100];
  int no_stop;
}_route;

typedef struct
{
  _route no[100];
  int no_route;
}_routes;

_routes routes;
typedef struct
{
  stop_name nam[100];
  int no_stop;
}_stops;

_stops stops;


void initialize()
{
  stops.no_stop=0;

}
void readstops()
{
  char *st_name;
  FILE *fptr;
  char *line=NULL;
  size_t len=0;
  ssize_t read;
  
  fptr=fopen("stops.txt","r");
  if(fptr!=NULL)
    {
      
      while((read = getline(&line, &len, fptr)) != -1)
	{
	  st_name=strtok(line," ,.-\n");
	  strcpy(stops.nam[stops.no_stop].name,st_name);
	}
    }
  fclose(fptr);  
}
void readroute()
{
  FILE *fptr;
  char *stname;
  char *line=NULL;
  size_t len=0;
  ssize_t read;
  
  int route_no=0;
  int stop_no=0;
  fptr=fopen("busdetails.txt","r");
  if(fptr!=NULL)
    {
      while((read = getline(&line, &len, fptr)) != -1)
	{
	  printf("%s",line);
	  stname=strtok(line," ,.-");
	  stop_no=0;
	  while(stname!=NULL)
	    {
	      strcpy(routes.no[route_no].route[stop_no].name,stname);
	      printf("%s\n",routes.no[route_no].route[stop_no].name);
	      stname=strtok(NULL," ,.-");
	      stop_no++;
	    }
	  routes.no[route_no].no_stop=stop_no;
	  route_no++;
	}
      routes.no_route=route_no;
    }
  fclose(fptr);
}
void print_all_stops()
{
  int i,j;
  for(i=0;i<stops.no_stop;i++)
    {
      printf("%d.%s\n",i+1,stops.nam[i].name);
    }

}
void print_all_routes()
{
  int i,j;
  
  for(i=0;i<routes.no_route;i++)
    {
      printf("route no %d -->  ",i+1);
      for(j=0;j<routes.no[i].no_stop;j++)
	{
	  printf("%d-%s  ",j,routes.no[i].route[j].name);
	}
    }
}
int main()
{
  initialize();
  readstops();
  print_all_stops();
  readroute();
  print_all_routes();
  printf("Welcome to IIT Kharagpur bus service system \n");
  printf("HOME\n");
  printf("1.Get bus routes between two stops\n");
  printf("2.Get all the bus routes\n");
  printf("3.Get all the bus routes through a specific bus stop\n");
  printf("4.Get all bus stops associated with a specific route\n");
  printf("5.Booking\n");
  printf("6.Check availability\n");
  printf("7.Pickup and drop facility between kharagpur railway station and IIT KGP");
  printf("8.Register a complaint");

}
