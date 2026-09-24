#include <iostream>
#include <iomanip>

#include "Ponto2D.hpp"
#include "Robo.hpp"

using namespace std;

int main() {
  
    // Tamanho do time
    int num_robos;
    cin >> num_robos;

    // Criando um vetor de ponteiros para guardar o time
    Robo *time[num_robos]; 

    // Criando os robos do time com os dados de entrada
    double x, y;
    bool com_bola;
    for (int i = 0; i < num_robos; i++) {
        cin >> x >> y >> com_bola;
        time[i] = new Robo(i, Ponto2D(x, y), com_bola);
    }

    // Definindo o formato da saida
    cout << fixed << setprecision(2); 
    
    int idx;
    char data;
    while (cin >> data) {   // Lendo o caractere que define o comando

        // Executando o comando informado
        switch (data) {
            
            // Imprimindo o status de todos os robos do time
            case 's': {                
                for (int i = 0; i < num_robos; i++)
                    time[i]->imprimir_status();

                break;
            }
            // Imprimindo a distancia entre todos os robos do time
            case 'd': {
                for (int i = 0; i < num_robos; i++)
                    for (int j = 0; j < num_robos; j++)
                        cout << time[i]->calcular_distancia(time[j]) << endl;
                
                break;
            }
            // Mover robo
            case 'm': {                 
                cin >> idx; // Indice do robo que vai mover

                double v, th, t; // Velocidade, Ângulo, Tempo
                cin >> v >> th >> t;

                time[idx]->mover(v, th, t);
                
                break;                              
            }
            // Recuperando robo mais proximo
            case 'p': {                 
                cin >> idx; // Indice do robo que vamos usar de base

                Robo *robo = time[idx]->determinar_robo_mais_proximo(time, num_robos);

                robo->imprimir_status();

                break;   
            }
            // Passar bola
            case 'b': {
                cin >> idx; // Index do robo que fará o passe

                time[idx]->passar_bola(time, num_robos);
                
                break;   
            }
        }
    }
    
    // Desalocando os ponteiros do vetor
    for (int i = 0; i < num_robos; i++) {
        delete time[i];
    }

    return 0;
}