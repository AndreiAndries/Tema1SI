#include<iostream>

class nodeB{
    private:
    unsigned char* cryptedKey;
    unsigned char kPrim[256] = "a^dM!g?Ol$izEBlI";
    char modDeOperare[256];
    bool confirmareComunicare;
    char text[1000];
    
    

    
    public:

    nodeB(){
        confirmareComunicare = false;
    }

    bool getConfirmareComunicare(){
        std::cout<<"Nod B: "<<confirmareComunicare << "\n";
        return confirmareComunicare;
    }

    void setModDeOperare(char mod[10]){
        strcpy(modDeOperare,mod);
    }
    
    //--- primeste modul de operare de la A
    void primesteModDeOperare(nodeA nodA){
        setModDeOperare(nodA.getModDeOperare());
        std::cout<<"Nod B: "<<modDeOperare<<"\n";
    }

    //--- primeste cheia criptata K de la A
    void primesteCheiaCriptata(nodeA nodA){
        cryptedKey=nodA.getCryptedKey();
        std::cout<<"Nod B: cheie primita ="<< cryptedKey <<"\n";
    }
    
    void incepeTrimitereaFisierului(){
        confirmareComunicare = true;
        if(confirmareComunicare){
            std::cout<<"Nod B: incepe trimiterea fisierului\n";
        }
    }

    void primesteText(nodeA nodA){
        strcpy(text,nodA.getText());
        std::cout<<"Nod B: text criptat = "<<text<<"\n";
    }

    char* decECB(char textCriptat1[]){
        char text1[256];
        unsigned char txt[256];
        unsigned char encOut[256];
        encOut[0] = '\0';
        for(int i = 0 ; i <= (strlen(textCriptat1)-1)/16 ; ++i){
            txt[0] = '\0';
            for(int j = 0 ; j < 16 ; ++j){
                if(16*i+j<strlen(textCriptat1)){
                    txt[j] = textCriptat1[16*i+j];
                }else{
                    txt[j]=' ';
                }
            }
            AES_KEY encKey;
            AES_set_decrypt_key(cryptedKey,128,&encKey);
            AES_decrypt(txt,encOut,&encKey);
            strcat(text1,reinterpret_cast<char*>(encOut));
            encOut[0]='\0';
        }
        char* p = text1;
        return p;
    }

    void xorCalc (int lung,unsigned char *a, unsigned char *b, unsigned char *c){
        for (int i=0;i<lung;++i){
            c[i]=a[i]^b[i];
        }
    }

    char *decOFB(char cipher[], unsigned char vector[]){
    unsigned char *bloc=new unsigned char[256];
    unsigned char blocCurent[256];
    unsigned char cipher1[256];
    char textfinal[256];
    textfinal[0]='\0';
    int val=16;
    AES_KEY dec_key;
    AES_set_encrypt_key(cryptedKey,128,&dec_key);
    AES_encrypt(vector, bloc,&dec_key);
    for (int i=0;i<=(strlen (cipher)-1)/16;++i){
        unsigned char text1[256];
        val=16;
        text1[0]='\0';
        cipher1[0]='\0';
        for (int j=0;j<16;++j){
            if (16*i+j<strlen(cipher))
                cipher1[j]=cipher[16*i+j];
            else{
                val=j;
                break;
            }
        }
        int min;
        if ( strlen((char*)(bloc))>val)
            min=val;
        else
            min=strlen((char*)(bloc));
        xorCalc(min,bloc,cipher1,text1);
        strcat(textfinal,reinterpret_cast<char *>(text1));
        if (i!=(strlen (cipher)-1)/16 ){
            AES_KEY dec_key1;
            AES_set_encrypt_key(cryptedKey,128,&dec_key);
            for (int i=0;i<=strlen ((char*)(bloc));++i)
                blocCurent[i]=bloc[i];
            bloc[0]='\0';
            delete bloc;
            bloc =new unsigned char[256];
            AES_encrypt(blocCurent, bloc,&dec_key);
        }else{
            delete bloc;
            bloc =new unsigned char[256];}
        }
        char *point=textfinal;
        return point;
    }

    void decripteaza(unsigned char vectorDeInitializare[]){
        std::cout<<"Nod B: Incepe Decriptatrea \n\n\n";
        char* s;
        if(!strcmp(modDeOperare,"OFB"))
            strcpy(s,decOFB(text,vectorDeInitializare));
        else
            s=decECB(text);
        std::cout<<s;
    }
};