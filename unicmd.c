
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


#define VERSIONNBR "0.11" 


////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////
///// some cat!! 
#include <fcntl.h>
#include <unistd.h>
static int cat_fd(int fd) 
{
  char buf[4096];
  ssize_t nread;

  while ((nread = read(fd, buf, sizeof buf)) > 0) 
  {
    ssize_t ntotalwritten = 0;
    while (ntotalwritten < nread) {
      ssize_t nwritten = write(STDOUT_FILENO, buf + ntotalwritten, nread - ntotalwritten);
      if (nwritten < 1)
        return -1;
      ntotalwritten += nwritten;
    }
  }
  return nread == 0 ? 0 : -1;
}
/////////////////
static int ncat_static(const char *fname) 
{
  int fd, success;
  if ((fd = open(fname, O_RDONLY)) == -1)
    return -1;

  success = cat_fd(fd);

  if (close(fd) != 0)
    return -1;

  return success;
}
////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////
////////////////////////////


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





char *strrlf(char *str)
{  // seems to work
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if (str[i] != '\n' && str[i] != '\n') 
        ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      //size_t siz = sizeof ptr ; 
      //char *r = malloc( sizeof ptr );
      //return r ? memcpy(r, ptr, siz ) : NULL;
      char *base = ptr ; 
      return (base);
}




//////////////////
void nappend( char *filetarget,  char *  filesource )
{
  // fread
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



//////////////////
void ncp( char *filetarget,  char *  filesource )
{
  // fread
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
        fp2 = fopen( filetarget, "wb");
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


int rstrstr(  char *mainstring , char charsearch )
{
  int i;  
  int freader = 1 ;  
  int found = 0 ; 
  for ( i = strlen( mainstring) ; ( freader == 1 ) && ( i >= 0) ; i--){
     if ( i >= 0 ){
        if ( mainstring[ i ] == charsearch ){
	    freader = 0; 
	    found = i ; 
	}
     }
  }
  return found;
}





////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
////////////////////////////////////////////////////
char *strpathname( char *myfile )
{
  char buffer[PATH_MAX];
  int lastslash = rstrstr( myfile , '/' );
  if ( lastslash >= 1 ) 
   strncpy( buffer, strcut( myfile, 1 , lastslash ), PATH_MAX );
  else
   strncpy( buffer, "", PATH_MAX );
  char *base = buffer ; 
  return (base);
}








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


void runcmdmg( char *thecmd , char *thefile, char *thetail )
{
       char cmdi[PATH_MAX];
       printf( "<CMD: %s>\n" , thecmd ) ; 
       printf( "<FILE: %s>\n" , thefile ) ; 
       strncpy( cmdi , "  " , PATH_MAX );
       strncat( cmdi , thecmd , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , " \"" , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , thefile , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi , "\"  " , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi ,  thetail  , PATH_MAX - strlen( cmdi ) -1 );
       strncat( cmdi ,  " "  , PATH_MAX - strlen( cmdi ) -1 );
       system( cmdi );
}





////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
char *strgetcol( char *str, int mygivencol )
{ 
      // str is input 
      // ptr is output 
      char ptr[PATH_MAX];
      char charo[PATH_MAX];
      strncpy( ptr, "", PATH_MAX );
      int i,j=0;   
      int fdcoll = 0;
      int fdcolr = 0;
      for(i=0; str[i]!='\0'; i++)
      {
        if ( str[i] == '{' ) 
        {
           fdcoll++;
           //snprintf( charo, PATH_MAX , " ( %s ) ", strfetchcontent( celldata[ foocy ][ foocx +1 ], foocy , foocx+1 ) );
           //strncat( ptr , charo , PATH_MAX - strlen( ptr ) -1 ); 
        }
        else if ( str[i] == '}' ) 
        {
           fdcolr++;
           //snprintf( charo, PATH_MAX , " ( %s ) ", strfetchcontent( celldata[ foocy ][ foocx +1 ], foocy , foocx+1 ) );
           //strncat( ptr , charo , PATH_MAX - strlen( ptr ) -1 ); 
        }
        else if (str[i] != '\n' && str[i] != '\n') 
        {
          snprintf( charo, PATH_MAX , "%c", str[i] );
          if ( ( mygivencol == 1 ) && ( fdcoll == 1 )  && ( fdcolr == 0 ) )
           strncat( ptr , charo , PATH_MAX - strlen( ptr ) -1 ); 
          else if ( ( mygivencol == 2 ) && ( fdcoll == 2 )  && ( fdcolr == 1 ) )
           strncat( ptr , charo , PATH_MAX - strlen( ptr ) -1 ); 
        }
      } 
      //ptr[j]='\0';
      //size_t siz = sizeof ptr ; 
      //char *r = malloc( sizeof ptr );
      //return r ? memcpy(r, ptr, siz ) : NULL;
      char *base = ptr ; 
      return (base);
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
void fileuniprocess(  char *filein )
{
  int fetchi;
  FILE *fp5;
  FILE *fp6;
  char fetchline[PATH_MAX];
  char fetchlinetmp[PATH_MAX];
  char inputfield[PATH_MAX];
  char fieldsrc[PATH_MAX];
  char fieldtrg[PATH_MAX];

  int linecounter = 1;
  int content_archive = 0;
  int content_export = 0;
  char file_export[PATH_MAX];
  strncpy( file_export, "", PATH_MAX );

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

              // !enddoc
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'e' )
              if ( fetchline[2] == 'n' )
              if ( fetchline[3] == 'd' )
              if ( fetchline[4] == 'd' )
              if ( fetchline[5] == 'o' )
              if ( fetchline[6] == 'c' )
              if ( foundcmd == 0 ) 
              {
                 filereader = 0;
                 foundcmd = 1;
              }




              ///////////////////////////////////
              if ( foundcmd == 0 )
              if ( fetchline[0] == '*' )
              if ( fetchline[1] == '/' )
              {
	          printf( "  => Archive or comments ends....\n" );
                  content_archive = 0;
                  foundcmd = 1;
              }

              ///////////////////////////////////
              if ( foundcmd == 0 )
              if ( fetchline[0] == '/' )
              if ( fetchline[1] == '*' )
              {
	          printf( "  => Archive or comments begins....\n" );
                  content_archive = 1;
                  foundcmd = 1;
              }
              ///////////////////////////////////
              if ( foundcmd == 0 ) 
              if ( content_archive == 1 ) 
              {
	         printf( "  => Line non considered, due to Archive or comments active.\n" );
                 foundcmd = 1;
              }





              ////////////////////////////
              /// !new file
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'n' )
              if ( fetchline[2] == 'e' )
              if ( fetchline[3] == 'w' )
              if ( fetchline[4] == ' ' )
              if ( foundcmd == 0 ) 
              {
                 strncpy( inputfield, strtrim( strcut( fetchline, 4+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[File export: %s]\n", inputfield );
 	         strncpy( file_export, inputfield, PATH_MAX );
                 FILE *fp11;
                 fp11 = fopen( file_export , "wb+" );
                 fputs( "\n", fp11 );
                 fputs( "//// unicmd \n", fp11 );
                 fputs( "!tex\n", fp11 );
                 fputs( "!utf\n", fp11 );
                 fputs( "!gfx\n", fp11 );
                 fputs( "!date      \n", fp11 );
                 fputs( "!author    \n", fp11 );
                 fputs( "!gpath{~/pool/figs/}\n", fp11 );
                 fputs( "\n", fp11 );
                 fclose( fp11 );
                 foundcmd = 1; 
              }
   

              // usage: !new file
              // !export
              // line1
              // line2
              // ...
              // !export
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'e' )
              if ( fetchline[2] == 'x' )
              if ( fetchline[3] == 'p' )
              if ( fetchline[4] == 'o' )
              if ( fetchline[5] == 'r' )
              if ( fetchline[6] == 't' )
              if ( foundcmd == 0 ) 
              {
                 content_export = 1;
                 if ( strcmp( file_export, "" ) == 0 ) 
 	           strncpy( file_export, "noname.dat" , PATH_MAX );
                 printf( "Create a basic noname.dat for export\n" );
                 foundcmd = 1; 
              }



              if ( foundcmd == 0 ) 
              if ( content_export == 1 ) 
              {
	         printf( "!export to file \n" );
                 strncpy( inputfield, strrlf( fetchline ) ,  PATH_MAX );
 	         printf( "[%s]\n", inputfield );
 	         printf( "[File to output %s]\n", file_export );
                 FILE *fp12;
                 fp12 = fopen( file_export , "ab+" );
                   fputs( inputfield, fp12 );
                   fputs( "\n", fp12 );
                 fclose( fp12 );
                 printf( "  Content Export: %s to file %s\n", inputfield, file_export );
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



              // !wget  command
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'w' )
              if ( fetchline[2] == 'g' )
              if ( fetchline[3] == 'e' )
              if ( fetchline[4] == 't' )
              if ( fetchline[5] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!wget\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 5+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 runwith( " wget  " , inputfield );                 
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




              // !nappend{source.dat}{target.dat}
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'n' )
              if ( fetchline[2] == 'a' )
              if ( fetchline[3] == 'p' )
              if ( fetchline[4] == '{' )
              if ( foundcmd == 0 )
              {
	         printf( "!nap (a simple file append).\n" );
                 strncpy( inputfield, strgetcol( strcut( fetchline,  3+2, strlen( fetchline )), 1) , PATH_MAX );
                 strncpy( fieldsrc, inputfield , PATH_MAX );
                 strncpy( inputfield, strgetcol( strcut( fetchline,  3+2, strlen( fetchline )), 2) , PATH_MAX );
                 strncpy( fieldtrg, inputfield , PATH_MAX );
 	         printf( "Output [Source: %s]\n",   fieldsrc );
 	         printf( "Output [Target: %s]\n",   fieldtrg );
 	         printf( "Output [Exist:  %d %d]\n", fexist( fieldsrc) , fexist( fieldtrg) );
 	         printf( "Appending %s=>%s...]\n", fieldsrc, fieldtrg );
                 if ( fexist( fieldsrc ) == 1 ) 
                  if ( fexist( fieldtrg ) != 2 ) 
                   nappend( fieldtrg, fieldsrc );
 	         printf( "Done Appending...]\n" );
                 foundcmd = 1;
              }


              // !ncptmp source
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'n' )
              if ( fetchline[2] == 'c' )
              if ( fetchline[3] == 'p' )
              if ( fetchline[4] == 't' )
              if ( fetchline[5] == 'm' )
              if ( fetchline[6] == 'p' )
              if ( fetchline[7] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!ncptmp (a simple filecopy).\n" );
                 strncpy( inputfield, strcut( fetchline,  7+2, strlen( fetchline )) , PATH_MAX );
                 runcmdmg( " cp -v " , inputfield , "/tmp" );
                 foundcmd = 1;
              }


              // !ncp{source}{target}
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'n' )
              if ( fetchline[2] == 'c' )
              if ( fetchline[3] == 'p' )
              if ( fetchline[4] == '{' )
              if ( foundcmd == 0 )
              {
	         printf( "!ncp (a simple filecopy).\n" );
                 strncpy( inputfield, strgetcol( strcut( fetchline,  3+2, strlen( fetchline )), 1) , PATH_MAX );
                 strncpy( fieldsrc, inputfield , PATH_MAX );
                 strncpy( inputfield, strgetcol( strcut( fetchline,  3+2, strlen( fetchline )), 2) , PATH_MAX );
                 strncpy( fieldtrg, inputfield , PATH_MAX );
 	         printf( "Output [Source: %s]\n",   fieldsrc );
 	         printf( "Output [Target: %s]\n",   fieldtrg );
 	         printf( "Output [Exist:  %d %d]\n", fexist( fieldsrc) , fexist( fieldtrg) );
 	         printf( "Copying %s=>%s...]\n", fieldsrc, fieldtrg );
                 if ( fexist( fieldsrc ) == 1 ) 
                  if ( fexist( fieldtrg ) != 2 ) 
                   ncp( fieldtrg, fieldsrc );
 	         printf( "Done Copying...]\n" );
                 foundcmd = 1;
              }


              // !getcol (...)  
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'g' )
              if ( fetchline[2] == 'e' )
              if ( fetchline[3] == 't' )
              if ( fetchline[4] == 'c' )
              if ( fetchline[5] == 'o' )
              if ( fetchline[6] == 'l' )
              if ( fetchline[7] == '[' )
             if (( fetchline[8] >= '1' ) &&  ( fetchline[8] <= '9' ))
              if ( fetchline[9] == ']' )
              if ( fetchline[10] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!getcol content text\n" );
                 if ( fetchline[8] ==      '1' )
                    strncpy( inputfield, strgetcol( strcut( fetchline, 10+2, strlen( fetchline )), 1) , PATH_MAX );
                 else if ( fetchline[8] == '2' )
                    strncpy( inputfield, strgetcol( strcut( fetchline, 10+2, strlen( fetchline )), 2) , PATH_MAX );
 	         printf( "Output [%s]\n", inputfield );
                 foundcmd = 1;
              }

              // !strlen (...)  
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 's' )
              if ( fetchline[2] == 't' )
              if ( fetchline[3] == 'r' )
              if ( fetchline[4] == 'l' )
              if ( fetchline[5] == 'e' )
              if ( fetchline[6] == 'n' )
              if ( fetchline[7] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!strlen text\n" );
                 strncpy( inputfield,  strcut( fetchline, 7+2, strlen( fetchline )) , PATH_MAX );
 	         printf( " => [string: %s]\n", inputfield );
 	         printf( " => [strlen: %d]\n", strlen( inputfield) );
                 foundcmd = 1;
              }


              // !cat (...)  
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'c' )
              if ( fetchline[2] == 'a' )
              if ( fetchline[3] == 't' )
              if ( fetchline[4] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!cat file\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 4+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 if ( fexist( inputfield ) == 1 ) 
                     ncat_static( inputfield );
                 foundcmd = 1;
              }


              // !mkdir (...)  
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'm' )
              if ( fetchline[2] == 'k' )
              if ( fetchline[3] == 'd' )
              if ( fetchline[4] == 'i' )
              if ( fetchline[5] == 'r' )
              if ( fetchline[6] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!mkdir text\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 6+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 runwith( " mkdir " , inputfield ); 
                 foundcmd = 1;
              }


              // !vim (...)  
              if ( fetchline[0] == '!' )
              if ( fetchline[1] == 'v' )
              if ( fetchline[2] == 'i' )
              if ( fetchline[3] == 'm' )
              if ( fetchline[4] == ' ' )
              if ( foundcmd == 0 )
              {
	         printf( "!vim file\n" );
                 strncpy( inputfield, strtrim( strcut( fetchline, 4+2, strlen( fetchline ))) , PATH_MAX );
 	         printf( "[%s]\n", inputfield );
                 if ( fexist( inputfield ) == 1 ) 
                   runwith( " vim " , inputfield ); 
                 else
 	           printf( "[FILE NOT FOUND! (%s)]\n", inputfield );
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
    if ( strcmp(argv[1], "--version" ) == 0)
    {
	  printf( "Unicmd version: %s\n", VERSIONNBR );
          return 0;
    }

    ////////////////////////////////////////////////////////
    if ( argc >= 2)
    if ( strcmp(argv[1], "--arg" ) == 0)
    {
          for( i = 1 ; i < argc ; i++) 
	     printf( "%d/%d: %s\n", i, argc-1 ,  argv[ i] );
          return 0;
    }

    
    ////////////////////////////////////////////////////////
    /// rescue and debugging function
    ////////////////////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "--cat" ) ==  0 ) 
      if ( fexist( argv[2] )  == 1 )
      {
         ncat_static( argv[ 2 ] );
         return 0;
      }

      //////////////////////////////////////////
      if ( argc == 3)
      if ( ( strcmp( argv[1] , "--browse" ) ==  0 ) 
      || ( strcmp( argv[1] , "--nc" ) ==  0 ) )
      {
         printf( "Going into directory: %s\n", strpathname( argv[ 2 ] ) );
         chdir( strpathname( argv[ 2 ] ) );
         nsystem( " nexplorer " );
         return 0;
      }

    //////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[2] , "--vim" ) ==  0 ) 
      if ( fexist( argv[1] )  == 1 )
      {
         runwith( " vim ",  argv[ 1 ] );
         return 0;
      }

    //////////////////////////////////////////
    if ( argc == 3)
      if ( strcmp( argv[1] , "--vim" ) ==  0 ) 
      if ( fexist( argv[2] )  == 1 )
      {
         runwith( " vim ",  argv[ 2 ] );
         return 0;
      }


    ////////////////////////////////////////////////////////
    if ( argc >= 2)
    {
          for( i = 1 ; i < argc ; i++) 
	     fileuniprocess( argv[ i ] );
          return 0;
    }

    return 0;
}



