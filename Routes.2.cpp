#include<iostream>
#include<string>
#include<iomanip>
#include<cstdlib>
#include<fstream>
#include<vector>
#include<cstring>
using namespace std;
class Leg
{
  const char* const startCity;
  const char* const endCity;
  const double distance;

public:
  Leg(const char* const, const char* const, const double);
  Leg& operator=(const Leg&);
  double getDistance() const;
  void output(ostream&) const;
  friend class Route;
};

class Route
{
private:
  vector<const Leg*> legs;
  const double totalDis;
public:
  Route(const Leg&);
  Route(const Route&,const Leg&);
  Route& operator=(const Route&);
  double getDistance() const;
  void output(ostream&) const;
};

ostream& roundingOne(ostream&);
ostream& roundingOff(ostream&);

int main()
{
  cout << "Programmer: Younghyun Kwon\n";
  cout << "Programmer's ID: 1651849\n";

  Leg l[] = {
    Leg("Davis", "Sacramento", 14.2),
    Leg("Sacramento", "San Rafael", 6.2),
    Leg("San Rafael", "Cupertino", 7.5),
    Leg("Cupertino", "Hayward", 7.8),
    Leg("Union City", "Milpitas", 8.4),
    Leg("Hayward", "Pleasanton", 6.7),
    Leg("Hayward", "Union City", 6.9),
    Leg("Pleasanton", "Union City", 8.5),
    Leg("Union City", "Sunnyvale", 9.3),
    Leg("Sunnyvale", "Gilroy", 9.8),
    Leg("Pleasanton", "Livermore", 10.2),
    Leg("Martinez", "Pleasant Hill", 4.9),
    Leg("Pleasant Hill", "Pacheco", 3.9),
    Leg("Walnut Creek", "Fremont", 30.8),
    Leg("Daly City", "San Mateo", 14.5),
    Leg("Cupertino", "Richmond", 14.9),
    Leg("Vacaville", "Davis", 13.1),
    Leg("Fremont", "Milpitas", 13.6),
    Leg("San Jose", "Santa Cruz", 30.5),
    Leg("Fremont", "San Ramon", 19.1),
    Leg("Livermore", "Tracy", 19.2),
    Leg("Tracy", "Stockton", 20.2),
    Leg("Benicia", "Vallejo", 10.2),
    Leg("Martinez", "Benicia", 11.5),
    Leg("Morgan Hill", "San Jose", 11.6),
    Leg("San Francisco", "Daly City", 12.6),
    Leg("Emeryville", "Berkeley", 16.9),
    Leg("Concord", "Walnut Creek", 2.1),
    Leg("Marin", "San Rafael", 2.9),
    Leg("Pleasnat Hill", "Concord", 3.1),
    Leg("Richmomd", "Berkeley", 4.5),
    Leg("San Rafael", "San Francisco", 20.8),
    Leg("Fairfield", "Davis", 24.8),
    Leg("Vallejo", "Fairfield", 25),
    Leg("Vallejo", "Napa", 26),
    Leg("Oakland", "Richmond", 15.2),
    Leg("Vallejo", "Novato", 16.3),
    Leg("Sunnyvale", "Cupertino", 16.4),
    Leg("Alameda", "Oakland", 4.3),
    Leg("El Cerrito", "Richmond", 5.2),
    Leg("Fairfield", "Vacaville", 14.9)
  };

  Route r[] = {
    Route(l[0]),
    Route(r[0], l[1]),
    Route(r[1], l[2]),
    Route(r[2], l[3]),
    Route(r[3], l[4]),
    Route(r[4], l[5]),
    Route(r[5], l[6]),
    Route(r[6], l[7]),
    Route(r[7], l[8]),
    Route(r[8], l[9]),
    Route(r[9], l[10]),
    Route(r[10], l[11]),
    Route(r[11], l[12]),
    Route(r[12], l[13]),
    Route(r[13], l[14]),
    Route(r[14], l[15]),
    Route(r[15], l[16]),
    Route(r[16], l[17]),
    Route(r[17], l[18]),
    Route(r[18], l[19]),
    Route(r[19], l[20])
  };

  const int routeSIZE = sizeof(r) / sizeof(r[0]);

  for(int i = 0; i < routeSIZE; i++)
  {
    for(int j = 0; j < routeSIZE-1; j++)
    {
      if(r[j].getDistance() < r[j+1].getDistance())
      {
        Route temp = r[j];
        r[j] = r[j+1];
        r[j+1] = temp;
      }
    }
  }
  cout << "*****There are total " << routeSIZE << " routes*****\n";
  for(int i = 0; i < routeSIZE; i++)
  {
    r[i].output(cout);
  }
}

Leg::Leg(const char* const startCity, const char* const endCity, const double distance)
: startCity(startCity), endCity(endCity), distance(distance)
{
}

Leg& Leg::operator=(const Leg& leg)
{
  Leg& host = *this;
  if(this != &leg)
  {
    const_cast<const char*&>(host.startCity) = leg.startCity;
    const_cast<const char*&>(host.endCity) = leg.endCity;
    const_cast<double&>(host.distance) = leg.distance;
  }
  return *this;
}

double Leg::getDistance() const
{
  return distance;
}

void Leg::output(ostream& out) const
{
  roundingOne(out);
  out << "Leg: " << startCity << " to " << endCity << ", " << distance << " miles\n";
  roundingOff(out);
}

Route::Route(const Leg& leg)
:totalDis(leg.distance)
{
  legs.push_back(&leg);
}

Route::Route(const Route& route,const Leg& leg)
:legs(route.legs), totalDis((strcmp(route.legs.back()->endCity,leg.startCity) == 0)? route.totalDis + leg.distance: route.totalDis)
{
  try
  {
    if(strcmp(route.legs.back()->endCity,leg.startCity) != 0)
    {
      throw "Cities don't match!";
    }
    legs.push_back(&leg);
  }
  catch(const char* ex)
  {
    cout << ex << endl;
  }
}

Route& Route::operator=(const Route& route)
{
  Route& host = *this;
  if(this != &route)
  {
    host.legs = route.legs;
    const_cast<double&>(host.totalDis) = route.totalDis;
  }
  return *this;
}

double Route::getDistance() const
{
  return totalDis;
}

void Route::output(ostream& out) const
{
  roundingOne(out);
  out << "Leg: " << legs[0]->startCity;
   for(int i = 0; i < legs.size(); i++)
   {
     out << " to "<< legs[i]->endCity;
   }
   out << ", " << totalDis << " miles.\n";
   roundingOff(out);
}

ostream& roundingOne(ostream& out)
  {
    out.setf(ios::fixed);
    out.precision(1);
    return out;
  }

ostream& roundingOff(ostream& out)
  {
    out.unsetf(ios::fixed);
    out.precision(6);
    return out;
  }
