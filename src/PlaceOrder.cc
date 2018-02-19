#include <iostream>
#include <Exchange.hpp>
#include <BaseExchange.hpp>
#include <common.hpp>
#include <cstring>



#define ARGUMENT_LENGTH 100

int main (int argc, char** argv) 
{
  char sCoin[ARGUMENT_LENGTH] ;
  char sPosition[ARGUMENT_LENGTH] ;
  char sPrice   [ARGUMENT_LENGTH] ;
  char sQty     [ARGUMENT_LENGTH] ;
  char sType    [ARGUMENT_LENGTH] ;
  char sOrder   [ARGUMENT_LENGTH] ;

  exchange::Request sRequest ;
  exchange::uint64  sReturn;
  exchange::IExchange *sExchange = new exchange::BaseExchange (8, exchange::GOLDILOCKS  )  ;
  sExchange->OpenDatabase ( "test" , "test", "DSN=GOLDILOCKS" ) ;

  if ( argc != 7 ) 
  {
    printf("$ %s [CoinName] [Position] [Price] [Qty] [Type] [Original Order]\n", argv[0] ) ;
    printf("ex) $ %s 1 1000 1.23123 1  1 \n", argv[0] ) ;
    exit ( -1 ) ;
  }


  strncpy (sCoin,     argv[1], ARGUMENT_LENGTH ) ;
  strncpy (sPosition, argv[2], ARGUMENT_LENGTH ) ;
  strncpy (sPrice,    argv[3], ARGUMENT_LENGTH ) ;
  strncpy (sQty,      argv[4], ARGUMENT_LENGTH ) ;
  strncpy (sType,     argv[5], ARGUMENT_LENGTH ) ;
  strncpy (sOrder,    argv[6], ARGUMENT_LENGTH ) ;


  strncpy ( sRequest.mCoin , sCoin, ARGUMENT_LENGTH ) ;
  sRequest.mPosition = atoi ( sPosition ) ;
  sRequest.mPrice = atoi ( sPrice ) ;
  strncpy ( sRequest.mQty, sQty, ARGUMENT_LENGTH ) ;
  sRequest.mOrderType = atoi ( sType )  ;
  sRequest.mOrderNo = atoi ( sOrder ) ;


  try { 
    sExchange->FillRequest ( sRequest, sReturn ) ;
  } 
  catch (std::exception& e ) 
  {
    printf("%s\n", e.what());
    sExchange->CloseDatabase();
    delete sExchange;
    exit(-1) ;
  }
  printf("Request Position[%d] Price [%ld] Qty [%s] Type[%d] Order [%ld] \n" , 
         sRequest.mPosition, 
         sRequest.mPrice, 
         sRequest.mQty, 
         sRequest.mOrderType, 
         sRequest.mOrderNo  ) ;

  sExchange->CloseDatabase();
  delete sExchange;
} 
