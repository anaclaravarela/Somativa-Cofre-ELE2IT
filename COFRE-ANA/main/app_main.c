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
char valor;
char mostra[40];
uint32_t ler_adc;
int senha; 
int resultado=0;
int num1=0;
int controle = 0;

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
void app_main(void)
{
    /////////////////////////////////////////////////////////////////////////////////////   Programa principal


    // a seguir, apenas informações de console, aquelas notas verdes no início da execução
    ESP_LOGI(TAG, "Iniciando...");
    ESP_LOGI(TAG, "Versão do IDF: %s", esp_get_idf_version());

    /////////////////////////////////////////////////////////////////////////////////////   Inicializações de periféricos (manter assim)
    
    // inicializar os IOs e teclado da placa
    ioinit();      
    entradas = io_le_escreve(saidas); // Limpa as saídas e lê o estado das entradas

    // inicializar o display LCD 
    lcd595_init();
    lcd595_write(1,1,"    Jornada 1   ");
    lcd595_write(2,1," Programa Basico");
    
    // Inicializar o componente de leitura de entrada analógica
    esp_err_t init_result = hcf_adc_iniciar();
    if (init_result != ESP_OK) {
        ESP_LOGE("MAIN", "Erro ao inicializar o componente ADC personalizado");
    }

    //delay inicial
    vTaskDelay(1000 / portTICK_PERIOD_MS); 
    lcd595_clear();
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
           // lcd595_write(1,3, "ROTACIONAR"); //escreve no display a palavara rotacionar e o vslor do adc
          //  sprintf( &mostra[0], "%"PRIu32"   ", ler_adc);// le o valor do adc 
           // lcd595_write(2,5,&mostra[0]); // mostra o valor do adc no display
       // vTaskDelay(300/portTICK_PERIOD_MS); //delay de 300 milisegundos
         
        lcd595_write (1,1, "Escreva a senha"); //escreve no display
        lcd595_write(2,1,"[ ] [ ] [ ] [ ]");
        vTaskDelay (10/portTICK_PERIOD_MS);

         
       if (controle==1) 
       {
        lcd595_write(2,1,"[*] [ ] [ ] [ ]"); // escreve no display
        vTaskDelay (10/portTICK_PERIOD_MS); // delay de 150 milisegundos
       }

        if (controle==2) 
       {
        lcd595_write(2,1,"[*] [*] [ ] [ ]"); // escreve no display
        vTaskDelay (10/portTICK_PERIOD_MS); // delay de 150 milisegundos
       }
       
        if (controle==3) 
       {
        lcd595_write(2,1,"[*] [*] [*] [ ]"); // escreve no display
        vTaskDelay (10/portTICK_PERIOD_MS); // delay de 150 milisegundos
       }

       if (controle==4) 
       {
        lcd595_write(2,1,"[*] [*] [*] [*]"); // escreve no display
        vTaskDelay (10/portTICK_PERIOD_MS); // delay de 150 milisegundos
       }


        if(controle == 4) //só faz as funções se 4 números forem digitados
        {
            if ( num1 == 1234 ) // se o número escrito for 1234 a função será feita
            {
            
                    lcd595_write(1,1, " Senha Correta ");
                    vTaskDelay (1000/portTICK_PERIOD_MS);

                    lcd595_write(1,1, " Cofre Abrindo ");

                    rotacionar_DRV(1, 100, saidas);     //SENTIDO- 1(abrir tampa); 0(fecha tampa)   ÂNGULO- Valor      SAÍDAS-Variável saídas 
                    vTaskDelay (1000/portTICK_PERIOD_MS);
                    
                    lcd595_write(1,1, " Cofre Fechando ");

                    rotacionar_DRV (0, 90, saidas); // sentido anti-horário (fecha tampa) 
                    vTaskDelay (2000/portTICK_PERIOD_MS);
              
                lcd595_clear();
                num1 = 0;
                resultado = 0;
                controle = 0;


            
            }
            else if (num1!=  1234 ) //se o número digitado for diferente de 1234 afunção será feita
            { 
                    lcd595_write(1,1, "Senha Incorreta");
                    vTaskDelay(1000/portTICK_PERIOD_MS);
                lcd595_clear();
                num1 = 0;
                resultado = 0;
                controle = 0;
            }
            

        }
        
        //-  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  -  - -  -  -  -  -  -  -  -  -  -  Escreva seu só até aqui!!! //
        //________________________________________________________________________________________________________________________________________________________//
        vTaskDelay(10 / portTICK_PERIOD_MS);    // delay mínimo obrigatório, se retirar, pode causar reset do ESP
    }
    
    // caso erro no programa, desliga o módulo ADC
    hcf_adc_limpar();

    /////////////////////////////////////////////////////////////////////////////////////   Fim do ramo principal
    
}