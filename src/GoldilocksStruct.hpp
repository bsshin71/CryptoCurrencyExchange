
EXEC SQL BEGIN DECLARE SECTION ; 

typedef unsigned int uint64 ;


const int MAX_FLOATING_LENGTH = 31;
const int MAX_COIN_NAME_LENGTH = 50; 

typedef struct { 
  char     mCoin[MAX_COIN_NAME_LENGTH];
  uint64   mTicketNo;  // Request No 
  int      mPosition;   // Position   : filled by caller 
  uint64   mPrice;      // Price      : filled by caller 
  char     mQty[MAX_FLOATING_LENGTH]; // Quantity   : filled by caller 
  char     mAvailQty[MAX_FLOATING_LENGTH];   // Available Quantity 
  int      mProcess;    // Process    
  int      mOrderType;  // Order Type : filled by caller 
  uint64   mOrderNo ;   // Order No   : filled by caller. must be unique.
} DBRequest; 

typedef struct { 
  uint64  mPrice ; 
  char    mQty[MAX_FLOATING_LENGTH];  
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
} Offer;



EXEC SQL END DECLARE SECTION ; 


