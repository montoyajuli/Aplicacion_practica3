#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>//para el pause y cdls

using namespace std;

ifstream archivo;ifstream archivo1;ofstream codificado;ofstream decodificado;

string toBinary(int num, bool esNum){

    string bin, binario="0";
    if (esNum==true){
        binario="00";
    }

    while(num>0){
        if(num%2==0){
            bin=bin+"0";
        }else{
            bin=bin+"1";
        }
        num=num/2;
    }

    if (esNum==true){
        for(int i=5;i>=0;i--){
           binario+=bin[i];
        }
    }else{
        for(int i=6;i>=0;i--){
           binario+=bin[i];
        }
    }

    return binario;
}

string toString(string binario){

    int len=binario.size();
    string num, cadena;
    int aux[]={1,2,4,8,16,32,64,128,256};
    int i=0;
    int digito;
    int res, cont=0;
    char letra;

    while(i<len){

        for(int j=0;j<=7;j++){
            num[j]=binario[i];
            i++;
        }
        for(int j=7;j>=0;j--){
            digito=num[j];
            if(digito=='1'){
                res=res+aux[cont];
            }
            cont++;
        }
        letra=res-8;
        cont=0,res=0;;
        cadena+=letra;

    }
    return cadena;
}

string AuxTostring(string cosa){
    string otra,cadena="";

    for(int i=0;i<cosa.length();i++){
        otra+=cosa[i];
        if ((i+1)%8==0){
             cadena+=toString(otra);
             otra="";
        }
    }
    return cadena;
}

string decodificacion2(string binario, int semilla){

    string copia=binario;
    int len=binario.size();
    int seed=semilla;
    int a=0;

    while(semilla<=len){

        for(int i=a;i<semilla;i++){
            if(i==semilla-1){
                binario[semilla-1]=copia[a];
            }else{
                binario[i]=copia[i+1];
            }
        }

        a=semilla;
        semilla=seed+semilla;

    }
    return binario;
}


string metodo2(string binario,int semilla){

    string copia=binario;
    int len=binario.size();
    int seed=semilla;
    int a=0;

    while(semilla<=len){

        for(int i=a;i<semilla;i++){
            if(i==a){
                binario[i]=copia[semilla-1];
            }else{
                binario[i]=copia[i-1];
            }
        }

        a=semilla;
        semilla=seed+semilla;

    }
    return binario;
}

string AuxCodificar(string caracteres){
    string binario="";
    bool esNum=false;

    for(int i=0;i<caracteres.length();i++){
        int acii=caracteres[i];
        if (48<=acii and acii<=57){
            esNum=true;
        }
        else {
            esNum=false;
        }
        binario+=toBinary(acii,esNum);
    }
    string YaCodificado=metodo2(binario,4);
    return YaCodificado;
}

bool login(void){

    //usuario administrador :juliana
    //Clave: juli

    bool loginU=false, loginC=false;
    string usuario, clave;
    string text,text1;
    while(!archivo.eof()){//si no esto en el end of file

        cout<<"------------INICIO DE SESION DE ADMINISTRADOR------------ "<<endl<<endl;

        while (loginU==false or loginC==false){//mejor un while
            cout<<"Ingrese el nombre de usuario: ";cin>>usuario;
            cout<<endl<<"Ingrese su clave: ";cin>>clave;

            //usuario verifico
            string binario="";bool esNum=false;
            for(int i=0;i<usuario.length();i++){
                int acii=usuario[i];
                if (48<=acii and acii<=57){
                    esNum=true;
                }
                else {
                    esNum=false;
                }
                binario+=toBinary(acii,esNum);
            }
            string UsuCod=metodo2(binario,4);

            getline(archivo,text);

            if (text==UsuCod ){
                loginU=true;
                text+='\n';
            }
             //clave verifico
            binario="";
            for(int i=0;i<clave.length();i++){
                int acii=clave[i];
                if (48<=acii and acii<=57){
                    esNum=true;
                }
                else {
                    esNum=false;
                }
                binario+=toBinary(acii,esNum);
            }
            UsuCod=metodo2(binario,4);

            getline(archivo,text1);
            if (text1==UsuCod ){
                loginC=true;
                text1+='\n';
            }
            else{
                cout<<endl<<"Intentelo de nuevo "<<endl;
                system("pause");
                system("cls");
            }
        }
   }
   cout<<endl<<"Ingreso exitoso"<<endl<<endl;
   bool si=true;
   archivo.close();

    return si;
}

int menu(){
    int x;
    system("cls");//la limpia,
    cout<<endl<<"------------ Bienvenido, elija la opcion -------------"<<endl;
    cout<<"1. Iniciar sesion como administrador para gregar personas. "<<endl;
    cout<<"2. Consultar saldo. "<<endl;
    cout<<"3. Retirar dinero. "<<endl;
    cout<<"4. Salir. "<<endl;
    cin>>x;
    return x;

}

void agregar(ofstream &es){
    system("cls");
    string cedula="";string clave="";string saldo="";
    es.open("Usuarios.txt", ios::out | ios::app);

    if (!es.is_open()){//!=si no esta abierto
        cout<< "No fue posible abrir el archivo"<<endl;
        exit(1);//Salga entonces del programa
    }

    cout<<"------------REGISTRO DE USUARIOS------------ "<<endl<<endl;
    cout<<"Ingrese la cedula: ";cin>>cedula;
    cout<<endl<<"Ingrese la clave: ";cin>>clave;
    cout<<endl<<"Ingrese el saldo: ";cin>>saldo;

    cedula=AuxCodificar(cedula);
    clave=AuxCodificar(clave);
    saldo=AuxCodificar(saldo);

    es<<cedula<<" "<<clave<<" "<<saldo<<"\n";
    es.close();

//ced 1616
    //clave 555
    //2800
}

void ConsultarSaldo(ifstream &Lec){ //recibir por referencia
    system("cls");
    Lec.open("Usuarios.txt", ios::in);
    string cedula="",cedAux="";string clave="";string saldo="";string claveAux="";
    bool encontrado=false;

    cout<<"Digite su cedula: ";cin>>cedAux;
    cout<<"Digite su clave: ";cin>>claveAux;

    while (!Lec.eof() && !encontrado) {
        Lec>>cedula;

        if (AuxTostring(decodificacion2(cedula,4)) == cedAux ){
            Lec>>clave;
            if (AuxTostring(decodificacion2(clave,4))==claveAux){
                cout<<"Usuario encontrado "<<endl<<endl;
                Lec>>saldo;
                cout<<"Su saldo es: "<<AuxTostring(decodificacion2(saldo,4))<<endl<<endl;
                encontrado=true;
            }
        }
    }
    Lec.close();
    if (encontrado==false){
        cout<<"Usuario no encontrado"<<endl;

    }
    system("pause");
}

int ConvertirCadenaAInt(string numstring){
    int numInt = 0;
    numInt = stoi(numstring);
    return numInt;
}

string deInt_aStr(int n){
    string str = to_string(n);
    return str;
}

void RetirarDinero(ifstream &Lec){

    ConsultarSaldo(Lec);
    system("cls");

    string cedula="",clave="",saldo="",cedAux="",saldoAux="";
    int cont=0;

    Lec.open("Usuarios.txt", ios::in);
    ifstream Lin("Usuarios.txt", ios::in);

    int NumLines=0;//me cuenta las NumLineseas para que no copie doble
    while(Lin.good()) if(Lin.get()=='\n'){
        NumLines++;
    }
    Lin.close();

    ofstream aux("auxiliar.txt", ios::out);


    if (Lec.is_open()){
        cout<<"Ingrese la cedula nuevamente: ";
        cin>>cedAux;

        while(!Lec.eof()and cont<NumLines){
            Lec>>cedula;
            Lec>>clave;
            if (AuxTostring(decodificacion2(cedula,4)) ==cedAux){
                cout<<"Digite cuanto quiere retirar: ";
                cin>>saldoAux;
                Lec>>saldo;

                //resto la cantidad retirada


                int saldoInt =  ConvertirCadenaAInt(AuxTostring(decodificacion2(saldo,4)));
                int saldoAuxInt =  ConvertirCadenaAInt(saldoAux);
                cout<<"Saldo aux "<<saldoAuxInt<<endl;
                int copiasaldo =  saldoInt;

                while((saldoAuxInt)>saldoInt-1000){
                    //ciclo por si mete mas de la cantidad que hay
                    cout<<"Intentelo de nuevo, cantida invalidad para su saldo";
                    aux<<cedula<<" "<<clave<<" "<<AuxCodificar(deInt_aStr(copiasaldo))<<"\n";
                    cout<<endl<<"ERROR"<<endl;
                    system("pause");
                    exit(0);

                }
                saldoInt=saldoInt-saldoAuxInt-1000;
                saldoAux =deInt_aStr(saldoInt);
                cout<<saldoAux<<"saldoaux"<<endl;
                //cout<<AuxCodificar(saldoAux)<<"con metodod"<<endl;

                //encontrado=true;
                aux<<cedula<<" "<<clave<<" "<<AuxCodificar(saldoAux)<<"\n";
                cout<<endl<<" Dinero retirado con exito "<<endl;
                system("pause");
            }else{
                Lec>>saldo;
                aux<<cedula<<" "<<clave<<" "<<saldo<<"\n";//me lo saca mal con metodo
            }
            cont++;
        }
        Lec.close();
        aux.close();

    }else
        cout<<"Error"<<endl;
    remove("Usuarios.txt");
    rename("auxiliar.txt", "Usuarios.txt");


}



int main()
{
   cout<<"Aplicacion"<<endl;
   archivo.open("sudo.txt");//por defecto es entrada

   if (!archivo.is_open()){//!=si no esta abierto
       cout<< "No fue posible abrir el archivo"<<endl;
       exit(1);//Salga entonces del programa
   }

   ofstream Esc;
   ifstream Lec;
   int op=0; bool adminlogin=false;

   do{
       system("cls");
       op=menu();
       switch(op){
       case 1:
           adminlogin=login();
           agregar(Esc);
       break;
       case 2:
           ConsultarSaldo(Lec);
       break;

       case 3:
           RetirarDinero(Lec);
       break;

       }
   } while(op!=4);


   //recuerde usar seek y eso pa guardar



    return 0;
}
