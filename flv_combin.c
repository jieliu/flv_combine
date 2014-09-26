#include <stdio.h>
#include <stdlib.h>
#include "flv.hpp"
//filename1, filename2, ...系列文件的合并 
void video_combin( char *filename, int video_num )
{
   char *videoname[video_num];
   char *buffer = (char*) malloc( sizeof(char)*1024 );
   //get the divided video name
   int i;
   for( i=0; i < video_num; ++i )
   {
        videoname[i] = (char*)malloc( sizeof(char)*MAXFILENAMELEN );
        sprintf( videoname[i], "%s%d%s", get_filename_prefix( filename ), i, get_filename_extent( filename ));
        //printf( "%s", videoname[i] );
   }
   
   //deal the first video
  FILE *output_file = fopen( filename , "wb");
   if( output_file == NULL )
   {
       perror( "fopen\n" );
       exit( -1 );
   }
   FILE *input_file = fopen( videoname[0], "rb");
   if( input_file == NULL )
   {
       perror( "fopen\n" );
       exit( -1 );
   }     
   char value = 1;
   fwrite( "FLV", sizeof(char), 3, output_file);
   fwrite( &value , sizeof(char), 1, output_file);
   fwrite( &value , sizeof(char), 1, output_file);
   fseek( input_file, 5, SEEK_SET );
   
   int n = 0;
   while( (n = fread( buffer, sizeof(char), 1024, input_file)) )
   {
       fwrite( buffer, sizeof(char), n, output_file );
       memset( buffer, 0, 1024);
   } 
   //combin the last video
   int header_len;
   for( i = 1; i < video_num; ++i )
   {
         freopen( videoname[1], "rb", input_file);           
         fseek( input_file, 16, SEEK_SET ); 
         fread( &value, sizeof(char), 1, input_file );   
         header_len = value;  
         if( header_len < 0)
            header_len += 256;
         header_len = header_len + 28;     //9+4+11+4
         fseek( input_file, header_len, SEEK_SET );  
           
         memset( buffer, 0, 1024 ); 
         while( (n = fread( buffer, sizeof(char), 1024, input_file)) )
         {
               fwrite( buffer, sizeof(char), n, output_file );
               memset( buffer, 0, 1024);
         }     
   }   
   fclose( input_file );
   fclose( output_file );   
}

int main(int argc, char *argv[])
{
   video_combin( "sin.flv", 2);
   system("pause");
   return 0;
}
