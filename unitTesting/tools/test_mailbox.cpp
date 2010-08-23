/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * Copyright Projet JRL 2007
 *+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * File:      test_flags.cc
 * Project:   sot
 * Author:    Nicolas Mansard
 *
 * Version control
 * ===============
 *
 *  $Id$
 *
 * Description
 * ============
 *
 *
 * ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//#undef WITH_OPENHRP

#include <iostream>
#include <sot-core/debug.h>

#include <MatrixAbstractLayer/boost.h>

#ifndef WIN32
#include <unistd.h>
#endif

using namespace std;
namespace ml = maal::boost;

#include <dynamic-graph/factory.h>
#include <dynamic-graph/entity.h>
#include <sot-core/feature-abstract.h>
#include <dynamic-graph/plugin-loader.h>
#include <dynamic-graph/interpreter.h>
#include <sot-core/mailbox-vector.h>
#include <sstream>

using namespace dynamicgraph;
using namespace sot;

#ifdef  HAVE_LIBBOOST_THREAD
#include <boost/thread.hpp>

sot::MailboxVector mailbox("mail");

void f( void ) 
{ 
  ml::Vector vect(25);
  ml::Vector vect2(25);
  for( int i=0;;++i )
    {
	  std::cout << " iter  " << i << std::endl;
      for( int j=0;j<25;++j ) vect(j) = j+i*10;
      mailbox.post( vect );
      maal::boost::Vector V = mailbox.getObject( vect2, 1 );
	  std::cout << vect2 << std::endl;
	  std::cout << " getClassName   " << mailbox.getClassName() << std::endl;
	  std::cout << " getName        " << mailbox.getName() << std::endl;
	  std::cout << " hasBeenUpdated " << mailbox.hasBeenUpdated() << std::endl;
	  std::cout << std::endl;
    }
}


int main( int argc,char** argv )
{
  boost::thread th( f );

#ifdef WIN32
  Sleep( 100 );
#else
  usleep( 1000*100 );
#endif

  return 0;
}
#else
	int main()
	{
		cout << "This test cannot be run without LIBBOOST_THREAD" << endl;
		return 0;
	}
#endif