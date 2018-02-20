#include <Exchange.hpp>
#include <BaseExchange.hpp>
#include <common.hpp>


#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include <sstream>
#include <sys/time.h>
#include <algorithm>

#define MAX_FILE_NAME_LEN 255
#define MAX_STRING_LEN 255 




typedef struct {
  char mFileName [ MAX_FILE_NAME_LEN ] ;
  char mUser     [ MAX_STRING_LEN ] ;
  char mPassword [ MAX_STRING_LEN ] ; 
  char mDSN      [ MAX_STRING_LEN ] ; 
  int  mPrintResult ;
} Params ;


void printHelp ( char** argv) 
{ 
  printf ("$ %s -f [file_name] -u [user_name] -p [password] -d [dsn] [-r]\n", argv[0] );
}

int ParseCommand ( int argc, char** argv , Params& aParams ) 
{ 

  int  sOpt ; 
  int  sCheck = 0 ;

  while (( sOpt = getopt ( argc, argv, "f:u:p:d:r"))  != -1  ){ 
    switch (sOpt )  { 
      case 'f' : 
        assert (strlen (optarg ) < MAX_FILE_NAME_LEN ) ;
        strcpy (aParams.mFileName, optarg  ) ;
        sCheck ++ ;
      break; 
      case 'u' : 
        assert (strlen (optarg ) < MAX_STRING_LEN ) ;
        strcpy (aParams.mUser, optarg  ) ;
        sCheck ++ ;
      break; 
      case 'p' : 
        assert (strlen (optarg ) < MAX_STRING_LEN ) ;
        strcpy (aParams.mPassword, optarg  ) ;
        sCheck ++ ;
      break; 
      case 'd' : 
        assert (strlen (optarg ) < MAX_STRING_LEN ) ;
        strcpy (aParams.mDSN, optarg  ) ;
        sCheck ++ ;
      break; 
      case 'r' : 
        aParams.mPrintResult = 1 ; 
      break;

    } 
  }

  if ( sCheck != 4 ) { 
    printHelp (argv ) ;
    exit (-1 ) ;
  } 

  return 0; 
} 


void PrintResult ( std::vector<long>& aTimeVector ) { 
  std::sort ( aTimeVector.begin(), aTimeVector.end());

  long sum = std::accumulate(aTimeVector.begin(), aTimeVector.end(), 0);
  long mean = sum / aTimeVector.size();

  int p99 = aTimeVector.size() - (aTimeVector.size() / 100) + 1; 
  int p999 = aTimeVector.size() - (aTimeVector.size() / 1000) + 1; 
  
  printf ("Min latency: [%ld] Max latency: [%ld] Avg Latency : [%ld] 99 percent latency : [%ld] 99.9 percent latency : [%ld]  ", aTimeVector[0] , aTimeVector[aTimeVector.size() - 1], mean, aTimeVector[p99] , aTimeVector[p999]  );
  double tps = (double)(aTimeVector.size())  / ( (double)sum / 1000000 ) ;
  printf ("TPS : %lf\n", tps ) ;
}


void PrintOffer ( exchange::OfferVector& aVector ) 
{
  for ( auto it = aVector.begin () ; it != aVector.end() ; 
        it ++ ) 
  {
    printf("[%10d] [%20s] [%10ld]  [%20s] [%10d]\n", 
           it->mBidQueue, it->mBidQty, it->mPrice, 
           it->mAskQty, it->mAskQueue ) ;
  }

  aVector.clear();

}


void PrintRequest (int aIdx,  const exchange::Request& aRequest ) 
{
  printf("Request [%10d] -> mPosition[%d] mPrice [%ld] mQty[%s] mType[%d]\n", aIdx, 
         aRequest.mPosition, aRequest.mPrice, aRequest.mQty, aRequest.mOrderType  );
}

int main (int argc, char **argv ) 
{ 
  Params sParams;
  memset ( &sParams, 0x00, sizeof ( Params )) ;
  std::string sLine ;
  ParseCommand ( argc, argv, sParams ) ;
  int sRC = 0;
  struct timeval sStart, sEnd; 
  std::vector <long>     sTimeVector;
  long              sDiff;
  
  int i = 0;


  exchange::Request sRequest;
  exchange::uint64  sReturn;
  exchange::OfferVector sOfferVector; 

  exchange::IExchange *sExchange = new exchange::BaseExchange (8, exchange::GOLDILOCKS)  ;
  sExchange->OpenDatabase ( sParams.mUser, sParams.mPassword, sParams.mDSN ) ;


  std::ifstream sFile ( sParams.mFileName ) ;

  while ( std::getline ( sFile, sLine ) ) 
  {
    ++i ;
    std::vector <std::string> sVector; 

    std::istringstream iss(sLine);

    for ( std::string s; iss >> s ; ) {
      sVector.push_back ( s ) ; 
    } 

    strncpy ( sRequest.mCoin, sVector[0].c_str(), exchange::MAX_COIN_NAME_LENGTH ) ;
    sRequest.mPosition = std::stoi ( sVector [1] ) ;
    sRequest.mPrice = stoi ( sVector[2] ) ;
    strncpy ( sRequest.mQty, sVector[3].c_str(), exchange::MAX_FLOATING_LENGTH ) ;
    sRequest.mOrderType = stoi ( sVector[4] )  ;
    sRequest.mOrderNo = stoi ( sVector[5] ) ;

    
    gettimeofday ( &sStart, NULL ) ; 


    try { 
      sExchange -> FillRequest ( sRequest, sReturn ) ;
      PrintRequest ( i, sRequest ) ;
      sExchange->GetOfferStatus ( sOfferVector ) ;
      PrintOffer ( sOfferVector ) ;
    } catch ( std::exception& e ) 
    {
    //  printf("%s\n", e.what()) ;
    }

    gettimeofday ( &sEnd, NULL ) ; 

    sDiff = (1000000 * ( sEnd.tv_sec - sStart.tv_sec )) + 
            (sEnd.tv_usec - sStart.tv_usec ) ;

    sTimeVector.push_back( sDiff ) ;
  } 

  PrintResult ( sTimeVector );
  sRC=sRC;


  return 0; 
}


