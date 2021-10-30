#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <cryptopp/rijndael.h>
#include <cryptopp/osrng.h>
#include <cryptopp/aes.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/modes.h>
#include <cryptopp/hex.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <fstream>
#include <string>
#include "nodeA.h"
#include "nodeB.h"
#include "keyManager.h" 

using namespace std;
using namespace CryptoPP;



int main(){
    char modDeOperare[256];
    unsigned char vectorDeInitializare[256] = "32fmcott.;[erf4`";
    cout<<"Modul de operare: ";
    cin>>modDeOperare;
    cout<<modDeOperare << '\n';
    nodeA nodA;
    nodeB nodB;
    keyManager KM;
    nodA.setModDeOperare(modDeOperare); //-debugged-
    nodB.primesteModDeOperare(nodA); //-debugged-
    KM.primesteSemnal(nodA.trimiteSemnal()); //-debugged-
    if(KM.getSignal()==true){ //-debugged-
        KM.genereazaRandomCheia(); //-debugged-
        nodA.primesteCheia(reinterpret_cast<unsigned char *>(KM.getKey())); //-debugged-
        nodB.primesteCheiaCriptata(nodA); //-debugged-
        nodB.incepeTrimitereaFisierului(); //-debugged-
    }
    nodA.primesteMesajDeConfirmare(nodB.getConfirmareComunicare());//-debugged-
    char numeleFisierului[256] = "fisier.txt";
    nodA.cripteaza(numeleFisierului,vectorDeInitializare);//-debugged-
    nodB.primesteText(nodA);//-debugged-
    nodB.decripteaza(vectorDeInitializare);
}