#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "fonctions_jp1.hpp"
// fonction donnant 1 sur terre 
bool merterre3(std::vector<int>  const &res,double lat,double lon)
    {   int j= int((90-lat)*120);
        int i= int(fmod((lon+180),360)*120);
        int indice =j*10800*4+i;// indice dans vecteur
        int t= rangValeurInferieure(res, indice);
        return (t+1+res[0])%2;
    }

struct Pointsimple {  double y, x;};


int main(){
 auto start = std::chrono::high_resolution_clock::now();
 auto end   = std::chrono::high_resolution_clock::now();
 std::chrono::duration<double, std::milli> float_ms ;

 start = std::chrono::high_resolution_clock::now();
// on va charger la bande1234 et la tester
std::string filename1234="/home/jp/cartoglobe/globe.bin";
vector<int> globe   = readIntVectorFromFile(filename1234);
end   = std::chrono::high_resolution_clock::now();
float_ms = end - start;
std::cout << "Temps d'execution du chargement de globe " << float_ms.count() << " milliseconds " << std::endl;





std::cout<<"\n\n\nTest unitaire de valeurs\n"; 
bool res6;
//std::vector<bool>resultat; 
std::vector<bool>resultat6; 
std::vector<Pointsimple> pointstest6 = { {81,-120},{81,-40},{61,-42},{61,-44},{64.72,-225392},{66.113,12.8945} ,{50.01,179.99}   ,{64.734,-223131},{66.131,12.15},{64.6240,-15},
{65.3815 , 23.4407},{49.999,-126.89},{49.92,-124.9737},{47.441,-96.0384}, {81,-120},{81,-40},{61,-42},{61,-44},{64.72,-22.5392},{66.113,12.8945} ,{50.01,179.99}   ,{64.734,-22.3131},{66.131,12.15},{64.6240,-15},
{22.8351,61.9565},{49.999,-126.88},{22.8545,70.3220},{22.8495,70.3584},{22.966,70.4125},{28.5407,121.4432},{28.5525,121.6183},{0.1234,127.7929},{0.01,179.99},{-0.0499,-79.5497},{-0.01,-179.99},
{-1.535665,-80.490862},{0.161213,-80.5164},{-0.2683 , -50.1563},{-0.0925 , -49.3400},{-0.0785 , 9.3508},{ -1.3722 , 41.8917},{-0.8175 , 114.3740},{ -49.7610 , -75.8928},{-49.6761 , -67.9544},
{-49.99,179.99},{-45.7779 , 169.5378},{-50.01,-179.99},{-50.001 , -75.3115},{-49.9697 , -76.0891},{-49.9132 , -72.7822},{-49.7026 , -67.3063},{-49.6671 , -68.0314},{-51.5490 , -60.6152},
{-51.5507 , -60.2472},{-51.5377 , -59.2446},{-54.2871 , -36.8620}}; 

std::cout <<"Nombre de points testes : "<<pointstest6.size();


start = std::chrono::high_resolution_clock::now();
for (auto &p : pointstest6)
{res6=merterre3 (globe,p.y,p.x);
resultat6.push_back( res6) ;}
end  = std::chrono::high_resolution_clock::now();
float_ms = end - start;
std::cout << "\nTemps d'execution de la fonction pour 560 recherches " << 10*float_ms.count() << " milliseconds " << std::endl;


std::cout<<"\n";
for (auto const valeur : resultat6){   std::cout << valeur << " ";    }
std::cout<<"\n";
std::vector<bool> reference={0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
for (auto const valeur : reference){   std::cout << valeur << " ";    }






return 0;  
}