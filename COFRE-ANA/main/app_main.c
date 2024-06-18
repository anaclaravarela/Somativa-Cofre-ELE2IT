//////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                       _              //
//               _    _       _      _        _     _   _   _    _   _   _        _   _  _   _          //
//           |  | |  |_| |\| |_| |\ |_|   |\ |_|   |_| |_| | |  |   |_| |_| |\/| |_| |  |_| | |   /|    //    
//         |_|  |_|  |\  | | | | |/ | |   |/ | |   |   |\  |_|  |_| |\  | | |  | | | |_ | | |_|   _|_   //
//                                                                                       /              //
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
*   Programa básico para controle da placa durante a Jornada da Programação 1
*   Permite o controle das entradas e saídas digitais, entradas analógicas, display LCD e teclado. 
*   Cada biblioteca pode ser consultada na respectiva pasta em componentes
*   Existem algumas imagens e outros documentos na pasta Recursos
*   O código principal pode ser escrito a partir da linha 86
*/

// Área de inclusão das bibliotecas
//-----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "ioplaca.h"   // Controles das Entradas e Saídas digitais e do teclado
#include "lcdvia595.h" // Controles do Display LCD
#include "hcf_adc.h"   // Controles do ADC
#include "MP_hcf.h"   // Controles do ADC

char tecla;
char mostrador [40];
uint32_t valor;
char mostra[40];
uint32_t ler_adc;
int senha; 
int resultado=0;
int num1=0;
int controle = 0;
int tentativa = 0;
char seguranca;
int i;


bool digitou4numeros = false;


// Área das macros
//-----------------------------------------------------------------------------------------------------------------------



// Área de declaração de variáveis e protótipos de funções
//-----------------------------------------------------------------------------------------------------------------------

static const char *TAG = "Placa";
static uint8_t entradas, saidas = 0; //variáveis de controle de entradas e saídas


// Funções e ramos auxiliares
//-----------------------------------------------------------------------------------------------------------------------
    void ler_entradas (void)// função ler entradas
    {
       entradas = io_le_escreve(saidas);    
       if( le_teclado()== '1'){
        sprintf( &mostrador[0] ," %x [%x %x %x %x %x %x %x %x] \n", entradas, 
                                                                                                (entradas>>7)&1, (entradas>>6)&1, (entradas>>5)&1,(entradas>>4)&1,
                                                                                                (entradas>>3)&1, (entradas>>2)&1, (entradas>>1)&1, entradas&1 );
      // lcd595_write(1,1 &mostrador[0]);
       }
    }                                                                                    


// Programa Principal
//-----------------------------------------------------------------------------------------------------------------------
    void control (void)
    {
        
         if(controle == 0) // Se o controle for igual a 0
              {
                 num1 = num1 * 10 + tecla - '0'; //numero 1 igual a numero 1 vezes 10 mais a tecla -48('0' char= 48)
              }

    }

    void abrir_cofre () 
{   lcd595_clear(); //limpa o que foi escrito no display

     lcd595_write (1, 1, " Abrindo Cofre  "); //escreve no display 
     for (int i = 0; i < 1800 ; i = valor) // se o valor for uma int=0, o valor do adc será de até 3500
     {
        hcf_adc_ler (&valor); //le o valor do adc
        rotacionar_DRV (1,10, saidas); // rotaciona o motor de passo de 10 em 10 graus até o valor do adc ser atingido, abrindo o cofre (sentido horário)
        seguranca ++;
        if (seguranca > 15)break;//se a segurança for maior do que 15, existe uma parada
     }
     seguranca = 0;
}

void fechar_cofre ()
{   lcd595_clear(); //limpa tudo que foi escrito anteriormente no display

     lcd595_write (1, 1, " Fechando Cofre "); //escreve no display
     hcf_adc_ler (&valor); // le o valor do adc
     for (int i = valor; i > 400 ; i = valor) //o valor davváriavel int não pode ficar menor do que 300(valor do adc)
     {
        hcf_adc_ler (&valor); //le o valor do adc
        rotacionar_DRV (0,10, saidas); //rotaciona o motor de passo aos poucos, de 10 em 10 graus fechando o cofre (sentido anti-horário)
        seguranca ++;
        if (seguranca > 15)break; //se a segurança for maior do que 15, existe uma parada
     }
     seguranca = 0;
}
void escrever_segundos()
{
    lcd595_write (1,2, "Fechando em 10 seg."); // escreve no display quantos segundos vai demorar para a tempa fechar (mudando a cada 1 segundo)
         vTaskDelay(1000/portTICK_PERIOD_MS); // delay de 1 segundo

    lcd595_write (1,2, "Fechando em 9 seg. "); // escreve no display quantos segundos vai demorar para a tempa fechar (mudando a cada 1 segundo)
         vTaskDelay(1000/portTICK_PERIOD_MS); // delay de 1 segundo

    lcd595_write (1,2, "Fechando em 8 seg. "); // escreve no display quantos segundos vai demorar para a tempa fechar (mudando a cada 1 segundo)
         vTaskDelay(1000/portTICK_PERIOD_MS); // delay de 1 segundo

    lcd595_write (1,2, "Fechando em 7 seg. "); // escreve no display quantos segundos vai demorar para a tempa fechar (mudando a cada 1 segundo)
         vTaskDelay(1000/portTICK_PERIOD_MS); // delay de 1 segundo

    lcd595_write (1,2, "Fechando em 6 seg. "); // escreve no display quantos segundos vai demorar para a tempa fechar (mudando a cada 1 segundo)
         vTaskDelay(1000/portTICK_PERIOD_MS); // delay de 1 segundo

    lcd595_write (1,2, "Fechando em 5 seg. "); // escreve no display quantos segundos vai demorar para a tempa fechar (mudando a cada 1 segundo)
         vTaskDelay(1000/portTICK_PERIOD_MS); // delay de 1 segundo

    lcd595_write (1,2, "Fechando em 4 seg. "); // escreve no display quantos segundos vai demorar para a tempa fechar (mudando a cada 1 segundo)
         vTaskDelay(1000/portTICK_PERIOD_MS); // delay de 1 segundo
    
    lcd595_write (1,2, "Fechando em 3 seg. "); // escreve no display quantos segundos vai demorar para a tempa fechar (mudando a cada 1 segundo)
         vTaskDelay(1000/portTICK_PERIOD_MS); // delay de 1 segundo

    lcd595_write (1,2, "Fechando em 2 seg. "); // escreve no display quantos segundos vai demorar para a tempa fechar (mudando a cada 1 segundo)
         vTaskDelay(1000/portTICK_PERIOD_MS); // delay de 1 segundo
    
    lcd595_write (1,2, "Fechando em 1 seg. "); // escreve no display quantos segundos vai demorar para a tempa fechar (mudando a cada 1 segundo)
         vTaskDelay(1000/portTICK_PERIOD_MS); // delay de 1 segundo

}


void app_main(void)
{
    /////////////////////////////////////////////////////////////////////////////////////   Programa principal


    // a seguir, apenas informações de console, aquelas notas verdes no início da execução
    ESP_LOGI(TAG, "Iniciando...");
    ESP_LOGI(TAG, "Versão do IDF: %s", esp_get_idf_version());

    /////////////////////////////////////////////////////////////////////////////////////   Inicializações de periféricos (manter assim)
    
    // inicializar os IOs e teclado da placa
    ioinit(); //inicia as entradas da placa  
    entradas = io_le_escreve(saidas); // Limpa as saídas e lê o estado das entradas

    // inicializar o display LCD 
    lcd595_init();
    lcd595_write(1,1,"    Cofre  ");
    lcd595_write(2,1,"  Ana Clara ");
    
    // Inicializar o componente de leitura de entrada analógica
    esp_err_t init_result = hcf_adc_iniciar();
    if (init_result != ESP_OK) {
        ESP_LOGE("MAIN", "Erro ao inicializar o componente ADC personalizado");
    }

    //delay inicial
    vTaskDelay(1000 / portTICK_PERIOD_MS); // delay de 10 segundos 
    lcd595_clear(); //limpa o display
    //DRV_init(); /* Fc= Entrada  onde está instalado o fim de curso;  I= Inicial(tampa fechada) F= Final (tampa fechada)*/


  

    /////////////////////////////////////////////////////////////////////////////////////   Periféricos inicializados

 

    /////////////////////////////////////////////////////////////////////////////////////   Início do ramo principal                    
    while (1)                                                                                                                         
    {                                                                                                                                 
        //_______________________________________________________________________________________________________________________________________________________ //
        //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - -  -  -  -  -  -  -  -  -  -  Escreva seu código aqui!!! //
        hcf_adc_ler(&ler_adc); //le o adc
        tecla = le_teclado(); //le o teclado da placa
        
          if (tecla >='0' && tecla <= '9')// se a tecla for maior ou igual a 0 e se a tecla for menor ou igual a 9 faz a função
            {
            controle = controle + 1;// Se o controle for igual a 0
                
               num1 = num1 * 10 + tecla - '0'; //numero 1 igual a numero 1 vezes 10 mais a tecla -48('0' char= 48)
                
            }
            lcd595_clear(); //limpa o display lcd
            
         
        lcd595_write (1,1, "Escreva a senha"); //escreve no display
        lcd595_write(2,1,"[ ] [ ] [ ] [ ]"); //local para escrever a senha
        vTaskDelay (100/portTICK_PERIOD_MS); // delay de 100 milisegundos 

         
       if (controle==1) // se uma primeira tecla for pressionada ele faz a função de colocar um asterisco
       {
        lcd595_write(2,1,"[X] [ ] [ ] [ ]"); // escreve no display
        vTaskDelay (100/portTICK_PERIOD_MS); // delay de 100 milisegundos
       }

        if (controle==2) // se uma segunda tecla for pressionada faz a função de colocar dois asteriscos 
       {
        lcd595_write(2,1,"[X] [X] [ ] [ ]"); // escreve no display
        vTaskDelay (100/portTICK_PERIOD_MS); // delay de 100 milisegundos
       }
       
        if (controle==3) //se uma terceira tecla for pressionada faz a função de colocar três asteriscos
       {
        lcd595_write(2,1,"[X] [X] [X] [ ]"); // escreve no display
        vTaskDelay (100/portTICK_PERIOD_MS); // delay de 100 milisegundos
       }

       if (controle==4)  // se uma quarta tecla (idependente do valor) for pressionada faz a função de colocar quatro asteriscos 
       {
        lcd595_write(2,1,"[X] [X] [X] [X]"); // escreve no display
        vTaskDelay (100/portTICK_PERIOD_MS); // delay de 100 milisegundos
       }


        if(controle == 4) //só faz as funções se 4 números forem digitados
        {
            if ( num1 == 1234 ) // se o número escrito for 1234 a função será feita
            {
            
                    lcd595_write(1,1, " Senha Correta ");// escreve no display lcd
                    vTaskDelay (1000/portTICK_PERIOD_MS);// delay de 10 segundos

                    abrir_cofre(); //faz a função void de abrir o cofre 
                    vTaskDelay (1000/portTICK_PERIOD_MS); //delay de 10 segundos 

                    escrever_segundos();  //executa a função de escrever os segundos em ordem decrescente                 
                   

                    fechar_cofre(); // função de fechar o cofre 
                    vTaskDelay (500/portTICK_PERIOD_MS);// tempo de delay (500 milisegundos)

                
              
                lcd595_clear();//limpa o dislay lcd
                num1 = 0;// limpa a váriavel num1
                resultado = 0; // limpa a variável resultado
                controle = 0;// limpa a variável controle
                tentativa = 0;//limpa  a variável tentativa (evitando o bloqueio do sistema)


            
            }
            else if (num1!=  1234 ) //se o número digitado for diferente de 1234 afunção será feita
            { 
                    lcd595_write(1,1, "Senha Incorreta"); //escreve no display 
                    vTaskDelay(1000/portTICK_PERIOD_MS); //tempo de delay

                lcd595_clear();//limpa o display
                num1 = 0; //limpa a variável
                resultado = 0; //limpa a variável
                controle = 0; //limpa a variável
                tentativa= tentativa + 1; //conta o número de tentativas

            }
            if (tentativa==1) //se houver a primeira tentativa, a função se inicia 
            {
                lcd595_write(1,1, "Restam 4 tent."); //escreve na primeira linha do display
                lcd595_write(2,1, "Tente Novamente"); //escreve na segunda linha do displauy
                vTaskDelay(5000/portTICK_PERIOD_MS); // delay de 5 segundos 
            }

            if (tentativa==2) // se houver uma segunda tentativa falha, a função é executada
            {
                lcd595_write(1,1, "Restam 3 tent.");//escreve na primeira linha do display
                lcd595_write(2,1, "Tente Novamente");// escreve na segunda linha do display
                vTaskDelay(5000/portTICK_PERIOD_MS); //delay de 5000 milisegundos
            }

            if (tentativa==3) //se existir a 3ª tentativa a função será executada
            {
                lcd595_write(1,1, "Restam 2 tent.");//escreve na primeira linha do display
                lcd595_write(2,1, "Tente Novamente");// escreve na segunda linha do display
                vTaskDelay(5000/portTICK_PERIOD_MS);//delay de 5000 milisegundos
            }

            if (tentativa==4)// se a quarta tentativa for escrita, a função será executada
            {
                lcd595_write(1,1, "Resta 1 tent.");// escreve na primeira linha do display lcd
                lcd595_write(2,1, "Tente Novamente");// escreve na segunda linha do display lcd
                vTaskDelay(5000/portTICK_PERIOD_MS);//delay de 5000 milisegundos
            }
            if (tentativa==5)// se houver a quinta tentativa o acesso será negado e o usuário deverá esperar 30 segundos
            {
                lcd595_write(1,1, " ACESSO NEGADO "); //escreve no display
            for(int i=30; i>0; i--) // o valor é igual a 30 e deverá chegar no 0, de forma decrescente
            {
                sprintf (&mostra[0], "Liberando em %d seg.", i);//"escreve" em quantos segundos será liberado (mudando a cada 1 segundo)
                
                lcd595_write(2,1, &mostra[0]);//escreve no display o que a função sprintf escreveu
                vTaskDelay(1000/portTICK_PERIOD_MS); //delay de 1 segundo, fazendo o número mudar de acordo com o tempo escrito

            }
            }


        }

        
        
        //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - -  -  -  -  -  -  -  -  -  -  Escreva seu só até aqui!!! //
        //________________________________________________________________________________________________________________________________________________________//
        vTaskDelay(10 / portTICK_PERIOD_MS);    // delay mínimo obrigatório, se retirar, pode causar reset do ESP
    }
    
    // caso erro no programa, desliga o módulo ADC
    hcf_adc_limpar(); // limpa o adc 

    /////////////////////////////////////////////////////////////////////////////////////   Fim do ramo principal
}
