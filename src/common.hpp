#pragma once 

namespace exchange {

enum { ASK = 0 , BID = 1 }  ;                          // Request :: mPosition
enum { LIMIT_ORDER = 1 , MARKET_ORDER, CANCEL_ORDER }; // Request :: mOrderType 
enum { PROCESSING = 1, FINISH , CANCEL };              // Request :: mProcess 
enum { GOLDILOCKS  } ;

typedef unsigned long uint64; 

const int MAX_FLOATING_LENGTH = 31;
const int MAX_COIN_NAME_LENGTH = 50;


enum { SUCCESS , ERROR , NOT_SUPPORTED_DATABASE};  

// Input Parameter interface 
typedef struct { 
  char     mCoin[MAX_COIN_NAME_LENGTH] ; 
  int      mPosition;   
  uint64   mPrice;     
  char     mQty[MAX_FLOATING_LENGTH];     
  int      mOrderType;  
  uint64   mOrderNo ;  
} Request; 


typedef struct { 
  char     mCoin[MAX_COIN_NAME_LENGTH] ;  // coin
  uint64   mTicketNo ; 
  int      mPosition;   // Position   : filled by caller 
  uint64   mPrice;      // Price      : filled by caller 
  char     mQty[MAX_FLOATING_LENGTH];        // Quantity   : filled by caller 
  int      mOrderType;  // Order Type : filled by caller 
  uint64   mOrderNo ;   // Order No   : filled by caller. must be unique.
  char     mAvailQty[MAX_FLOATING_LENGTH];   // Available Quantity 
  int      mProcess;    // Process    
} DBRequest; 


typedef struct { 
  uint64  mFillNo; 
  uint64  mPrice ; 
  char    mQty[MAX_FLOATING_LENGTH] ;  
  uint64  mAskNo ; 
  uint64  mBidNo ; 
} DBFill ; 


typedef struct 
{
  int     mBidQueue ; 
  char    mBidQty[MAX_FLOATING_LENGTH]; 
  uint64  mPrice    ; 
  char    mAskQty[MAX_FLOATING_LENGTH]; 
  int     mAskQueue ; 
} Offer ;


}


