
//////////////////////
//unicmd
//////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h> 
#include <time.h>


int foundcmd = 0;
int filereader = 1;
int content_remarks = 0;


///////////////////////////////
///////////////////////////////
///////////////////////////////
char *strtimestamp()
{
      long t;
      struct tm *ltime;
      time(&t);
      ltime=localtime(&t);
      char charo[50];  int fooi ; 
      fooi = snprintf( charo, 50 , "%04d%02d%02d%02d%02d%02d",
	1900 + ltime->tm_year, ltime->tm_mon +1 , ltime->tm_mday, 
	ltime->tm_hour, ltime->tm_min, ltime->tm_sec 
	);
    size_t siz = sizeof charo ; 
    char *r = malloc( sizeof charo );
    return r ? memcpy(r, charo, siz ) : NULL;
}



void runwith( char *thecmd , char *thefile )
{
       char cmdi[PATH_MAX];
       printf( "<CMD: %s>\n" , thecmd ) ; 
       printf( "<FILE: %s>\n" , thefile ) ; 
       strncpy( cmdi , "  " , PATH_MAX );
       strncat( cmdi , thecmd , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , thefile , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"" , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
}

void nsystem( char *mycmd )
{
   printf( "<CMD: %s>\n", mycmd );
   system( mycmd );
   printf( "<Defunc CMD: %s>\n", mycmd );
}




/////////////////////////////////
/////////////////////////////////
/////////////////////////////////
int fexist(char *a_option)
{
  char dir1[PATH_MAX]; 
  char *dir2;
  DIR *dip;
  strncpy( dir1 , "",  PATH_MAX  );
  strncpy( dir1 , a_option,  PATH_MAX  );

  struct stat st_buf; 
  int status; 
  int fileordir = 0 ; 

  status = stat ( dir1 , &st_buf);
  if (status != 0) {
    fileordir = 0;
  }

  // this is compatible to check if a file exists
  FILE *fp2check = fopen( dir1  ,"r");
  if( fp2check ) {
  // exists
  fileordir = 1; 
  fclose(fp2check);
  } 

  if (S_ISDIR (st_buf.st_mode)) {
    fileordir = 2; 
  }
return fileordir;
/////////////////////////////
}




//////////////////
void ncatfile( char *filetarget,  char *filesource )
{
  char            buffer[1];
  size_t          n;
  size_t          m;
  FILE *fp;
  FILE *fp1; 
  FILE *fp2;
  int counter = 0 ; 
  int freader = 1 ; 
  int i , j ,posy, posx ; 
  if ( fexist( filesource ) == 1 )
  {
        fp = fopen( filesource, "rb");
        fp2 = fopen( filetarget, "ab");
        counter = 0; 
        while(  !feof(fp) && ( freader == 1)   ) {
           if (  feof(fp)   ) {
                freader = 0 ; 
            }
            n = fread(  buffer, sizeof(char), 1 , fp);
            m = fwrite( buffer, sizeof(char), 1,  fp2);
        }
        fclose(fp2);
        fclose(fp);
      }
}







char *strcut( char *str , int myposstart, int myposend )
{  
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( ( str[i] != '\0' ) && ( str[i] != '\0') )
         if ( ( i >=  myposstart-1 ) && (  i <= myposend-1 ) )
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}




char *strtrim(char *str)
{  
      // right side to to finish
      char ptr[strlen(str)+1];
      int strposmax = strlen( str );
      int lastposchar = strposmax;
      int i,j=0;
      int foundspace = 1;

      /// find last char
      foundspace = 1;
      for( i= strposmax-1 ; i >= 0 ; i--)
      {
         //printf( "|%d-%d-%c| ", i , lastposchar , str[i] );
	 // find where to space
         if ( foundspace == 1 ) 
         if ( str[i] == ' ' ) 
   	    lastposchar = i-1;

         if ( str[i] != ' ' ) 
           foundspace = 0;
      } 

      // add the content
      foundspace = 1;
      for(i=0; i <= lastposchar ; i++)
      {
        if ( foundspace == 1 ) 
         if ( ( str[i] != ' ' )  && ( str[i] != 9 ) ) //added! with 9 for a TAB!!
          foundspace = 0;

        if ( foundspace == 0 ) 
           ptr[j++]=str[i];
      } 
      ptr[j]='\0';

      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}





///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
void filecat(  char *filein )
{
  int fetchi;
  FILE *fp5;
  FILE *fp6;
  char fetchline[PATH_MAX];
  char fetchlinetmp[PATH_MAX];
  char inputfield[PATH_MAX];

  int linecounter = 1;

  /////////////////////////////////////////////////
  {

    printf( "\n" );
    printf( "###################################\n" );
    printf( "!title %s\n", filein );
    printf( "###################################\n" );

    fp6 = fopen( filein , "rb");
    while( !feof(fp6) )
    {
       printf( "Loop FREADER: %d\n" , filereader );
       fgets(fetchlinetmp, PATH_MAX, fp6); 
       printf( " => Line: %s\n" , fetchlinetmp );
       if ( filereader == 1 )
       if ( !feof(fp6) )
       {  
          strncpy( fetchline, "" , PATH_MAX );
          for( fetchi = 0 ; ( fetchi <= strlen( fetchlinetmp ) ); fetchi++ )
            if ( fetchlinetmp[ fetchi ] != '\n' )
              fetchline[fetchi]=fetchlinetmp[fetchi];
  
         if ( !feof(fp6) )
         {
	      printf( "%d: %s", linecounter++, fetchline );
	      printf( "\n" );
              foundcmd = 0;

              ///////////////////////////////////
              if ( foundcmd == 0 )
              if ( fetchline[0] == '#' )
              {
	         printf( "  => Skip the line with # (notes).\n" );
                 foundcmd = 1;
              }
              ///////////////////////////////////
              if ( foundcmd == 0 )
              if ( fetchline[0] == '/' )
              if ( fetchline[1] == '/' )
              {
	          printf( "  => Skip the line with notes.\n" );
                  foundcmd = 1;
              }

              /////////////////////////
              // !play url  
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'p' )
              if ( fetchline[2] == 'l' )
              if ( fetchline[3] == 'a' )
              if ( fetchline[4] == 'y' )
              if ( fetchline[5] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!play \n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 5+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 runwith( " mplayer " , inputfield );                 
                 foundcmd = 1;
              }

              /////////////////////////
              // !mp url  
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'm' )
              if ( fetchline[2] == 'p' )
              if ( fetchline[3] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!mplayer (!mp)\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 3+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 runwith( " mplayer -fs -zoom " , inputfield );                 
                 foundcmd = 1;
              }


              /////////////////////////
              // !mplayer  
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'm' )
              if ( fetchline[2] == 'p' )
              if ( fetchline[3] == 'l' )
              if ( fetchline[4] == 'a' )
              if ( fetchline[5] == 'y' )
              if ( fetchline[6] == 'e' )
              if ( fetchline[7] == 'r' )
              if ( fetchline[8] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!mplayer (!mp)\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 8+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 runwith( " mplayer -fs -zoom " , inputfield );                 
                 foundcmd = 1;
              }



              /////////////////////////
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'n' )
              if ( fetchline[2] == 'm' )
              if ( fetchline[3] == 'p' )
              if ( fetchline[4] == 'l' )
              if ( fetchline[5] == 'a' )
              if ( fetchline[6] == 'y' )
              if ( fetchline[7] == 'e' )
              if ( fetchline[8] == 'r' )
              if ( fetchline[9] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!nmplayer (!mp)\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 8+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 runwith( " nmplayer " , inputfield );                 
                 foundcmd = 1;
              }

              // !enddoc
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'e' )
              if ( fetchline[2] == 'n' )
              if ( fetchline[3] == 'd' )
              if ( fetchline[4] == 'd' )
              if ( fetchline[5] == 'o' )
              if ( fetchline[6] == 'c' )
              {
                 filereader = 0;
                 foundcmd = 1;
              }


              // !ntube install
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'n' )
              if ( fetchline[2] == 't' )
              if ( fetchline[3] == 'u' )
              if ( fetchline[4] == 'b' )
              if ( fetchline[5] == 'e' )
              if ( fetchline[6] == ' ' )
              if ( fetchline[7] == 'i' )
              if ( fetchline[8] == 'n' )
              if ( fetchline[9] == 's' )
              if ( fetchline[10] == 't' )
              if ( fetchline[11] == 'a' )
              if ( fetchline[12] == 'l' )
              if ( fetchline[13] == 'l' )
              if ( foundcmd == 0 )
              {
                  printf("TUBE Service: wget / Install...\n");
                  system( " cd ; wget \"https://yt-dl.org/downloads/2017.08.23/youtube-dl\" -O ~/.youtube-dl  " );
                  system( "  cd ; python ~/.youtube-dl -U  " );
                  foundcmd = 1;
              }


              // !bash  command
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'b' )
              if ( fetchline[2] == 'a' )
              if ( fetchline[3] == 's' )
              if ( fetchline[4] == 'h' )
              if ( fetchline[5] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!bash\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 5+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 nsystem( inputfield );                 
                 foundcmd = 1;
              }
              // !sh  command
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 's' )
              if ( fetchline[2] == 'h' )
              if ( fetchline[3] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!sh \n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 3+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 nsystem( inputfield );                 
                 foundcmd = 1;
              }



              // !create content
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'c' )
              if ( fetchline[2] == 'r' )
              if ( fetchline[3] == 'e' )
              if ( fetchline[4] == 'a' )
              if ( fetchline[5] == 't' )
              if ( fetchline[6] == 'e' )
              if ( fetchline[7] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!create\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 7+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 FILE *fp9;
                 fp9 = fopen( strtimestamp() , "ab+" );
                 fputs( inputfield, fp9 );
                 fclose( fp9 );
                 foundcmd = 1;
              }




              // !ntube 
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'n' )
              if ( fetchline[2] == 't' )
              if ( fetchline[3] == 'u' )
              if ( fetchline[4] == 'b' )
              if ( fetchline[5] == 'e' )
              if ( fetchline[6] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!NTUBE\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 6+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 runwith( " ntube  " , inputfield );                 
                 foundcmd = 1;
              }


              // !ntubemp 
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'n' )
              if ( fetchline[2] == 't' )
              if ( fetchline[3] == 'u' )
              if ( fetchline[4] == 'b' )
              if ( fetchline[5] == 'e' )
              if ( fetchline[6] == 'm' )
              if ( fetchline[7] == 'p' )
              if ( fetchline[8] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!NTUBE MPLAYER\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 8+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 runwith( " ntube play " , inputfield );                 
                 foundcmd = 1;
              }



              // !fig (...)
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'f' )
              if ( fetchline[2] == 'i' )
              if ( fetchline[3] == 'g' )
              if ( fetchline[4] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!FIG\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 4+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 runwith( " feh -FZ  " , inputfield );                 
                 foundcmd = 1;
              }


              // !cr (...)  for chromium-browser (Pi)
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'c' )
              if ( fetchline[2] == 'r' )
              if ( fetchline[3] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!URL (chromium)\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 3+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 runwith( " chromium-browser " , inputfield );                 
                 foundcmd = 1;
              }

              // !links (...)  
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'l' )
              if ( fetchline[2] == 'i' )
              if ( fetchline[3] == 'n' )
              if ( fetchline[4] == 'k' )
              if ( fetchline[5] == 's' )
              if ( fetchline[6] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!links app\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 6+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 runwith( " links " , inputfield );                 
                 foundcmd = 1;
              }


              // !url (...)  for chromium-browser (Pi)
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'u' )
              if ( fetchline[2] == 'r' )
              if ( fetchline[3] == 'l' )
              if ( fetchline[4] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!URL (chromium)\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 4+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 if ( fexist( "/usr/bin/chromium" ) == 1 )
                    runwith( " chromium --new-window " , inputfield );                 

                 else if ( fexist( "/usr/bin/chromium-browser" ) == 1 )
                    runwith( " chromium-browser --new-window " , inputfield );                 
                 else if ( fexist( "/usr/bin/dillo" ) == 1 )
                    runwith( " dillo " , inputfield );                 

                 else
                    runwith( " links " , inputfield );                 
                 foundcmd = 1;
              }


              // !echo text text
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'e' )
              if ( fetchline[2] == 'c' )
              if ( fetchline[3] == 'h' )
              if ( fetchline[4] == 'o' )
              if ( fetchline[5] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "<!echo command>\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 5+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "%s\n", inputfield );
                 foundcmd = 1;
              }


              // !url (...)
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'u' )
              if ( fetchline[2] == 'r' )
              if ( fetchline[3] == 'l' )
              if ( fetchline[4] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!URL\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 4+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 runwith( " chromium-browser " , inputfield );                 
                 foundcmd = 1;
              }



	 } // end of check end of file
       }
      }
      fclose( fp6 ); 
  }
}





int main( int argc, char *argv[])
{
    char cwd[PATH_MAX]; int i ; 

    ////////////////////////////////////////////////////////
    if ( argc >= 2)
    if ( strcmp(argv[1], "--arg" ) == 0)
    {
          for( i = 1 ; i < argc ; i++) 
	     printf( "%d/%d: %s\n", i, argc-1 ,  argv[ i] );
          return 0;
    }
    
    ////////////////////////////////////////////////////////
    if ( argc >= 2)
    {
          for( i = 1 ; i < argc ; i++) 
	     filecat( argv[ i ] );
          return 0;
    }

    return 0;
}


