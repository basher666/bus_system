#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
  char name[100];
  char time[100];
}stop_det;
typedef struct
{
  stop_det route[100];
  int num_stop;
}_route;

typedef struct
{
  _route no[100];
  int no_route;
}_routes;

_routes routes;
typedef struct
{
  stop_det nam[100];
  int no_stop;
}_stops;

_stops stops;



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
	  strcpy(stops.nam[stops.no_stop++].name,st_name);

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
	  stname=strtok(line," ,.-\n");
	  
	  stop_no=0;
	  
	  while(stname!=NULL)
	    {
	      if(stop_no==0)
		{
		  strcpy(routes.no[route_no].route[stop_no].name,stname);
		  stname=strtok(NULL," ,.-\n");
		  strcpy(routes.no[route_no].route[stop_no].time,stname);
		  stname=strtok(NULL," ,.-\n");
		  stop_no++;
		  continue;
		}
	      strcpy(routes.no[route_no].route[stop_no].name,stname);
	      printf("%s-",routes.no[route_no].route[stop_no].name);
	      
	      stname=strtok(NULL," ,.-\n");
	      strcpy(routes.no[route_no].route[stop_no].time,stname);
	      printf("%s\n",routes.no[route_no].route[stop_no].time);
	      
	      stname=strtok(NULL," ,.-\n");
	      stop_no++;
	    }
	  routes.no[route_no].num_stop=stop_no;
	  route_no++;
	}
      routes.no_route=route_no;
    }
  fclose(fptr);
}

void initialize()
{
  stops.no_stop=0;
  routes.no_route=0;
  readstops(); 
  readroute();
}

void print_all_stops()
{
  int i,j;
  printf("STOPS\n");
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
      for(j=0;j<routes.no[i].num_stop;j++)
	{
	  printf("%d-%s  ",j,routes.no[i].route[j].name);
	}
      printf("\n");
    }
}
void get_bus_stop(char *s)
{
  printf("choose your stop:\n");
  print_all_stops();
  int a;
  scanf("%d",&a);
  strcpy(s,stops.nam[a-1].name);
}

void routes_between_stops()
{
  int i,j,k,f;
  char start[100],des[100];
  printf("Enter Starting and Destination Bus stop:\n");
  printf("Starting Bus Stop:");
  get_bus_stop(start);
  printf("Destination Bus Stop:");
  get_bus_stop(des);
  printf("Route No. -- Bus Start from -- Bus Goes to\n");
  for(i=0;i<routes.no_route;i++)
    {
      f=0;
      for(j=0;j<routes.no[i].num_stop;j++)
	{
	  if(strcmp(routes.no[i].route[j].name,start)==0)
	    {
	      for(k=j+1;k<routes.no[i].num_stop;k++)
		{
		  if(strcmp(routes.no[i].route[k].name,des)==0)
		    {
		      f=1;
		      break;
		    }
		}
	      if(f==1)
		break;
	    }
	}
      if(f==1)
	{
  
	  printf("%d     -----     %s   -----   %s \n",i+1,routes.no[i].route[0].name,routes.no[i].route[routes.no[i].num_stop-1].name);
	}
    }
 
  return;
}
void routes_through_stop()
{
  int i,j;
  char st[100];
  printf("Enter Bus Stop name to find routes:\n");
  get_bus_stop(st);
  int f;
  for(i=0;i<routes.no_route;i++)
    {
      f=0;
      
      for(j=0;j<routes.no[i].num_stop;j++)
	{
	  if(strcmp(routes.no[i].route[j].name,st)==0)
	    {
	      f=1;
	      break;
	    }
	}
      if(f==1)
	{
	  printf("Route NO.  ---   Bus start from ---  Bus goes to  --- Time\n");
	  printf("%d  -----   %s  ---  %s  ---  %s\n",i+1,routes.no[i].route[0].name,routes.no[i].route[routes.no[i].num_stop-1].name,routes.no[i].route[j].time);
	}
    }
}

void stops_in_route()
{
  int a,i;
  printf("Enter Route No (between 1 and %d):\n",routes.no_route);
  scanf("%d",&a);
  printf("Sl. No. ------- Bus Stop ------ Time\n");
  for(i=0;i<routes.no[a].num_stop;i++)
    {
      printf("%d  ------ %s  ------- %s \n",i+1,routes.no[a].route[i].name,routes.no[a].route[i].time);
    }
}

void complaint()
{
  FILE *fptr;
  char name[100];
  char complaint[5000];
  fptr=fopen("complaints.txt","a");
  
  printf("Enter your name\n");
  fgets(name,100,stdin);  
  fgets(name,100,stdin);
  fprintf(fptr,"%s",name);
  
  printf("Write your complaint in a line(under 5000 characters) \n");
  fgets(complaint,5000,stdin);  
  fprintf(fptr,"%s\n \n",complaint);
  
  fclose(fptr);
}
int main()
{
  int a,f=0;
  initialize();
  
  //print_all_routes();
  //complaint();
  //routes_through_stop();
  //stops_in_route();
  while(f==0)
    {
      printf("Welcome to IIT Kharagpur bus service system \n");
      printf("HOME\n");
      printf("1.Get bus routes between two stops\n");
      printf("2.Get all the bus routes\n");
      printf("3.Get all the bus routes through a specific bus stop\n");
      printf("4.Get all bus stops associated with a specific route\n");
      printf("5.Booking\n");
      printf("6.Check availability\n");
      printf("7.Pickup and drop facility between kharagpur railway station and IIT KGP\n");
      printf("8.Register a complaint\n");
      printf("9.exit\n");
      scanf("%d",&a);

      if(a==1)
	{
	  printf("counter\n");
	  routes_between_stops();
	  f=1;
	}
      else if(a==2)
	{
	  print_all_routes();
	  f=1;
	}
      else if(a==3)
	{
	  routes_through_stop();
	  f=1;
	}
      else if(a==4)
	{
	  stops_in_route();
	  f=1;
	}
      else if(a==5)
	{
	  f=1;
	}
      else if(a==6)
	{
	  f=1;
	}
      else if(a==7)
	{
	  f=1;
	}
      else if(a==8)
	{
	  complaint();
	  f=1;
	}
      else if(a==9)
	{
	  exit(0);
	}
      else
	{
	  printf("not a valid input. try again\n");
	}
    }
  printf("Thank you for using IIT Kharagpur Bus Service System\n");
}
