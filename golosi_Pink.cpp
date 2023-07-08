/*
* USUARIO DEL JUEZ: G04
* NOMBRE Y APELLIDOS: JAIME BENEDI GALDEANO
*/

#include <iostream>
#include <vector>

 // uncomment to read from a file instead of standard input
 //#include <fstream>

using namespace std;

/*OBSERVACIONES DEL EJERCICIO:
* 
* A pesar de la parafernalia del enunciado, consiste en
* encontrar la mayor distancia de un subsegmento en nut
* con mayor suma de sus elementos cuyos valores en cal
* sean iguales o menores a el umbral calorico
* 
* Recalco esto, porque dice que la solucion tienen que
* ser chuches que cumplan eso en posiciones consecutivas
*/
/*COSTE DEL ALGORITMO:
* Todas las instrucciones son de coste constante.
* 
* Realizamos instrucciones de coste constante de forma ciclica
* en ambos vectores cal y nut a la vez.
* 
* Nos vemos forzados a recorrer todas las distintas chuches,
* pero solo lo hacemos exactamente una vez.
* 
* Por lo tanto, el coste del algoritmo es:
* 
*   O(numChuches)
*/
/*P:
*   0 < cal.size() = nut.size() <= 10^5
* ^
*   PARA_TODO e : 0 <= cal < cal.size() : cal[e] <= maxCal
* 
* Definimos para mas adelante ayudar en la definicion de ciertos conceptos:
* 
*   enRangoCalorico(v, a, b, c) =
*       (SUMA i : a <= i < b : v[i]) <= c
*/
int max_chuchesPerCalorias(
    const vector<int>& cal, // valores caloricos
    const vector<int>& nut, // valores nutricionales
    int maxCal,             // umbral 
    int numChuches          // numero total de chuches de las que elegir
) {
    int maxValorNutricional = 0, // solucion
        sumNutricional = 0,      // suma del valor nutricional del segmento actual
        sumCalorias = 0;         // suma de calorias del segmento actual

    /*FUNCION DE COTA:
    * fc(x) = numChuches - idx
    */
    for (int idx = 0; idx < numChuches; ++idx) {
        // Si ya no podemos meter mas chuches
        if (cal[idx] + sumCalorias > maxCal) {
            sumCalorias = cal[idx];
            sumNutricional = nut[idx];;
        }// Si podemos seguir metiendo chuches
        else {
            sumCalorias += cal[idx];
            sumNutricional += nut[idx];
        }
        // Comprobamos si se ha rebasado el valor nutricional maximo
        if (sumNutricional > maxValorNutricional)
            maxValorNutricional = sumNutricional;
    }
    /*INVARIANTE:
    *   0 <= idx <= numChuches
    *  ^
    *   sumCalorias = SUMA e : 0 <= e < idx && enRangoCalorico(cal[], e, idx, maxCal) : cal[e]
    *  ^
    *   sumNutricional = SUMA x : 0 <= x < idx && enRangoCalorico(cal[], x, idx, maxCal) : nut[e]
    *  ^
    *   maxValorNutricional = MAX s : 0 < s <= (SUMA y : 0 <= y < idx : nut[y]) : 
    *       s = (SUMA z : 0 <= z < idx && enRangoCalorico(cal[], z, idx, maxCal) : nut[z])
    */

    return maxValorNutricional;
}
/*Q:
*   maxValorNutricional = MAX sum : 0 < sum <= (SUMA y : 0 <= y < numChuches : nut[y]) :
*       sum = SUMA r : (EXISTE head, tail : 0 <= head <= r <= tail < numChuChes && enRangoCalorico(cal[], head, tail, maxCal)) : nut[r]
*/

bool solve() {
    // read case
    int n;
    cin >> n;
    if (n == -1)
        return false;

    int maxCalorias;
    vector<int> cal(n), nut(n);

    for (int i = 0; i < n; ++i)
        cin >> cal[i];

    for (int i = 0; i < n; ++i)
        cin >> nut[i];

    cin >> maxCalorias;

    if (n == 0 || maxCalorias == 0)
        cout << 0 << endl;

    else {
        // compute solution
        int r = max_chuchesPerCalorias(cal, nut, maxCalorias, n);

        // write solution
        cout << r << endl;
    }

    return true;
}

int main() {
    // uncomment to read from a file instead of standard input
    // ifstream ifs("sample.in");
    // cin.rdbuf(ifs.rdbuf());

    while (solve());

    return 0;
}