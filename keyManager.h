class keyManager
{
private:
    bool signal;
    unsigned char k[256];
    unsigned char kPrim[256] = "a^dM!g?Ol$izEBlI";
    char* cryptedKey;
public:
    keyManager(){
        signal = false;
    }

    void primesteSemnal(bool semnal){
        signal = semnal;
        std::cout<<"Nod KM: semanl = " << signal << "\n";
    }

    bool getSignal(){
        std::cout<<"Nod KM: semnal verificare "<< signal <<"\n";
        return signal;
    }

    void genereazaRandomCheia(){
        unsigned char key[256];
        RAND_bytes(key,16);
        AES_KEY encKey;
        AES_set_encrypt_key(kPrim ,128, &encKey);
        AES_encrypt(key,k,&encKey);
        cryptedKey = reinterpret_cast<char*>(k);
        std::cout<<"Nod KM: cheie generata = " << cryptedKey <<"\n";
    }

    char* getKey(){
        return cryptedKey;
    }
};
