//TO-DO:

//Finish translations. Add for new lines.
// For search: ¡NL ¡IT ¡DE
// Probably unneeded: ¡FR ¡EN ¡ES ¡JA ¡KO
// Due to encoding problems, Japanese likely can't be added.
//Fix issues I guess.

//Suggested by jeptioak:
//Add immediate start feature (instead of countdown). Done.
//Fix laps. Done.
//Add GameCube controller support--a want more than a need. Done.
//Fix the compiler and make it work just fine with this UTF-8 file. Couldn't really
//  figure out this one, but I just added details to the README file that work.
//I was going to add else something here, but I've forgotten.


//ISSUES:

//The pause function is not working. Fixed with "break;" removed.
//Credits shown in every language. Solved with "break;" added.


//Issues with some special characters. Wii display uses CP437.
//So, an "ó" is C3 B3 is UTF-8 Hex bytes,
//but it's read as two CP437 graphical characters.
//Following are resource websites:
//https://www.ascii-codes.com/
//https://www.cogsci.ed.ac.uk/~richard/utf-8.cgi?input=%C3%B3&mode=char
//I made a solution whereby Python makes a backup copy in a folder
//(named based on date and hour, only first minute digit to avoid more files),
//then reads the original file in UTF-8 and writes it back in CP437.
//I just changed it to be less dangerous, so now it just copies the
//file that's called "template-to-edit-utf8.c" to "template.c".
//By the way, only 77 characters fit on one line. also be aware
//that CRTs crop more than modern TVs that are set up well.


#include <gccore.h>
#include "wpad.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wchar.h>
#include <locale.h>
#include <math.h>

char* versionProgram = "v2.0.0 Alpha Dev v1";
//I think a higher version number is warranted.

//{
	//setlocale(LC_CTYPE, "");
	//printf("%lc", E_AIGU);
//}

static void *xfb = NULL;
static GXRModeObj *rmode = NULL;

    


//printf("%d\n", language); //DEBUG. Prints the language variable.
//printf("118 start%d\n", Start); //DEBUG. Prints the starts variable.

void supprimeLigne(void){
    printf("                                                                         \r");
}

//int language =2;


inline void displayHorraire(int Lap,int LLapHour, int LLapMinute, int LLapSecond, int LLapMilli, int Hour, int Minute, int Second, int Milli) {
    if (Lap == 1){
	printf("								   %02d:%02d:%02d.%03d\r", Hour, Minute, Second, Milli);
    }
    else {
        printf("			+%02d:%02d:%02d.%03d			%02d:%02d:%02d.%03d\r", LLapHour, LLapMinute, LLapSecond, LLapMilli, Hour, Minute, Second, Milli);
    }
}
//---------------------------------------------------------------------------------
int main(int argc, char **argv)
//---------------------------------------------------------------------------------
{
	// Initialise the video system
	VIDEO_Init();

	// This function initialises the attached controllers
	WPAD_Init();
    PAD_Init();

	// Obtain the preferred video mode from the system
	// This will correspond to the settings in the Wii menu
	rmode = VIDEO_GetPreferredMode(NULL);

	// Allocate memory for the display in the uncached region
	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));

	// Initialise the console, required for printf
	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);

	// Set up the video registers with the chosen mode
	VIDEO_Configure(rmode);

	// Tell the video hardware where our display memory is
	VIDEO_SetNextFramebuffer(xfb);

	// Make the display visible
	VIDEO_SetBlack(FALSE);

	// Flush the video register changes to the hardware
	VIDEO_Flush();

	// Wait for Video setup to complete
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();

	// Detects the system language. Not used.
	//LANGUAGE_Init();
	//language = LANGUAGE_GetPreferredMode(NULL);
    
	// The console understands VT terminal escape codes
	// This positions the cursor on row 2, column 0
	// we can use variables for this with format codes too
	// e.g. printf ("\x1b[%d;%dH", row, column );
	printf("\x1b[2;0H");
    
    
    //Get the system language
    //int language ***= CONF_GetLanguage(); //*** is to be removed later as it's just to avoid Python taking this line.
    int language = CONF_GetLanguage();//DEBUG. PYTHON CHANGE THIS. Sets to system language.
    
    void afficheLogo(void){
        switch(language){
            case 1: //English
                printf("                                                                         \r");
                printf("				  _____ _                           _       _     \n");
                printf("				 /  ___| |                         | |     | |    \n");
                printf("				 \\ `--.| |_ ___  _ ____      ____ _| |_ ___| |__  \n");
                printf("				  `--. \\ __/ _ \\| '_ \\ \\ /\\ / / _` | __/ __| '_ \\ \n");
                printf("				 /\\__/ / || (_) | |_) \\ V  V / (_| | || (__| | | |\n");
                printf("				 \\____/ \\__\\___/| .__/ \\_/\\_/ \\__,_|\\__\\___|_| |_|\n");
                printf("				                | |                               \n");
                printf("				                |_|                               \n");
                printf(" \n");
                printf("Homebrew made by Ilovemyhouse.\n");
                printf("Version %s\n",versionProgram);
                break;
            case 2: //Germanx
                supprimeLigne();
                printf("				  _____ _                          _\n");
                printf("				 /  ___| |                        | |    \n");
                printf("				 \\ `--.| |_ ___  _ __  _ __  _   _| |__  _ _\n");
                printf("				  `--. \\ __/ _ \\| '_ \\| '_ \\| | | | '_ \\| '_|\n");
                printf("				 /\\__/ / || (_) | |_) | |_) | |_| | | | | |\n");
                printf("				 \\____/ \\__\\___/| .__/| .__/ \\__,_|_| |_|_|	\n");
                printf("				                | |   | |                          \n");
                printf("				                |_|   |_|\n");
                printf(" \n");
                printf("Homebrew von Ilovemyhouse.\n");
                printf("Version %s\n",versionProgram);
                break;
            case 3: //French
                printf("                                                                         \r");
                printf("		  ____ _                                    _\n");
                printf("		 /  __| |                             _    | |\n");
                printf("		|  /  | |                             \\ \\__| |_\n");
                printf("		| |   | |_                             \\_\\_   _\\\n");
                printf("		| |   |   \\|\\___  ___|\\___  ___|\\_  __  ___| ||\\___  ___\n");
                printf("		| |   | |\\ |  _ \\/ _ \\  _ \\/   \\  \\/  \\/ _ \\ ||  _ \\/ _ \\\n");
                printf("		|  \\__| || | | \\_\\(_)| | | |(_)| |\\/| |  __/ || | \\_\\ __/\n");
                printf("		 \\____|_||_|_|   \\___/_| |_|___/_|  |_|\\___\\___/|   \\___\\\n");     
                printf(" \n");
                printf("Homebrew fait par Ilovemyhouse.\n");
                printf("Version %s\n",versionProgram);
                break;
            case 4: //Spanish
                printf("                                                                         \r");
                printf("			  ____                                 _\n");
                printf("			 /  __|                    _          | |\n");
                printf("			|  /                     / /         _| |_\n");
                printf("			| |                    /_/          /_   _/\n");
                printf("			| |   |\\___  ___|\\___  ___|\\_  __  ___| ||\\___  ___\n");
                printf("			| |   |  _ \\/ _ \\  _ \\/ _ \\  \\/  \\/ _ \\ ||  _ \\/ _ \\\n");
                printf("			|  \\__| | \\_\\(_)| | | |(_)| |\\/| |  __/ || | \\_\\(_)|\n");
                printf("			 \\____|_|   \\___/_| |_|___/_|  |_|\\___\\___/|   \\___/\n");
                printf(" \n");
                printf("Autor: Ilovemyhouse.\n");
                printf("Versión: %s\n",versionProgram);
                break;
            case 5: //Italian
                printf("                                                                         \r");
                printf("			  ____                                 _\n");
                printf("			 /  __|                               | |\n");
                printf("			|  /                                 _| |_\n");
                printf("			| |                                 /_   _/\n");
                printf("			| |   |\\___  ___|\\___  ___|\\_  __  ___| ||\\___  ___\n");
                printf("			| |   |  _ \\/ _ \\  _ \\/ _ \\  \\/  \\/ _ \\ ||  _ \\/ _ \\\n");
                printf("			|  \\__| | \\_\\(_)| | | |(_)| |\\/| |  __/ || | \\_\\(_)|\n");
                printf("			 \\____|_|   \\___/_| |_|___/_|  |_|\\___\\___/|   \\___/\n");
                printf("\nHomebrew realizzato da Ilovemyhouse.\n");
                printf("Versione %s\n",versionProgram);
                break;
            case 6: //Dutch
                printf("                                                                         \r");
                printf("				  _____ _                           _       _     \n");
                printf("				 /  ___| |                         | |     | |    \n");
                printf("				 \\ `--.| |_ ___  _ ____      ____ _| |_ ___| |__  \n");
                printf("				  `--. \\ __/ _ \\| '_ \\ \\ /\\ / / _` | __/ __| '_ \\ \n");
                printf("				 /\\__/ / || (_) | |_) \\ V  V / (_| | || (__| | | |\n");
                printf("				 \\____/ \\__\\___/| .__/ \\_/\\_/ \\__,_|\\__\\___|_| |_|\n");
                printf("				                | |                               \n");
                printf("				                |_|                               \n");
                printf(" \n");
                printf("Homebrew gemaakt door Ilovemyhouse.\n");
                printf("Versie %s\n",versionProgram);
                break;
            default : //Translation missing
                printf("                                                                         \r");
                printf("			Stopwatch   Chronómetro\n");
                printf("			   __               _____          /\\   Olympic\n");
                printf("			  _||_╥       000  |___  \\ .573ms /  \\   athlete | \n");
                printf("			 /  |  \\  0  0   0     / /  ____ /_  _\\          | 400m\n");
                printf("			|   |   | 0  0 | 0  __/ /_ / __/   ││      =  O  | Lap\n");
                printf("			|-  ·  -|    0 | 0 /__ __/ \\__     ││     =  7   | 1/4 mi\n");
                printf("			|  /    | 0  0   0  / /    ___\\ \\  ││       /    |\n");
                printf("			 \\──┴──/  0   000  /_/     \\____/  └┘      M____________/ \n");
                printf(" \n");
                printf("By user Ilovemyhouse.\n");
                printf("Version %s\n",versionProgram); 
                break;
        }
    }

    void afficheControles(void){
        switch(language){
            case 1: //Anglais
                printf(" \n  Stopwatch controls  Wii (GC)\n");
                printf("Press A to start with three-second countdown.\n");
                printf("Press 1 (Y) to start immediately.\n");
                printf("Press A (Z) again to make a lap.\n");
                printf("Press B (R) to pause or resume.\n");
                printf("Press + (L) to stop and reset.\n");
                printf("Press - (X) to see the credits.\n");
                printf("Press the HOME (START) button to exit.\n");
                break;
            case 2: //Allemand
                printf(" \n  Stopwatch controls  Wii (GC)\n"); // ¡DE
                printf("Drücke A um die Stoppuhr zu starten.\n");
                printf("Press 1 (Y) to start immediately.\n"); // ¡DE
                printf("Drücke wieder A (Z) um eine Runde zu machen.\n");
                printf("Drücke auf B (B) um die Stoppuhr zu pausen oder zu entpausen.\n");
                printf("Drücke + (L) um die Stoppuhr aufzuhalten, und zu reinitialisieren.\n");
                printf("Drücke - (X) um die Kredite zu sehen.\n");
                printf("Drücke den HOME-(START-)Knopf um die Stoppuhr zu verlassen.\n");
                break;
            case 3: //Français
                printf(" \n  Contrôles de chronomètre   Wii (GC)\n");
                printf("Appuyez sur A (A) pour démarrer avec un délai.\n");
                printf("Appuyez sur 1 (Y) pour démarrer sans délai.\n");
                printf("Appuyez de nouveau sur A (Z) pour faire un tour.\n");
                printf("Appuyez sur B (R) pour mettre sur pause ou pour continuer.\n");
                printf("Appuyez sur + (L) pour arrêter et réinistialiser.\n");
                printf("Appuyez sur - (X) pour afficher les crédits.\n");
                printf("Appuyez sur le bouton HOME (START) pour le quitter.\n");
                break;
            case 4: //Espagnol
                printf(" \n  Controles de cronómetro   Wii (GC)\n");
                printf("Presiona A para iniciar con un retraso.\n");
                printf("Presiona 1 (Y) para iniciar de inmediato.\n");
                printf("Presiona A (Z) otra vez para contar una vuelta.\n");
                printf("Presiona B (R) para pausar o reanudar.\n");
                printf("Presiona + (L) para parar y reiniciar.\n");
                printf("Presiona - (X) para ver los créditos.\n");
                printf("Presiona HOME (START) para salir del programa.\n");
                break;
            case 5: //Italien
                printf(" \n  Stopwatch controls  Wii (GC)\n"); // ¡IT
                printf("Premi A per avviare il cronometro.\n");
                printf("Premi 1 (Y) per avviare immediatamente.\n");
                printf("Premi A (Z) per fare un giro.\n");
                printf("Premi B (R) per stoppare e riprendere il cronometro.\n");
                printf("Premi + (L) per fermare e resettare il timer.\n");
                printf("Premi - (X) per visualizzare i crediti.\n");
                printf("Premi il pulsante HOME (START) per uscire dal cronometro.\n");
                break;
            case 6: //Néerlandais
                printf(" \n  Stopwatch controls  Wii (GC)\n"); //¡NL
                printf("Druk op A om de stopwatch te starten.\n");
                printf("Press 1 (Y) to start ismmediately.\n"); // ¡NL
                printf("Druk nogmaals op A (Z) om een ronde tz maken.\n");;
                printf("Press B (R) to pause or resume.\n"); // ¡NL
                printf("Druk op + (L) om de stopwatch te stoppen zn te resetten.\n");
                printf("Druk op - (X) om ze credits te zien.\n");
                printf("Druk op de HOME (START) knop om de stopwatch af te sluiten.\n");
                break;
            default : //Simple English
                printf(" \n  Wii/GC: controls\n");
                printf("A: Start after 3 seconds.\n");
                printf("1/Y: Start with quick start.\n");
                printf("A/Z: Count lap (400m).\n");
                printf("B/R: Pause/resume.\n");
                printf("+/L: Stop/restart. (00:00:000 <--)\n");
                printf("-/X: Credits.\n");
                printf("HOME/START-PAUSE: Exit.\n");
                break;
        }
    }

  
  
    switch(language){
        case 1: //Anglais
            printf("Initialising... Please Wait\r");
            break;
        case 2: //Allemand
            printf("Initialisierung. Bitte warten.\r");
            break;
        case 3: //Français
            printf("Initialisation... veuillez patienter\r");
            break;
        case 4: //Espagnol
            printf("Inicializndo... espera un momento.\r");
            break;
        case 5: //Italien
			printf("Caricamento... Attendere\r");
            break;
        case 6: //Néerlandais
            printf("Initialiseren... een moment geduld\r");
            break;
        default : //Anglais simple
            printf("Translation missing...\nConsole langauge not supported,\nso simple English is displayed.\n");
            printf("Wait for start up.\r");
            break;
    }
	//Resets the timer
	int Hour = 0;
	int Minute = 0;
	int Second = 0;
	int Milli = 0;
	int Start = 0;
    int SixtyMilli = 0;
    int Lap = 1;
	bool Pause = false;
    //SixtyMilli is for internal use because it's more accurate
    //to use the frame rate instead of trying to use the actual
    //milliseconds. But it's only to 59, unlike real milliseconds,
    //so it shouldn't be displayed.
    //Below is for storing last lap's data,
    int LLapHour = 0;
	int LLapMinute = 0;
	int LLapSecond = 0;
	int LLapMilli = 0;
    int LLapSixtyMilli = 0;
    
    sleep(1);
    afficheLogo();
    sleep(.5);
    afficheControles();
    
	while(1) {

		// Call WPAD_ScanPads each loop, this reads the latest controller states
		WPAD_ScanPads();
        PAD_ScanPads();

		// WPAD_ButtonsDown tells us which buttons were wpressed in this loop
		// this is a "one shot" state which will not fire again until the button has been released
		u32 wpressed = WPAD_ButtonsDown(0);
        u32 gpressed = PAD_ButtonsDown(0);

		//To exit the homebrew, you simply have to press the home button
		if ( wpressed & WPAD_BUTTON_HOME || gpressed & PAD_BUTTON_START)
		{
			// printf("Debug exit\r"); //DEBUG. Prints a message before exiting.
			sleep(.5);
            printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // 29 lines total available.
			switch(language){
				case 1: //Anglais
					printf("Exiting...\r");
					break;

				case 2: //Allemand
					printf("Beenden ...\r");
					break;

				case 3: //Français
					printf("Sortie...\r");
					break;

				case 4: //Espagnol
					printf("Cerrando...\r");
					break;

				case 5: //Italien
					printf("Uscita...\r");
					break;

				case 6: //Néerlandais
					printf("Afsluiten...\r");
					break;

				default : //Traduction manquante
					//printf("Translation missing!\n");
					printf("Exiting...\r");
					break;
			}
			exit(0);
		}

		//Code to make laps
		if (( wpressed & WPAD_BUTTON_A || gpressed & PAD_TRIGGER_Z)  && Start != 0){
			//Start = Start + 1;
			if (Start <= 1){
                supprimeLigne();
                //printf("                                                                         \r");
            //printf("373 start%d\n", Start);
                switch(language){
                    case 1: //English
                        printf("           			    Lap %d:",Lap);
                        break;
                    case 2: //German
                        printf("           			Runde %d:",Lap);
                        break;
                    case 3:	//French
                        printf("           			Tour nº %d :",Lap);
                        break;
                    case 4:	//Spanish
                        printf("           			  Vuelta %d:",Lap);
                        break;
                    case 5: //Italian
                        printf("           			Giro %d:",Lap);
                        break;
                    case 6: //Dutch
                        printf("           			Ronde %d:",Lap);
                        break;
                    default : //Missing translation
                        printf("						Lap %d (%dm):", Lap, (Lap * 400));
                }
                printf("                  \n");
                printf("			+%02d:%02d:%02d.%03d		%02d:%02d:%02d.%03d\n\n", LLapHour, LLapMinute, LLapSecond, LLapMilli, Hour, Minute, Second, Milli);
                Lap = Lap+1;
                LLapHour = 0;
                LLapMinute = 0;
                LLapSecond = 0;
                LLapSixtyMilli = 0;
                //displayHorraire(Lap,LLapHour,LLapMinute,LLapSecond,LLapMilli,Hour,Minute,Second,Milli);
            }
		}
        //New immediate start feature.
		if ( ( wpressed & WPAD_BUTTON_1 || gpressed & PAD_BUTTON_Y) && Start == 0){
            Start = 1;
            switch(language){
                case 1: //English
                    printf("Immediate start\n");
                    break;
                case 2: //German
                    printf("Blitz-start\n"); //This is completely made up. Translation missing, might as well be. ¡DE
                    break;
                case 3:	//French
                    printf("Commencement immédiat\n");
                    break;
                case 4:	//Spanish
                    printf("Inicio rápido\n");
                    break;
                case 5: //Italian
                    printf("\n"); // ¡IT
                    break;
                case 6: //Dutch
                    printf("\n"); // ¡NL
                    break;
                default : //Missing translation
                    printf("Quick start\n");
            }
        }
		//Shows the timer beofre start, and then set's the start value to 1
		if (( wpressed & WPAD_BUTTON_A || gpressed & PAD_BUTTON_A)  && Start == 0){
			//printf("354 start%d\n", Start);
			if ( Start == 0 ){
				printf(" \n");
                switch(language){
                    case 2:	//German
                        printf("3 ...\r");
                        sleep(1);
                        printf("		2 ...\r");
                        sleep(1);
                        printf("				1 ...\n");
                        break;
                    default : //Other languages where spaces aren't needed.
                        printf("3...\r");
                        sleep(1);
                        printf("		2...\r");
                        sleep(1);
                        printf("				1...\n");
                }   
				//printf(" \n");
				sleep(1);
				//printf("362 start%d\n", Start);
				Start = 1;}
            //printf("366start%d\n", Start);
		}

		
		//Timer
		if ( Start >= 1){
			if (Pause)
			{
				//printf("Pause ON\r"); //DEBUG. To check if the pause is on.
				//break;
			}
			else
			{
				//printf("Debug timer\n"); //DEBUG. To check if the pause is OFF and the timer running. 
				//Milli += 16; // 400/24; //407?
				//LLapMilli += 16;
                SixtyMilli += 1;
                LLapSixtyMilli += 1;
				Milli = round(SixtyMilli * (50/3)); // 400/24; //407?
				LLapMilli = round(LLapSixtyMilli * (50/3));
				if ( LLapSixtyMilli >= 60 ){
					LLapSecond += 1;
					//LLapMilli = 39;
                    LLapSixtyMilli -= 60;
					if ( LLapSecond >= 60){
						LLapMinute += 1;
						LLapSecond -= 60;
						if ( LLapMinute >= 60 ){
							LLapHour += 1;
							LLapMinute -= 60;
						}
					}
				}
				if ( SixtyMilli >= 60 ){
					Second += 1;
					//Milli = 39;
                    SixtyMilli -= 60;
					if ( Second >= 60){
						Minute += 1;
						Second -= 60;
						if ( Minute >= 60 ){
							Hour += 1;
							Minute -= 60;
						}
					}
				}
				displayHorraire(Lap,LLapHour,LLapMinute,LLapSecond,LLapMilli,Hour,Minute,Second,Milli);
			}	
		}

		//Code to stop, and reset the stopwatch
		if ( wpressed & WPAD_BUTTON_PLUS  || gpressed & PAD_TRIGGER_L){
			Hour = 0;
			Minute = 0;
			Second = 0;
			Milli = 0;
			Start = 0;
            SixtyMilli = 0;
            Lap = 1;
            LLapHour = 0;
            LLapMinute = 0;
            LLapSecond = 0;
            //LLapMilli = 0;
            LLapSixtyMilli = 0;
			Pause = false;
            
			switch(language){
				case 1:	//English
					printf("\nStopped and reset!\n");
					break;
				case 2: //German
					printf("\nGestopppt und zurückgesetzt!\n");
					break;
				case 3: //French
					printf("\nStoppé et réinistialisé !\n");
					break;
				case 4: //Spanish
					printf("\nSe ha parado y reiniciado el cronómetro.\n");
					break;
				case 5: //Italian
					printf("\nFermato e resettato!\n");
					break;
				case 6: //Dutch
					printf("\nGestopt en gereset!\n");
					break;
				default : //Missing translation
					//printf("\nTranslation missing!\n");
					printf("\nStopwatch reset to 00:00:00.000\n");
					break;
			}
		}

		//Code to make time pause. Needs to be tested.
		if (wpressed & WPAD_BUTTON_B || gpressed & PAD_TRIGGER_R)
			if (Start == 1)
			{
				Pause = !Pause;
                switch(language){
                    //Translators ensure the pause string is padded with spaces to make them same length. ¡DE ¡IT ¡NL
                    case 1: //Anglais
                        printf("%s\r",(Pause) ? "Pause  " : "Unpause");
                        break;
                    case 2: //Allemand // Not translated.
                        printf("%s\r",(Pause) ? "Pause  " : "Unpause"); //¡DE
                        break;
                    case 3: //Français
                        printf("%s\r",(Pause) ? "Pause   " : "Continue");
                        break;
                    case 4: //Espagnol
                        printf("%s\r",(Pause) ? "Pausa    " : "Reanudado");
                        break;
                    case 5: //Italien // Not translated.
                        printf("%s\r",(Pause) ? "Pause  " : "Unpause"); //¡IT
                        break;
                    case 6: //Néerlandais // Not translated.
                        printf("%s\r",(Pause) ? "Pause  " : "Unpause"); //¡DE
                        break;
                    default : //Traduction manquante
                        printf("%s\r",(Pause) ? "Pause  " : "Unpause");
                        break;
                }
			}

		//Credits
		if (wpressed & WPAD_BUTTON_MINUS || gpressed & PAD_BUTTON_X) {
			if ( Start == 1)
			{
                supprimeLigne();
				switch(language){
                    case 1:	//English
                        printf("Cannot show the credits because the stopwatch is running.\n");
                        break;
                    case 2: //German
                        printf("Kann die Kredite nicht anzeigen weill die Stoppuhr lauuft.\n");
                        break;
                    case 3: //French
                        printf("La générique ne peut pas être affichée car le chronomètre est allumé.\n");
                        break;
                    case 4: //Spanish
                        printf("No se puede mostrar los créditos cuándo el cronómetro está en marcha.\n");
                        break;
                    case 5: //Italian
                        printf("I crediti non possono essere visualizzati perché il cronometro è acceso.\n");
                        break;
                    case 6: //Dutch. Translation needed
                        printf("Gestopt en gereset!\n"); // ¡NL
                        break;
                    default : //Translation missing
                        //printf("Translation missing!\n");
                        printf("No credits because stopwatch is running.");
                        break;
				}
				afficheControles();
			}
			else
			{
				switch(language){
                    case 1:	//English
                        printf("\n");
                        printf("CREDITS\n");
                        printf("Idea: Ilovemyhouse\n");
                        printf("Testing: Ilovemyhouse\n");
                        printf("Translation: Some friends and myself\n");
                        printf("Libraries: libogc - github.com/devkitPro/libogc\n");
                        break;
                    case 2: //German
                        printf("\n");
                        printf("KREDITE\n");
                        printf("Idee: Ilovemyhouse\n");
                        printf("Testen: Ilovemyhouse\n");
                        printf("Übersetzungen: Freunde und ich selber.\n");
                        printf("Bibliotheken: libogc - github.com/devkitPro/libogc\n");
                        break;
                    case 3: //French
                        printf("\n");
                        printf("GÉNÉRIQUE\n");
                        printf("Idée : Ilovemyhouse\n");
                        printf("Test : Ilovemyhouse\n");
                        printf("Traductions : Des amis et moi-même.\n");
                        printf("Librairies : libogc - github.com/devkitPro/libogc\n");
                        break;
                    case 4: //Spanish
                        printf("\n");
                        printf("CRÉDITOS\n");
                        printf("Idea y prueba: Ilovemyhouse\n");
                        printf("Traducciones: Unos amigos, yo mismo, y un tejano que se llama... ¿jeptioak?\n");
                        printf("Bibliotecas: libogc - github.com/devkitPro/libogc\n");
                        break;
                    case 5: //Italian
                        printf("\n");
                        printf("To be translated\n"); // ¡IT
                        break;
                    case 6: //Dutch
                        printf("\n");
                        printf("Insert translation.\n"); // ¡NL
                        break;
                    default : //Translation missing
                        printf("\n");
                        //printf("Translation missing!\n");
                        printf("CREDITS\n");
                        printf("Idea: Ilovemyhouse\n");
                        printf("Testing: Ilovemyhouse\n");
                        printf("Translation: Some friends and myself.\n");
                        printf("Libraries: libogc - github.com/devkitPro/libogc\n");
                        break;
				}
				afficheLogo();
                afficheControles();
			}
		}
		//Easter Egg
		if (((wpressed & WPAD_BUTTON_1)  && (wpressed & WPAD_BUTTON_2)) || ((gpressed & PAD_BUTTON_A) && (gpressed & PAD_BUTTON_B))){
            printf("\n1/3\nHello World!\n");
        }
		//Easter Egg 2
		if ( ((wpressed & WPAD_BUTTON_PLUS) && (wpressed & WPAD_BUTTON_MINUS)) || ((gpressed & PAD_TRIGGER_L) && (gpressed & PAD_TRIGGER_R))){
            printf("\n2/3\nYou found an Easter Egg!\n\n¡Encontraste un pequeño secreto!\nNo se lo digas a nadie, amigo mío.\n\nVous avez trouvé un petit secret !\nCette programme est plus qu'un chronomètre, c'est un Wiimètre !\n"); // I, jeptioak, think this is more interesting if everyone sees what's written in every language, so don't worry about the "case(language)" feature, just ensure you put two \n line breaks between each language and that no single line exceeds some 77 characters. It's just an easter egg, write whatever you want. In this case, something upbeat preferably. ¡DE ¡IT ¡NL
        }
		//Easter Egg 3
		if (( (wpressed & WPAD_BUTTON_B) && (wpressed & WPAD_BUTTON_A)) || ((gpressed & PAD_BUTTON_B) && (gpressed & PAD_TRIGGER_Z))){
            printf("\n3/3\nThis text is just 0's & 1's.\n\nLa mensaje que ves está hecho de señales électricas binarias.\n¡Te amo!--dicen los jovenes a través de nada más que ceros y unos.\n\nZéro et un, la moyenne préférée des jeunes pour communiquer.\n"); // In this case, write something profound about computers and their role in modern society. ¡DE ¡IT ¡NL
        }
		//Refreshes screen.
		VIDEO_WaitVSync();
	}
	return 0;
}
