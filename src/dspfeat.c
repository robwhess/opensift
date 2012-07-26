/*
  Displays image features from a file on an image

  Copyright (C) 2006-2010  Rob Hess <hess@eecs.oregonstate.edu>

  @version 1.1.2-20100521
*/

#include "imgfeatures.h"
#include "utils.h"

#include <cxcore.h>
#include <highgui.h>

#include <unistd.h>

#define OPTIONS ":oh"

/*************************** Function Prototypes *****************************/

static void usage( char* );
static void arg_parse( int, char** );

/******************************** Globals ************************************/

char* pname;
char* feat_file;
char* img_file;
int feat_type = FEATURE_LOWE;


/********************************** Main *************************************/


int main( int argc, char** argv )
{
  IplImage* img;
  struct feature* feat;
  char* name;
  int n;

  arg_parse( argc, argv );

  img = cvLoadImage( img_file, 1 );
  if( ! img )
    fatal_error( "unable to load image from %s", img_file );
  n = import_features( feat_file, feat_type, &feat );
  if( n == -1 )
    fatal_error( "unable to import features from %s", feat_file );
  name = feat_file;

  draw_features( img, feat, n );
  cvNamedWindow( name, 1 );
  cvShowImage( name, img );
  cvWaitKey( 0 );
  return 0;
}


/************************** Function Definitions *****************************/

/*
  Print usage info for this program.

  @param name program name
*/
static void usage( char* name )
{
  fprintf( stderr, "%s: display image features on an image\n\n", name );
  fprintf( stderr, "Usage: %s [options] <feat_file> <img_file>\n", name );
  fprintf( stderr, "Options:\n" );
  fprintf( stderr, "  -h      Display this message and exit\n" );
  fprintf( stderr, "  -o      Specifies that <feat_file> is an"	\
	   " Oxford-type feature file.  By\n");
  fprintf( stderr, "             default, it is treated as a"	\
	   " Lowe-type file.\n" );
}



/*
  arg_parse() parses the command line arguments, setting appropriate globals.
  
  argc and argv should be passed directly from the command line
*/
static void arg_parse( int argc, char** argv )
{
  pname = basename( argv[0] );
  int arg;
  while( 1 )
    {
      arg = getopt( argc, argv, OPTIONS );
      if( arg == -1 ) 
	break;

      switch( arg )
	{
	case ':':
	  fatal_error( "-%c option requires an argument\n"		\
		       "Try '%s -h' for help.", optopt, pname );
	  break;
	  
	case 'h':
	  usage( pname );
	  exit(0);
	  break;

	case 'o':
	  feat_type = FEATURE_OXFD;
	  break;
	}
    }
  if( argc - optind != 2 )
    fatal_error( "bad argument count.\nTry '%s -h' for help.", pname );
  feat_file = argv[optind++];
  img_file = argv[optind];
}
