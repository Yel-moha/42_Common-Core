#include "classi.hpp"

void sample_print(void)
{

    std::cout<<"Io sono sample_print del costruttore Sample"<<std::endl;
}

Sample::Sample(int pappa)
{
    this->pappa = 0; // qui il riferimento alla variabile della classe.
    std::cout << "Io sono il costruttore" << std::endl;
    std::cout << "pappa della classe: "<< this->pappa << std::endl;
    std::cout << "pappa da fuori: "<< pappa << std::endl;
    sample_print();
}

Sample::~Sample()
{
    std::cout << "Io sono il distruttore" << std::endl;
}

